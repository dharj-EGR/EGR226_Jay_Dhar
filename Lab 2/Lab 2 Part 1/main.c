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

/*In the main function, only 3 variables will be needed, most of the work will be
done in the custom function. A loop is used to ask the user whether or not they
would like to try another 3-band resistor. The main function will also be taking
the integer input that will be sent to the custom function for computation.*/
int main()
{
    int userInput, dummy, repeat = 1;//dummy is used here for error checking. we want to make sure the input is a number, not anything else

    while (repeat == 1){//program will loop as long as the user would like it to
    prompt();
    dummy  = scanf("%d", &userInput); //if the user input is incorrect, the if statement will trigger
    if (dummy != 1) { //dummy will not be 1 whenever user input is something besides an integer
        printf("Invalid Input, restart program and try again\n");
        exit (-1);
    }
    calcResistorColors(userInput);

    printf("\n\nTry a different resistor? 1 = yes; anything else = quit\n");
    scanf("%d", &repeat);
    }
    exit (-1);//when the user no longer would like to loop the program, it will exit


    return 0;
}
/*The prompt function will display a table of resistor codes.
The user will make a selection and type out a complete code based on these colors*/
void prompt() {
    printf("---------------Resistor Codes---------------\n");
    printf("|Character| Color | Band 1 & 2 |   Band 3   |\n");
    printf("|    K    | Black |      0     |*1          |\n");
    printf("|    N    | Brown |      1     |*10         |\n");
    printf("|    R    |  Red  |      2     |*100        |\n");
    printf("|    O    | Orange|      3     |*1,000      |\n");
    printf("|    Y    | Yellow|      4     |*10,000     |\n");
    printf("|    G    | Green |      5     |*100,000    |\n");
    printf("|    B    | Blue  |      6     |*1,000,000  |\n");
    printf("|    V    | Violet|      7     |*10,000,000 |\n");
    printf("|    E    | Grey  |      8     |            |\n");
    printf("|    W    | White |      9     |            |\n");
    printf("|    D    | Gold  |            |            |\n");
    printf("|    S    | Silver|            |            |\n");
    printf("---------------------------------------------\n\n");

    printf("What resistance should be color-coded?\n"); //asks the user for input
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
