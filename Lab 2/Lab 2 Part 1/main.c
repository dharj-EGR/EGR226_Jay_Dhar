/**************************************************************************************
 * Author:      Jay Dhar
 * Course:      EGR 226 - 905
 * Date:        01/28/2021
 * Project:     Lab 1
 * File:        Lab1pt1.c
 * Description: This program will take color code input of 3-band resistors and print their true colors
 * **************************************************************************************/
#include <stdio.h>
#include <stdlib.h>

void prompt(void);
void calcResistorColors(int userInput);
void getColorBands(char* band1, char* band2, char* band3, char* band4);
void calcResistance(char r1, char r2, char r3, char r4);

/*In the main function, only 3 variables will be needed, most of the work will be
done in the custom function. A loop is used to ask the user whether or not they
would like to try another 3-band resistor. The main function will also be taking
the integer input that will be sent to the custom function for computation.*/
int main()
{
    int userInput, dummy, repeat = 1, functionChoice;//dummy is used here for error checking. we want to make sure the input is a number, not anything else
    char band1, band2, band3, band4;

    while (repeat == 1){//program will loop as long as the user would like it to
    prompt();
    scanf("%d", &functionChoice);

    if (functionChoice == 1) {
        getColorBands(&band1, &band2, &band3, &band4);
        calcResistance(band1, band2, band3, band4);
    }

    dummy  = scanf("%d", &userInput); //if the user input is incorrect, the if statement will trigger
    if (dummy != 1 || userInput < 0 || userInput > 990000000) { //dummy will not be 1 whenever user input is something besides an integer
        printf("Invalid Input, restart program and try again\n");
        exit (-1);
    }


    calcResistorColors(userInput);

    printf("\n\nTry again? 1 = yes; anything else = quit\n");
    scanf("%d", &repeat);
    }
    exit (-1);//when the user no longer would like to loop the program, it will exit


    return 0;
}
/*The prompt function will display a table of resistor codes.
The user will make a selection and type out a complete code based on these colors*/
void prompt() {
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

    printf("Would you like to find resistance based color code, or find color code based on resistance?\nPress 1 for resistance, 2 for color code\n"); //asks the user for input
}

void getColorBands(char* band1, char* band2, char* band3, char* band4){
    printf("Enter band 1: \n");
    scanf(" %c", band1);

    printf("Enter band 2: \n");
    scanf(" %c", band2);

    printf("Enter band 3: \n");
    scanf(" %c", band3);

    printf("Enter band 4: \n");
    scanf(" %c", band4);
}

void calcResistance(char r1, char r2, char r3, char r4){
    float res;

    printf("The resistor is ");

    switch(r1) {
    case 'k':
        printf("");

    case 'n':
        printf("1");
        res = 1.0 * 10.0;

    case 'r':
        printf("2");
        res = 2.0 * 10.0;

    case 'o':
        printf("3");
        res = 3.0 * 10.0;

    case 'y':
        printf("4");
        res = 4.0 * 10.0;

    case 'g':
        printf("5");
        res = 5.0 * 10.0;

    case 'b':
        printf("6");
        res = 6.0 * 10.0;

    case 'v':
        printf("7");
        res = 7.0 *10.0;

    case 'e':
        printf("8");
        res = 8.0 * 10.0;

    case 'w':
        printf("9");
        res = 9.0 * 10.0;

    case 'd':
        printf("");

    case 's':
        printf("");
    }

    switch (r2) {

    case 'k':
        printf("0");

    case 'n':
        printf("1");
        res += 1.0;

    case 'r':
        printf("2");
        res += 2.0;

    case 'o':
        printf("3");
        res += 3.0;

    case 'y':
        printf("4");
        res += 4.0;

    case 'g':
        printf("5");
        res += 5.0;

    case 'b':
        printf("6");
        res += 6.0;

    case 'v':
        printf("7");
        res += 7.0;

    case 'e':
        printf("8");
        res += 8.0;

    case 'w':
        printf("9");
        res += 9.0;

    case 'd':
        printf("");

    case 's':
        printf("");
    }

    switch(r3) {
    case 'k':
        printf("");

    case 'n':
        printf("0");
        res *= 10.0;

    case 'r':
        printf("00");
        res *= 100.0;

    case 'o':
        printf("000");
        res *= 1000.0;

    case 'y':
        printf("0000");
        res *= 10000.0;

    case 'g':
        printf("00000");
        res *= 100000.0;

    case 'b':
        printf("000000");
        res *= 1000000.0;

    case 'v':
        printf("0000000");
        res *= 10000000.0;

    case 'e':
        printf("00000000");
        res *= 100000000.0;

    case 'w':
        printf("000000000");
        res *= 1000000000.0;

    case 'd':
        res *= 0.1;
        printf("%f", res);

    case 's':
        res *= 0.01;
        printf("%f", res);
    }

    printf(" Ohms with a ");

    switch (r4) {
    case 'k':
        printf("+/- 1%");

    case 'n':
        printf("+/- 2%");

    case 'r':
        printf("");

    case 'o':
        printf("");

    case 'y':
        printf("");

    case 'g':
        printf("+/- 0.5%");

    case 'b':
        printf("+/- 0.25");

    case 'v':
        printf("+/- 0.1");

    case 'e':
        printf("+/- 0.05");

    case 'w':
        printf("");

    case 'd':
        printf("+/- 5%");

    case 's':
        printf("+/- 10%");
    }

    printf("tolerance.\n");
}

/*In the calcResistorColors function, the computations of determining colors are done.
The process of getting from a number to actual colors is quite simple but the coding is a bit
repetitive. The function will work backwards by first dividing the userInput by 10 until it is less
than 100. This will count the zeros, the program will then count the tens and ones place to find
the band 2 and band 2.*/
void calcResistorColors(int userInput) {
    int i, band1, band2, band3;

    for (i = 0; userInput >= 100; i++) { //for loop will count the trailing zeros that make up the third band
        userInput /= 10;
    }
    band3 = i;

    band1 = userInput / 10; //the first and second bands are then found when the trailing zeros have been rid of
    band2 = userInput % 10;


    //the if/else if statements below will print the final colors of the 3 band color code of the resistor
    if (band1 == 0){
        printf("Black-");
    }
    else if (band1 == 1) {
        printf("Brown-");
    }
    else if (band1 == 2) {
        printf("Red-");
    }
    else if (band1 == 3) {
        printf("Orange-");
    }
    else if (band1 == 4) {
        printf("Yellow-");
    }
    else if (band1 == 5) {
        printf("Green-");
    }
    else if (band1 == 6) {
        printf("Blue-");
    }
    else if (band1 == 7) {
        printf("Violet-");
    }
    else if (band1 == 8) {
        printf("Grey-");
    }
    else if (band1 == 9) {
        printf("White-");
    }


    if (band2 == 0){
        printf("Black-");
    }
    else if (band2 == 1) {
        printf("Brown-");
    }
    else if (band2 == 2) {
        printf("Red-");
    }
    else if (band2 == 3) {
        printf("Orange-");
    }
    else if (band2 == 4) {
        printf("Yellow-");
    }
    else if (band2 == 5) {
        printf("Green-");
    }
    else if (band2 == 6) {
        printf("Blue-");
    }
    else if (band2 == 7) {
        printf("Violet-");
    }
    else if (band2 == 8) {
        printf("Grey-");
    }
    else if (band2 == 9) {
        printf("White-");
    }


    if (band3 == 0){
        printf("Black");
    }
    else if (band3 == 1) {
        printf("Brown");
    }
    else if (band3 == 2) {
        printf("Red");
    }
    else if (band3 == 3) {
        printf("Orange");
    }
    else if (band3 == 4) {
        printf("Yellow");
    }
    else if (band3 == 5) {
        printf("Green");
    }
    else if (band3 == 6) {
        printf("Blue");
    }
    else if (band3 == 7) {
        printf("Violet");
    }


}
