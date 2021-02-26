/*
 * Author: Jay Dhar
 * Date: 2/26/21
 * Program Description: Upon holding a button, lights will sequence from green to yellow to red
 */

#include "msp.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void buttonSetup(void);
void LEDSetup(void);
uint16_t checkButton(void);
void SysTick_Init(void);
void SysTick_delay(uint16_t delay);

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    buttonSetup();
    LEDSetup();
    SysTick_Init();

    while(1) {
        if(checkButton()) {          //button pressed
            if(P4->OUT & BIT1) {        //red is on
                P4->OUT &= ~BIT1;       //turn off red
                P4->OUT |= BIT2;        //turn on green
            }
            else if(P4->OUT & BIT2) {   //green is on
                P4->OUT &= ~BIT2;       //turn off green
                P4->OUT |= BIT3;        //turn on blue
            }
            else if(P4->OUT & BIT3) {   //blue is on
                P4->OUT &= ~BIT3;       //turn off blue
                P4->OUT |= BIT1;        //turn on red
            }
            else {
               P4->OUT &= ~BIT1;        //LEDs off,
               P4->OUT |= BIT1;         //turn on red
            }
        }
    }
}
/*Function: buttonSetup
 * Description: Setup GPIO as input for button
 */
void buttonSetup() {        //sets up button
    P4->SEL0 &= ~BIT0;
    P4->SEL1 &= ~BIT0;
    P4->DIR &= ~BIT0;   //sets as input
    P4->REN |= BIT0;    //calls internal resistor
    P4->OUT |= BIT0;    //pull-up
}
/*Function: LEDSetup
 * Description: Setup LED's GPIO, output
 */
void LEDSetup() {                        //sets up LEDs
    P4->SEL0 &= ~(BIT3 | BIT1 | BIT2);
    P4->SEL1 &= ~(BIT3 | BIT1 | BIT2);
    P4->DIR |= (BIT3 | BIT1 | BIT2);    //sets as outputs
    P4->OUT &= ~(BIT3 | BIT1 | BIT2);   //set as off (clear)
}
/*Function: checkButton
 * Description: A function that checks for button input and also uses SysTick for debouncing
 */
uint16_t checkButton(void) {

    static uint16_t pin_state_p4_0;   // Variable for P4.0 debouncer. If this equals 0xf800,
                                          // the debounce function returns BIT0 to the main function.
    pin_state_p4_0 = pin_state_p4_0 << 1;   // Shift the rightmost bit over so new bit can be used.
    pin_state_p4_0 |= ( 0xf000 | ( (BIT0 & P4->IN) >> 0 ) );
    SysTick_delay(5);      // Delay for five cycles (3000 cycles = 1 ms)

    if (pin_state_p4_0 == 0xf800)  return BIT0;

        return 0;
}
/*Function: SysTick_Init
 * Description: SysTick timer initialization
 */
void SysTick_Init(void) {
    SysTick->CTRL = 0;
    SysTick->LOAD = 0x00FFFFFF;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x00000005;
}
/*Function: SysTick_delay
 * Description: Uses SysTick timer as a delay for computations
 * Input: time amount in ms
 * Return: N/A
 */
void SysTick_delay(uint16_t delay) {
    SysTick->LOAD = ((delay * 3000) - 1);
    SysTick->VAL = 0;
    while ((SysTick->CTRL & 0x00010000) == 0);
}
