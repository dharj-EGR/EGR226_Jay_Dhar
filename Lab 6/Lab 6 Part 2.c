/*
 * Author: Jay Dhar
 * Date: 3/5/21
 * Proejct: This program will connect the MSP to 3x4 matrix keypad and print the pressed keys to the console.
 * This program also utilizes debouncing and will not repeat keys that are held.
 */

#include "msp.h"
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"

void keypad_init();
uint8_t read_keypad();
void print_keys();
void SysTick_Init();
void SysTick_delay(uint16_t delay);
void store_input();
void reset_pins();

uint8_t return_value, keypress, code_array[5] = {20, 20, 20, 20, 20};

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    SysTick_Init();
    keypad_init();                                  //calling function
                                //variables

    printf("Press a 4 digit number, then #\n"); //Printing instructions to user

    while(1){
        keypress = read_keypad();                    //call function to check for user input
        if(keypress){
            print_keys(); //custom function to print user input
        }
        store_input(); //custom function to store 4 numbers on user input, then print when necessary


        if (code_array[0] != 20 && code_array[4] == 12){
            printf("Number entered: %d %d %d %d\n", code_array[0], code_array[1], code_array[2], code_array[3]);
            reset_pins();
        }
    }
}

/*
 * Function: store_input
 * Description: Store user input into array and decide what user inputs are stored
 */
void store_input(){
    if (return_value == 10); //if *, do nothing
    else if (return_value == 12 && code_array[0] == 20); //if # but not enough digits, do nothing
    else if (return_value == 12 && code_array[0] != 20){ //if #, and enough digits, okay to print
        code_array[4] = return_value;
    }
    else if (keypress == 0); //if no key entered, do nothing
    else{ //store numbers
        code_array[0] = code_array[1];
        code_array[1] = code_array[2];
        code_array[2] = code_array[3];
        code_array[3] = return_value;
    }
}
/*
 * Function: reset_pins
 * Description: Resets pins for next input after pressing #
 */
void reset_pins (){
    code_array[0] = 20;
    code_array[1] = 20;
    code_array[2] = 20;
    code_array[3] = 20;
    code_array[4] = 20;
}
/*
 * Function: keypad_init
 * Description: Initializes ports for GPIO for matrix keypad
 */
void keypad_init(void){
    //Port 4 and pins 4, 5, and 6 are connected to the columns on the keypad
    P4SEL0 &= ~(BIT4|BIT5|BIT6);
    P4SEL1 &= ~(BIT4|BIT5|BIT6);
    P4DIR  &= ~(BIT4|BIT5|BIT6);

    //Port 4 and pins 0,1,2,3 are connected to the rows on the keypad
    P4SEL0 &= ~(BIT0|BIT1|BIT2|BIT3);
    P4SEL1 &= ~(BIT0|BIT1|BIT2|BIT3);
    P4DIR  &= ~(BIT0|BIT1|BIT2|BIT3);           // GPIO input configuration
    P4REN  |=  (BIT0|BIT1|BIT2|BIT3);           //PULL-UP RESISTOR
}

/*
 * Function: SysTick_Init
 * Description: Intializing SysTick Timer
 */
void SysTick_Init(void){
    SysTick->CTRL = 0;              //disable SysTick during step
    SysTick->LOAD = 0x00FFFFFF;     //max reload value
    SysTick->VAL  = 0;
    SysTick->CTRL = 0x00000005;     //enable systick
}
/*
 * Function: SysTick_delay
 * Description: Function to use SysTick Timer
 */
void SysTick_delay(uint16_t delay){
    SysTick->LOAD = ((delay * 3000) - 1);       //delay for 1ms
    SysTick->VAL  = 0;
    while((SysTick->CTRL & 0x00010000) == 0);   //wait for flat to be set
}
/*
 * Function: read_keypad
 * Description: Function to take input from matrix keypad
 */
uint8_t read_keypad(void){
    uint8_t col, row;

    for(col =0; col <3; col++){
        P4DIR =   0x00;               //column input
        P4DIR |=  BIT(4+col);         //column output
        P4OUT &= ~BIT(4+col);         //column low

        __delay_cycles(10);           //delay
        row = P4IN & 0x0F;            //read rows

        while(!(P4IN & BIT0) || !(P4IN & BIT1) || !(P4IN & BIT2) || !(P4IN & BIT3));

        if(row != 0x0F)
            break;                  //key is pressed if it's grounded, ie. it's low
    }

    P4DIR = 0x00;                   // SET COLUMNS TO INPUTS
    if(col ==3){
        return 0;
    }
    if(row == 0x0E){
        return_value =     col + 1;               //key in row 0 (1,2,3)
    }
    if(row == 0x0D){
        return_value = 3 + col + 1;               //key in row 1 (4,5,6)
    }
    if(row == 0x0B){
        return_value = 6 + col + 1;               //key in row 2 (7,8,9)
    }
    if(row == 0x07){
        return_value = 9 + col + 1;               // key in row 3 (*,0,#)
    }
    return 1;
}
/*
 * Function: print_keys
 * Description: Function to display input from keypad to console
 */
void print_keys(void){
    printf("Key: ");
    if(return_value<10)
            printf("%d\n", return_value);
    if(return_value == 12)
        printf("#\n");
    if(return_value == 11)
        printf("0\n");
    if(return_value == 10)
        printf("*\n");
}
