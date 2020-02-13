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
    // configuracion de los puertos para la salida de un LED 
    
    LATA=LATB=LATC= 0;
    
    TRISAbits.TRISA0=1;//selecciona A0 como entrada para el AD
     ANSELAbits.ANSA0=1;//selecciona A0 como analogico
     WPUAbits.WPUA0 = 0;
       
     TRISAbits.TRISA1=0;//selecciona A1 como salida cruce por cero(en este caso led de estado))
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
    

    // configuracion de las interrupciones
    // se configuras las propiedades generales de las interrupciones 
    
    //se permite que las configuracion sea global 
    INTCONbits.GIE = 1;
    INTCONbits.PEIE =1; // se activan las ainterrupciones perifericas    
    PIE1bits.ADIE=0; //analogo digital interruption enable on
    INTCONbits.TMR0IE=1;//Timer0 Overflow Interrupt Enable bit, habilita la interruptcion del timer0
    PIE1bits.TXIE= 0;//transmition interrupt
    PIE3bits.ZCDIE = 1; // abilito la interrupcion por cruce por cero 

    // configuraccion de la interrupcion por cruce por cero 
    ZCD1CONbits.ZCD1EN=1 ; //  habilito el puerto y como tal el cruce por cero
    ZCD1CONbits.ZCD1INTN=1; // abilitamos que la interrupcion se a por flanco de bajada 
    ZCD1CONbits.ZCD1POL= 0; // estoy diciendo que no hay inversion en la salida de la corriente 
    ZCD1CONbits.ZCD1OUT=0; // indica que la corriente es de la fuente y no va hacia el sumidero        
    PIR3bits.ZCDIF= 0; // interrupcion pendiente o no pendiente 
        

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

    BAUD1CONbits.BRG16= 0;
    TX1STAbits.BRGH= 1;
    TX1STAbits.SYNC= 0;
    SP1BRG = 25;    
    RC1STAbits.SPEN=1; //habilitacion del serial port
    TX1STAbits.TX9=0;//no habilita 9 bits
    TX1STAbits.TXEN=1; //habilita el trasmitter
    RC1STAbits.CREN=1; // habilitar reception
    PIE1bits.RCIE = 1; //Habilitamos interrupciones recepcion UART//
   
   
     
    
   
   
}

