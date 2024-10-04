# Homework
[Back to Main](README.md)

In this homework, the setup consists of a development board (which has 2 buttons and 4 LEDs), a servo, and a tiny "paddle" attached to the servo. You need to use PWM to control the servo to achieve the desired functionality described below.

> Note: This homework treat the range of the servo from 0 to 180 degree instead of -90 to 90 degree.

## Details

There are **three types of movements**:

* Single Move
* Double Move (Chargeable)
* Special Move (Bonus) (Designed by you)

When there is nothing to do, the servo stays at the Resting Angle on either side. All movements start at one side's Resting Angle and end at the other side's Resting Angle.

### Single Move

A Single Move needs to move slower than a Double Move.

> It starts at 0deg, moves towards the target and ends at 180deg (of the opposite side).

### Double Move

It consists of 2 stages. First, it starts at 0 deg and pauses at 40 deg (charging for 2 seconds) until the player releases the Double Move button. (If it is at 180 deg, then it will pause at 140 deg).

While performing the Double Move, you should also use LEDs to indicate the charging status as shown:


| State | LED Status       | Duration    |
| ----- | ---------------- | ----------- |
| 1     | \[0]\[0]\[0]\[0] | 0.0\~0.499s |
| 2     | \[1]\[0]\[0]\[0] | 0.5\~0.999s |
| 3     | \[1]\[1]\[0]\[0] | 1\~1.499s   |
| 4     | \[1]\[1]\[1]\[0] | 1.5\~1.999s |
| 5     | \[1]\[1]\[1]\[1] | >=2.0s      |

> Note: **\[0]** = LED off, **\[1]**: LED on.

**Non-fully-charged Double Move** If the player had already released the button while the Double Move was not charged enough, then there wouldn't be any charging or pausing. It will only move for one time. _Notice that the Double Move needs to move faster than the Single Move._

**A fully-charged Double Move** is a Double Move that has been charged for at least 2 seconds. After the button is released. It then moves for 2 times. _Notice that the Double Move needs to move faster than the Single Move._

### Display

* Count and list the number of single, double (list out fully-charged and non-fully-chared), and special moves triggered.


### Button Arrangement (Bonus)

\[Single Move] \[Double Move] \[Special Move]

A move request is made when the corresponding button is pressed. Notice that there are only 2 buttons on the board, so you guys need to think how to use 2 button to do 3 different task.

### Special Move (Bonus)

You can design your own Special Move: **A Special Move** is a custom Move that must be designed by yourself. The only requirements are:

* Use the servo. At least not similar to Single and Double Move.
* Use some LEDs.
* Display a message when the special move is triggered twice.

## Rules to obey

* Single Move can be used at any time.
* Every 2 Single Move can unlock a chance to use Double Move.
* Every 2 Double Move can unlock a chance to use Special Move.
* When 2 Fully-charged Double Move is used consecutively, it will auto-triggered Special Move.

## Marking scheme 

The task is split into 8 (+2 bonus) checkpoints. We grade this homework by checking how many checkpoints you completed.

#### Display

1. Having the number of moves count correctly. (Single Move, Double Move, Fully-charged Double Move, Special Move(Bonus))

#### Single Move

2. Having the servo move **slowly** from one side to another side (0 degree -> 180 degree) based on button clicks 
3. Having the servo move **slowly** from another side to original side (180 degree -> 0 degree) based on button clicks 

#### Double Move

4. Having two stages at Double Move mode. (stops at 40 or 140 degree until button release) 
5. Having the correct LED blinking action when holding the button.
6. Having correct Non-fully-charged Double Move. (0->40->180 and the other way round)
7. Having a correct fully-charged Double Move. (0->40->180->0 and the other way round)
8. Obey the rule of "2 Single Move unlocks a Double Move".

#### Special Move (Bonus)

9. Having the Special Move triggered by buttons. (need to handle both 0 degree and 180 degree)
10. Having the Special Move auto-triggered after 2 consecutive Fully-charged Double Move. (need to handle both 0 degree and 180 degree)

