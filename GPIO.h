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
 *          TX: port 3  Pin 3 UCA2
 *          RX: port 3  Pin 2 UCA2
 *      Call this inside of UART.C to configure the pins for UART
 *
 *      @param: input none
 *      @param: output none
 */
 void UART_RX_TX_Config();


 /*     @name: IR_Beam_Break_Config()
  *     @brief: Configure port for the IR Beam Break
  *        Photo Diode Pin: Port 2 pin 5
  *        LED IR Pin: wired to 5v
  *     Also enables interrupts for PORT 2
  * */
 void IR_Beam_Break_Config();

/*
 *  @name: IR_Beam_Break_Config_JW
 *  @brief: sets up the ir beam break for pin 6
 *  */
 void IR_Beam_Break_Config_JW();

 /*
  *     @name: RGB_Config
  *     @brief: configures the pins for the RGB led
  * */
 void RGB_Config();


 /*     @name: Lef_Right_Button_Config
  *     @brief: configures the pins for the left and right buttons
  *         enables the port interrupt for the left and right buttons
  *
  * */
 void Left_Right_Button_Config();

 /*     @name: Port1_IQRHandler
  *     @brief: interrupt triggered based on the input from the Left and Right Buttons
  *     TODO: nothing configured, but interrupts are enabled.
  *
  */




#endif /* GPIO_H_ */
