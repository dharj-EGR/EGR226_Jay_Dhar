/*
 * Author: Jay Dhar
 * Date: 2/19/21
 * Program Description: This program will utilize GPIO on ports 1 and 2
 * as well as use a crude delay method for debouncing to change the colors
 * of the onboard LED ta a sequence every time a button is pressed
 */
#include "msp.h"

void SetupP1(void);
void SetupP2(void);
int CheckButton1_1(void);
void delay_ms(uint32_t ms);
void SetupP1(void);
void SetupP2(void);

void main(void)
{
WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // stop watchdog timer

SetupP1(); //setup button
SetupP2(); //setup LED

while (1)
{
    if(CheckButton1_1())        //button pressed
    {
        if(P2OUT & BIT0)        //red is already on
        {
            P2OUT &= ~BIT0;     //turn off red
            P2OUT |= BIT1;      // turn on green
        }
        else if(P2OUT & BIT1)   //green is already on
        {
            P2OUT &= ~BIT1;     //turn off green
            P2OUT |= BIT2;      // turn on green
        }
        else if(P2OUT & BIT2)       //blue is already on
        {
            P2OUT &= ~BIT2;         // turn off blue
            P2OUT |= BIT0;          // turn on red
        }
        else                // nothing on, no default to red
        {
            P2OUT &= ~BIT0;     //turn off red
            P2OUT |= BIT0;      // turn on red
        }

}
    }
}

/*************************************************
 * Function: SetupP1
 * Description: Sets up the button for input
 * Return: N/A
 */

void SetupP1(void)
{
    P1SEL0 &= ~BIT1;
    P1SEL1 &= ~BIT1;
    P1DIR &= ~BIT1;
    P1REN |= BIT1;
    P1OUT |= BIT1;
}

/*
 * Function: SetupP2
 * Description: Setup LED's as output, start as LED's off
 * Return: N/A
 */

void SetupP2(void)
{
    P2 -> SEL0 &= ~(BIT0|BIT1|BIT2);
    P2 -> SEL1 &= ~(BIT0|BIT1|BIT2);
    P2 -> DIR |= (BIT0|BIT1|BIT2);          //Output
    P2 -> OUT &= ~(BIT0|BIT1|BIT2);         //Start the LEDs as OFF
}

/*
 * Function: CheckButton
 * Description: Checks for button input from P1, also implements debouncing
 * Return: N/A
 */

int CheckButton1_1(void)
{
    int delay = 0;
    uint8_t delayed = 0;
    //  P1->IN == 0b10101010
    // BIT1  == 0b00000010
    // &     == 0b00000010  (True)
    // !     !== 0 (False)
    if(P1IN & BIT1)       // If P1.1 is pressed   (pressed == GND)
    {
      delay_ms(3);    // 0.01 seconds (3000000 = 1 sec)
      if(!(P1->IN & BIT1))
      {

          while((P1IN & BIT1) && delayed < 100) //check for when button is no longer pressed
          {
              delay ++;
          delay_ms(3);        // 0.01 seconds (3000000 = 1 sec)
          }
          delay_ms(3);
        return 1;
  }

}
    return(0); //button not pressed, return 0
}

/*
 * Function: delay_ms
 * Description: Crude method to hang the MSP for debouncing for a certain interval
 * Parameters: Predefined time in ms to hang the MSP
 * Return: N/A
 */
void delay_ms(unsigned int ms){
    int i;
    for(i=0;i<ms;i++)
    {
        __delay_cycles(30000);       // 3000 == a millisecond (0.001)
    }
}
