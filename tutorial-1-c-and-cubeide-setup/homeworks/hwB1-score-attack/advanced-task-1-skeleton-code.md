# Advanced Task 1 Skeleton Code

> Please don't include any extra libraries in your homework. We already included
> all necessary libraries in the skeleton code.

```c
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

const char* const msg_prompt_show_steps = "Show intermediate steps? (y or n):\n";
const char* const msg_prompt_input = "Please enter a string:\n";
const char* const msg_max_scores = "Maximum Score:\n";

int main(){
    printf("%s", msg_prompt_show_steps);
    char show_steps_input;
    scanf("%c", &show_steps_input);
  
    printf("%s", msg_prompt_input);
    // get input from the command line interface

    // output the result
    printf("%s", msg_max_scores);
  
    return 0;
}
```
