#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
// DO NOT INCLUDE OTHER LIBRARIES

#define BOARD_SIZE 9

void print_board(){
	printf(" -");
	for(int i=0; i<BOARD_SIZE; i++) printf("---");
	printf("-\n");
	
	for(int i=0; i<BOARD_SIZE; i++){
	    printf("%d|", i+1);
		for(int j=0; j<BOARD_SIZE; j++){
            // TODO: Modify this part such that it prints the chess board
		    printf(" . ");
    	}
    	printf("|\n");
	}
	printf(" -");
	for(int i=0; i<BOARD_SIZE; i++) printf("---");
	printf("-\n");
	
	printf(" ");
	for(int i=0; i<BOARD_SIZE; i++){
	    printf("  %c", 'A'+i);
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
    printf("CAPITAL letter's turn\n");
    // printf("small letter's turn\n");
    print_board();

    printf("Which piece you want to move?\n");
    printf("Where do you want to move to?\n");
    
	printf("CAPITAL letter team wins!\n");
	// printf("small letter team wins!\n");
    print_board();
    return 0;
}