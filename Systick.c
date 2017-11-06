/*
 * Systick.c
 *
 *  Created on: Nov 1, 2017
 *      Author: Jordan Wright
 */
#include "msp.h"
#include "Systick.h"

extern volatile uint16_t systick_int;
extern volatile uint32_t seconds;
extern volatile uint16_t systickflag;



void config_systick(void){
    SYST_CSR |= (CounterEnable|ProcessorClock|TickINT);
    SYST_RVR |= 3000000; //This can only hold 24 bits max at 3*10^6 because we are assuming 3Mhz
    NVIC_EnableIRQ(SysTick_IRQn);
}

void SysTick_Handler(){ //this is where the timing for velocity, and distance are calculated
    if(SYST_CSR & CountFlag){ //if systick counts down to 0 (every 1 second)
        systickflag++;
        seconds++;
        (SYST_CSR) &= ~(CountFlag);
    }
}
