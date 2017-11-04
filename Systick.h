/*
 * Systick.h
 *
 *  Created on: Nov 1, 2017
 *      Author: Jordan Wright
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#define SYST_CSR            *(uint32_t*) 0xE000E010
#define SYST_RVR            *(uint32_t*) 0xE000E014
#define SYST_CV             *(uint32_t*) 0xE000E018

#define CounterEnable       0x01        //BIT 0
#define ProcessorClock      0x04        //BIT 4
#define TickINT             0x02        //BIT 1
//#define 3M                ((uint32_t)0x2DC6C0)    //3M ticks (one second for 3MHz clock)
#define CountFlag         ((uint16_t)1 << (16))

void config_systick(void);

#endif /* SYSTICK_H_ */
