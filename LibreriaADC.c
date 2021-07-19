#include <xc.h>
#include <stdint.h>             // TIPOS DE DATOS ESTANDAR Y OTROS.
#define _XTAL_FREQ 4000000
#include <pic16f887.h>
#include "ADC.h"

uint8_t V;
void Recib_ADC(void){
    if(ADIF == 1){                //Verificamos si la bandera del IoCH es 1 
        if(ADCON0bits.CHS == 0){  //Verificamos si el pin esta precionado 
           V = ADRESH;            //Decrementamos el Puerto C cuando se preciona el boton 
        }
        ADIF = 0;                 //Limpiamos la bandera del IoCH
    }
}

void Stard_ADC(void){
    if(ADCON0bits.GO == 0){ 
        __delay_us(50);
         }
         ADCON0bits.GO = 1;
         
}
