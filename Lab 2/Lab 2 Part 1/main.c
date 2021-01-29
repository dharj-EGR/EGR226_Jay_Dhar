#include <stdio.h>
#include <stdlib.h>

void getColorBands(char*, char*, char*, char*);
void calcResistance(char, char, char, char);
void prompt(void);
void calcResistorColors(int userInput);

int main()
{
    int userInput, dummy, repeat = 1;//dummy is used here for error checking. we want to make sure the input is a number, not anything else

    while (repeat == 1){//program will loop as long as the user would like it to
    prompt();
    dummy  = scanf("%d", &userInput); //if the user input is incorrect, the if statement will trigger
    if (dummy != 1 || dummy < 0 || dummy > ) { //dummy will not be 1 whenever user input is something besides an integer
        printf("Invalid Input, restart program and try again\n");
        exit (-1);
    }

    printf("\n\nTry a different resistor? 1 = yes; anything else = quit\n");
    scanf("%d", &repeat);
    }
    exit (-1);//when the user no longer would like to loop the program, it will exit


    return 0;
}


void prompt () {
 printf("--------------------Resistor Codes---------------------\n");
 printf("|Character| Color | Band 1 & 2 | Band 3 | Band 4 |\n");
 printf("| K       | Black | 0          |*1      |+/- 1%% |\n");
 printf("| N       | Brown | 1          |*10     |+/- 2%% |\n");
 printf("| R       | Red   | 2          |*100    |        |\n");
 printf("| O       | Orange| 3          |*1,000  |        |\n");
 printf("| Y       | Yellow| 4          |*10,000 |        |\n");
 printf("| G       | Green | 5          |*100,000|+/- 0.5%%|\n");
 printf("| B       | Blue  | 6          |*1,000,000|+/- 0.25%%|\n");
 printf("| V       | Violet| 7          |*10,000,000|+/- 0.1%%|\n");
 printf("| E       | Grey  | 8          |        |+/- 0.05%%|\n");
 printf("| W       | White | 9          |        |        |\n");
 printf("| D       | Gold  |            |        |+/- 5%% |\n");
 printf("| S       | Silver|            |        |+/- 10%%|\n");
 printf("-------------------------------------------------------\n\n");
}
