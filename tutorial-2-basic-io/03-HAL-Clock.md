[Back to Main](README.md) | [Previous Page](02-GPIO.md)

# HAL Clock

While knowledge of GPIO allows for immediate input response in a robot, it is not sufficient on its own. In embedded systems, time management is crucial for tasks such as scheduling, generating PWM signals, and managing delays. The STM32 microcontroller utilizes the Hardware Abstraction Layer (HAL) to handle clock functions efficiently. This section will focus on the system clock and setting up timers for various tasks.

> **Hardware Abstraction Layer (HAL)**: A software layer that provides an interface for hardware components, allowing developers to write code without needing to understand the underlying hardware details.

The system clock in STM32 is a critical component that drives the operation of the microcontroller. It provides the timing needed for executing instructions and managing peripheral operations. The HAL library offers convenient functions to interact with the system clock.

```c
uint32_t HAL_GetTick(void);
uint32_t ticks = HAL_GetTick();
// Return how many ms have pass though since the MCU start running
```

- In STM32, the MCU has introduced an application time base that increments every 1 ms. Using `HAL_GetTick()` returns the time base (in ms) since the mainboard was powered on.
- You can think of the MCU as holding a stopwatch that starts when the MCU begins running, and `HAL_GetTick()` is ask the stopwatch what is the counting right now

```c
void HAL_Delay(uint32_t Delay);
```

- This function pauses program execution for a specified number of milliseconds.
- While straightforward, using `HAL_Delay()` can halt all operations, which is often undesirable in real-time applications. Instead, consider using non-blocking techniques to achieve delays.

### Practical Example of a non-block delay with `HAL_GetTick()`

- A LED that toggle every 200ms:

  ```c
  while (1) {
      static uint32_t last_ticks = 0;
      //Static attribute keep the value across every iterations while it will not be re-initized
      //Everything inside this if-statements gets called every 200ms
      if((HAL_GetTick() - last_ticks) >= 200){
          gpio_toggle(LED1);
          last_ticks = HAL_GetTick();
          //Store the tick of last time
      }
  }
  ```

- A LED turn on 100ms after u first time press the `BTN1`:
  ```c
  while (1) {
      static uint32_t last_ticks = 0;
      static uint8_t btn_pressed = 0;
      if (!btn_pressed && btn_read(BTN1)){ //Only when never pressed
          btn_pressed = 1;
          last_ticks = HAL_GetTick();
      }
      if (btn_pressed){
        if ((HAL_GetTick() - last_ticks) <= 100){
            led_on(LED1);
        }
        else {
            led_off(LED1);
        }
      }
  }
  ``` 

### Demo 2: Writing Code in a function 
While you might only need to write tens of code to finish different classwork and homework, in real life you would write thousands line of code , and so it is important for you to write your code in different functions.

In today tutorial, you should put all your code in the four function we give to you in `tutorial2_hw.c`, here I would provide you an example of how it works

1. Write what you want it to do every loop:
   1. During the 1 - 2 second: `LED3` is flashing (toggle every 100 ms)
   2. During the 3 - 4 second: Only turn on `LED4` 
    ```c
    /* tutorial2_hw.c*/
    void gpio_classwork(void) {
    /* Your code start here */
        // You should use static uint32_t here, as any variable that defined in main.c cannot call here unless you extern it
        static uint32_t last_ticks_btn = 0;
        static uint32_t last_ticks_led = 0;
        if (HAL_GetTick() - last_ticks_btn <= 2000){ 
            // Inside the Flashing Cycle
            led_off(LED4);
            if (HAL_GetTick() - last_ticks_led > 100){
                led_toggle(LED3);
                last_ticks_led = HAL_GetTick();
            }
        }
        else if ((HAL_GetTick() - last_ticks_btn > 2000) && (HAL_GetTick() - last_ticks_btn < 4000)) {
            led_off(LED3);
            led_on(LED4);
        }
        else {
            last_ticks_btn = HAL_GetTick();
        }        
    /* Your code end here */
    }
    ```

2. After you have written your program in `tutorial2_hw.c`, you would like to call it in your main loop.
   - Before calling it, you need to have declared this function before the `main` function. 
   - Normally we will do by include a corrsponding `.h` of that `.c`, but as we forogr to give you this.
   - So you can directly put the function prototype (function declaration) in the top of your `main.c`
        ```c
        /* main.c */
        /* USER CODE BEGIN PFP */
        void gpio_classwork(void);
        /* USER CODE END PFP */
        ```
3. After you have done all these, you can directly call the function in your `main.c`:
   ```c 
    /* main.c::int main() */

    /* USER CODE BEGIN WHILE */
    while(1){
        gpio_classwork();
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
   ```
> Some of you may apply another `while` loop in your function for this purpose:
> ```c
>   if (btn_read(BTN2)){
>       static uint32_t last_ticks_BTN = 0;
>       last_ticks_BTN = HAL_GetTick();
>       while (HAL_GetTick - last_ticks_BTN < 1000){
>           //Code for Toggle LED
>       }
>   }
> ```
> While the solution work fine under this single task context, it will create problem in a lot of way, consider this, your robot may have a lot of things to do at the same time, for example, Flashing LED and also control the pnematic valve at the same time. Using this code, you **cannot do anything** when you flashing the LED for 1 second, which is not perferable. \
> This also the reason we tell you guys to never use `HAL_Delay()`


<!-- ## Action that constantly repeat

### Program Structure:

```c
int main(void)
{
    // Initialize Everything Here, this is like setup() in Arduino
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();     //Initialize most GPIOs on board
    MX_DMA_Init();      //Initialize DMA

    while (1) {
        static uint32_t last_ticks = 0;	//Static attribute keeps its stored value through every iteration
        //Everything inside this if-statements gets called every 100ms
        if((HAL_GetTick() - last_ticks) >= 100){
            // do something every 100 ms
            last_ticks = HAL_GetTick();
            //Store the tick of last time
        }

        static uint32_t last_ticks2 = 0;	//This variable keeps its stored value through every iteration
        //Everything inside this if-statements gets called every 60ms
        if((HAL_GetTick() - last_ticks2) >= 60){
            // do another thing every 60 ms
            last_ticks2 = HAL_GetTick();
        }
    }
}
```

- In the example above, we do something every 100 ms and another thing every 60 ms. Since they are only an if-statement, there won't be any while loops/ for loops that prevent the other tasks from doing their tasks.
- This structure is easy and keep your MCU active all the time to do whatever you want it to do. -->

<!-- ### HAL_Delay

Some of you may find that a `HAL_Delay()` function exists, and use it in your code like so:

```c
while(1){
    //do something (task1)
    HAL_Delay(100);
    //do another thing (task2)
    HAL_Delay(60);
}
```

This may not work as expected, and can cause problems. The issue here is that `HAL_Delay()` stops **EVERYTHING**, and your entire board will freeze for x milliseconds before moving on. In the example above, this will cause both tasks to run every 60+100ms. \
Timing actions by freezing the entire board is also not desirable for us 99% of the time, since freezing would mean it would not respond to any control inputs. (imagine if your robot's wheels couldn't move because an LED was freezing the robot)

> TLDR you shouldn’t be using `HAL_Delay()` most of the time

<details><summary>Side note:

`HAL_Delay()` uses `HAL_GetTick()` under the hood

</summary>
     
```c
__weak void HAL_Delay(uint32_t Delay)
{
uint32_t tickstart = HAL_GetTick();
uint32_t wait = Delay;

/_ Add a freq to guarantee minimum wait _/
if (wait < HAL_MAX_DELAY)
{
wait += (uint32_t)(uwTickFreq);
}

while((HAL_GetTick() - tickstart) < wait)
{
}
}

````
 </details> -->

## Classwork 1: GPIO and HAL
To make our code more readable and make things more organized, we have provided separate functions for you to work in.
You should write your code there in the respective functions and call the functions in the `main.c` 

> As we have included the function prototype of the `gpio_classwork()` in the previous demo, you don't need do that for this classwork.

- When `BTN1` is held, `LED1` should be on. **(@1)**
- When `BTN2` is held, `LED1` should be flashing (toggle in 50ms).**(@1)**
- When both `BTN1` and `BTN2` are held, the following sequence is conducted:**(@2)**
  - `LED1` on while `LED2` are flashing (toggle in 50ms), for one second.
  - `LED1` and `LED3` are flashing while `LED2` are on, for one second.
  - Repeat from step 1.
- Keyword: Finite State Machine

[Continue to The Next Page](./04-TFT.md)
