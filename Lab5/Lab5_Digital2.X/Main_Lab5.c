 /*UNIVERSIDAD DEL VALLE DE GUATEMALA 
 * File:   Lab05.c
 * Author: SELVIN E. PERALTA CIFUENTES
 *
 * Created on 12 de Agosto de 2021, 16:30 PM
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
#include <pic16f887.h>
#include <math.h>
#include <stdlib.h>
#include "UART5.h"
#include <string.h>
uint8_t PC = 0;       /*Declaración variables*/
uint8_t Cont;
int Cm = 0;
float V1;
float V2;
char s[20];
//***********Prototipos de funciones************
void setup(void);           /*funcion principal */
void valorsensores(void);
void configuracionUART(void);
//**************Interrupciones**************
void __interrupt()isr(void) /*interrupciones*/
{
if(RBIF == 1)           //Bandera IOCB
    {
    Cont=PORTD;
        if(RB0 == 0)        //Si boton en RB0 esta presionado
        {
            PORTD++;        //Aumenta contador del PORTA
        }
        if(RB1 == 0)        //Boton en RB1 esta presionado
        {
            PORTD--;        //Decrementa PORTA
        }
    }
    INTCONbits.RBIF = 0;
    
}
//*********************************funcionPrincipal**********
void main(void) {
    setup();                /*funcion de configuracion principal*/
    //*********************************LoopPrincipal*********
    while(1){
       
        if (PIR1bits.RCIF)
        {
            PORTA = RCREG;
            PC = PORTA;
        }
        
        valorsensores();
    }
}
//*************Funciones************************
void setup(void)
{ 
    //*******configuración io entradas y salidas****
    ANSEL = 0x00;
    ANSELH = 0x00;     //Salidas Digitales
    
  
    TRISE = 0x00;  
    TRISA = 0x00;
    TRISB = 0x03;  
    TRISD = 0x00;
    OPTION_REGbits.nRBPU = 0; 
    WPUB = 0b00000011;      //Habilitar Pull interno 
  
    PORTA = 0x00; 
    PORTE = 0x00;
    PORTB = 0x00;
    PORTD = 0x00;
    
    PORTCbits.RC2 = 1;
     //configuración IOC
    IOCBbits. IOCB0 = 1; 
    IOCBbits. IOCB1 = 1;
    //configuración del reloj (oscilador interno)
    OSCCONbits. IRCF2 = 1; 
    OSCCONbits. IRCF1 = 1;
    OSCCONbits. IRCF0 = 0;  //4Mhz
    OSCCONbits. SCS = 1;
    //configuración interrupción
    INTCONbits. GIE = 1;        //Globales
    INTCONbits. RBIE = 1;       //IOCB
    INTCONbits. RBIF = 0;
    INTCONbits.PEIE = 1;        //Perifericas
    PIE1bits.SSPIE = 1;
    PIR1bits.SSPIF = 0;
    
    //*****ConfiguraciónUART TX Y RX ***********
    configuracionUART();
   
}

