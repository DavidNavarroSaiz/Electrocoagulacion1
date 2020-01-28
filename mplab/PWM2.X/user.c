/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */
    LATA=LATB=LATC= 0;
    /* Setup analog functionality and port direction */
     TRISAbits.TRISA0=1;//selecciona A0 como entrada para el AD
     ANSELAbits.ANSA0=1;//selecciona A0 como analogico
     WPUAbits.WPUA0 = 0;
     
     //led para el timer0
     TRISAbits.TRISA1=0;//selecciona A1 como salida para el led del TMR0
     ANSELAbits.ANSA1=1;//selecciona A2 como I/O digital
     WPUAbits.WPUA1=0; 
     
     //configuracion para el RX, input
     TRISCbits.TRISC7=1;
     ANSELCbits.ANSC7=0;
     WPUCbits.WPUC7=0;
     RXPPS=010111; //010 PUERTO C, 111 PORT C7
             
     //configuracion para TX, output
     TRISCbits.TRISC6=0;
     ANSELCbits.ANSC6=0;
     WPUCbits.WPUC6 = 0;
     RC6PPS= 100100; 
     /* Initialize peripherals */
     
    /* Enable interrupts */
    INTCONbits.GIE=1;//global interruption enable
    INTCONbits.PEIE=1;//Peripheral Interrupt Enable bit, 
    PIE1bits.ADIE=1; //analogo digital interruption enable on
    INTCONbits.TMR0IE=1;//Timer0 Overflow Interrupt Enable bit, habilita la interruptcion del timer0
    PIE1bits.TXIE= 1;//transmition interrupt
    
    /* AD mocdule configuration*/
    ADCON1bits.ADCS=0b011; //ADC Conversion Clock Select bits, selecciona el oscilador interno
    ADCON1bits.ADPREF= 0;//Analog digital positive reference, toma el VDD como referencia
    ADCON1bits.ADNREF = 0; //Analog digital negative reference, toma el VSS como referenicia
    ADCON1bits.ADFM=1; //ADC Result Format Select bit, justificado hacia la derecha
    ADCON0bits.CHS = 0; // channel seleccion, selecciona A0 como canal de entrada
    ADCON0bits.ADON=0; //Analog digital on
    
    /* TIMER0 module configuracion */
    OPTION_REGbits.PSA=0;//Prescaler Assignment bit, 0 se utiliza un preescaler,  
    OPTION_REGbits.T0CS=0;//Timer0 Clock Source Select bit, Internal instruction cycle clock (FOSC/4)
    OPTION_REGbits.PS=101; //Prescaler 1:64
    
    /*configuracion EUSART ASYNCHRONOUS*/
    //habilitacion  del trasmitter
    //primero: configuracion del Baud Rate generator
    BAUD1CONbits.BRG16= 0;
    TX1STAbits.BRGH= 0;
    TX1STAbits.SYNC= 0;
    SP1BRG = 25;
    
    RC1STAbits.SPEN=1; //habilitacion del serial port
    TX1STAbits.TX9=0;//no habilita 9 bits
    TX1STAbits.TXEN=1; //habilita el trasmitter
    
    //habilitacion  del receiver
    RC1STAbits.CREN=1; // habilitar reception
}

