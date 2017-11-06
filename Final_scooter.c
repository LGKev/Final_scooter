/*
 * Final_scooter.c
 *
 *  Created on: Oct 27, 2017
 *      Author: kwat1
 */

/*
 * @name: movement_Detection.
 * @brief: Detects movement forward and backward.
 *  no input no output
 *  global variables set: direction, and moving
 * */


#include "msp.h"
#include "UART.h"
#include "GPIO.h"

/*========================   Globals  for Distance and Velocity ==============================*/
extern  uint16_t systickflag;
extern  uint32_t count_int;
extern  uint16_t systick_int;
extern  uint32_t seconds;


extern  float distance;
extern  float velocity;

/*========================   Globals  for Movement Detection  ==============================*/

extern  uint8_t direction;
extern uint16_t moving;
uint16_t forward;
extern uint16_t X_ADC14;
extern uint16_t Y_ADC14;
extern uint16_t Z_ADC14;
extern uint32_t zero_speed;

/*======================================================*/

void movement_Detection(){

    direction = 0;
    forward = 0;
    moving = 0;


         velocity=(((systick_int)*(0.3078761/14))/systickflag);
          distance=((count_int)*(0.3078761/14)); //m
          if(velocity==0){
              //Set an interrupt flag that show show the escooter is stopped
               moving =0;
               direction =0;
          }
          else{
              ADC14->CTL0 |= ADC14_CTL0_SC;
              Y_ADC14 = ADC14->MEM[1];
              if (Y_ADC14<7600){
                 //uart print that escooter is moving backward
                  direction =1;
                  forward =0; // backward
                  moving = 1;
                  //add other content here
                  }
              else if(Y_ADC14>8400){
                  //uart print that escooter is moving forward
                  direction =1;
                  forward =1; // forward
                  moving=1;
                  //add other content here
              }
              else {
                  direction = 0; //no direction detected the acceleration is not enough
              }
         }
}
