/*
 * GPIO.c
 *
 *  Created on: Oct 27, 2017
 *      Author: kwat1
 */
#include "GPIO.h"
#include "msp.h"

/*====== Globals Related to Buffer  =======*/
extern uint8_t dump_Buffer;
extern volatile uint16_t systickflag;
extern volatile uint32_t count_int;
extern volatile uint16_t systick_int;
extern volatile uint32_t seconds;


 void UART_RX_TX_Config(){
     //RX SETUP
         P3SEL0 |= BIT2;
         P3SEL1 &= ~BIT2;

    //TX SETUP
         P3SEL0 |= BIT3;
         P3SEL1 &= ~BIT3;
 }

 void IR_Beam_Break_Config(){
//        P2SEL0 &= ~BIT5;
//        P2SEL1 &= ~BIT5;
//        //set up for pull down
//        P2->REN |= BIT;
//        P2->OUT &= ~BIT5;
//        P2->IFG &= ~BIT5; //interrupt flag to be cleared first
//        P2->IES &= ~BIT5; //high to low trigger
//        P2->IE |= BIT5;
//        P2DIR &= ~BIT5; //PIN 5 INPUT

     P2SEL0 &= ~BIT7;
     P2SEL1 &= ~BIT7;
     //set up for pull down
     P2->REN |= BIT7;
     P2->OUT &= ~BIT7;
     P2->IFG &= ~BIT7; //interrupt flag to be cleared first
     P2->IES &= ~BIT7; //high to low trigger
     P2->IE |= BIT7;
     P2DIR &= ~BIT7; //PIN 5 INPUT
        NVIC_EnableIRQ(PORT2_IRQn);
 }




void RGB_Config(){
    P2->SEL0 &= ~(BIT0 | BIT1 | BIT2 );
    P2->SEL1 &= ~(BIT0 | BIT1 | BIT2 );
    P2->DIR |= (BIT0 | BIT1 | BIT2 );
    P2->OUT |= (BIT0 | BIT1 | BIT2 ); //HIGH
    P2->OUT &= ~(BIT0 | BIT1 | BIT2 ); //LOW
}

void Left_Right_Button_Config(){
    /* Right button configure */
        P1->SEL0 &= ~BIT1;
        P1->SEL1 &= ~BIT1;
        P1->DIR &= ~BIT1; //amazing that this even works. its a fluke. it is set as output right now.
        P1->REN |= BIT1;
        P1->OUT |= BIT1;
        P1->IFG &= ~BIT1; //interrupt flag to be cleared first
        P1->IES |= BIT1; //high to low
        P1->IE |= BIT1;

        /* LEFT button configure */
        P1->SEL0 &= ~BIT4;
        P1->SEL1 &= ~BIT4;
        P1->DIR &= ~BIT4;
        P1->REN |= BIT4;
        P1->OUT |= BIT4;
        P1->IFG &= ~BIT4; //interrupt flag to be cleared first
        P1->IES |= BIT4; //high to low
        P1->IE |= BIT4;


        /* Enable Interrupts in the NVIC */
        NVIC_EnableIRQ(PORT1_IRQn);

}

/*   Port interrupts ISRs   */
void PORT1_IRQHandler(){
    uint8_t required_ISR_Delay = 0;
    for(required_ISR_Delay = 0; required_ISR_Delay < 200; required_ISR_Delay++);
    if (P1IFG & BIT1){
            P1->IFG &= ~BIT1;
            //:TODO configure actions based on button presss
            TIMER_A0->CCR[0] = 4700;
            dump_Buffer = 1;

        }
    if (P1IFG & BIT4){
            P1->IFG &= ~BIT4;
            //:TODO configure actions based on button presss
            TIMER_A0->CCR[0] = 12000;
        }


}

void PORT2_IRQHandler(){
    if (P2IFG & BIT7){ // IR beam break
          count_int++;
          systick_int++; //interrupt count from the ir beam break
          P1->OUT ^= BIT0; //visual output
          //P2->IFG &= ~BIT5;
          P2->IFG = 0;
      }
}
