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
uint8_t dump_Buffer =0;

//:TODO find a better place to declare buffer





/*====== Globals Related to Distance/Velocity  =======*/
//uint32_t global_number_Of_Beam_Breaks;
//uint8_t Calculate_Distance = 0; //flag to calculate
//float total_distance_cummulative = 0.0;
volatile uint16_t systickflag=0;
volatile uint32_t count_int=0;
volatile uint16_t systick_int=0;
float distance=0;
float velocity=0;
volatile uint32_t seconds=0; // counted with in the ISR for systick




/*=====================++===========================*/

uint8_t * foo(uint32_t ** ptr){
    (*(*ptr)) += 1048576;
    (*ptr)++;
    return ((uint8_t *)(*ptr));
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

	   //IR_Beam_Break_Config();
	IR_Beam_Break_Config_JW();

	//   UART_Config();
	  // Timer_A0_Config(); //enabling timer with vector table forces port 1 interrupt to fail.

	    config_systick(); //enable timing for velocity

	    __enable_irq();

	    while(1){

//	        if(dump_Buffer == 1){
//	            print(myBufferPTR);
//	            dump_Buffer = 0;
//
//
//	        }

	        if(systickflag==1){
	                 velocity=(((systick_int)*(0.3078761/14))/systickflag);
	                 distance=((count_int)*(0.3078761/14)); //m
	                 systick_int=0;
	                 systickflag=0;
	               }
	    }



}


