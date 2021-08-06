/*
 * File:   main.c
 * Author: Pablo
 * Ejemplo de uso de I2C Esclavo
 * Created on 17 de febrero de 2020, 10:32 AM
 */
//*****************************************************************************
// Palabra de configuración
//*****************************************************************************
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
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//*****************************************************************************
// Definición e importación de librerías
//*****************************************************************************
#include <stdint.h>
#include <pic16f887.h>
#include "I2C.h"
#include "ADC_1C.h"
#include <xc.h>
//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 4000000
uint8_t z;
uint8_t dato;
int POT;
//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);
//*****************************************************************************
// Código de Interrupción 
//*****************************************************************************
void __interrupt() isr(void){
   recib_valoresADC();
   if(PIR1bits.SSPIF == 1){ 

        SSPCONbits.CKP = 0;
       
        if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL)){
            z = SSPBUF;                 // Read the previous value to clear the buffer
            SSPCONbits.SSPOV = 0;       // Clear the overflow flag
            SSPCONbits.WCOL = 0;        // Clear the collision bit
            SSPCONbits.CKP = 1;         // Enables SCL (Clock)
        }

        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {
            //__delay_us(7);
            z = SSPBUF;                 // Lectura del SSBUF para limpiar el buffer y la bandera BF
            //__delay_us(2);
            PIR1bits.SSPIF = 0;         // Limpia bandera de interrupción recepción/transmisión SSP
            SSPCONbits.CKP = 1;         // Habilita entrada de pulsos de reloj SCL
            while(!SSPSTATbits.BF);     // Esperar a que la recepción se complete
            PORTD = SSPBUF;             // Guardar en el PORTD el valor del buffer de recepción
            __delay_us(250);
            
        }else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){
            z = SSPBUF;
            BF = 0;
            SSPBUF = POT;
            SSPCONbits.CKP = 1;
            __delay_us(250);
            while(SSPSTATbits.BF);
        }
       
        PIR1bits.SSPIF = 0;    
    }
}
//*****************************************************************************
// Main
//*****************************************************************************
void main(void) {
    setup();
    __delay_us(50);
    ADCON0bits.GO = 1;
    while(1){
       inicio_conversionADC();
    }
    return;
}
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
void setup(void){
    //*******configuración io entradas y salidas****
    ANSEL = 0b01100000;
    ANSELH = 0x00;     //Salidas Digitales
    
    
    TRISE = 0x03;  
    TRISB = 0x00; 
    TRISD = 0x00;    
  
    
    PORTC = 0x00; 
    PORTE = 0x00;
    PORTB = 0x00; 
    PORTD = 0X00;
    
    I2C_Slave_Init(0x50);
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
}