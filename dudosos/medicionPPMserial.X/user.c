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
/*char A = 1;
char B = 0;*/
void InitApp(void) {
    /* TODO Initialize User Ports/Peripherals/Project here */
    PORTA = PORTB = PORTC = 0x00;
    LATA = LATB = LATC = 0x00;
    TRISA = 0b00000110;
    TRISB = 0x00;
    TRISC = 0x00;
    /*ADCON1bits.PCFG = 0b1110;*/
    // Input para la transmision
    TRISCbits.RC6 = 0; //Output (TX)
    TRISCbits.RC7 = 1;

    /* Setup analog functionality and port direction */

    /* Initialize peripherals */

    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */
    RCONbits.IPEN=1;
    /* Enable interrupts */
    INTCONbits.GIE = 1; // Interrupciones globales
    INTCONbits.PEIE = 1; // Prioridades perifericas
    INTCONbits.TMR0IE = 1; // Activa la interrupcion de TMR0
    INTCON2bits.TMR0IP = 1; // Interrupcion Timer0 de alta prioridad

    // Configuracion de Timer0
    T0CONbits.TMR0ON = 1; // Timer0 ON
    T0CONbits.T08BIT = 0; // Timer0 16-Bit
    T0CONbits.T0CS = 0; // CLKO
    T0CONbits.T0SE = 0; // Incremento con flancos de subida
    T0CONbits.PSA = 0; // Timer0 prescaler
    T0CONbits.T0PS = 0b111; // Prescaler 256
    /*TMR0 = 46005;*/
    
    
    /* conf de modulo ADC*/
    
    ADCON1bits.PCFG= 0b1100;//AD port conf control bit, pone analogo AN0
                            //Analog Channel Select bits, se selcciona el canal de AD conversion 
    
    ADCON2bits.ADFM=1;// formato del resultado a la derecha
    ADCON2bits.ACQT=0b110;//A/D Acquisition Time Select bits se
    ADCON2bits.ADCS=0b100;//  A/D Conversion Clock Select bits
    ADCON0bits.ADON= 1; //
    PIE1bits.ADIE=1; // interrupcion
    
    //Transmit status and control register
    SPBRG = 129;
    TXSTAbits.BRGH = 1; //High speed to Baud Rate 
    TXSTAbits.SYNC = 0;
    RCSTAbits.SPEN = 1;
    PIE1bits.TXIE = 0;
    TXSTAbits.TXEN = 1; // Transmit enabled 
    TXSTAbits.TX9 = 0; // 8 bits to transmission
    RCSTAbits.CREN = 1; //ENABLES RECEIVER
}

