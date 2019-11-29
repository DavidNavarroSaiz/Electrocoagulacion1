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
    /* TODO Initialize User Ports/Peripherals/Project here */

    
    ADCON1bits.PCFG=0b0111; //TODOS LOS PINES DIGITALES//
    
    PORTA=0b00;
    PORTB=0b00;
    PORTC=0b00;
    
    TRISC=0b11000001; //RC0 ES EL PIN DEL TIMER1, RC6 TRANSMITTER PIN, RC7 RECEIVER PIN//
    TRISA=0b0010000; //RA4 ES EL PIN DEL TIMER0 DE IGUAL FORMA NO SE UTLIZA EN ESTA PRACTICA PORQUE ES INTERNO//
    TRISBbits.RB0=0; 
    TRISBbits.RB1=0;
    TRISBbits.RB2=0;
    TRISBbits.RB3=0;
    TRISBbits.RB4=0;
    TRISBbits.RB5=0;
    TRISBbits.RB6=0;
    TRISBbits.RB7=0; //LED DE ESTADO//
    
    
    //CONFIGURACION RB-CHANGE //
    INTCON2bits.RBIP=1; //RB PORT CHANGE PRIORITY//
//    INTCONbits.RBIE=1; //RB PORT CHANGE ACTIVACION//
    
    TRISCbits.RC7=1; // RECEIVER RX INPUT. SE QUIERE ESTE PIN COMO ENTRADA PARA RECEPCIÒN//
    TRISCbits.RC6=0; //TRANSMITTER TX OUTPUT, SE QUIERE ESTE PIN COMO SALIDA PARA TRANSMISIÒN//
    SPBRG=10; //BAUD RATE DE 115200 BITS POR SEGUNDO TEORICAMENTE//
    
    // CONFIGURACIÒN DEL USART ASYNCHRONOUS TRANSMITTER //
    
    RCSTAbits.SPEN=1; //Habilitar UART,ACTIVAR PUERTO SERIAL ASINCRONO //
    TXSTAbits.SYNC=0; // ASYNCHRONOUS MODE//
    TXSTAbits.BRGH=1; //ALTA RESOLUCIÒN, PUEDE AYUDAR A DISMINUIR EL ERROR //
    TXSTAbits.TXEN=1; //Habilitar la transmisiòn//
    
    
    //CONFIGURACIÒN DEL USART ASYNCHRONOUS RECEIVER//
    
    RCSTAbits.CREN=1; 
    RCONbits.IPEN=1;  //ACTIVAR PRIORIDADES//
    INTCONbits.GIE=1; //ACTIVAR INTERRUPCIONES GLOBALES//
    INTCONbits.PEIE=1; //ACTIVAR INTERRUPCIONES PERIFERICAS//
    PIE1bits.RCIE=1; //Habilitamos interrupciones recepcion UART//
    IPR1bits.RCIP=1; //ALTA PRIORIDAD//
    
    
    //CONFIGURACION DEL TIMER 0 PARA CONTADOR DE 1 SEGUNDO//
    
    T0CONbits.T08BIT=0; //EL TIMERO ES CONFIGURADO COMO 16-bits COUNTER//
    T0CONbits.T0CS=0; // RELOJ DE CICLO DE INSTRUCCIÒN INTERNO//
    T0CONbits.T0SE=0; //LOW TO HIGH TRANSITION//
    T0CONbits.PSA=0;    //SE ASIGNA UN "PRESCALER", LA ENTRADA DEL RELOJ DEL TIMER0 VIENE DE LA SALIDA DEL "PRESCALER"//
    T0CONbits.T0PS=0b0111;  //ESTE VALOR SE CAMBIA DEPENDIENDO EL VALOR DE PRESCALER QUE QUERAMOS PAG.105//
    //SE UTILIZAN PARA TENER EN CUENTA EL OVERFLOW COMO UNA INTERRUPCIÒN//
    //TIMER O//
    INTCON2bits.TMR0IP=1;   //TMR0 OVERFLOW INTERRUPT PRIORITY BIT//
    INTCONbits.TMR0IE=1;    //TMR0 OVERFLOW INTERRUPT ENABLE BIT//
    T0CONbits.TMR0ON=1; //SE ACTIVA EL TIMER 0//
    TMR0 = 46005;
    
    //TIMER 1_ DONDE SE LEE LA FRECUENCIA // 
    
    IPR1bits.TMR1IP=0; //OVERFLOW PRIORITY//
    PIE1bits.TMR1IE=0; //OVERFLOW ENABLE//
    T1CONbits.RD16 =1; // 16 BITS//
    T1CONbits.TMR1CS=1; //RELOJ EXTERNO CON FLANCO DE SUBIDA//
    T1CONbits.T1CKPS0=0; //PRESCALER 1:1// 
    T1CONbits.T1CKPS1=0; //PRESCALER 1:1//
    T1CONbits.TMR1ON =1; //ACTIVAR EL TIMER 1/
    TMR1=0; // INICIA EN CERO//
    
    //TIMER3 PARA LED DE ESTADO//
    
    IPR2bits.TMR3IP=1; // Overflow priority//
    PIE2bits.TMR3IE=1; //Overflow enable para TMR3//
    T3CONbits.RD16=1;   //16 bits//
    T3CONbits.TMR3CS=0; //INTERNO//
    T3CONbits.T3CKPS1=1; //PRESCALER DE 1:8//
    T3CONbits.T3CKPS0=1; //PRESCALER DE 1:8//
    T3CONbits.TMR3ON=1; //ACTIVACIÒN TIMER 3//
    TMR3=64911;

    
    
    /* Setup analog functionality and port direction */

    /* Initialize peripherals */

    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */

    /* Enable interrupts */
}

