#define _XTAL_FREQ 4000000
#include <stdint.h>
#include <pic16f887.h>
#include "ADC_1C.h"
int POT;
void recib_valoresADC(void){
    if (PIR1bits.ADIF == 1){
     
            POT = ADRESH;
            PIR1bits.ADIF = 0;
    }
    
}
void inicio_conversionADC(void)
{
    if(ADCON0bits.GO == 0)
    {
    __delay_us(50);
    ADCON0bits.GO = 1;
    }
   
}

