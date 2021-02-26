/*
 * Author: Jay Dhar
 * Date: 2/26/21
 * Program Description: Upon holding a button, lights will sequence from green to yellow to red
 * Upon holding second button, color shift sequence will go in reverse order
 */

#include "msp.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define STANDBY 0
#define GREEN   1
#define YELLOW  2
#define RED     3

void buttonSetup1(void);
void buttonSetup2(void);
void LEDSetup(void);
uint16_t buttonCheck1(void);
uint16_t buttonCheck2(void);
void SysTick_Init(void);
void SysTick_delay(uint16_t delay);

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    buttonSetup1();
    buttonSetup2();
    LEDSetup();
    SysTick_Init();
    static uint8_t state = 0;       //allows color cycle to pause and pick up where it last left off


    while(1) {  //while the button is pressed, the led color will flow through the following states
        if(buttonCheck1()) {
            if (state == GREEN)
                state = YELLOW;
            else if (state == YELLOW)
                state = RED;
            else if (state == RED)
                state = GREEN;
            else
                state = state;

            while(buttonCheck1()) {
                switch(state) {             //= 0 because standby state will be accessed when button is initially pressed
                case STANDBY:                           //turns on red by sending to red state
                    P4->OUT &= ~(BIT3 | BIT1 | BIT2);
                    state = GREEN;
                    SysTick_delay(1000);
                    break;
                case GREEN:                               //switches to green
                    P4->OUT &= ~(BIT3 | BIT1 | BIT2);
                    P4->OUT |= BIT1;
                    state = YELLOW;                     //sets next color to be yellow
                    SysTick_delay(1000);
                    break;
                case YELLOW:                             //switches to yellow
                    P4->OUT &= ~(BIT3 | BIT1 | BIT2);
                    P4->OUT |= BIT2;
                    state = RED;                        //sets next color to be red
                    SysTick_delay(1000);
                    break;
                case RED:                              //switches to red
                    P4->OUT &= ~(BIT3 | BIT1 | BIT2);
                    P4->OUT |= BIT3;
                    state = GREEN;                      //sets next color to be green
                    SysTick_delay(1000);
                    break;
            }

            }
        }
        else if(buttonCheck2()) {                      //second button mirrors first one
            if (state == RED)                         //color sequence is reversed
                state = YELLOW;
            else if (state == YELLOW)
                state = GREEN;
            else if (state == GREEN)
                state = RED;
            else
                state = state;

            while(buttonCheck2()) {
                switch(state) {             //= 0 because standby state will be accessed when button is initially pressed
                                           //turns on red by sending to red state

                case GREEN:                               //switches to green
                    P4->OUT &= ~(BIT3 | BIT1 | BIT2);
                    P4->OUT |= BIT1;
                    state = RED;                         //sets next color to be red
                    SysTick_delay(1000);
                    break;
                case YELLOW:                             //switches to yellow
                    P4->OUT &= ~(BIT3 | BIT1 | BIT2);
                    P4->OUT |= BIT2;
                    state = GREEN;                      //sets next color to be green
                    SysTick_delay(1000);
                    break;
                case RED:                              //switches to red
                    P4->OUT &= ~(BIT3 | BIT1 | BIT2);
                    P4->OUT |= BIT3;
                    state = YELLOW;                   //sets next color to be yellow
                    SysTick_delay(1000);
                    break;
                }

        }
        }
    }
}
/*Function: buttonSetup1
 * Description: Sets up button for output
 */
void buttonSetup1() {        //sets up button
    P4->SEL0 &= ~BIT0;
    P4->SEL1 &= ~BIT0;
    P4->DIR &= ~BIT0;   //sets as input
    P4->REN |= BIT0;    //calls internal resistor
    P4->OUT |= BIT0;    //pull-up
}
/*Function: buttonSetup2
 * Description: Sets up button for output
 */
void buttonSetup2() {        //sets up button
    P4->SEL0 &= ~BIT4;
    P4->SEL1 &= ~BIT4;
    P4->DIR &= ~BIT4;   //sets as input
    P4->REN |= BIT4;    //calls internal resistor
    P4->OUT |= BIT4;    //pull-up
}
/*Function: LEDSetup
 * Description: Sets up the LEDs for output
 */
void LEDSetup() {                        //sets up LEDs
    P4->SEL0 &= ~(BIT3 | BIT1 | BIT2);
    P4->SEL1 &= ~(BIT3 | BIT1 | BIT2);
    P4->DIR |= (BIT3 | BIT1 | BIT2);    //sets as outputs
    P4->OUT &= ~(BIT3 | BIT1 | BIT2);   //set as off (clear)
}
/*Function: buttonCheck1
 * Description: Function to check for button input and also utilize systick timer for debouncing
 */
uint16_t buttonCheck1(void) {

    static uint16_t butt1;   // Variable for P4.0 debouncer. If this equals 0xf800,
                                          // the debounce function returns BIT0 to the main function.
    butt1 = butt1 << 1;   // Shift the rightmost bit over so new bit can be used.
    butt1 |= ( 0xff00 | ( (BIT0 & P4->IN) >> 0 ) );
    SysTick_delay(5);      // Delay for five cycles (3000 cycles = 1 ms)

    if (butt1 == 0xff00)  return BIT0;

    return 0;
}
/*Function: buttonCheck2
 * Description: Function to check for button input and also utilize systick timer for debouncing
 */
uint16_t buttonCheck2(void) {


    static uint16_t butt2;   // Variable for P4.4 debouncer. If this equals 0xf800,
                                          // the debounce function returns BIT4 to the main function.

    butt2 = butt2 << 1;   // Shift the rightmost bit over so new bit can be used.
    butt2 |= ( 0xff00 | ( (BIT4 & P4->IN) >> 4 ) );
    __delay_cycles(5);      // Delay for five cycles (3000 cycles = 1 ms)

    if (butt2 == 0xff00)  return BIT4;

    return 0;
}
/* Function: SysTick_Init
 * Description: Initializes MSP's onboard systick timer
 */
void SysTick_Init(void) {
    SysTick->CTRL = 0;
    SysTick->LOAD = 0x00FFFFFF;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x00000005;
}
/*Function: SysTick_delay
 * Description: Utilizes MSP's onboard systick timer with input as time in ms for delaying in computing
 */
void SysTick_delay(uint16_t delay) {
    SysTick->LOAD = ((delay * 3000) - 1);
    SysTick->VAL = 0;
    while ((SysTick->CTRL & 0x00010000) == 0);
}
