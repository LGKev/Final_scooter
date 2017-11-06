/*
 * UART.h
 *
 *  Created on: Oct 27, 2017
 *      Author: kwat1
 */
#include "msp.h"
#include <stdint.h>

#ifndef UART_H_
#define UART_H_


/* @name: UART_Config
 * @brief: Configures the Enhanced Universal Serial Communication
 *         Configures ISR for UARTA2
 *          DO NOT CONFIGURE PINS WITH UART CONFIG CALL UART_Pin_Config();
 * @param: output none
 * @param: input none
 *
 * */
void UART_Config();


void UART_Config2();


/* @name: UART_send_byte
 * @brief: Sends a byte of data
 * @param: data: a uint8_t a number representing an ASCII value.
 * @param: output none
 *
 * If you need to send a number be sure to use ITOA to convert number to ascii value.
 * IE 0 is not 0 in ASCII, its 48
 * */
void UART_send_byte(uint8_t data);


/* @name: UART_send_n_bytes
 * @brief: Sends a string to UART TX pins
 * @param: string: The input is an array of characters or simply a string with "double quotes"
 */
void UART_send_n_bytes(uint8_t *string);

/* @name: EUSCIA2_IRQHanlder()
 * @brief: The interrupt handler is in the UART.c and is configured for RX and TX interrupts
 * TODO: Need to configure RX Buffer and interrupt to trigger modes
 * */
void EUSCIA2_IRQHandler();

/*
 *@name: Escooter_Printout
 *@brief: Takes global data (distance, velocity, direction) and prints it via UART. No buffer required.
 * @param: direction, velocity, distance are globals!
 * */
void Escooter_Printout();


/*======================       Convert to ASCIII            ==============================*/
void reverse(uint8_t length);
char intToStr(int value, int length);
char itoa(int value, char str[], int base);          //Integer to ASCII (should return ascii)
char ftoa(float f);         //Float to ASCII (should return ascii)



#endif /* UART_H_ */
