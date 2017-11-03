#include "msp.h"
#include "GPIO.h"
#include "adc_driver.h"
#include "Timer.h"
#include "circ_buffer_basic.h"
#include "Final_scooter.h"
#include "UART.h"


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
uint32_t global_number_Of_Beam_Breaks;
uint8_t Calculate_Distance = 0; //flag to calculate
float total_distance_cummulative = 0.0;



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






	   RGB_Config();
	   Left_Right_Button_Config();

	   UART_Config();
	   Timer_A0_Config(); //enabling timer with vector table forces port 1 interrupt to fail.

    initialize_Circ_Buffer(&myBufferPTR, 200);

    add_To_Buffer(&myBufferPTR, 101);

	    __enable_irq();

	    while(1){

	        if(dump_Buffer == 1){
	            print(myBufferPTR);
	            dump_Buffer = 0;


	        }
	    }



}


