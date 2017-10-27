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
 *
 *
 * */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	   Timer_A0_Config();
	   RGB_Config();
	   Left_Right_Button_Config();
	   UART_Config();




}
