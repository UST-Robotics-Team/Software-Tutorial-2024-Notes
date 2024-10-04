# Classwork
[Back to Main](README.md)

## Classwork 1

There are many combinations of prescaler value and auto reload register that can generate the same frequency output.

Find 3 possible combinations of prescaler value and auto-reload values for controlling the servo.

> Yes, this is just a MATH question.

> Hint: *** Remember they are `uint16_t` . So, they can only be 0 to 65535***

[Back to notes](02-pwm-and-servo.md#timer)

## Classwork 2

Choose 1 of your combination of prescaler value and auto reload register from classwork 1.

Calculate the CCR value for moving the servo to -90, 0, and 90 degree. (1 ms, 1.5 ms, and 2 ms On-time respectively)

> Yes, this is another MATH question.

[Back to notes](02-pwm-and-servo.md#channel)

## Classwork 3

Try to control servo motor to turn to -90 degrees-> 0 degrees -> 90 degrees (with a short pause at 0 degrees)

> Note: for the servo motor we are using, the on-time at -90 degrees should be 0.5ms, and the on-time at 90 degrees should be 2.5ms. Calculate the on-time for 0 degrees on your own.
>
> Bonus: control the angle of the motor with a button

> Note: We are using TIM5 and channel 1

[Back to notes](02-pwm-and-servo.md#start-coding!!!)