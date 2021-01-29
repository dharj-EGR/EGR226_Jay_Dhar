/**************************************************************************************
 * Author:      Jay Dhar
 * Course:      EGR 226 - 905
 * Date:        01/28/2021
 * Project:     Lab 1
 * File:        Lab1pt2.c
 * Description: This program will read numbers from a text file and perform a statistical
 * analysis of the values within the file
 * **************************************************************************************/
#include "stats_lib.h"
#include <stdio.h>
#include <stdlib.h>
#define upperlim 1000 //utilizing a macro for a limit to array size in case of error

/*The main function will read the values from the data file and also find the amount of values in the file.
The main function will then send these values to 7 different custom functions to do the stats calculations*/

int main()
{
    int i, count = 0;
    float input[upperlim], min, max, avg, med, var, stdev;

    FILE *fp;

    fp = fopen("data.txt", "r"); //opening text file in read mode

    if(fp == NULL) //searching through file
       {
           printf("Could not open file");
           return 1; // program halt
       }

       while(fscanf(fp,"%f", &input[count]) != EOF) //while loop will look for how many entries are in the file and also read into an array
       {
           count++;
       }

        for (i = 0; i<count; i++) {
        printf("The value is: %f\n", input[i]); //displays read values to user
       }

        min = minimum(input, count); //takes input and count and sends to minimum function
        printf("Minimum Value: %g\n", min);

        max = maximum(input, count); //takes input and counts and sends to maximum function
        printf("Maximum Value: %g\n", max);

        avg = mean(input, count); //takes input and count and sends to mean function
        printf("Mean: %g\n", avg);

        med = median(input, count); //takes input and count and sends to medain function
        printf("Median: %g\n", med);

        stdev = standard_deviation(input, count); //takes input and count and sends to stdev function
        printf("Standard Deviation: %g\n", stdev);

        var = variance(input, count); //takes input and count and sends to variance function
        printf("Variance: %g\n", var);

    return 0;
}
