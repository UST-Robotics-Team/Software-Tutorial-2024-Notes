# OpenCV in Python

<details>

<summary>Authors</summary>

Li Chi Kin, Andy (ckliam)

Ng Ching Yin, Alvin (cyangbh)

</details>

You may realize that to perform a simple image processing task, you need to apply many layers of filters.
It's painful to write every filter line by line.
But what if you could simplify this process?
What if you could perform complex image-processing tasks with just a handful of function calls?
That's where **OpenCV** comes into play.

## What is OpenCV

OpenCV (Open-source Computer Vision) is a free library for real-time image processing and computer vision applications.
This widely used library includes hundreds of optimized algorithms for image processing, feature extraction, and more, making it a crucial tool for many developers and researchers in the field of computer vision.

## Video Guide

For those of you who prefer video guides, here is a very helpful video: [https://www.youtube.com/watch?v=oXlwWbU8l2o](https://www.youtube.com/watch?v=oXlwWbU8l2o)\
The majority of this tutorial is designed based on this video, so feel free to reference either one.
We suggest watching until 1:44:02 to gain a basic understanding of image processing with OpenCV.

## Install OpenCV

This tutorial will teach OpenCV-Python, a branch of OpenCV that uses the Python programming language.
OpenCV is also available for C++, although syntax will be more complicated.

(We assume you have basic knowledge of Python programming.
If you don't, there are many online resources for Python tutorials on Youtube.)

Installing OpenCV-Python is as simple as an one-line-command

```bash
pip install opencv-python
```

## Image Input and Output

```python
import cv2

img = cv2.imread(r"Photos/cat.png")

cv2.imshow("Image", img)

cv2.waitKey(0)
```

We store the image in a variable called `img`.
You can put the image's relative or absolute path in the `cv2.imread` function.

`cv2.imshow` opens a new window called `Image` and then shows `img` in it.

`cv2.waitkey(0)` will display the window infinitely until any key is pressed.

## Video Camera Feed

A video is just a stream of still images (frames).\
Here is how you would load a video or live camera feed:

```python
import cv2

# set the cam feed source to be the default one
capture = cv2.VideoCapture(0)

# infinite loop
while True:
    # capture a frame
    ret, frame = capture.read()

    # show the frame on a window
    cv2.imshow("cam feed", frame)

    # close the window if 'q' is pressed
    key = cv2.waitKey(1) & 0XFF
    if key == ord('q'):
        break

capture.release()
cv2.destroyAllWindows()
```

> [!TIP]
> `key = cv2.waitKey(1) & 0XFF` if you want to know why 0XFF is here, you can read this [thread](https://stackoverflow.com/questions/35372700/whats-0xff-for-in-cv2-waitkey1)

## Basic functions

### Changing color space

Color spaces are an essential concept in image processing and computer vision, and OpenCV provides robust support for a variety of these color spaces.
At its core, a color space is a specific organization of colors, allowing for consistent color representation across various devices and platforms.

However, real-world image processing tasks often require different color spaces, and OpenCV provides functionality to convert between these different color spaces.
Some of the most commonly used color spaces in OpenCV, besides BGR and RGB, include:

- **Grayscale**: This color space represents an image in different shades of gray, where the pixel value typically ranges from 0 (black) to 255 (white).
- **HSV (Hue, Saturation, Value)**: As we've discussed, the HSV color space separates the color information (hue) from the lightness or brightness information (value), which can provide a more intuitive representation of color that aligns better with how humans perceive color.

```python
import cv2

img = cv2.imread(r"your/photo/path")
cv2.imshow("Original", img)

# convert to grayscale
gray_img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
cv2.imshow("Grayscale", gray_img)

hsv_img = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
cv2.imshow("HSV", hsv_img)
cv2.waitKey(0)
```

> [!WARNING]
> Because of some historical issues, OpenCv uses the BGR color format instead of the conventional RGB format.
> All of the following image processing that is related to colors will also be using this format.

### Gaussian Blur

The Gaussian Blur is an image processing technique used in computer vision and image analysis to reduce noise and detail in an image.
It's a type of image-blurring filter that uses a Gaussian function, which is a function that represents the normal distribution (also known as the bell curve) in mathematics.

In OpenCV, the Gaussian Blur filter is implemented with the `cv2.GaussianBlur()` function.
This function convolves the source image with a Gaussian kernel, blurring the image to reduce high-frequency noise and detail.

```python
import cv2

# Load an image
img = cv2.imread("image.jpg")

# Apply Gaussian blur
blurred_img = cv2.GaussianBlur(img, (5, 5), 0)

# Display the original and blurred images
cv2.imshow("Original Image", img)
cv2.imshow("Gaussian Blurred Image", blurred_img)

cv2.waitKey(0)

cv2.destroyAllWindows()
```

`cv2.GaussianBlur` function takes three fundamental arguments:

1. image_source: the image variable
2. kernel_size: `(5, 5)` is the kernel size, which should be a positive and odd number.
The kernel size determines the area over which the Gaussian function is computed and applied to blur the image.
The larger the kernel size, the greater the blur effect.

### Median blur filter

The median blur is another type of image processing filter used to reduce noise in an image, specifically "salt-and-pepper" noise, which appears as sparsely occurring white and black pixels.

The median blur filter works by replacing each pixel's value with the median value of the intensities in its neighborhood.
This method is quite effective at eliminating noise while preserving edges, making it a great choice for certain types of applications.

```python
import cv2

# Load an image
img = cv2.imread("image.jpg")

# Apply median blur
blurred_img = cv2.medianBlur(img, 5)

# Display the original and blurred images
cv2.imshow("Original Image", img)
cv2.imshow("Median Blurred Image", blurred_img)

cv2.waitKey(0)

cv2.destroyAllWindows()
```

In this code, `5` is the size of the kernel, the area over which the median is computed.
The kernel size must be a positive odd number.
The larger the kernel size, the more the image is blurred, but noise is more effectively removed.

### Thresholding

```python
import cv2

# Load an image in grayscale mode
img = cv2.imread("image.png", 0)

# Apply threshold.
# All pixels with a value above 127 will be set to 255, others will be set to 0.
ret, thresh_img = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)

cv2.imshow("Threshold Image", thresh_img)

cv2.waitKey(0)

cv2.destroyAllWindows()
```

In the example above, we first read an image in grayscale mode.
Then, we use the `cv2.threshold()` function to apply a binary threshold.
The threshold value is set at 127, and the maximum value is set at 255.
So, all pixel intensities greater than or equal to 127 are set to 255, and all others are set to 0.
The result is a binary image that clearly distinguishes between the foreground and the background based on the threshold value.

There are other thresholding filters like inverse threshold and adaptive threshold.
If you want to learn more about it, please visit the following website [https://docs.opencv.org/4.x/d7/d4d/tutorial_py_thresholding.html](https://docs.opencv.org/4.x/d7/d4d/tutorial_py_thresholding.html)

### Crop

Images are treated like arrays in OpenCV, you can apply the same 1D array slicing technique to 2D images.

```python
cropped_img = img[start_row:end_row, start_col:end_col]
```

[https://learnopencv.com/cropping-an-image-using-opencv/](https://learnopencv.com/cropping-an-image-using-opencv/)

## Contour Detection

Contour detection is a very useful technique for simple object detection.

Please see this article for the tutorial:
[https://learnopencv.com/contour-detection-using-opencv-python-c/](https://learnopencv.com/contour-detection-using-opencv-python-c/)

## Color Channel

A color image consists of 3 channels

- red
- green
- blue

Normally, they are merged together.
With OpenCV, you can split an image into its respective color channels with one function call.

```python
b, g, r = cv2.split(img)
```

Using cv2.split, you split a color image into Blue, Green, and Red channels.

You'll see three slightly different grayscale images when you use cv2.imshow to show each image's channel.

![bgr_channel](../images/bgr_channel.png)

## Documentation & other resources

[https://docs.opencv.org/4.x/d6/d00/tutorial_py_root.html"]("https://docs.opencv.org/4.x/d6/d00/tutorial_py_root.html")

The documentation has many other functions that maybe helpful to you.
You can read the documentation tutorial to learn more about computer vision beyond image processing.

[https://www.geeksforgeeks.org/opencv-python-tutorial/]("https://www.geeksforgeeks.org/opencv-python-tutorial/")

GeeksforGeeks also provides a comprehensive and easy-to-read tutorial on image processing in OpenCV.
