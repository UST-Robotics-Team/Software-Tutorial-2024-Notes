[Back to Main](../README.md)

# Introduce Yourself

> Hello!

It is recommended to understand everything about input and output before attempting this homework

Create a program such that when the user inputs their study year and their GPA, it will output a formatted version of it. Please print GPA in 3 decimal points (refer to the guide of `printf` to do this)

Note that you should make this program interactive. You need to first ask "What year are you in?\n" and wait until the user responds. Each lines printed are ended with `\n` except the last one.

```c
#include <stdio.h>

int main(){
  int year; float gpa;
  printf("What year are you in?\n");
  //your code starts here

  //your code ends here
  return 0;
}
```

## Example Input:

```
1
4.12
```

Output (Without the input):
```
What year are you in?
What is your GPA?
Hello, I am a year 1 student with 4.120 GPA
```

Output (With the input, seen in your terminal if you respond interactively):
```
What year are you in?
1
What is your GPA?
4.12
Hello, I am a year 1 student with 4.120 GPA
```

## How to Run Your Code

To run the code, you need to make sure that you are first in the right folder/directory in your terminal (the text area under your code):
Currently, in the example, the user is in the directory `/workspaces/codespaces-blank` you need to get to `/workspaces/codespaces-blank/<homework-repository-name>/hw2` to run your `main.c` code, do this by writing the command `cd <homework-repository-name>/hw2` (cd: change directory) and press enter.

(Note: if you want to go up a folder you can use `cd ..`)

![image](./../images/462ba8f7-a31a-4797-86fc-250e2d353d8e.png)

Note that you need to do this everytime you open the Github Codespace.

Once you are in the direcctory, run the following command in the terminal:
```
gcc -o homework.exe main.c && ./homework.exe
```
(Note: for a C code to run, we need to make it an executable file, then run it)

![image](./../images/368292205-462ba8f7-a31a-4797-86fc-250e2d353d8e.png)

## Submission

Modify `main.c` file inside the `hw2` folder containing the code that does the above. Refer to the [Main README.md](../README.md) for details.
