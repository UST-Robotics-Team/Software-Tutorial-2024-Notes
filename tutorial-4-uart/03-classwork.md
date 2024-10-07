# Classwork
[Back to Main](README.md)

## Classwork #1: Send your name and student from MCU to coolterm.

What you should see in coolterm:\


<figure><img src="https://i.imgur.com/y152z6j.png" alt=""><figcaption></figcaption></figure>

## Classwork #2: Send a string to MCU, then echo it back to coolterm

![](https://i.imgur.com/xAm0BFS.png)

## Classwork #3: Control LEDs by sending commands from computer to MCU through bluetooth.

Strings to send:

* Turn on LEDx: `+x`
* Turn off LEDx: `-x`
  * e.g. to turn on LED1: `+1`; to turn off LED3: `-3`.
* Toggle LEDx: `/x`
  * LED should keep toggling until a `+` or `-` command is sent.

You should parse these commands on the mainboard and perform the appropriate action.

note: in C, you do not directly compare two strings (i.e. `" "==" "` is invalid), instead, you compare each char (i.e. `' '==' '`is valid)
