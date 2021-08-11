/*
 * File:   ADC_1Slave.c
 * Author: acer
 *
 * Created on 10 de agosto de 2021, 12:55 PM
 */
#define _XTAL_FREQ 4000000
#include <stdint.h>
#include <pic16f887.h>
#include "ADC_1Slave.h"
uint8_t POT;
uint8_t var2;
void Recib_valoresADC(void)
{
    if (PIR1bits.ADIF == 1)
    {
            POT = ADRESH;
            //PIR1bits.ADIF = 0;
    }
    PIR1bits.ADIF = 0;
}
void Star_conversionADC(void)
{
    if(ADCON0bits.GO == 0)
    {
      
    __delay_us(50);
    ADCON0bits.GO = 1; 
    }
}