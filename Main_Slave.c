/* UNIVERSIDAD DEL VALLE DE GUATEMALA
 * File:   main_Slave.c
 * Author: SELVIN ESTUARDO PERALTA CIFUENTES
 *
 * Created on 8 de agosto de 2021, 12:56 PM
 */
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
// D
//*****************************************************************************
#include <stdint.h>
#include <pic16f887.h>
#include "ADC_1Slave.h"
#include "I2C_Slave1.h"
#include <xc.h>
//*****************************************************************************
// Definiciï¿½n de variables
//*****************************************************************************
#define _XTAL_FREQ 4000000
uint8_t z;
uint8_t dato;
uint8_t POT;
//*****************************************************************************
// Definiciï¿½n de funciones para que se puedan colocar despuï¿½s del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);
//*****************************************************************************
// 
//*****************************************************************************
void __interrupt() isr(void)
{
    Recib_valoresADC();
    PORTB = POT;
    if(PIR1bits.SSPIF){ 

        SSPCONbits.CKP = 0; //reloj bajo configuracion datos
       
        if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL)){
            z = SSPBUF;                 // Read the previous value to clear the buffer
            SSPCONbits.SSPOV = 0;       // Clear the overflow flag
            SSPCONbits.WCOL = 0;        // Clear the collision bit
            SSPCONbits.CKP = 1;         // Enables SCL (Clock)
        }

        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) { //recepcion de datos
            //__delay_us(7);
            z = SSPBUF;                 // Lectura del SSBUF para limpiar el buffer y la bandera BF
            //__delay_us(2);
            PIR1bits.SSPIF = 0;         // Limpia bandera de inte SSP
            SSPCONbits.CKP = 1;         // Habilita entrada de pulsos de reloj SCL
            while(!SSPSTATbits.BF);     // Esperar a que la recepciï¿½n se complete
            PORTD = SSPBUF;             // Guardar en el PORTD el valor del buffer de recepc
            __delay_us(250);
            
        }else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){ //Env de datos
            z = SSPBUF;
            SSPSTATbits.BF = 0;
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
/********LoopPrincipal********/
    while(1)
    {
        Star_conversionADC();
    }
    return;
}
//*****************************************************************************
//*****************************************************************************
void setup(void){
    //*******cio entradas y salidas****
    ANSEL = 0b00100000;
    ANSELH = 0x00;     //Salidas Digitales
    
    TRISE = 0x01;
    
    TRISB = 0;
    TRISD = 0;
    
    PORTE = 0x00;
    PORTB = 0;
    PORTD = 0;
    I2C_Slave_Init(0x50);   //definimos direccion de Slave (7 bits msb)
    //configuracin del reloj (oscilador interno)
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
    //configura
    INTCONbits. GIE = 1;        //Globales
    INTCONbits.PEIE = 1;        //Perifericas
    PIE1bits.SSPIE = 1;
    PIR1bits.SSPIF = 0;
    PIE1bits.ADIE = 1;          //ADC
    PIR1bits.ADIF = 0;
    
}
