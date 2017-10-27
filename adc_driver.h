/*
 * adc_driver.h
 *
 *  Created on: Oct 11, 2017
 *      Author: kk
 */

#include "msp.h"

#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_




/*       @name: ADC_Config_Accelerometer
 *       @brief: Sets up the ADC for the accelerometer for the X, Y, and Z axis
 *
 *
 * */
void ADC_Accelerometer_Config(void);

/*      @name: ADC14_IRQHandler
 *      @brief: Handler for the ADC conversions. Triggers whenever data is converted and stored in Mem[x]
 *          IFG set is corresponding to MEM[x]: ie, Mem[5] triggers IFG5
 *          Currently set to trigger on MEM[2]
 * */
void ADC14_IRQHandler(void);

#endif /* ADC_DRIVER_H_ */
