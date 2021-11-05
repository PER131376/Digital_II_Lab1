//**************************************************************************************************************
/**
 * Universidad del Valle de Guatemala
 * Digital No.2
 * Selvin Peralta Cifuentes
 * Laboratorio No.9
 */
//**************************************************************************************************************
// Librerias
//**************************************************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
//*****

/**
 * main.c
 */
#define XTAL 1600000
//**************************************
// Variables Globales
//**************************************
void initGPIOF (void);
unsigned char letra;
uint8_t bandera;
uint8_t bandera1;
uint8_t cont;
uint8_t Push;

//**************************************
// Código Principal
//**************************************
void Timer0Config(void);
int main(void){

    // Configuración del oscilador externo, usando PLL y teniendo una frecuencia de 40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ); // Reloj de 40MHz
    initGPIOF();

    Timer0Config(); // Configuracion del TIMER 0 //
    // Se habilita el reloj para el puerto F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    // Se establecen como salidas el puerto F
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
    GPIO_PORTF_CR_R = 0x0f;
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);


    while (1){
        Push = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);
        if(Push == 0)
             {
                 bandera1 = 1;
             }else{
                 bandera1 = 0;
             }

        if(cont > 3 & bandera1 == 1 ){
             cont = 0;
           }
    }
}

void Timer0Config(void){

    uint32_t ui32Period;
    // Se habilita el reloj para el temporizador
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0))
    {
    }
    // Configuración del Timer 0 como temporizador períodico
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

    // Se calcula el período para el temporizador (0.5 seg)
    ui32Period = ( SysCtlClockGet() ) / 4;
    // Establecer el periodo del temporizador
    TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period - 1);

    // Se habilita la interrupción por el TIMER0A
    IntEnable(INT_TIMER0A);   // Configuro las interrupciones
    // Se establece que exista la interrupción por Timeout
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);  // Configuro las interrupciones
    // Se habilitan las interrupciones Globales
    IntMasterEnable();   // Configuro las interrupciones
    // Se habilita el Timer
    TimerEnable(TIMER0_BASE, TIMER_A); // timers.
}

//***Interrupcion de TIMER 0******
void Timer0IntHandler(void){
    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);


        if(cont == 0)
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
        }
        else
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
        }
        if(cont == 1)
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
        }
        else
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
        }
        if(cont == 2)
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
        }
        else
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
        }
        cont = cont+1;
    }


//****INICIALIZA PUERTO F Y LEDS OUTPUTS-------------------
void initGPIOF (void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

}
