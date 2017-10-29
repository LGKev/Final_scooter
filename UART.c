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
#include "Clock.h"


void UART_Config(){
    /* Pin Configuration
     * configures pin3.2 and pin3.3 for RX/TX
     */
    UART_RX_TX_Config();

    /* Clock Configuration for 4 Mhz */
    Clock_Config();


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
    while(!(EUSCI_A2->IFG & EUSCI_A_IFG_TXIFG));
     EUSCI_A2->TXBUF = tx_data;             // be sure data is in ASCII
}

void UART_send_n_bytes(uint8_t *string){
    uint32_t index =0;
    uint32_t length = strlen(string); //automatically calculate the length
     for(index = 0; index <length ; index++){
         UART_send_byte(string[index]);
     }
}
\




/*======================       Convert to ASCIII            ==============================*/
 void reverse(char str[], int len)        //function to reverse string to get it readable and not backwards
{
    int start, end;
    char temp;
    for (start=0, end = len-1; start<end; start++, end--)
    {
        temp = *(str+start);
        *(str+start)= *(str+end);
        *(str+end) = temp;
    }
}

 int intToStr(int value, char str[], int length)
{
    int i = 0;
    while (value)
    {
        str[i++] = (value%10) + '0';
        value = value/10;
    }
    while (i < length)
    {
        str[i++] = '0';
    }
    reverse(str,i);
    str[i] = '\0';
    return i;
}

 char itoa (int value, char str[], int base)           //integer to string function
{
    int  i = 0;
    int sign;

    if ((sign = value) < 0){        //What to do if values is negative
        value = -value;         //make value positive so we can work with
    }

    do{
        str[i++] = value % base + '0';
    }while ((value /= base) > 0);

    if (sign < 0){
        str[i++] = '-';
    }
    str[i] = '\0';
    reverse(str,i);

}

 char ftoa(float f, char str[], int afterpoint)           //float to string function
{
    int ipart = (int)f;

    float fpart = f - (float)ipart;

    int i = intToStr(ipart, str, 0);

    if (afterpoint != 0)
    {
        str[i] = '.';

        fpart = fpart * pow(10,afterpoint);

        intToStr((int)fpart, str + i + 1, afterpoint);
    }
}

/*============================================================================*/

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

