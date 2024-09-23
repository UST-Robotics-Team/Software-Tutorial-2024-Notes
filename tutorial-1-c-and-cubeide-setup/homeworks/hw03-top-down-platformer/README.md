[Back to Main](../../README.md)

# Task 3: Terminal Top-Down Platformer

> I originally planned to give the trainees Tetris as homework... Nevermind, this is double the fun anyway >.<

<details>
Tan Joshua (jtanav@connect.ust.hk)
<summary>Author</summary>
</details>

<br/>

![Walls and Floors](https://images.unsplash.com/photo-1613645695025-20e3f38de4a6?q=80&w=2070&auto=format&fit=crop&ixlib=rb-4.0.3&ixid=M3wxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8fA%3D%3D)

In this task, I would like you to make a 2D top-down platformer that you can play on your terminal. You will be given an integer $M$ and $N$ separated by a space and ended with a new line that will determine you game map size. Your map will have $M$ rows and $N$ columns.

It will then be followed by $M \times N$ characters in $M$ rows of $N$ characters that you should read and put into an array of `char`. (I even provided you with a reader function... provided that you can use it...)

There will be 6 groups of `char` that you need to consider.

- Empty spaces `.`
- Walls `#`
- Player `P`
- Cliffsides `=`
- Conveyer Belts `>`, `^`, `<`, `v`, and `x`
- Treasure Chest `T`

After that, you will be given some commands that `w`, `a`, `s`, and `d` that denotes all 4 movement directions. After each command, you need to print the state of the game map. All of these characters are separated by a newline cahracter.

It is guaranteed that:

$0 < M \leq 100$

$0 < N \leq 100$

There will always be one unique `P` and `T` in the $M \times N$ characters given

Player always starts on an empty space.

Cliffsides `=` will never be on top of a location you cannot move to (walls or locations that are out of bound) nor another cliffisde. It is possible, however to land on a conveyor belt track or a treasure chest.

Unless the conveyer belts will create a loop which you need to terminate (explanation below), all conveyor belts will lead to a stopper `x` block. Hence, you will not need to consider the case of your player crashing to a wall or getting out of the map. Moreover, conveyor belts will not lead you to slide down cliffsides nor go through the treasure chest.

One of the possible input can be as such:

```
6 15
###############
#T..x........<#
###=========#.#
#P.v..........#
#==>.........^#
#..........####
w
a
s
d
```

## Player, Empty Space, and Walls

Let's first consider the first three `char` groups:

The player `P` can be moved upward in the map by the command `w`, moved leftward in the map by the command `a`, moved downward in the map by the command `s`, and moved rightward in the map by the command `d`.

However, the player can only move to a location if it is an empty space. If the player attempts to run into a wall `#` or get out of bound, keep the player where they are.

For example, consider the map:

```
...P#..T
....#...
....#...
........
```

Inputting `a` will move player to the left, the game state will be:

```
..P.#..T
....#...
....#...
........
```

Inputting `s` will move the player down, the game state will be:
```
....#..T
...P#...
....#...
........
```

If you input `w` instead of `a`, keep the player where they are, as they will go out of bound.

If you input `d` instead of `a`, keep the player where they are, as they will run into a wall.

## Cliffsides

Cliffsides are blocks that works like walls in general, except if you are on top of it. In that case, you will pass through it instead. (It works like a one way path)

For example, consider the map:

```
.......T
...===..
..=P....
...===..
........
```

Inputting `s` will make the player go down through the cliffside (as if they slide down it):

```
.......T
...===..
..=.....
...===..
...P....
```

However, inputting `w` will keep the player where they are because they are not on top of a cliffside.

Inputting `a` will also have a similar effect.

Please read the remarks about some guaranteed restrictions about cliffside above.

## Conveyer Belts: `<`, `^`, `>`, `v`, and `x`

If the player is on top of any the first four characters: `<`, `^`, `>`, and `v` it will move to the direction it points to until:

- The player is on top of another `<`, `^`, `>`, and `v`. In this case they will change direction.

- The player is on top of `x`. In this case they will stop. Do nothing if they already stopped.

Just to be clear:
`<` points to the left, `>` points to the right, `^` points to the top, and `v` points to the bottom.

Consider the case of inputting `w` when given the following game state:
```
...........
.v..<...x..
...........
.>......^..
....^.....<
....P......
```

The trail is marked by `~`
```
...........
.v~~<...P..
.~..~...~..
.>~~~~~~^..
....^......
...........
```
You first go to the top, then left, then down, then right, then up.

However, the testcase may contain some conveyer belt loops, for example:

```
5 7
......x
.v...<.
...T...
P>...^.
.......
d
```
In this case, if the player steps into a conveyer belt loop as seen above, detect it using some way (left to you to think about) and display a crash message (please refer to `utility.c`) and terminate the program.

If there exists such loop but the player does not use it, keep the program going as it should normally.

Please run `return 0` in `main.c` to quit the program.

Please read the remarks about some guaranteed restrictions about conveyor belts above.

## Treasure Chest: `T`
If you the player is on the location of a `T` character. Print a congratulation message (please refer to `utility.c`) and stop the program.

## Sample Testcase
These testcases should be able to mention how you should handle some strange testcases. If you have doubt about something, please consult the above guaranteed restrictions. If you are still confused about something, please feel free to contact me via discord or email.

Note that the endline after the user input nor the user input is displayed (unless otherwise stated)

**Ends normally**

Input:
```
6 15
###############
#T..x........<#
###=========#.#
#P.v..........#
#==>.........^#
#..........####
w
a
d
a
d
s
s
s
w
d
w
s
a
a
s
a
a
a
```

Output:
<details>
<summary>Reveal (it's quite long)</summary>

```
Welcome to Terminal Treasure Hunter!
Please input your map:
Current game condition:
###############
#T..x........<#
###=========#.#
#P.v..........#
#==>.........^#
#..........####
Where would you like to move to? Current game condition:
###############
#T..x........<#
###=========#.#
#P.v..........#
#==>.........^#
#..........####
Where would you like to move to? Current game condition:
###############
#T..x........<#
###=========#.#
#P.v..........#
#==>.........^#
#..........####
Where would you like to move to? Current game condition:
###############
#T..x........<#
###=========#.#
#.Pv..........#
#==>.........^#
#..........####
Where would you like to move to? Current game condition:
###############
#T..x........<#
###=========#.#
#P.v..........#
#==>.........^#
#..........####
Where would you like to move to? Current game condition:
###############
#T..x........<#
###=========#.#
#.Pv..........#
#==>.........^#
#..........####
Where would you like to move to? Current game condition:
###############
#T..x........<#
###=========#.#
#..v..........#
#==>.........^#
#.P........####
Where would you like to move to? Current game condition:
###############
#T..x........<#
###=========#.#
#..v..........#
#==>.........^#
#.P........####
Where would you like to move to? Current game condition:
###############
#T..x........<#
###=========#.#
#..v..........#
#==>.........^#
#.P........####
Where would you like to move to? Current game condition:
###############
#T..x........<#
###=========#.#
#..v..........#
#==>.........^#
#.P........####
Where would you like to move to? Current game condition:
###############
#T..x........<#
###=========#.#
#..v..........#
#==>.........^#
#..P.......####
Where would you like to move to? Current game condition:
###############
#T..P........<#
###=========#.#
#..v..........#
#==>.........^#
#..........####
Where would you like to move to? Current game condition:
###############
#T..x........<#
###=========#.#
#..vP.........#
#==>.........^#
#..........####
Where would you like to move to? Current game condition:
###############
#T..P........<#
###=========#.#
#..v..........#
#==>.........^#
#..........####
Where would you like to move to? Current game condition:
###############
#T.Px........<#
###=========#.#
#..v..........#
#==>.........^#
#..........####
Where would you like to move to? Current game condition:
###############
#T..P........<#
###=========#.#
#..v..........#
#==>.........^#
#..........####
Where would you like to move to? Current game condition:
###############
#T.Px........<#
###=========#.#
#..v..........#
#==>.........^#
#..........####
Where would you like to move to? Current game condition:
###############
#TP.x........<#
###=========#.#
#..v..........#
#==>.........^#
#..........####
Where would you like to move to? Current game condition:
###############
#P..x........<#
###=========#.#
#..v..........#
#==>.........^#
#..........####
You found the treasure!!!
I can buy a new laptop will all these money >.<
```
</details>
<br/>

Output with the input:
<details>

```
Welcome to Terminal Treasure Hunter!
Please input your map:
6 15
###############
#T..x........<#
###=========#.#
#P.v..........#
#==>.........^#
#..........####
Current game condition:
###############
#T..x........<#
###=========#.#
#P.v..........#
#==>.........^#
#..........####
Where would you like to move to? w
Current game condition:
###############
#T..x........<#
###=========#.#
#P.v..........#
#==>.........^#
#..........####
Where would you like to move to? a
Current game condition:
###############
#T..x........<#
###=========#.#
#P.v..........#
#==>.........^#
#..........####
Where would you like to move to? d
Current game condition:
###############
#T..x........<#
###=========#.#
#.Pv..........#
#==>.........^#
#..........####
Where would you like to move to? a
Current game condition:
###############
#T..x........<#
###=========#.#
#P.v..........#
#==>.........^#
#..........####
Where would you like to move to? d
Current game condition:
###############
#T..x........<#
###=========#.#
#.Pv..........#
#==>.........^#
#..........####
Where would you like to move to? s
Current game condition:
###############
#T..x........<#
###=========#.#
#..v..........#
#==>.........^#
#.P........####
Where would you like to move to? s
Current game condition:
###############
#T..x........<#
###=========#.#
#..v..........#
#==>.........^#
#.P........####
Where would you like to move to? s
Current game condition:
###############
#T..x........<#
###=========#.#
#..v..........#
#==>.........^#
#.P........####
Where would you like to move to? w
Current game condition:
###############
#T..x........<#
###=========#.#
#..v..........#
#==>.........^#
#.P........####
Where would you like to move to? d
Current game condition:
###############
#T..x........<#
###=========#.#
#..v..........#
#==>.........^#
#..P.......####
Where would you like to move to? w
Current game condition:
###############
#T..P........<#
###=========#.#
#..v..........#
#==>.........^#
#..........####
Where would you like to move to? s
Current game condition:
###############
#T..x........<#
###=========#.#
#..vP.........#
#==>.........^#
#..........####
Where would you like to move to? a
Current game condition:
###############
#T..P........<#
###=========#.#
#..v..........#
#==>.........^#
#..........####
Where would you like to move to? a
Current game condition:
###############
#T.Px........<#
###=========#.#
#..v..........#
#==>.........^#
#..........####
Where would you like to move to? s
Current game condition:
###############
#T..P........<#
###=========#.#
#..v..........#
#==>.........^#
#..........####
Where would you like to move to? a
Current game condition:
###############
#T.Px........<#
###=========#.#
#..v..........#
#==>.........^#
#..........####
Where would you like to move to? a
Current game condition:
###############
#TP.x........<#
###=========#.#
#..v..........#
#==>.........^#
#..........####
Where would you like to move to? a
Current game condition:
###############
#P..x........<#
###=========#.#
#..v..........#
#==>.........^#
#..........####
You found the treasure!!!
I can buy a new laptop will all these money >.<
```
<summary>Reveal (also long)</summary>
</details>
<br/>

**Ends via conveyor belt loop termination**

Input:
```
5 5
.....
.v.<.
..T..
.>.^.
.P...
w
```

Output:
```
Welcome to Terminal Treasure Hunter!
Please input your map:
Current game condition:
.....
.v.<.
..T..
.>.^.
.P...
Where would you like to move to? AaaaAaAAAAaa that's a conveyer loop!
Your terminal ran into a problem and needs to terminate the previous program. Error code: 0xdeadbeef
Well, we can get the treasure next time I guess T^T
```

## Testing

Please refer to the testcases [here](testcases.zip). It should handle more edge cases. However, feel free to confirm in the discord server if you have more doubts.

## Submission

You are not allowed to write extra `printf` and `scanf`, but you may use the functions given in `utility.c` for input output >.<

There are also more helper functions provided in `utility.c`

Edit the `main.c` in the `hw3` folder.

## How to Run Your Code

To run the code, you need to make sure that you are first in the right folder/directory in your terminal (the text area under your code):
Currently, in the example, the user is in the directory `/workspaces/codespaces-blank` you need to get to `/workspaces/codespaces-blank/<homework-repository-name>/hw3` to run your `main.c` code, do this by writing the command `cd <homework-repository-name>/hw3` (cd: change directory) and press enter.

(Note: if you want to go up a folder you can use `cd ..`)

![image](./../../images/462ba8f7-a31a-4797-86fc-250e2d353d8e.png)


Note that you need to do this everytime you open the Github Codespace.

Once you are in the direcctory, run the following command in the terminal:
```
gcc -o homework.exe main.c utility.h utility.c && ./homework.exe
```

To give input, you can write in the terminal directly and press enter when you are finished.

(Note: for a C code to run, we need to make it an executable file, then run it)

![image](./../../images/368292205-462ba8f7-a31a-4797-86fc-250e2d353d8e.png)

## Submission
Modify your `main.c` file. We still use Github Classroom to grade your submissions, the instruction is still similar to the one in Tutorial 0 README.md.
