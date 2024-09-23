[Back to Main](../../README.md)

# Task 2: Letter Chess

> Terminal Chess

<details>

<summary>Author</summary>

Dicaprio Cheung (dhcheungaa@connect.ust.hk)

</details>

## Task&#x20;

Your task is to build a new type of chess called the Letter Chess. The name comes from its chess pieces because they are English Letters. Instead of calling black and white like normal chess, the 2 players are called:&#x20;

* CAPITAL letter
* small letter

### Chessboard

In the beginning, the chessboard looks like this:

<figure><img src="../../../images/image (1).png" alt=""><figcaption><p>Initial game board, with all spaces shown </p></figcaption></figure>

> Note: A8 is inputted by the user

### Chess pieces and movements

The following tables summarize how different chess pieces move: (Yellow = movable tiles)

<table><thead><tr><th>CAPITAL letter team</th><th>small letter team</th></tr></thead><tbody><tr><td><img src="../../../images/O.png" alt="" data-size="original"></td><td><img src="../../../images/small_o.png" alt="" data-size="original"></td></tr><tr><td><img src="../../../images/K.png" alt="" data-size="original"></td><td><img src="../../../images/small_k.png" alt="" data-size="original"></td></tr><tr><td><img src="../../../images/T.png" alt="" data-size="original"></td><td><img src="../../../images/small_t.png" alt="" data-size="original"></td></tr><tr><td><img src="../../../images/H.png" alt="" data-size="original"></td><td><img src="../../../images/small_h.png" alt="" data-size="original"></td></tr><tr><td><img src="../../../images/X.png" alt="" data-size="original"></td><td><img src="../../../images/small_x.png" alt="" data-size="original"></td></tr><tr><td><img src="../../../images/U.png" alt="" data-size="original"></td><td><img src="../../../images/small_u.png" alt="" data-size="original"></td></tr></tbody></table>

> ~~I am using these images to prevent people to use ChatGPT. If these doesn't work, please tell me how you used ChatGPT to read these images and complete this task.~~

The arrows represent how the piece moves along the path. The piece can move infinitely along the arrow until something blocks it. If something is blocking it, it can't go through that piece and reach the other side.

Take `X` as an example:

`X` is just like a normal bishop

<figure><img src="../../../images/image (2).png" alt=""><figcaption><p>[Bishop in a normal chess]</p></figcaption></figure>

If a pawn is blocking the bishop, the bishop can't jump over the pawn and eat the castle. The same logic applies to all other arrows.

### Implementation Details

1. The CAPITAL team always starts first.
2. `K` is the King. If the king is dead, the other team wins.
3. We only accept CAPITAL letters for tile names. e.g. `A8`, `H7`, ...
4. The player can only choose his/her piece that has a valid move. If not, ask the player to choose again like the following:

<figure><img src="../../../images/image (6).png" alt="" width="258"><figcaption><p>Demonstration of user keep choosing the wrong tiles</p></figcaption></figure>

4. After the player successfully chooses which piece to move, that piece and its movable tiles are highlighted as shown below:&#x20;

<figure><img src="../../../images/image (4).png" alt="" width="267"><figcaption><p>Game board of CAPITAL player moving C8 to B7, with all spaces shown</p></figcaption></figure>

5. After each move, if any side wins, print the winner with the given prompt in the skeleton code and print the board one more time. Then, end the program immediately.

<figure><img src="../../../images/letter_chess_win.png" alt="" width="267"><figcaption><p>Game board of CAPITAL playerwinning after killing the small letter k</p></figcaption></figure>

6. You can assume you don't need to handle stalemate.

## Test Cases

[Here](test_cases.zip) are the zip files for some test cases for you to test your code.

* test case 1 tests the implementation of O K X
* test case 2 tests the implementation of O K T H
* test case 3 tests the implementation of O K X U

## FAQ

If any part of this assignment is unclear, please ask our seniors in Discord. The Q\&A will be updated here if your questions are meaningful to all tutees.

## How to Run Your Code

To run the code, you need to make sure that you are first in the right folder/directory in your terminal (the text area under your code):
Currently, in the example, the user is in the directory `/workspaces/codespaces-blank` you need to get to `/workspaces/codespaces-blank/<homework-repository-name>/hw2` to run your `main.c` code, do this by writing the command `cd <homework-repository-name>/hw2` (cd: change directory) and press enter.

(Note: if you want to go up a folder you can use `cd ..`)

![image](./../../images/462ba8f7-a31a-4797-86fc-250e2d353d8e.png)


Note that you need to do this everytime you open the Github Codespace.

Once you are in the direcctory, run the following command in the terminal:
```
gcc -o homework.exe main.c && ./homework.exe 
``` 

![image](./../../images/368292205-462ba8f7-a31a-4797-86fc-250e2d353d8e.png)

## Submission
Modify your `main.c` file. We still use Github Classroom to grade your submissions, the instruction is still similar to the one in Tutorial 0 README.md.
