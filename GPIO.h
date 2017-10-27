/*
 * GPIO.h
 *
 *  Created on: Oct 27, 2017
 *      Author: kwat1
 */
#define BLUE_LED_UART_VISUAL        (0b010) /* Pin Reserved for UART RX Received*/



/*
 *  Please adhere to the C Standard programming standard
 *  Each function should have the following template:
 *
 *  @name: function Name
 *  @brief: a description of the function and what it does
 *
 *  @param: input parameters/arguments
 *
 *  @param: expected output or return statement
 *
 *  Example:
 *      @name: UART_Pin_Config

 *      @brief: sets up the RX and TX pins for Port 1
 *      @param: input none
 *      @param: output none
 *
 */

#ifndef GPIO_H_
#define GPIO_H_

/*
 *      @name: UART_Pin_Config
 *      @brief: Configure port 3 RX and TX pins for easy access to headers.
 *          TX: Pin 3 UCA2
 *          RX: Pin 2 UCA2
 *      Call this inside of UART.C to configure the pins for UART
 *
 *      @param: input none
 *      @param: output none
 */
 void UART_PIN_Config(){}





#endif /* GPIO_H_ */
