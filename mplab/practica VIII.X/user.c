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
#include <stdbool.h>
#include <pic18f252.h>        /* For true/false definition */

#endif

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void) {

    PORTA = 0b00;
    PORTB = 0b00;
    PORTC = 0b00;
    TRISAbits.RA0 = 1 ;
    TRISAbits.RA1 = 1 ;
    TRISAbits.RA2 = 1 ;
    TRISAbits.RA3 = 1 ; //
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

    //TIMER 0 muestreo
    T0CONbits.T08BIT = 0; //EL TIMERO ES CONFIGURADO COMO 16-bits COUNTER//
    T0CONbits.T0CS = 0; // RELOJ DE CICLO DE INSTRUCCIÒN INTERNO//
    T0CONbits.T0SE = 0; //LOW TO HIGH TRANSITION//
    T0CONbits.PSA = 0; //SE ASIGNA UN "PRESCALER", LA ENTRADA DEL RELOJ DEL TIMER0 VIENE DE LA SALIDA DEL "PRESCALER"//
    T0CONbits.T0PS = 0b101; //preescarler 1:64
    //SE UTILIZAN PARA TENER EN CUENTA EL OVERFLOW COMO UNA INTERRUPCIÒN//
    INTCON2bits.TMR0IP = 1; //TMR0 OVERFLOW INTERRUPT PRIORITY BIT//
    INTCONbits.TMR0IE = 1; //TMR0 OVERFLOW INTERRUPT ENABLE BIT//
    T0CONbits.TMR0ON = 1; //SE ACTIVA EL TIMER 0//
    TMR0 = 65458; //10 ms  muestreo
    //TIMER 1 visualizacion
    T1CONbits.RD16 = 1; //read /write 16 bits
    T1CONbits.T1CKPS = 0b11; //preescaler 1:8
    T1CONbits.TMR1CS = 0; //timer interno   
    T1CONbits.T1SYNC = 1; //sincronizar con reloj externo
    T1CONbits.TMR1ON = 1; //iniciar timer
    PIE1bits.TMR1IE = 1; //activar interrupciones de overflow
    IPR1bits.TMR1IP = 1; //alta prioridad 
    TMR1 = 3036; //100 ms
    //ledd de estado
    IPR2bits.TMR3IP = 1; // Overflow priority//
    PIE2bits.TMR3IE = 1; //Overflow enable para TMR3//
    T3CONbits.RD16 = 1; //16 bits//
    T3CONbits.TMR3CS = 0; //INTERNO//
    T3CONbits.T3CKPS1 = 1; //PRESCALER DE 1:8//
    T3CONbits.T3CKPS0 = 1; //PRESCALER DE 1:8//
    T3CONbits.TMR3ON = 1; //ACTIVACIÒN TIMER 3//
    TMR3 = 64911;//10 ms


    
    ADCON1bits.ADFM = 1; //justificado a la derecha
    ADCON1bits.ADCS2 = 0 ;
    ADCON0bits.ADCS = 0b10; //32 Fosc   
    ADCON0bits.ADON = 1; //modulo iniciado
    RCONbits.IPEN = 1; //activar prioridades
    INTCONbits.GIE = 1; //ACTIVAR INTERRUPCIONES GLOBALES//
    INTCONbits.PEIE = 1; //ACTIVAR INTERRUPCIONES PERIFERICAS//
    PIR1bits.ADIF = 0; //limpiar la bandera
    IPR1bits.ADIP = 1;
    PIE1bits.ADIE = 1;    
    ADCON1bits.PCFG = 0b0010 ;//AN0 - AN5 Analog inputs   
    for (int i = 0; i < 20; i++) {
        NOP();
    }

}

