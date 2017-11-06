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

/*======================== Globals  ========================*/

extern  float distance;
extern  float velocity;
extern  uint8_t direction;


extern  uint8_t ascii_distance[10];         //creates an ascii string representation for distance
extern uint8_t ascii_velocity[10];         //creates an ascii string representation for velocity

extern uint8_t printout_Klee;
extern uint32_t seconds; // counted with in the ISR for systick

volatile char str[10];

/*===========================================================*/

void UART_Config2(){
    /*  Steps for Setting up UART Table 22.3.1
     *      Set UCSWRST
     *      Initialize all registers with UCSWRT = 1
     *      Configure Ports
     *      Clear UCSWST with software, aka clear that 1.
     *      Enable interrupts for UCRxie and UCTxie
     *
     *
     * Resets as all 0's so only the clock sources is the
     *  that need to be changed will change.
     *
     *  "Frame parameters" means the parity, stop bits, etc. but cuz all reset as 0's
     *  no worries.
     * */

    //Set up pins.
        //Pin 2 is the RX           pin 3 is the TX
        //RX SETUP
        P1SEL0 |= BIT2;
        P1SEL1 &= ~BIT2;

        //TX SETUP
        P1SEL0 |= BIT3;
        P1SEL1 &= ~BIT3;


        // UART must be in reset mode to configure
        EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST; //reset by setting to 1.


        EUSCI_A0->IFG = 0b0; //CLEAR FLAGS WHILE RESET 1.




        EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SSEL__SMCLK; //frame parameter , enable interrupt on the RX
        //baud rate clock is 4 Mhz
        //what register is UCBR? it needs to be set as 26 is that the word one?
        EUSCI_A0->BRW = 26; //baud rate, so baud rate set at 26 with other settings will result in a rate of 9600


        // UCOS16 = 1,          UCbRx = 26;              UCBRF = 0 ;              UCBRSx = 0xB6
        EUSCI_A0->MCTLW|=  (EUSCI_A_MCTLW_OS16); //from table 22.3.13

        EUSCI_A0->MCTLW|= ((0xB600)) ;//| (EUSCI_A_MCTLW_OS16); //from table 22.3.13


        // CLEAR UCSWRST
        EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;

        //set up interrupt
           EUSCI_A0->IE |= UCRXIE ;//BIT1 | EUSCI_A_IFG_RXIFG; // set up interrupt enable for both Rx and Tx.

           NVIC_EnableIRQ(EUSCIA0_IRQn);
}

void UART_Config(){
    /* Pin Configuration
     * configures pin3.2 and pin3.3 for RX/TX
     */
    UART_RX_TX_Config();

    /* Clock Configuration for 4 Mhz */
    Clock_Config();


/* Rest of Configuration for UART*/
    EUSCI_A2->CTLW0 |= EUSCI_A_CTLW0_SWRST; //reset by setting to 1.
    EUSCI_A2->IFG = 0b0;                                            // Clear any flags WHILE RESET IS 1


    EUSCI_A2->CTLW0 |= EUSCI_A_CTLW0_SSEL__SMCLK;                 //frame parameter , enable interrupt on the RX
    EUSCI_A2->BRW = 26;                                           //baud rate, so baud rate set at 26 with other settings will result in a rate of 9600
    // UCOS16 = 1,          UCbRx = 26;              UCBRF = 0 ;              UCBRSx = 0xB6
    EUSCI_A2->MCTLW|=  (EUSCI_A_MCTLW_OS16);                      //from table 22.3.13 over sampling enabled
    EUSCI_A2->MCTLW|= ((0xB600)) ;                                //from table 22.3.13
    // CLEAR UCSWRST
    EUSCI_A2->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;


    EUSCI_A2->IE |=  EUSCI_A_IFG_RXIFG;        // set up interrupt enable for both Rx and Tx. ENABLE INTERRUPTS AFTER RESET

    NVIC_EnableIRQ(EUSCIA2_IRQn);

}

void UART_send_byte(uint8_t tx_data){
    while(!(EUSCI_A2->IFG & EUSCI_A_IFG_TXIFG));
     EUSCI_A2->TXBUF = tx_data;             // be sure data is in ASCII
}

//:TODO change back to UARTA2
void UART_send_n_bytes(uint8_t *string){
    uint32_t index =0;
    uint32_t length = strlen(string); //automatically calculate the length
     for(index = 0; index <length ; index++){
         UART_send_byte(string[index]);
     }
}


void Escooter_Printout(){
    char ascii_distance[10] ={0,0,0,0,0,0,0,0,0,0};         //creates an ascii string representation for distance
    char ascii_velocity[10];         //creates an ascii string representation for velocity

    //     ftoa(distance, ascii_distance, 3);         //converts distance number value to ascii string
         ftoa(distance, 3);         //converts distance number value to ascii string

//    ftoa(velocity, ascii_velocity, 3);         //converts velocity number value to ascii string

    /* -----------------------------  Distance Print Out   ----------------------------------*/
    /* --------------------------------------------------------------------------------------*/
    UART_send_n_bytes("Distance Traveled:  ");
    UART_send_n_bytes(ascii_distance);
    UART_send_n_bytes(" meters");
    UART_send_byte(13);

    /* -----------------------------  Velocity Print Out   ----------------------------------*/
    /* --------------------------------------------------------------------------------------*/
    UART_send_n_bytes("Instantaneous Velocity: ");
    UART_send_n_bytes(ascii_velocity);
    UART_send_n_bytes(" meters/seconds");
    UART_send_byte(13);

    /* -----------------------------  Direction Print Out   ----------------------------------*/
    /* ---------------------------------------------------------------------------------------*/
    if(direction == 1){            /*-------- Forward --------- */
    UART_send_n_bytes("Direction: Forward");
    UART_send_byte(13);
    }
    if(direction == 0){            /*-------- Backward --------- */
    UART_send_n_bytes("Direction: Backward");
    UART_send_byte(13);
    }
    if(velocity == 0){                              /*-------- Condition if stopped --------- */
    UART_send_n_bytes("Direction: Stopped");
    UART_send_byte(13);
    }

    /* -----------------------------  Motion Print Out   ----------------------------------*/
    /* ------------------------------------------------------------------------------------*/

    if(velocity == 0){                              /*-------- Stationary --------- */
    UART_send_n_bytes("Motion: Stopped");
    UART_send_byte(13);
    }
    else{                                           /*-------- In Motion --------- */
    UART_send_n_bytes("Motion: Moving");
    UART_send_byte(13);
    }

}



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

 char ftoa(float f, int afterpoint)           //float to string function
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

    return str;
}

/*============================================================================*/

/* ISR Handler for RX and TX */
extern void EUSCIA2_IRQHandler(){
    uint16_t delay;

    if(EUSCI_A2->IFG & EUSCI_A_IFG_RXIFG){


               EUSCI_A2->IFG &= ~EUSCI_A_IFG_RXIFG;//clear the flag.
             //:TODO need to implement buffer
             //  add_To_Buffer(&myBufferPTR, EUSCI_A2->RXBUF);




               /*visual output to confirm RX */
                       P2OUT = 0;
                       P2OUT ^= BLUE_LED_UART_VISUAL; //vis
                      for(delay =0; delay<200; delay++);
                      P2OUT ^= BLUE_LED_UART_VISUAL;
               /*end of visual output */
}


    if(EUSCI_A2->IFG & EUSCI_A_IFG_TXIFG){

    }
}

extern void EUSCIA0_IRQHandler(){
    uint16_t delay;

    if(EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG){


               EUSCI_A0->IFG &= ~EUSCI_A_IFG_RXIFG;//clear the flag.
             //:TODO need to implement buffer
             //  add_To_Buffer(&myBufferPTR, EUSCI_A2->RXBUF);




               /*visual output to confirm RX */
                       P2OUT = 0;
                       P2OUT ^= BLUE_LED_UART_VISUAL; //vis
                      for(delay =0; delay<200; delay++);
                      P2OUT ^= BLUE_LED_UART_VISUAL;
               /*end of visual output */
}


    if(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG){

    }
}
