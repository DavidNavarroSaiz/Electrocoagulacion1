/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
#include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
#include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */       
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#endif

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"   
/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
char event;
extern int intccp ;
extern int valorccp;
int primeracaptura;
int segundacaptura;
float frecuencia;
int muestreo;
int duty;
float dutycicle;
long x;
int modo1  = 0;

char salida [50];
int led;
int d;
const char saludo[] = "Bienvenido a modulo ccp";
const char norango [] = "la frecuencia no esta en el rango de trabajo";
void ledestado(int tiempoled);
void enviarTrama(char *datos);

void main(void) {
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    /* TODO <INSERT USER APPLICATION CODE HERE> */
    enviarTrama(saludo);

    while (1) {
        if (modo1 == 1 && led == 1){
            ledestado(10);
        }
        else if (modo1 == 0 && led == 1){   
            ledestado(5);
        }
        
        if (muestreo == 1) {
            muestreo = 0;
            PIR2bits.CCP2IF = 0;
            PIE2bits.CCP2IE = 1;
            T3CONbits.TMR3ON = 1;
            intccp = 0 ;
            while (intccp == 0);
            intccp = 0;
            primeracaptura = valorccp;
            while (intccp == 0);
            intccp = 0;
            segundacaptura = valorccp;
            PIE2bits.CCP2IE = 0;
            T3CONbits.TMR3ON = 0;

            frecuencia = segundacaptura - primeracaptura;
            frecuencia = frecuencia / 4;
            frecuencia = frecuencia * 0.2;
            frecuencia = 1000000 / frecuencia;
                   
            duty = 100 * ((frecuencia - 10000) / 10000);          
            dutycicle = duty * 0.0002/100; // 1 / 5000 = 0,0002 s 
            x = dutycicle * 1000000 / 0.2;         
            CCPR1L = ((x & 0b1111111100)>> 2);
            CCP1CONbits.DC1B = (x & 0b0000000011);            
            
            if (frecuencia >= 10000 && frecuencia <= 20000) {
                
                modo1= 1 ;
                sprintf(salida, "frecuencia: %f Hz  ", frecuencia);
                enviarTrama(salida);
            } else {                
                modo1 = 0;
                enviarTrama(norango);
            }
            
        }
        
        
    }

}

void enviarTrama(char *datos) {

    //saludo[0] = *datos:

    while (*datos != 0) {
        TXREG = *datos;
        while (TXSTAbits.TRMT == 0);
        *datos++;
    }

    TXREG = 0x0A;
    while (TXSTAbits.TRMT == 0);
    TXREG = 0x0D;
    while (TXSTAbits.TRMT == 0);

}

void ledestado(int tiempoled) {
    d++;
    if (d >= tiempoled) {        
        LATBbits.LB7 = ~PORTBbits.RB7;
        d = 0;
    }
    led = 0;
}