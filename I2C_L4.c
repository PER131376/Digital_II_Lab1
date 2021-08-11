/*
 * File:   I2C_L3.c
 * Author: acer
 *
 * Created on 10 de agosto de 2021, 10:31 AM
 */


#include <xc.h>
#include "I2C_L4.h"
void I2C_Master_Init(const unsigned long c)
{
    SSPCON = 0b00101000;
    SSPCON2 = 0;
    SSPADD = (_XTAL_FREQ/(4*c))-1;
    SSPSTAT = 0;
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;
}
//*****************************************************************************
// Funciï¿½n de espera: mientras se estï¿½ iniciada una comunicaciï¿½n,
// estï¿½ habilitado una recepciï¿½n, estï¿½ habilitado una parada
// estï¿½ habilitado un reinicio de la comunicaciï¿½n, estï¿½ iniciada
// una comunicaciï¿½n o se este transmitiendo, el IC2 PIC se esperarï¿½
// antes de realizar algï¿½n trabajo
//*****************************************************************************
void I2C_Master_Wait()
{
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F)); 
}
//*****************************************************************************
// Funciï¿½n de inicio de la comunicaciï¿½n I2C PIC
//*****************************************************************************
void I2C_Master_Start()
{
    I2C_Master_Wait();      //espera que se cumplan las condiciones adecuadas
    SSPCON2bits.SEN = 1;    //inicia la comunicaciï¿½n i2c
}
//*****************************************************************************
// Funciï¿½n de reinicio de la comunicaciï¿½n I2C PIC
//*****************************************************************************
void I2C_Master_RepeatedStart()
{
    I2C_Master_Wait();      //espera que se cumplan las condiciones adecuadas
    SSPCON2bits.RSEN = 1;   //reinicia la comunicaciï¿½n i2c
}
//*****************************************************************************
// Funciï¿½n de parada de la comunicaciï¿½n I2C PIC
//*****************************************************************************
void I2C_Master_Stop()
{
    I2C_Master_Wait();      //espera que se cumplan las condiciones adecuadas
    SSPCON2bits.PEN = 1;    //detener la comunicaciï¿½n i2c
}
//*****************************************************************************
//Funciï¿½n de transmisiï¿½n de datos del maestro al esclavo
//esta funciï¿½n devolverï¿½ un 0 si el esclavo a recibido
//el dato
//*****************************************************************************
void I2C_Master_Write(unsigned d)
{
    I2C_Master_Wait();      //espera que se cumplan las condiciones adecuadas
    SSPBUF = d;             
}
//*****************************************************************************
//Funciï¿½n de recepciï¿½n de datos enviados por el esclavo al maestro
//esta funciï¿½n es para leer los datos que estï¿½n en el esclavo
//*****************************************************************************
unsigned short I2C_Master_Read(unsigned short a)
{
    unsigned short temp;
    I2C_Master_Wait();      //espera que se cumplan las condiciones adecuadas
    SSPCON2bits.RCEN = 1; //habilitar modo recepecion I2c
    I2C_Master_Wait();      //espera que se cumplan las condiciones adecuadas
    temp = SSPBUF;      //GUARDAMOS informacion en variable
    I2C_Master_Wait();      //espera que se cumplan las condiciones adecuadas
    if(a == 1){
        SSPCON2bits.ACKDT = 0;
    }
    else
    {
        SSPCON2bits.ACKDT = 1;
    }
    SSPCON2bits.ACKEN = 1;          // Iniciar sequencia de Acknowledge
    return temp;                    // Regresar valor del dato leï¿½do
}
//*****************************************************************************
// Funciï¿½n para inicializar I2C Esclavo
//*****************************************************************************
void I2C_Slave_Init(uint8_t address)
{ 
    SSPADD = address;   //Di
    SSPCON = 0x36;      // 0b00110110
    SSPSTAT = 0x80;     // 0b10000000
    SSPCON2 = 0x01;     // 0b00000001
    TRISC3 = 1;
    TRISC4 = 1;
    GIE = 1;
    PEIE = 1;
    SSPIF = 0;
    SSPIE = 1;
}
//*****************************************************************************
