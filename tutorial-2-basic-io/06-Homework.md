# T2: Homework

> Before you start working on your homework, remember to declare the function prototype first, please refer to the classwork instruction if you dun understand what I mean.

## Q1: GPIO Configuration + Pneumatic Valve
> Actucally It Suppose to be the third classwork but I doubt if I can go thru all the things so I make it as homework to make both u and my life easiler.

After the tutorial on how to set up a GPIO Pin, it is now for you to try out how to connect two Pneumatic Valve to the mainboard and then make a clamp. (We are not going to provide you high pressure air for safety issue.)

## Requirement:
- You should connect the one Pneumatic Valve to the following pins: `PB8`
- When you press one of the button, you should send a signal to the valve(i.e. the led of the valve should on)
- Demo it to any helper
> Ez right? So I say it suppose to be a classwork

--- 
## Q2: Tutorial 2 Homework

Before you start doing homework, You may find these defines in `lcd.h` useful:

```c
#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16

#define MAX_WIDTH 128
#define MAX_HEIGHT 160

#define CHAR_MAX_X_VERTICAL 16
#define CHAR_MAX_Y_VERTICAL 10

#define CHAR_MAX_X_HORIZONTAL 20
#define CHAR_MAX_Y_HORIZONTAL 8

#define CHAR_MAX_X 20  // max between CHAR_MAX_X_VERTICAL and CHAR_MAX_X_HORIZONTAL
#define CHAR_MAX_Y 10  // max between CHAR_MAX_Y_VERTICAL and CHAR_MAX_Y_HORIZONTAL
```

### **Edge Triggering vs Level Triggering**

Consider 2 uses for a single button: (choose BTN1 or BTN2)

#### **Q1 Level Triggering**

* While the button is down, print `Hello, (Your name)` on TFT **(@1)**
* While it is not, flash the LED (at least one LED). **(@1)**
* Two actions should not happen simultaneously.
* Hints:
  * In this case every time the loop comes around, we are concerned with the **current state** (or level) of the buttons GPIO Pin
  * The implementation of the button reading here should be obvious and simple

![](https://i.imgur.com/qSrTmjr.gif)&#x20;

> Notice the green button and the green LED

#### **Q2 Edge Triggering**

* We want to print `Hello, (Your name)` for 1 second when the button is pressed, but only once for each press, so holding the button does nothing more. **(@1)**
* When the button is released, we want to flash the LED for 1 second, but again only once for each release. **(@1)**
* The process repeats. i.e. it will print text again if you click the button. **(@1)**
* Keywords:
  * The event of a signal going from low to high is called the _**rising edge**_ and the opposite is the _**falling edge**_
  * The `gpio_read()` macro gives us the current state, but edge triggering also requires knowledge of the **past state** as well as some logic
* Hints: How can we design some code that can call a function _only_ when the button is first clicked? (Rising edge)

#### **Bonus**

* Create a sprite in the middle of the screen. (Can be in any shape other than simple rectangle) **(@1)**
* It will move to the left for one `CHAR_WIDTH` when `BTN1` is clicked and released,
* move to the right for one `CHAR_WIDTH` when `BTN2` is clicked and released. **(@2 for both short press)**
