#include "stats_lib.h"
#include <math.h>

/****| maximum | *****************************************
* Brief: This function finds the maximum value from the
* array
* param:
* nums arary, integer n
* return:
* computed maximum
*************************************************************/
float maximum(float nums[], int n) {
    float value = nums[0];

    for (int i = 0; i < n; i++) {
        if (nums[i] > value) {
            value = nums[i];
        }
    }

    return (value);
}

/****| minimum | *****************************************
* Brief: This function finds the minimum value from the
* array
* param:
* nums arary, integer n
* return:
* computed minimum
*************************************************************/
float minimum(float nums[], int n) {
    float value = nums[0];

    for (int i = 0; i < n; i ++) {
        if (nums[i] < value) {
            value = nums[i];
        }
    }

    return (value);
}

/****| mean | *****************************************
* Brief: This function finds the mean value from the
* array input
* param:
* nums arary, integer n
* return:
* computed mean
*************************************************************/
float mean(float nums[], int n) {
    float sum = 0.0;

    for (int i = 0; i < n; i++) {
        sum += nums[i];
    }
    return (sum/n);
}

/****| median | *****************************************
* Brief: This function finds the maximum value from the
* array by sorting from least to greatest then finding the
* middle
* param:
* nums arary, integer n
* return:
* sorted median
*************************************************************/
float median(float nums[], int n) {
    int i, j, currnum = 0;
    float currmed = 0;

    for(i = 0; i < n; i++) {// nested for loops will sift through the array and sort the values from least to greatest

            for(j = i+1; j < n; j++) {
                if(nums[j] > nums[j+1]) {
                    currnum = nums[i];
                    nums[i] = nums[j];
                    nums[j] = currnum;
            }
        }
    }

      if(n%2 == 0){ //the function will then find the median based after it finds whether or not there are an even or odd number of values in the data input
          currmed = (nums[(n-1)/2] + nums[n/2])/2.0;
      }
      else{
          currmed = nums[n/2];
      }


return (currmed);
}

/****| variance | *****************************************
* Brief: This function finds the variance value from the
* array
* param:
* nums arary, integer n
* return:
* calculated variance
*************************************************************/
float variance (float nums[], int n) {
    int i;
    float avg = mean(nums, n), sum = 0.0, val;


        for(i = 0; i < n; i++){ //this for loop will do the calculations that are shown in the summation equation shown on the lab prompt
         sum += ((nums[i] - avg)*(nums[i] - avg));
         }
        val = ((sum)/(n-1)); // the sum is the divided by the total number of values minus 1

  return val;
}

/****| standard_deviation | *****************************************
* Brief: This function finds the standard deviation from the
* array
* param:
* nums arary, integer n
* return:
* computed standard deviation
*************************************************************/
float standard_deviation(float nums[], int n) {
    float var = variance(nums, n);

    var = sqrt(var);

    return (var);
}
