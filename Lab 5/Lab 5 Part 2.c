/*
 * Author: Jay Dhar
 * Date: 2/26/21
 * Program Description: Upon holding a button, lights will sequence from green to yellow to red
 */

#include "msp.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define STANDBY 0
#define GREEN 1
#define YELLOW 2
#define RED 3

void ButtonSetup(void);
void LEDSetup(void);
uint16_t buttonCheck(void);
void SysTick_Init(void);
void SysTick_delay(uint16_t delay);

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    ButtonSetup();
    LEDSetup();
    SysTick_Init();

    static uint8_t state = 0;

    while(1) {
        if(buttonCheck()) {
                    switch(state) {
                    case STANDBY:
                        P4->OUT &= ~(BIT1 | BIT2 | BIT3);
                        state = GREEN;                      //sets up next color ot be green
                        break;
                    case RED:                               //switches to red
                        P4->OUT &= ~(BIT3 | BIT1 | BIT2);
                        P4->OUT |= BIT3;
                        state = GREEN;                      //sets up next color to be green
                        break;
                    case GREEN:                             //switches to green
                        P4->OUT &= ~(BIT3 | BIT1 | BIT2);
                        P4->OUT |= BIT1;
                        state = YELLOW;                     //sets up next color to be yellow
                        break;
                    case YELLOW:                              //switches to blue
                        P4->OUT &= ~(BIT3 | BIT1 | BIT2);
                        P4->OUT |= BIT2;
                        state = RED;                        //sets up next color to be red
                        break;
                    }
                    SysTick_delay(1000);//3000 = 1ms, wait 1 second between color switch
                }
    }
}
/*Function: ButtonSetup
 * Description: Sets up button for output
 */
void ButtonSetup() {        //sets up button
    P4->SEL0 &= ~BIT0;
    P4->SEL1 &= ~BIT0;
    P4->DIR &= ~BIT0;   //sets as input
    P4->REN |= BIT0;    //calls internal resistor
    P4->OUT |= BIT0;    //pull-up
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
/*Function: buttonCheck
 * Description: Function to check for button input and also utilize systick timer for debouncing
 */
uint16_t buttonCheck(void) {

    static uint16_t pin_state_p4_0;   // Variable for P4.0 debouncer. If this equals 0xf800,
                                          // the debounce function returns BIT0 to the main function.
    pin_state_p4_0 = pin_state_p4_0 << 1;   // Shift the rightmost bit over so new bit can be used.
    pin_state_p4_0 |= ( 0xff00 | ( (BIT0 & P4->IN) >> 0 ) );
    SysTick_delay(5);      // Delay for five cycles (3000 cycles = 1 ms)

    if (pin_state_p4_0 == 0xff00){
        return BIT0;
    }

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
