/*
 * Author:  Jay Dhar
 * Date:    2/19/21
 * Program Description: This program will change colors of the onboard LED
 * at a predefined interval as long as the user is pressing the button
 */
#include "msp.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define STANDBY 0
#define RED     1
#define GREEN   2
#define BLUE    3

void SetupP1(void);
void SetupP2(void);
uint16_t CheckButton1_1(void);


void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    SetupP1();
    SetupP2();

    static uint8_t state = 0;   //remembers last place when color shift is paused

    while(1) {  //while button press, color shift will occur
        if(CheckButton1_1()) {
            switch(state) {
            case STANDBY:
                P2->OUT &= ~(BIT0 | BIT1 | BIT2);
                state = RED;
                break;
            case RED:                               //switches to red
                P2->OUT &= ~(BIT0 | BIT1 | BIT2);
                P2->OUT |= BIT0;
                state = GREEN;
                break;
            case GREEN:                             //switches to green
                P2->OUT &= ~(BIT0 | BIT1 | BIT2);
                P2->OUT |= BIT1;
                state = BLUE;
                break;
            case BLUE:                              //switches to blue
                P2->OUT &= ~(BIT0 | BIT1 | BIT2);
                P2->OUT |= BIT2;
                state = RED;
                break;
            }
            _delay_cycles(3000000);//3000 = 1ms, wait 1 second between color switch
        }
    }
}

/*
 * Function: SetupP1
 * Description: Sets up port 1 for button input
 */

void SetupP1() {                        //initialize button
    P1->SEL0 &= ~BIT1;
    P1->SEL1 &= ~BIT1;
    P1->DIR &= ~BIT1;
    P1->REN |= BIT1;                    //call internal resistor
    P1->OUT |= BIT1;                    //set as pull up
}

/*
 * Function: SetupP2
 * Description: Sets up port 2 for LED output
 */

void SetupP2() {                        //initialize LEDs
    P2->SEL0 &= ~(BIT0 | BIT1 | BIT2);
    P2->SEL0 &= ~(BIT0 | BIT1 | BIT2);
    P2->DIR |= (BIT0 | BIT1 | BIT2);
    P2->OUT &= ~(BIT0 | BIT1 | BIT2);
}

/*
 * Function: CheckButton1_1
 * Description: Modified version of part 1's checkbutton.
 * Delay function readjusted for debouncing while button is pressed
 */


uint16_t CheckButton1_1(void) {
        static uint16_t pstate;   //Variable for pin1 debouncer; if p1.1 == 0xff00, return BIT1

        pstate = pstate << 1;   //shift last bit left to make space for new
        pstate |= ( 0xff00 | ( (BIT1 & P1->IN) >> 1 ) );
        __delay_cycles(5);      //delay for five cycles (3000 cycles = 1 ms)

        if (pstate == 0xff00) {
            return BIT1;
        }
        return 0;
}
