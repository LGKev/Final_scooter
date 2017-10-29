/*
 * Timer.c
 *
 *  Created on: Oct 27, 2017
 *      Author: kwat1
 */

#include "Timer.h"
#include "msp.h"


void Timer_A0_Config(){
        __disable_irq(); //start a critical section
      TIMER_A0->R = 0;
      TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2|TIMER_A_CTL_ID__8| TIMER_A_CTL_MC__UP;//UP MODE, SOURCE SEL SMCLK
      TIMER_A0->CCR[0] = 4727;                      // Value to count to, //:TODO change for 50 ms

      TIMER_A0->CCTL[0] &= ~CCIFG;                  // Clear flags
      TIMER_A0->CCTL[0] |= TIMER_A_CCTLN_CCIE;      // INTERRUPT INABLE CAPTURE COMPARE
      TIMER_A0->EX0 = TIMER_A_EX0_TAIDEX_7;         // divide by 8
       NVIC_EnableIRQ(TA0_0_IRQn);

       __enable_irq();
}

void TA0_0_IRQHandler(){ //basically used only to cycle led colors
    TIMER_A0->CCTL[0] &= ~CCIFG; //clear compare captture flag

    P2OUT++;

    if(P2OUT > 7){
        TIMER_A0->CCR[0] = 0; //stop timer.
        P2OUT = 0; /// RESET rgb
    }


    //:TODO make sure to set up isr for timer
}
