/*UNIVERSIDAD DEL VALLE DE GUATEMALA 
 * File:   Lab03Digital2.c
 * Author: SELVIN E.PERALTA CIFUENTES
 *
 * Created on 29 de julio de 2021, 18:00 PM
 */
//Configuración PIC16F887
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)
// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Progra
//****DirectivasCompliador*****//
#define _XTAL_FREQ 4000000
//*****IMPORTACION DE LIBRERIAS******
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pic16f887.h>
#include <string.h>
#include "converADC3.h"      //Importar libreria creada para ADC 
#include "SPI_Slave3.h"
int POT1;
uint8_t POT2;
int Cs = 0;
uint8_t v1;
char string[15];
//***********Prototipos de funciones************
void setup(void);           /*funcion principal */
void parametros(void); 
//**************Interrupciones**************
void __interrupt()isr(void) /*interrupciones*/
{
    recibir_valoresADC();   //Funcion de libreria_Reibe valores del Adresh
    if(PIR1bits.SSPIF == 1)
    {
        v1 = spiRead();
        if (Cs == 0)
        {
            spiWrite(POT1);
            Cs = 1;
        }
        else
        {
            spiWrite(POT2);
            Cs = 0;
        }
    }
    PIR1bits.SSPIF = 0;
}
//*********************************funcionPrincipal**********
void main(void) {
    setup();                /*funcion de configuracion principal*/
    __delay_us(50);
    ADCON0bits.GO = 1;
    //*********************************LoopPrincipal*********
    while(1)
    {
        inicio_conversionADC();     //Funcion de libreria
    }
}
//*************Funciones************************
void setup(void)
{ 
    //*******configuración io entradas y salidas****
    ANSEL = 0b01100000;
    ANSELH = 0x00;     //Salidas Digitales
    
    TRISE = 0x03; 
    TRISC = 0x00;  
    TRISB = 0x00; 
    TRISD = 0x00;    
    //OPTION_REGbits.nRBPU = 0; 
    //WPUB = 0b00000011;      //Habilitar Pull interno 
    
    PORTC = 0x00; 
    PORTE = 0x00;
    PORTB = 0x00; 
    PORTD = 0X00;
    //configuración del reloj (oscilador interno)
    OSCCONbits. IRCF2 = 1; 
    OSCCONbits. IRCF1 = 1;
    OSCCONbits. IRCF0 = 0;  //4Mhz
    OSCCONbits. SCS = 1;
    
    //CONFIGURACIOS ADC
    ADCON1bits.ADFM = 0;        //justificado a la izquierda 
    ADCON1bits.VCFG0 = 0;       //Voltaje VDD referencia
    ADCON1bits.VCFG1 = 0;       //Voltaje Vss referencia
    
    ADCON0bits.ADCS0 = 1;        //ADC Clock FOSC = 8Mhz/32
    ADCON0bits.ADCS1 = 0;
    ADCON0bits.CHS = 5;         //Canal 5
    __delay_us(100);
    ADCON0bits.ADON = 1;        //Habiliar Modulo de ADC
    //configuración interrupción
    INTCONbits. GIE = 1;        //Globales
    INTCONbits.PEIE = 1;        //Perifericas
    PIE1bits.ADIE = 1;          //ADC
    PIR1bits.ADIF = 0;
    PIE1bits.SSPIE = 1;
    PIR1bits.SSPIF = 0;
    TRISAbits.TRISA5 = 1;       //Slave select
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
}
void parametros(void)
{
    sprintf (string,"%d", POT1);
}