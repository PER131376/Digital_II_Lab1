#define _XTAL_FREQ 4000000
#include <stdint.h>
#include <pic16f887.h>
#include "converADC3.h"
int POT1;
uint8_t POT2;
void recibir_valoresADC(void)
{
    if (PIR1bits.ADIF == 1)
    {
        if(ADCON0bits.CHS == 5)
        {
            POT1 = ADRESH;
        }
        if(ADCON0bits.CHS == 6)
        {
            POT2 = ADRESH;
        }
    }
    PIR1bits.ADIF = 0;
}
void inicio_conversionADC(void)
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
