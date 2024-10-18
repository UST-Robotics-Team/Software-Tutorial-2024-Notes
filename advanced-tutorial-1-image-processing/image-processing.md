# Image Processing

## NOTE: Image Processing in RDC 2024

For the Robot Design Contest 2024, you'll be doing the processing on your own computer and with OpenCV, meaning that you gain access to a lot of algorithms that come with the OpenCV library.

In previous years, participants had to do image processing on the STM32 board, and had no access to OpenCV.
This document was designed for those participants, who were expected to be able to write the algorithms by themselves after reading the document, and you will notice that a lot of the examples here are written in C.

Despite this, I would still recommend taking the time to read through this document, as it covers a lot of the basic concepts about image processing, and explains the theory behind some of the more common image processing techniques (which OpenCV may also provide for you).

## What is an image?

Before we start, it is crucial to understand what an image is.
A representation of an image in computer is actually very similar to a spreadsheet.
In fact, you can view a image with a spreadsheet application.
Take a look at this image made in a spreadsheet for example.

![](https://i.imgur.com/Ic9KcYq.png)

You might be wondering how this is possible. To answer your question, we need to zoom in to take a closer look.

![](https://i.imgur.com/EB3jpNv.png)

We can see that each cell is either red, green or blue.
By using different brightness of the three colors, we can create an illusion that there are a lot of different colors.

To represent an image digitally, we need to store these cells, which are called pixels.
Each pixel consist of the brightness value of the red, green and blue colors.
These values in computers or robots are stored in a **2D array**
(Remember [tutorial 1 classwork 4](https://github.com/UST-Robotics-Team/Software-Tutorial-2024-Notes/blob/main/tutorial-1-c-and-cubeide-setup/classwork/classwork-4-greyscale-image.md)? :D).
You may have direct access to this array or may only be given a **pointer**.
Note that the coordinate system of an image in computing is different from the coordinate system normally used in mathematics.
The origin (0, 0) is on the top-left corner of the image.

Computer vision is one of the major perception systems in the robotics field.
The robot receives image or video data from the camera module and stores it in the RAM.

Here is a camera module.

![camera module](https://upload.wikimedia.org/wikipedia/commons/4/4b/Raspberry\_Pi\_Camera\_Module\_-\_Hand-Held\_\(14672275231\).jpg)

### Before Image Processing

Since the camera image is stored in pixels in a 2D array, it is important to know the concept and implementations of arrays.

Here is a 2D array with width 5 and height 3:

| \[0]\[0] | \[0]\[1] | \[0]\[2] | \[0]\[3] | \[0]\[4] |
| -------- | -------- | -------- | -------- | -------- |
| \[1]\[0] | \[1]\[1] | \[1]\[2] | \[1]\[3] | \[1]\[4] |
| \[2]\[0] | \[2]\[1] | \[2]\[2] | \[2]\[3] | \[2]\[4] |

The following demonstrates the typical way to print and manipulate 2D arrays:

```c
#include <stdio.h>
#define WIDTH 5
#define HEIGHT 3
void print_array(int A[][WIDTH], int height) {
    for(int i = 0; i < height; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}
int main() {
    int myArray[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            myArray[i][j] = WIDTH * i + j;
        }
    }
    print_array(myArray, HEIGHT);
}
```

Output

```
0 1 2 3 4 
5 6 7 8 9 
10 11 12 13 14 
```

### 1. Image Type (Colored, Grayscale or Black&White)

Although a color mode setting may not exist in the emulator's camera, color modes are still worth learning.
It is very important for real-life situations since it will affect the quality of the image you obtain.

#### Colored

![colored](https://user-images.githubusercontent.com/32810188/44947015-2f9d3180-ae39-11e8-854a-a32387a246ef.png)

Please note that the images are rendered instead of taking in reality, so the image shown here may not fully represent the real image that you will be getting.

#### RGB565

If we want to have colored pictures, we also need information about the color.
The color depth defines how many bits are used to represent a color.
The more bits (information), the more colors we can display.
There are different ways to represent a color but virtually all displays use RGB, where a color is represented by its Red, Green, and Blue components.

RGB565 requires only 16 (5+6+5) bits (i.e. 2 bytes) and is commonly used with embedded screens.
Each pixel occupies 2 bytes, the bits are split into 3 groups to represent RGB respectively.
The value stored in each group is just the intensity of that color.

R: Occupies 5 bits, so its value ranges from 00000 to 11111.

G: Occupies 6 bits, so its value ranges from 000000 to 111111.

B: Occupies 5 bits, so its value ranges from 00000 to 11111.

We concatenate the 3 values in the order R, G, B.
So if R=11011, G=110010 and B=11010, then the final RGB565 value is 1101111001011010.

![RGB565](https://www.newton.com.tw/img/7/e01/cGcq5SM0YDM5ADMkJGNxQmZ5QWM0UzMjJjN4AzLtVGdp9yYpB3LltWahJ2Lt92YuUHZpFmYuMmczdWbp9yL6MHc0RHa.jpg)

Note that the Green component has 6 bits, not because it needs higher values but because it needs higher resolution (see [RGB 565 - Why 6 Bits for Green Color](https://stackoverflow.com/questions/25467682/rgb-565-why-6-bits-for-green-color)).

#### Grayscale

![greyscale](https://user-images.githubusercontent.com/32810188/44947020-404da780-ae39-11e8-8c8b-f1113f03550c.png)

A grayscale image is essentially an image that only carries intensity information.
Each pixel is just represented by a number that ranges from 0% (Total absence of light/ black) to 100% (Total presence of light/ white).
Any fraction between is what we call **'gray'**.

Note that if the RGB values in a colored image pixel are equal, there would be no color information.
Therefore, we can also **convert RGB565 images to grayscale images**.

#### Average Method

Firstly, get the individual RGB components through bitwise operations.

```C++
int16_t pixel = *buffer;
int16_t red = ((pixel & 0xF800) >> 11);
int16_t green = ((pixel & 0x07E0) >> 5);
int16_t blue = (pixel & 0x001F);
```

Then, take the average value of the red, green and blue values to generate a grayscale value.

$$
\text{Grayscale} = \frac{red + green + blue}{3}
$$

However, human eyes are more sensitive to green than other colors, averaging the three colors would generate an output that is less close to the original image under human perception.

#### Luminosity Method

Therefore, we combine the red, green and blue values with weights to generate a grayscale value.

A common ratio (weight) is **R: 0.2989, G: 0.5870, B: 0.1140**.

Try it yourself.

#### Pros and Cons of Using Different Image Type

* Colored: (colors are stored as RGB in the MCU)
  * Pros: Contains a lot of details
  * Cons: Hard to control
* Grayscale: (range from 0 \~ 255, where black = 0 and white = 255) **Recommended**
  * Pros: Relatively easier to control, able to use gradient to differentiate features
  * Cons: -
* Black\&White: (represented by 1 and 0, which black = 1 and white = 0)
  * Pros: Easiest to control
  * Cons: Hard to adjust thresholding for the image, has minimal information

These pros and cons are just a means to guide you.
However, these rules aren't set in stone.
It is general that for image processing, we would usually choose grayscale or black&white images to analyze as they provide adequate information in order to handle the dynamics of the car.
The use of colored images may provide more information but it is up to you to determine if the extra information available is of any substantial benefit.

#### Black-and-White

![mediumintense](https://user-images.githubusercontent.com/32810188/44949432-b961f480-ae63-11e8-8896-d919740a78bd.png)

A black-and-white image is an image that just contains either black (0) or white (1) in any pixels.

Setting a simple threshold for the grayscale image can generate a black-and-white image.

### 2. Brightness & Intensity

Apart from color choices, the brightness and the intensity of the image captured also affect the quality of the image you obtain, which in turn affect the ability to extract good data from it.

**Low Intensity**

![lowintense](https://user-images.githubusercontent.com/32810188/44949429-b49d4080-ae63-11e8-902e-17e64f7caf88.png)

**Medium Intensity**

![mediumintense](https://user-images.githubusercontent.com/32810188/44949432-b961f480-ae63-11e8-8896-d919740a78bd.png)

**High Intensity**

![highintense](https://user-images.githubusercontent.com/32810188/44949434-bbc44e80-ae63-11e8-8e68-152058dd8f3a.png)

If you do not find the proper intensity, your image might contain noise that would deter you from processing the information accurately.
It is important that your program is able to adjust the brightness and intensity based on different lighting conditions as it is against the rules to flash your program during the competition.

Here is a guideline if you want to write code to adjust the brightness and intensity of the image:

[https://pippin.gimp.org/image-processing/chap\_point.html](https://pippin.gimp.org/image-processing/chap\_point.html)

## Convolution of image

### Introduction to Kernel

A kernel is a square matrix that specifies spatial weights of various pixels in an image.
Different image processing contexts may use different kernels.

![wrxle](https://user-images.githubusercontent.com/32810188/45767787-afb2fc00-bc6d-11e8-81a5-29ba95f1c94a.png)

### Convolution Process

Convolution of a matrix involves laying a matrix over another and then calculating the weighted sum of all pixel values.
The example below uses a 3x3 kernel for convolution.
If the input image is a mxn array, then the output array would be (m-2)x(n-2).

![](https://user-images.githubusercontent.com/32810188/45766774-f6ebbd80-bc6a-11e8-9aed-c7f57fe57159.JPG)

$$
105 \times (0) + 102 \times (-1) + 100 \times (0) + 103 \times (-1) + \dots = 89
$$

More examples:

![](https://user-images.githubusercontent.com/32810188/45768526-bb9fbd80-bc6f-11e8-9d93-120bb90f9175.gif)

Try it yourself: [https://setosa.io/ev/image-kernels/](https://setosa.io/ev/image-kernels/)

The weighting of each pixel entry is intuitive.
For example a sharpening filter, we want to emphasize the center pixel and increase the color difference of it with the ones surrounding it.
We would create a kernel like this:

| -  | -  | -  |
| -- | -- | -- |
| 0  | -1 | 0  |
| -1 | 5  | -1 |
| 0  | -1 | 0  |

To further intensify the sharpening effect:

| -  | -  | -  |
| -- | -- | -- |
| -1 | -1 | -1 |
| -1 | 9  | -1 |
| -1 | -1 | -1 |

Note that the sum of weighting is 1.

## Application of Convolution - Reducing Noise

Usually the image generated by a camera might contain noise and will have to be **filtered/ smoothened** to prevent it from affecting the image analysis.

There are mainly two types of noise: salt-and-pepper noise and Gaussian noise.

### Salt-and-Pepper Noise - Median Filter

Salt-and-pepper noise is a form of noise sometimes seen on images.
It is also known as impulse noise.
This noise can be caused by sharp and sudden disturbances in the image signal.
It presents itself as sparsely occurring white and black pixels.

![salt-and-pepper noise](https://upload.wikimedia.org/wikipedia/commons/f/f4/Noise_salt_and_pepper.png)

For salt-and-pepper noise, we can use a median filter.

![median filter](https://www.researchgate.net/profile/Vu\_Hoang\_Minh/publication/320547422/figure/fig4/AS:551864018141185@1508586043638/3-3-kernel-in-median-filter.png)

Use of a median filter to improve an image severely corrupted by defective pixels.

![colored](https://i.imgur.com/v9DjmbP.png)

Example Code:

```c++
void medianFilter(const uint8_t *cameraDataPtr, uint8_t *processedDataPtr, uint16_t width, uint16_t height) {
    uint8_t window[9];
    // Loop though entire image array
    // ignored the outer edge of the image to simplify the code
    for (uint16_t x=1; x<width-1; x++) {
        for (uint16_t y=1; y<height-1; y++) {
            // Fill the 3x3 window
            uint8_t k = 0;
            for (int u=x-1; u<=x+1; u++) {
                for (int v=y-1; v<=y+1; v++) {
                    window[k++] = *(cameraDataPtr + width * v + u);
                }
            }
            // Find the median
            for(uint8_t i=0; i<5; i++) {
                for (uint8_t j=i+1; j<9; j++) {
                    if (window[j] < window[i]) {
                        uint8_t temp = window[i];
                        window[i] = window[j];
                        window[j] = temp;
                    }
                }
            }
            // Assign the median to the processed image array
            *(processedDataPtr + width * y + x) = window[4];
        }
    }
}
```

What if the image is too noisy and much information is missing?

![noisy_image](https://i.imgur.com/PUOn0wM.png)

A larger kernel size can be used, it smooths out the image better.
However, a large kernel means the sharpness of the image is lost.

### Gaussian Noise - Gaussian Filter

Gaussian noise is statistical noise having a probability density function equal to that of the normal distribution, which is also known as the Gaussian distribution.
In other words, the values that the noise can take on are Gaussian-distributed.

![gaussian noise](https://www.researchgate.net/publication/252066070/figure/fig2/AS:361043193810945@1463090813645/Noisy-image-Gaussian-noise-with-mean-and-variance-0005\_Q640.jpg) ![gaussian noise](https://www.sfu.ca/sonic-studio-webdav/handbook/Graphics/Gaussian.gif) ![gaussian noise](https://miro.medium.com/max/3264/1\*nOkI4VIQKM5FaSVBP8TiZw.png)

For Gaussian noise, we can use a Gaussian filter kernel.

![Gaussian filter kernel](https://4.bp.blogspot.com/-v4dH8qhFnEE/WqHaTPel8RI/AAAAAAAAI8g/AxIVu5i7mHU5UDcu6BkJQJj\_UO11sMomwCLcBGAs/s1600/3x3%2BGaussian%2BKernel.png)

## Application for Convolution - Feature Detection

Here are some images that have gone through the convolution.

![colored](https://i.imgur.com/T17jDCz.png)

### Edge Detection - Sobel Filter

The Sobel filter emphasizes edges of an image.

![colored](https://slideplayer.com/slide/14419272/90/images/8/Sobel+operator+In+practice%2C+it+is+common+to+use%3A+Magnitude%3A.jpg)

Before:

![colored](https://upload.wikimedia.org/wikipedia/commons/thumb/3/3f/Bikesgray.jpg/300px-Bikesgray.jpg)

After:

![colored](https://upload.wikimedia.org/wikipedia/commons/thumb/2/24/Bikesgray\_sobel.JPG/300px-Bikesgray\_sobel.JPG)

#### Why it works

Take a look at gx kernel first.

| -  | Gx | - |
| -- | -- | - |
| -1 | 0  | 1 |
| -2 | 0  | 2 |
| -1 | 0  | 1 |

If this kernel is place onto an area with no edge.
It means that all the pixels in the area is about the same.
Let's assume all the pixel have a value of **C**.
The new value for the center pixel will be (-1**C** + 1**C** - 2**C** + 2**C** -1**C** + 1**C** = 0).
The pixel will be black if all the pixels in the area are similar.
The only place that the result pixel will be white is when the left and right side of pixels are very different (an edge).

The same can also be apply to gy.
Finally, we can use the Pythagorean theorem to get the overall value.

Convolutions can be extended to further detect other vital features of a track.
Another key term to keep in mind is **Gradient**.

![colored](https://i.imgur.com/AbQLWej.png)

**Points to remember:**

1. Real life situations largely vary from digital replicated simulations.
Application of algorithms should thus be geared to tackle the blemishes you would face.
2. Analyze features and algorithms from a mathematical and physical perspective.
3. Keep the program robust in order to tackle the worst cases possible.
4. Keep in mind the run time of your program during feature extraction.

### Further Pondering

* Applying convolution to the whole image is a processor-intensive task and might produce a large amount of unnecessary information. 
How can we only extract the information needed?
* Or even better, only _produce_ the information needed? (This will be crucial in our application.)
