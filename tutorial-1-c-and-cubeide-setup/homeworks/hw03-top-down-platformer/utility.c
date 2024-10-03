//modification to this file is NOT allowed

/*
    Remarks about the infinite looping issue when given input pipelined from a file

    I just recently found that this issue is related to \r\n being pipelined into the executable on Linux. If you change the \r\n into \n in the test-
    case file, you are fine. However, I just made some changes to this skeleton code such that it can still work under this condition. The old code
    still actually works but may fail if the issue mentioned occurs. Both files should still be fine for the autograder. If any issue occur with the
    old utility.c, I will be responsible to change your utility.c when grading :)
*/

#include "utility.h"
#include <stdio.h>

/*
    read_map(char[100][100], int*, int*)

    Reads the user's input

    Please note that I need to modify the M and N in main.c
    However, as mentioned in the tutorial functions cannot do that
    if you pass M and N normally

    To call this function you need to add an extra "&" in front of
    the variable that will store the value of M and N as in scanf

    e.g.
    read_input(map, &M, &N);

    Changes will be done directly on the objects passed
*/

void read_map(char map[100][100], int* M, int* N){
    char buf[105];
    scanf("%d", M);
    scanf("%d", N);
    for(int i=0; i<*M; i++){
        scanf("%s", buf); //I changed the input method :)
        for(int j=0; j<*N; j++){
            map[i][j] = buf[j];
        }
    }
}

/*
    void print_map(char[100][100], int, int)

    Given a char array as an input, prints the map out
*/
void print_map(char map[100][100], int M, int N){
    printf("Current game condition:\n");
    for(int i=0; i<M; i++){
        for(int j=0; j<N; j++){
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

/*
    char capture_movement()

    Reads the command w, a, s, or d given by the user ans returns it
*/

char capture_movement(){
    char buf[105];
    scanf("%s", buf);
    return buf[0]; //also changed here :)
}

/*
    void prompt_map_input()

    Prompts user to input the map configuration
*/

void prompt_map_input(){
    printf("Welcome to Terminal Treasure Hunter!\n");
    printf("Please input your map:\n");
    return;
}

/*
    void prompt_command_input()

    Prompts command input
*/

void prompt_command_input(){
    printf("Where would you like to move to? ");
    return;
}

/*
    void treasure_found()

    Prints a congratulation message for finding the treasure
*/

void treasure_found(){
    printf("You found the treasure!!!\n");
    printf("I can buy a new laptop will all these money >.<\n");
    return;
}

/*
    void termination_message()

    Prints a termination message due to the infinite conveyer loop
*/

void termination_message(){
    printf("AaaaAaAAAAaa that's a conveyer loop!\n");
    printf("Your terminal ran into a problem and needs to terminate the previous program. Error code: 0xdeadbeef\n");
    printf("Well, we can get the treasure next time I guess T^T\n");
    return;
}
