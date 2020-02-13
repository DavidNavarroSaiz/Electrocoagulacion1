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
    
    TRISBbits.RB5 = 1 ; //mostrar numero de flanco de subida
    TRISBbits.RB1 = 1 ; //mediciones de frecuencia cada 5 seg
    TRISBbits.RB4 = 1 ; // cambio periodo de led de estado 
   
    TRISCbits.RC0 = 1 ;//señal de entrada
    
    TRISCbits.RC1 = 0 ;//led de salida
    TRISCbits.RC2 = 0 ;//led de salida
    TRISCbits.RC3 = 0 ;//led de salida
    TRISCbits.RC4 = 0 ;//led de salida
    TRISCbits.RC5 = 0 ;//led de salida
    TRISCbits.RC6 = 0 ;//led de salida
    TRISCbits.RC7 = 0 ;//led de salida
    
    TRISBbits.RB2 = 0 ;//led de salida
    TRISBbits.RB0 = 0 ;//led de salida
    TRISBbits.RB6 = 0 ;//led de salida
    TRISBbits.RB7 = 0 ;//led de salida
    TRISAbits.RA0 = 0 ;//led de salida
    TRISAbits.RA1 = 0 ;//led de salida 
    TRISAbits.RA2 = 0 ;//led de salida
    TRISAbits.RA3 = 0 ; //led de salida
    TRISAbits.RA4 = 0 ; //led de salida
    TRISAbits.RA5 = 0 ; //led de estado
         
    TMR1 = 0 ; //inicia en cero
    PORTA= 0 ;
    PORTB= 0 ;
    PORTC = 0 ;
    ADCON1bits.PCFG = 0b0111 ;//entradas digitales
    RCONbits.IPEN = 1 ; // alta prioridades 
    INTCONbits.GIE = 1 ; //globales activadas
    INTCONbits.PEIE = 1 ; //perifericas activadas
    
    INTCON3bits.INT1IP = 1 ;//activar interrupciones externas de alta prioridad
    INTCON3bits.INT1IE = 1 ; //activar interrupciones externas
    INTCON2bits.INTEDG1 = 0 ; //interrupcion por flanco de subida
   
    
    INTCON2bits.RBIP = 1 ; // alta prioridad
    INTCONbits.RBIE = 1 ; //activar RB change RB4 - RB7
        
    INTCONbits.TMR0IE = 1 ;  //activar overflow
    INTCON2bits.TMR0IP = 0 ; //overflow prioridad
    T0CONbits.T08BIT=0; //16 bits
    T0CONbits.T0CS = 0 ; //contador interno
    T0CONbits.T0SE = 0 ; //low to high  transition
    T0CONbits.PSA = 0 ; //utilizamos preescaler 
    T0CONbits.T0PS = 0b0111 ; // escaler 1:256
    TMR0 = 46005 ; //precarga = Timer1 Oscillator is shut-o
     T0CONbits.TMR0ON = 1 ;//activa timer 
   
    T1CONbits.RD16 = 1 ; //16 bits
    T1CONbits.TMR1CS = 1 ; //reloj externo con flanco de subida
    T1CONbits.TMR1ON = 1 ; //timer uno encendido
    
    T1CONbits.T1CKPS0 = 0 ; //  preescaler 1:1
    T1CONbits.T1CKPS1 = 0 ; 
    T1CONbits.T1OSCEN = 0 ; //oscilador descativado 
    PIE1bits.TMR1IE = 0 ;//overflow deactivado
    
    T3CONbits.RD16 = 1 ; //16bits
    T3CONbits.T3CKPS = 0b11 ; // 1:8 preescaler
    T3CONbits.TMR3CS = 0 ; //internal clock
    T3CONbits.TMR3ON = 1 ; //activar timer
    PIE2bits.TMR3IE = 1 ;//activar overflow
    IPR2bits.TMR3IP = 1 ; //overflow prioridad
}
    
    
    
        
    
           
    
    
           
    

