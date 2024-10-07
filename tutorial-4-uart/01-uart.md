# UART
[Back to Main](README.md)

> How your robot send and receive data from sensors and controller

<details>

<summary>Authors</summary>

Danny Lau, Chalex, Samuel Chee, Vivian Chan, Dicaprio Cheung

</details>

## Introduction

Imagine you want to transfer 8-bit data to another board, one way is to connect 8 wires to another board:

![](https://cdn.sparkfun.com/r/700-700/assets/c/a/c/3/a/50e1cca6ce395fbc27000000.png)

However, this is terrible. What if we want to transfer 32-bit data? We would need a lot of wires.

This calls for communication protocols, which aims to allow devices to communicate with each other using as few wires as possible.

![](https://cdn.sparkfun.com/r/700-700/assets/e/5/4/2/a/50e1ccf1ce395f962b000000.png)

## Universal Asynchronous Receiver-Transmitter (UART)

UART is a protocol used for serial communication and is used when the rate of transmission is not a concern. For example, UART could be used to send control commands but it isn't suitable to send high resolution images.

In our embedded system, UART is commonly used between two different boards or when trying to send data from an mobile/desktop application to your board using bluetooth.

### Sending and Receiving Data with UART

UART sends your data in serial, **asynchronous** mode.

![](https://www.circuitbasics.com/wp-content/uploads/2016/01/Introduction-to-UART-Basic-Connection-Diagram-768x376.png)

Serial communication is the process of sending data one bit at a time. For example, if we want to transmit data from UART1 to UART2, data will be sent bit by bit from the **TX pins** and received by the **RX pins**.

Asynchronous means that there is no common clock signal between the sender and receivers. In other words, the clocks of the STM32 and the bluetooth device may be different. As there is no way for the receiving side to determine the transmission speed dynamically, we need to predefine the same **baud rate** on both sides for the communication.

### Configuring UART Ports

![](https://i.imgur.com/F6AvURr.png)

To check which serial ports can be used as UART, you need to take a look on the main board, there should be small text `UART X` (Should be UART 1 and 3).

**1. Word Length, Parity and Start/Stop Bits**

During transformation, data is sent in **a packet**. According to the standard of uart, it sends 1 start bit (must), 5/6/7/8 bits of data (not 9), 1 bit of parity check (optional),1/1.5/2 bit of stop bit.

![](https://www.circuitbasics.com/wp-content/uploads/2016/01/Introduction-to-UART-Packet-Frame-and-Bits-2.png)

You do not need to modify these parameters for now, just use the default values and make sure the config on both sides of communication is the same. _The two extra bit of start bit and stop bit are **handled automatically** by stm32 and coolterm(later discussed) and you don't have to worry about them._

**2. Baud rate**

Baud rate is the number of bits of the signal sent per second and have predefined standards.

**Possible baud rate values**: 9600, 14400, 19200, 38400, 57600, **115200**, 128000, 230400, 256000, 460800 ...

`115200` is the most common and quickest speed that works on most devices without any problem, therefore, recommended in this tutorial. For example, standard windows (or, .net) utilities does not support anything above 115200. Our setting uses 1 start bit, 8 data bits, 0 parity bit and 1 stop bit, which means that 8 bit = 1 byte out of 10 bits sent are data, with a baud rate of 115200, effectively 11520 bytes of data could be sent in one second.

> **Note** Make sure the baud rates on both sides of the communication are the **same**.

### Initialization of UART Pins

Like most board/pin controls you have learnt so far, a UART port needs to be initialised before it is available for use. The init functions should already be called in main.c based on your board configuration.

**From main.c:**

```c
MX_USART1_UART_Init();
MX_USART3_UART_Init();
```

### Transmitting and Receiving Data

After the initialization, you can start sending and receiving data by calling functions from the HAL Library.

#### Transmit function

```c
HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
```

`HAL_UART_Transmit()` transmits the given data within the time limit.

`huart`: UART handler. HAL Library needs to know what UART port should be used for data transfer. \&huart1 and \&huart3 are the possible values.

`pData`: Data array. Here it means the sequence of data that you want to transmit.

`Size`: The length of data array.

`Timeout`: Time limit for transmitting data. If huart is busy for some reasons (for example, sending other data), the program will stay for at most Timeout millisecond to wait until the sending operation is completed. if the program reaches time limit, it will give up to transmit data.

**TX Example:**

```c
while (1)
{
    /* Sending */
	static const char dat[] = "Hello, Word!";
	HAL_UART_Transmit(&huart1, (uint8_t*)&dat, sizeof(dat), 0xFFFF);
	HAL_Delay(200);
}
```

#### Receive function

```c
HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
```

`HAL_UART_Receive()` receives the given data within the time limit.

`huart`: UART handler. HAL Library needs to know what UART port should be used for data receive. \&huart1 and \&huart3 are the possible values.

`pData`: Data array. Here it means the array that you want to store received data in.

`Size`: The length of data array.

`Timeout`: Time limit for receiving data. If huart is busy for some reasons (for example, not receiving any data), the program will stay for at most Timeout millisecond to wait until the receiving operation is completed. if the program reaches time limit, it will give up to receive data.

**RX Example:**

```c
while (1)
{
    /* Receiving */
	static char dat[99];
	HAL_UART_Receive(&huart1, (uint8_t*)&dat, sizeof(dat), 0xFFFF);
}
```

#### Blocking vs Non-Blocking:**

When calling HAL\_UART\_Transmit() / HAL\_UART\_Receive(), your code will pause at the function call until data is successfully transmitted / received.

In some situations this is problematic, for example:

```c
uint8_t rx_buff[99];
uint8_t tx_buff[99];

int main(void)
{
    uint16_t timeout = 0xFFFF; // Long timeout.

    while (1)
    {
        //Code will stop here if nothing is received
        HAL_UART_Receive(&huart1, rx_buff, sizeof(rx_buff), timeout);
        
        //Unable to transmit while waiting for data to be received
        HAL_UART_Transmit(&huart1, tx_buff, sizeof(tx_buff), timeout);
    }
}

```


#### Transmit function (Non-blocking)

```c
HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
```

`HAL_UART_Transmit_IT()` transmits the given data in the background using Interrupt mode.

`huart`: UART handler. HAL Library needs to know what UART port should be used for data transfer. \&huart1 and \&huart3 are the possible values.

`pData`: Data array. Here it means the sequence of data that you want to transmit.

`Size`: The length of data array.

When it finish transmitting the data, the UART transmit interrupt will be triggered.
tehn the `HAL_UART_TxCpltCallback` function is called, which allows you to perform any necessary post-transmission actions.

`HAL_UART_TxCpltCallback()` (HAL library UART Transmit Complete Callback) This will be called whenever it finishes transmitting something on UART(no matter which UART port). You don't need to call this function in your code, but you need to define it.

`huart`: UART handler. HAL Library will tell you which UART port finished data transfer. \&huart1 and \&huart3 are the possible values.

**TX Example:**

```c
const char data[] = "Hello, Word!";

// you need to write this function yourself, it won't auto-generate
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) 
{
    // Check if there is more data to be transmitted
    if (moreDataToTransmit)
    {
        // Transmit the next data buffer
        HAL_UART_Transmit_IT(huart, nextDataBuffer, nextDataSize);
        /* actually this is some kind of recursion. It calls itself after it finishes */
    }
    else
    {
        // Notify other parts of the application that the transmission is complete
        transmissionCompleteFlag = 1;
    }
}

int main(void)
{
    // Initialize the UART peripheral
    // ...

    // Start transmiting data
    HAL_UART_Transmit_IT(&huart1, data, 1);

    // Main loop
    while (1)
    {
        // Do other tasks
    }
}
```

#### Receive function (Non-blocking)

```c
HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
```

`HAL_UART_Receive_IT()` receives the given data in the background using Interrupt mode.

`huart`: UART handler. HAL Library needs to know what UART port should be used for data transfer. \&huart1 and \&huart3 are the possible values.

`pData`: Data array. Here it means the sequence of data that you want to transmit.

`Size`: The length of data array you want to receive.

When it finish receving the whole length of data, the UART receive interrupt will be triggered.
then the `HAL_UART_RxCpltCallback` function is called, which allows you to perform any necessary post-receive actions.

`HAL_UART_RxCpltCallback()` (HAL library UART Receive Complete Callback) This will be called whenever it finishes receiving the required length of data on UART(no matter which UART port). You don't need to call this function in your code, but you need to define it.

`huart`: UART handler. HAL Library will tell you which UART port finished data transfer. \&huart1 and \&huart3 are the possible values.

**RX Example:**

```c
uint8_t rxBuffer[1]; //idk why but it has a high chance to fail when it is >1
UART_HandleTypeDef huart1;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart1)
    {
        // Process the received data
        if(rxBuffer[0] == 'a'){
          //do something
        }else if(rxBuffer[0] == 'b'){
          //do some other thing
        }else{
          ...
        }

        // Start receiving the next data
        HAL_UART_Receive_IT(&huart1, rxBuffer, sizeof(rxBuffer));
        /* actually this is some kind of recursion. It calls itself after it finishes */
    }
}

int main(void)
{
    // Initialize the UART peripheral
    // ...

    // Start receiving data
    HAL_UART_Receive_IT(&huart1, rxBuffer, 1);

    // Main loop
    while (1)
    {
        // Do other tasks
    }
}
```

[Continue to The Next Page](./02-bluetooth.md)
