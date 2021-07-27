/*
 * File:   ADC_2canales.c
 * Author: acer
 *
 * Created on 22 de julio de 2021, 11:09 AM
 */
#define _XTAL_FREQ 4000000
#include <stdint.h>
#include <pic16f887.h>
#include "ADC.h"
int Pot1 = 0;
int Pot2 = 0;
void Recib_ADC(void){
    if (PIR1bits.ADIF == 1)
    {
        if(ADCON0bits.CHS == 5)
        {
            Pot1 = ADRESH;
        }
        else
        {
            Pot2 = ADRESH;
        }
    }
    PIR1bits.ADIF = 0;
}
void Stard_ADC(void)
{
    if(ADCON0bits.GO == 0)
    {
        if(ADCON0bits.CHS == 5)
        {
            ADCON0bits.CHS = 6;
        }
        else
        {
            ADCON0bits.CHS = 5;
        }
        //__delay_us(50);
    }
    __delay_us(50);
    ADCON0bits.GO = 1;
}
