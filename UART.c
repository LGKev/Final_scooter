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

extern char ascii_backwards[10];
extern char ascii_string_from_INT_STRING[10];

extern char ascii_string_FLOAT_Int_Portion[10]; //Integer portion of the float conversion
extern char ascii_string_FLOAT_fraction_Portion[10]; //Fractional portion of the float conversion

extern char ascii_backwards_float_int_portion[10];
extern char ascii_backwards_float_fraction_portion[10];


/*===========================================================*/

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


    //intToStr((int)distance, 10);

    ftoa(distance);


    /* -----------------------------  Distance Print Out   ----------------------------------*/
    /* --------------------------------------------------------------------------------------*/
    UART_send_n_bytes("Distance Traveled:  ");
    UART_send_n_bytes(ascii_backwards_float_int_portion);
    UART_send_n_bytes(" meters");
    UART_send_byte(13);


    ftoa(velocity);


    /* -----------------------------  Velocity Print Out   ----------------------------------*/
    /* --------------------------------------------------------------------------------------*/
    UART_send_n_bytes("Instantaneous Velocity: ");
    UART_send_n_bytes(ascii_backwards_float_int_portion);
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
/* @name: reverse
 * @brief: takes in a global: ascii_backwards and reverses it. changes the global string
 * */
void reverse(uint8_t length)
{
    uint8_t i = 0;
    uint8_t j = length - 1; //hard coded length
    uint8_t temp;

    while(i<j){
        temp = ascii_backwards[i];
        ascii_backwards[i] = ascii_backwards[j];
        ascii_backwards[j] = temp;
        i++;
        j--;
    }
}

 char intToStr(int value, int length)
{
    int i = 0;
    while (value)
    {
        ascii_string_from_INT_STRING[i++] = (value%10) + '0';
        value = value/10;
    }
    while (i < length)
    {
        ascii_string_from_INT_STRING[i++] = '0';
    }
    uint8_t index = 0;
    for(index = 0; index < i; index++){
        ascii_backwards[index] = ascii_string_from_INT_STRING[index];
    }

    reverse(10); //uses global variable
    ascii_string_from_INT_STRING[i] = '\0';
    return ascii_string_from_INT_STRING;
}



 char ftoa(float value)           //float to string function
{
     if(value == 0.0){
         ascii_backwards_float_int_portion[0] ='0';
     ascii_backwards_float_int_portion[1] = '.';
     ascii_backwards_float_int_portion[2] = '0';//termination
     ascii_backwards_float_int_portion[3] = '\0';
          return;
     }

     uint8_t number_of_integer_digits = 0; //use this to keep track for reversal
     uint8_t reversal_array[10];

     __disable_irq();
     uint32_t value_int = (int)value;

     uint32_t value_fractional =( value - value_int ) * 1000; //3 decimal place precision

     uint8_t index_overall = 0;
       uint8_t index_for_fractional = 0;
       while(value_fractional !=0){
           reversal_array[index_for_fractional] = value_fractional % 10 + '0';
           index_for_fractional++;
           number_of_integer_digits++;
           value_fractional = value_fractional / 10;
       }
       //its zero now, so now we need to add a point
           reversal_array[index_for_fractional] = '.'; //add decimal //TODO: might be off by 1 place.
           index_for_fractional++;
//lets get the numerical part, then reverse all at the end
       while(value_int != 0){
                    reversal_array[index_for_fractional] = value_int%10 + '0';
                    index_for_fractional++;
                    number_of_integer_digits++;
                    value_int = value_int / 10;
                }

         //now we have the integer portion it needs to be swapped


       uint8_t copy_index = 0;
               for(copy_index =0; copy_index < number_of_integer_digits; copy_index++){
                   ascii_backwards_float_int_portion[copy_index] = reversal_array[number_of_integer_digits - copy_index];
               }

       index_for_fractional++;
       ascii_backwards_float_int_portion[index_for_fractional] = '\0'; //don't you dare not terminate the string

       __enable_irq();
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
