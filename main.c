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
 * */

/*===============   Globals    ======================*/
//:TODO find a better place to declare buffer

CircBuf_t myBuffer;
CircBuf_t * myBufferPTR = &myBuffer;

uint32_t global_number_Of_Beam_Breaks;
uint8_t Calculate_Distance = 0; //flag to calculate
float total_distance_cummulative = 0.0;

/*=====================++===========================*/


void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer



	   RGB_Config();
	   Left_Right_Button_Config();
	   UART_Config();
	   Timer_A0_Config(); //enabling timer with vector table forces port 1 interrupt to fail.

//	    initialize_Circ_Buffer(&myBufferPTR, 200);

	    __enable_irq();

	    while(1);



}


