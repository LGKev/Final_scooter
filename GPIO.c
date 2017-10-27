/*
 * GPIO.c
 *
 *  Created on: Oct 27, 2017
 *      Author: kwat1
 */
#include "GPIO.h"
#include "msp.h"

 void UART_RX_TX_Config(){
     //RX SETUP
         P3SEL0 |= BIT2;
         P3SEL1 &= ~BIT2;

    //TX SETUP
         P3SEL0 |= BIT3;
         P3SEL1 &= ~BIT3;
 }

 void IR_Beam_Break_Config(){
        P2SEL0 &= ~BIT5;
        P2SEL1 &= ~BIT5;
        //set up for pull down
        P2->REN |= BIT5;
        P2->OUT &= ~BIT5;
        P2->IFG &= ~BIT5; //interrupt flag to be cleared first
        P1->IES &= ~BIT5; //high to low trigger
        P2->IE |= BIT5;
        P2DIR &= ~BIT5; //PIN 5 INPUT
        NVIC_EnableIRQ(PORT2_IRQn);
 }


void RGB_Config(){
    P2->SEL0 &= ~(BIT0 | BIT1 | BIT2 );
    P2->SEL1 &= ~(BIT0 | BIT1 | BIT2 );
    P2->DIR |= (BIT0 | BIT1 | BIT2 );
    P2->OUT |= (BIT0 | BIT1 | BIT2 ); //HIGH
    P2->OUT &= ~(BIT0 | BIT1 | BIT2 ); //LOW
}
