/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    //TIMER 1 led estado
    T1CONbits.RD16 = 1; //read /write 16 bits
    T1CONbits.T1CKPS = 0b11; //preescaler 1:8
    T1CONbits.TMR1CS = 0; //timer interno   
    T1CONbits.T1SYNC = 1; //sincronizar con reloj externo
    T1CONbits.TMR1ON = 1; //iniciar timer
    PIE1bits.TMR1IE = 1; //activar interrupciones de overflow
    IPR1bits.TMR1IP = 1; //alta prioridad 
    TMR1 = 3036; //100 ms
    
   // Timer 3 ++ CCP2
    T3CONbits.T3CCP2 = 0b01 ; //timer  para captura de ccp2
    T3CONbits.T3CKPS = 0b00 ; //preescaler 1:1 
    T3CONbits.TMR3CS = 0 ; //como temporizador
    T3CONbits.TMR3ON = 0 ;//apagamos timer
    PIE2bits.TMR3IE = 0 ; //deshabilitamos las interrupciones
    ADCON1bits.PCFG = 0b110 ; //todos los puertos digitales
    TRISB = 0 ;
    TRISBbits.RB3 = 1 ; // ccpp2 captura
    CCP2CONbits.CCP2M = 0b0110 ; //modo captura cada 4 flancos de subida 
    RCONbits.IPEN = 1 ;//activamos prioridades
    INTCONbits.GIE = 1 ;
    INTCONbits.PEIE = 1 ;
    PIE2bits.CCP2IE = 0 ; //deshabilitar interrupciones
    IPR2bits.CCP2IP = 1 ;//alta prioridad
    
    //pwm
    
    T2CONbits.TOUTPS = 0b000 ; //
    T2CONbits.T2CKPS = 0b01 ;//
    PIE1bits.TMR2IE =0 ; //deshabilitamos int
    PR2 = 250 ;//con 20 MHz , 1:4 , frecuencia de pwm de 5KHz
    //x = 225 en binario es 0011100001 
//    CCPR1L =0b0011100;
    //CCP1CONbits.DC1B = 0b01 ; //duty 45 %        ojo        ojo             ojoj    ojo     ojo             ojo
    TRISCbits.RC2 = 0 ; //salida del ccp1 PWM
    CCP1CONbits.CCP1M = 0b1111 ; //modo PWM
    T2CONbits.TMR2ON = 1 ;
    
    
    
    
    //TIMER 0 muestreo frecuencia
    T0CONbits.T08BIT = 0; //EL TIMERO ES CONFIGURADO COMO 16-bits COUNTER//
    T0CONbits.T0CS = 0; // RELOJ DE CICLO DE INSTRUCCIÒN INTERNO//
    T0CONbits.T0SE = 0; //LOW TO HIGH TRANSITION//
    T0CONbits.PSA = 0; //SE ASIGNA UN "PRESCALER", LA ENTRADA DEL RELOJ DEL TIMER0 VIENE DE LA SALIDA DEL "PRESCALER"//
    T0CONbits.T0PS = 0b101; //preescarler 1:64
    //SE UTILIZAN PARA TENER EN CUENTA EL OVERFLOW COMO UNA INTERRUPCIÒN//
    INTCON2bits.TMR0IP = 1; //TMR0 OVERFLOW INTERRUPT PRIORITY BIT//
    INTCONbits.TMR0IE = 1; //TMR0 OVERFLOW INTERRUPT ENABLE BIT//
    T0CONbits.TMR0ON = 1; //SE ACTIVA EL TIMER 0//
    TMR0 = 26473; //500 ms  muestreo
    
    
    
    TRISBbits.RB7 = 0; //LED DE ESTADO//
    TRISCbits.RC7 = 1; // RECEIVER RX INPUT. SE QUIERE ESTE PIN COMO ENTRADA PARA RECEPCIÒN//
    TRISCbits.RC6 = 0; //TRANSMITTER TX OUTPUT, SE QUIERE ESTE PIN COMO SALIDA PARA TRANSMISIÒN//
    SPBRG = 10; //BAUD RATE DE 115200 BITS POR SEGUNDO TEORICAMENTE//
    RCSTAbits.SPEN = 1; //Habilitar UART,ACTIVAR PUERTO SERIAL ASINCRONO //
    TXSTAbits.SYNC = 0; // ASYNCHRONOUS MODE//
    TXSTAbits.BRGH = 1; //ALTA RESOLUCIÒN, PUEDE AYUDAR A DISMINUIR EL ERROR //
    TXSTAbits.TXEN = 1; //Habilitar la transmisiòn//
    RCSTAbits.CREN = 1;
    PIE1bits.RCIE = 1; //Habilitamos interrupciones recepcion UART//
    IPR1bits.RCIP = 1; //ALTA PRIORIDAD//
   
    
    
    
    
}

