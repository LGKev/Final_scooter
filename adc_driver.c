/*
 * adc_driver.c
 *
 *  Created on: Oct 11, 2017
 *      Author: kk
 */

#include "msp.h"
#include "Final_scooter.h"

/*  GLOBALS     */
   volatile uint16_t X_Accelerometer_ADC;
   volatile uint16_t Y_Accelerometer_ADC;
   volatile uint16_t Z_Accelerometer_ADC;

   extern uint16_t NADC_Temperature;


void ADC_Accelerometer_Config(){

    /*
     * Set up the pins for the accelerometer on the Booster Pack MK II
     * According To Booster Pack:
     *      J3.23   = X-Axis
     *      J3.24   = Y-Axis
     *      J3.25   = Z-Axis
     *
     * According to the MSP432p401R
     *     AnalogPin14  = P6.1    = X-Axis
     *     AnalogPin13  = P4.0    = Y-Axis
     *     AnalogPin11  = P4.2    = Z-Axis
     *
     *      Accelerometer has an enable pin and ST pin... :MARK complete, done for us hard wired.
     * */

    //:TODO double check secondary mode values. Table 10.2.6 and Figure 4.1
      P6SEL1 &= ~BIT1;//Primary mode
      P6SEL0 = BIT1;//Primary mode

      P4SEL1 &= ~BIT0; //Primary mode
      P4SEL0 = BIT0; //Primary mode

      P4SEL1 = BIT2; //tertiary mode
      P4SEL0 = BIT2; //tertiary mode

      /*Set directions as input*/
      P4DIR &= ~(BIT0 | BIT2);
      P6DIR &= ~BIT1;

      //:TODO end of sequence (EOS (done), and CONSEQ, and start address(left at default))

    while(REF_A->CTL0 & REF_A_CTL0_GENBUSY);
       REF_A->CTL0 = REF_A_CTL0_VSEL_0 | REF_A_CTL0_ON;
       REF_A->CTL0 &= ~REF_A_CTL0_TCOFF;

       ADC14->CTL0 = ADC14_CTL0_SHT0__96 | ADC14_CTL0_ON | ADC14_CTL0_SHP | ADC14_CTL0_CONSEQ_1; //96 clocks, turn on, and sample and hold mode
       ADC14->CTL1 |= ADC14_CTL1_RES__14BIT; //temp sensor, set resolution: 16 clock cycles

       ADC14->MCTL[0] = ADC14_MCTLN_INCH_14 | ADC14_MCTLN_VRSEL_0;      //X, full range ADG (3.3 to 0v)
       ADC14->MCTL[1] = ADC14_MCTLN_INCH_13 | ADC14_MCTLN_VRSEL_0;      //Y, full range ADG (3.3 to 0v)
       ADC14->MCTL[2] = ADC14_MCTLN_INCH_11 | ADC14_MCTLN_VRSEL_0 | ADC14_MCTLN_EOS;      //Z, full range ADG (3.3 to 0v)



       // need to enable interrupt for conversion of data.
       ADC14->IER0 = ADC14_IER0_IE2; //interrupt for mem[0]

       while(REF_A->CTL0 & REF_A_CTL0_GENBUSY);
       ADC14->CTL0 |= ADC14_CTL0_ENC;
       NVIC_EnableIRQ(ADC14_IRQn); //a flag ADC14IFGx is set when x has a conversion result.

}

void ADC14_IRQHandler(){
    if(ADC14->IFGR0 & ADC14_IFGR0_IFG2){
         X_Accelerometer_ADC = ADC14->MEM[0];
         Y_Accelerometer_ADC = ADC14->MEM[1];
         Z_Accelerometer_ADC = ADC14->MEM[2];
    }

}


