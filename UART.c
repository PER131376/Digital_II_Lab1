/*
 * File:   ADC_2canales.c
 * Author: acer
 *
 * Created on 22 de julio de 2021, 11:09 AM
 */
#define _XTAL_FREQ 4000000
#include <stdint.h>
#include <pic16f887.h>
#include "UART.h"

uint8_t cont = 0;
char op;
int Pot1;
int Pot2;
float Sen1;
float Sen2;
int Sen3;
char s[20];


void Sent_caracter(char caracter){
    while(!TXIF);       //Espera que envie dato TXIF = 1 siempre
    TXREG = caracter;   //Carga el caracter a TXREG y envía 
    return; 
}
void Cadena_caracteres(char st[]){
    int i = 0;          //i igual 0 posicion 
    while (st[i] !=0)   //revisar la posicion de valor de i 
    {
        Sent_caracter(st[i]); //enviar caracter de esa posicion 
        i++;                //incrementar variable para pasar a otra posicion 
    }                       //de cadena 
    return;
}

void Sensores(void){
    sprintf(s, "\r ValorS1=%d \n", Pot1);
    Cadena_caracteres(s);
    
    sprintf(s, "\n ValorS2=%d", Pot2);
    Cadena_caracteres(s);
    
    sprintf(s, "\n ValorS3=%d", cont);
    Cadena_caracteres(s);
}

