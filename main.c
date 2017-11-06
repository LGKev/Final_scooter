#include "msp.h"
#include "GPIO.h"
#include "adc_driver.h"
#include "Timer.h"
#include "circ_buffer_basic.h"
#include "Final_scooter.h"
#include "UART.h"
#include "Systick.h"

/**
 * main.c
 */

/*      Over All TODO LIST
 *          Configure UART_A2
 *          Configure Timer
 *          Configure GPIO
 *
 *          Determine velocity
 *          Determine distance
 *          Determine direction
 *
 *
 *          TEST Beam Break Interrupt
 *          TEST Button Interrupts
 *          Test Distance Calculation
 *
 *
 /*===================================================*/
/*===============   Globals    ======================*/
/*===================================================*/

/*====== Globals Related to Buffer  =======*/
CircBuf_t myBuffer;
CircBuf_t * myBufferPTR = &myBuffer;
uint8_t dump_Buffer = 0;

//:TODO find a better place to declare buffer

/*====== Globals Related to Distance/Velocity  =======*/
//uint32_t global_number_Of_Beam_Breaks;
//uint8_t Calculate_Distance = 0; //flag to calculate
//float total_distance_cummulative = 0.0;
volatile uint16_t systickflag = 0;
volatile uint32_t count_int = 0;
volatile uint16_t systick_int = 0;
volatile uint32_t seconds = 0; // counted with in the ISR for systick

volatile float distance = 44.44;
volatile float velocity = 53.00;
volatile uint16_t direction = 0;
volatile uint16_t moving = 0;

uint16_t forward;
volatile uint16_t X_ADC14;
volatile uint16_t Y_ADC14;
volatile uint16_t Z_ADC14;
volatile uint32_t zero_speed;

 volatile uint8_t printout_Klee  =0;

 volatile  uint8_t ascii_distance[10];         //creates an ascii string representation for distance
 volatile uint8_t ascii_velocity[10];         //creates an ascii string representation for velocity

/*=====================++===========================*/

uint8_t * foo(uint32_t ** ptr)
{
    (*(*ptr)) += 1048576;
    (*ptr)++;
    return ((uint8_t *) (*ptr));
}

/*
 * TODO: we need to assign pins for the accerlometer to work with the pins on the booster pack. should be the same as
 * lab 4
 * */

void main(void)
    {
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    //  RGB_Config();
    // Left_Right_Button_Config();

    IR_Beam_Break_Config();
    //IR_Beam_Break_Config_JW();

     UART_Config();
    //UART_Config2();


    Timer_A0_Config(); //enabling timer with vector table forces port 1 interrupt to fail.

    config_systick(); //enable timing for velocity

    __enable_irq();

    P1SEL0 &= ~BIT0;
           P1SEL1 &= ~BIT0;
           P1->DIR |= BIT0;
           P1->OUT |= BIT0;
    while (1)
    {




        if (systickflag == 1 )
        {
            //disable
//            NVIC_DisableIRQ(systick);
//            NVIC_DisableIRQ(Adc);
            velocity = (((systick_int) * (0.3078761 / 14)) / systickflag);
            distance = ((count_int) * (0.3078761 / 14)); //m
            systick_int = 0;
            systickflag = 0;
        }




        if( printout_Klee == 1){

          //  movement_Detection();
            UART_send_n_bytes("we are: ");
            UART_send_byte(48+direction);
            UART_send_byte(13);

            Escooter_Printout();
            printout_Klee = 0;
        }
    }

}

