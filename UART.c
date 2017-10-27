/*
 * UART.c
 *
 *  Created on: Oct 27, 2017
 *      Author: kwat1
 */
#include "msp.h"
#include "GPIO.h"
#include "UART.h"
#include "string.h"


void UART_Config(){
    /* Pin Configuration
     * configures pin3.2 and pin3.3 for RX/TX
     */
    UART_RX_TX_Config();

/* Rest of Configuration for UART*/
    EUSCI_A2->CTLW0 |= EUSCI_A_CTLW0_SWRST; //reset by setting to 1.

    EUSCI_A2->IFG = 0;                                            // Clear any flags
    EUSCI_A2->IE |= EUSCI_A_IFG_TXIFG | EUSCI_A_IFG_RXIFG;        // set up interrupt enable for both Rx and Tx.
    EUSCI_A2->CTLW0 |= EUSCI_A_CTLW0_SSEL__SMCLK;                 //frame parameter , enable interrupt on the RX
    EUSCI_A2->BRW = 26;                                           //baud rate, so baud rate set at 26 with other settings will result in a rate of 9600
    // UCOS16 = 1,          UCbRx = 26;              UCBRF = 0 ;              UCBRSx = 0xB6
    EUSCI_A2->MCTLW|=  (EUSCI_A_MCTLW_OS16);                      //from table 22.3.13 over sampling enabled
    EUSCI_A2->MCTLW|= ((0xB600)) ;                                //from table 22.3.13
    // CLEAR UCSWRST
    EUSCI_A2->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;
    NVIC_EnableIRQ(EUSCIA2_IRQn);

}

void UART_send_byte(uint8_t tx_data){
    while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG));
     EUSCI_A0->TXBUF = tx_data;             // be sure data is in ASCII
}

void UART_send_n_bytes(uint8_t *string){
    uint32_t index =0;
    uint32_t length = strlen(string); //automatically calculate the length
     for(index = 0; index <length ; index++){
         UART_send_byte(string[index]);
     }
}


/* ISR Handler for RX and TX */
extern void EUSCIA2_IRQHandler(){
    uint16_t delay;

    if(EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG){

               EUSCI_A0->IFG &= ~EUSCI_A_IFG_RXIFG;//clear the flag.
             //:TODO need to implement buffer
             //  add_To_Buffer(&myBufferPTR, EUSCI_A2->RXBUF);




               /*visual output to confirm RX */
                       P2OUT ^= BLUE_LED_UART_VISUAL; //vis
                      for(delay =0; delay<200; delay++);
                      P2OUT ^= BLUE_LED_UART_VISUAL;
               /*end of visual output */
}


    if(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG){

    }
}

