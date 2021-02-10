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

void prompt(void); //prompt the user with a resistor table and ask what kind of function to do
void calcResistorColors(int userInput); //same function as lab 1, takes user input integer and converts into colors
void getColorBands(char* band1, char* band2, char* band3, char* band4); //function to take user input for colors and then convert to number resistance
void calcResistance(char r1, char r2, char r3, char r4); //computes what the chars from the above custom function actually are as a resistance

/*In the main function, only 3 variables will be needed, most of the work will be
done in the custom function. A loop is used to ask the user whether or not they
would like to try another 3-band resistor. The main function will also be taking
the integer input that will be sent to the custom function for computation.*/
int main()
{
    int userInput, dummy = 0, repeat = 1, functionChoice;//dummy is used here for error checking. we want to make sure the input is a number, not anything else
    char band1, band2, band3, band4; //these band chars will be used as pointers for the user input function

    while (repeat == 1){//program will loop as long as the user would like it to
    prompt();
    scanf("%d", &functionChoice); //user will input whether they would like to see colors from a resistor code or vice versa

    if (functionChoice == 1) {
        getColorBands(&band1, &band2, &band3, &band4);//first get user input
        calcResistance(band1, band2, band3, band4); //compute what these colors mean in a resistance value
    }

    else if (functionChoice == 2) {

        printf("Enter color code: ");
    dummy  = scanf(" %d", &userInput); //if the user input is incorrect, the if statement will trigger
    if (dummy != 1 || userInput < 0 || userInput > 990000000) { //dummy will not be 1 whenever user input is something besides an integer
        printf("Invalid Input, restart program and try again\n");
        exit (-1);
    }
    calcResistorColors(userInput);

    }

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

/*This function takes 4 chars as input as pointers. This allows the function to return more than just one function at a time
This function will ask for user input on each band and then will take that input into each band's pointer*/
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
/*This function will take the inputs from the band chars found in the function above and compute the total resistance as well as
error. It will print the numbers as the computations are made.*/
void calcResistance(char r1, char r2, char r3, char r4){
    float res; //this float is used for the program to also know what the current resistance value is

    printf("The resistor is "); //starting off with a print statement to be able to tell the user what the resistance is

    switch(r1) { //switch case used to sort the user inputs from each char and find which character matches. It will print a number based on the corresponding letter
    case 'k':
        printf("");
        break;

    case 'n':
        printf("1");
        res = 1.0 * 10.0;
        break;

    case 'r':
        printf("2");
        res = 2.0 * 10.0;
        break;

    case 'o':
        printf("3");
        res = 3.0 * 10.0;
        break;

    case 'y':
        printf("4");
        res = 4.0 * 10.0;
        break;

    case 'g':
        printf("5");
        res = 5.0 * 10.0;
        break;

    case 'b':
        printf("6");
        res = 6.0 * 10.0;
        break;

    case 'v':
        printf("7");
        res = 7.0 *10.0;
        break;

    case 'e':
        printf("8");
        res = 8.0 * 10.0;
        break;

    case 'w':
        printf("9");
        res = 9.0 * 10.0;
        break;

    case 'd':
        printf("");
        break;

    case 's':
        printf("");
        break;
    }

    switch (r2) {//same as switch r1

    case 'k':
        printf("0");
        break;

    case 'n':
        printf("1");
        res += 1.0;
        break;

    case 'r':
        printf("2");
        res += 2.0;
        break;

    case 'o':
        printf("3");
        res += 3.0;
        break;

    case 'y':
        printf("4");
        res += 4.0;
        break;

    case 'g':
        printf("5");
        res += 5.0;
        break;

    case 'b':
        printf("6");
        res += 6.0;
        break;

    case 'v':
        printf("7");
        res += 7.0;
        break;

    case 'e':
        printf("8");
        res += 8.0;
        break;

    case 'w':
        printf("9");
        res += 9.0;
        break;

    case 'd':
        printf("");
        break;

    case 's':
        printf("");
        break;
    }

    switch(r3) {//same as switch r1 & r2
    case 'k':
        printf("");
        break;

    case 'n':
        printf("0");
        res *= 10.0;
        break;

    case 'r':
        printf("00");
        res *= 100.0;
        break;

    case 'o':
        printf("000");
        res *= 1000.0;
        break;

    case 'y':
        printf("0000");
        res *= 10000.0;

    case 'g':
        printf("00000");
        res *= 100000.0;
        break;

    case 'b':
        printf("000000");
        res *= 1000000.0;

    case 'v':
        printf("0000000");
        res *= 10000000.0;
        break;

    case 'e':
        printf("00000000");
        res *= 100000000.0;
        break;

    case 'w':
        printf("000000000");
        res *= 1000000000.0;
        break;

    case 'd':
        res *= 0.1;
        printf("%f", res);
        break;

    case 's':
        res *= 0.01;
        printf("%f", res);
        break;
    }

    printf(" Ohms with a ");

    switch (r4) {
    case 'k':
        printf("+/- 1% tolerance.\n");
        break;

    case 'n':
        printf("+/- 2% tolerance.\n");
        break;

    case 'r':
        printf("zero tolerance.\n");
        break;

    case 'o':
        printf("zero tolerance.\n");
        break;

    case 'y':
        printf("zero tolerance.\n");
        break;

    case 'g':
        printf("+/- 0.5% tolerance.\n");
        break;

    case 'b':
        printf("+/- 0.25 tolerance.\n");
        break;

    case 'v':
        printf("+/- 0.1 tolerance.\n");
        break;

    case 'e':
        printf("+/- 0.05 tolerance.\n");
        break;

    case 'w':
        printf("zero tolerance.\n");
        break;

    case 'd':
        printf("+/- 5% tolerance.\n");
        break;

    case 's':
        printf("+/- 10% tolerance.\n");
        break;
    }


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
