[Back to Main](README.md) | [Previous Page](02-GPIO.md)

# HAL Clock

While knowledge of GPIO allows for immediate input response in a robot, it is not sufficient on its own. In embedded systems, time management is crucial for tasks such as scheduling, generating PWM signals, and managing delays. The STM32 microcontroller utilizes the Hardware Abstraction Layer (HAL) to handle clock functions efficiently. This section will focus on the system clock and setting up timers for various tasks.
>**Hardware Abstraction Layer (HAL)**: A software layer that provides an interface for hardware components, allowing developers to write code without needing to understand the underlying hardware details.

The system clock in STM32 is a critical component that drives the operation of the microcontroller. It provides the timing needed for executing instructions and managing peripheral operations. The HAL library offers convenient functions to interact with the system clock.

```c
uint32_t HAL_GetTick(void);
uint32_t ticks = HAL_GetTick(); 
// Return how many ms have pass though since the MCU start running
```

- In STM32, the MCU has introduced an application time base that increments every 1 ms. Using `HAL_GetTick()` returns the time base (in ms) since the mainboard was powered on.
- You can think of the MCU as holding a stopwatch that starts when the MCU begins running, and `HAL_GetTick()` provides the current reading of this stopwatch.

```c
void HAL_Delay(uint32_t Delay);
```

- This function pauses program execution for a specified number of milliseconds.
- While straightforward, using `HAL_Delay()` can halt all operations, which is often undesirable in real-time applications. Instead, consider using non-blocking techniques to achieve delays.
### Practical Example of a non-block delay with  `HAL_GetTick()`
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

- A LED turn on 100ms after u press the button:
    ```c
    while (1) {
        static uint32_t last_ticks = 0;
        static uint8_t BTN_Pressed = 0;	
        if (!BTN_Pressed && btn_read(BTN1)){ //Only when never pressed
            BTN_Pressed = 1;
            last_ticks = HAL_GetTick();
        }
        if(BTN_Pressed && (HAL_GetTick() - last_ticks) >= 100){
            led_on(LED1);
        }
    }
    ```
## Action that constantly repeat

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
- This structure is easy and keep your MCU active all the time to do whatever you want it to do.

### Why Delay doesn’t work?

You may think you can write it as delay like this:

```c
while(1){
    //do something (task1)
    HAL_Delay(100);
    //do another thing (task2)
    HAL_Delay(60);
}
```

This doesn't work as task1 need to wait for 100+60 ms before it can execute again and task2 also need to wait for 60+100 ms before it can execute again. This is not what we want.

You might say you can carefully design the delay time such that it delays accurately:

T1, T2, delay 60, T2, delay 40, T1, delay 20, T2, delay 60, T2, delay 20, T1, delay 40, T2, delay 60

However, you will have to write many different tasks(>10) for the mainboard to do in many different intervals. it is nearly impossible for you to design a delay pattern for that many tasks accurately. It is also difficult to add, remove, or modify the interval if you write using delay.

> Therefore you shouldn’t use `HAL_Delay()` in basically most of the time

<details><summary>Side Note:  

Actually `HAL_Delay()` are just using `HAL_GetTick()`
</summary>
     
```c
__weak void HAL_Delay(uint32_t Delay)
{
uint32_t tickstart = HAL_GetTick();
uint32_t wait = Delay;

/* Add a freq to guarantee minimum wait */
if (wait < HAL_MAX_DELAY)
{
    wait += (uint32_t)(uwTickFreq);
}

while((HAL_GetTick() - tickstart) < wait)
{
}
}
```
 </details>

## Classwork 1: GPIO and HAL
To hold our code integrity and also enable you guys to further apply this project in the later RDC Phase, we have already set up a separate file `tutorial 2.c`. You should write your code there in the respective function and call the function in the `main.c`
Remember to add the function prototype before you call it.
```c 
/* main.c */
/* USER CODE BEGIN PFP */
void gpio_classwork(void);
/* USER CODE END PFP */
```

* When `BTN1` is held, `LED1` should be on. **(@1)**
* When `BTN2` is held, `LED1` should be flashing (toggle in 50ms).**(@1)**
* When both `BTN1` and `BTN2` are held, the following sequence is conducted:**(@2)**
  * `LED1` on while `LED2` are flashing (toggle in 50ms), for one second.
  * `LED1` and `LED3` are flashing while `LED2` are on, for one second.
  * Repeat from step 1.
* Keyword: Finite State Machine

[Continue to The Next Page](./04-TFT.md)