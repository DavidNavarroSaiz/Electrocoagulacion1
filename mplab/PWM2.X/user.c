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
    
    
    /* AD mocdule configuration*/
    ADCON1bits.ADCS=0b011; //ADC Conversion Clock Select bits, selecciona el oscilador interno
    ADCON1bits.ADPREF= 0;//Analog digital positive reference, toma el VDD como referencia
    ADCON1bits.ADNREF = 0; //Analog digital negative reference, toma el VSS como referenicia
    ADCON1bits.ADFM=1; //ADC Result Format Select bit, justificado hacia la derecha
    ADCON0bits.CHS = 0; // channel seleccion, selecciona A0 como canal de entrada
    ADCON0bits.ADON=1; //Analog digital on
    
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
    RC1STAbits.CREN=1; // habilitar reception continua  
}

/*
 Bit 0 TX9D : This is the 9th bit of data in the 9 bit transmission mode which is commonly used as a Parity Bit.
Bit 1 TRMT : This is the Transmit Shift Register (TSR) status bit. This can be used to check whether the data written to transmit register is transmitted or not. When the TRS is empty this bit is set and when the TSR is full this bit will be 0.
Bit 2 BRGH : This is the High Baud Rate Select bit for Asynchronous mode operation and is unused in Synchronous mode. Setting this bit selects High Speed and clearing this bit selects Low Speed baud rates. You will can see the baud rate calculation later in this article.
Bit 3 Unimplemented : This bit is unimplemented and will read as 0.
Bit 4 SYNC : This is the USART Mode select bit. Setting this bit selects Synchronous mode while clearing this bit selects Asynchronous mode.
Bit 5 TXEN : Setting this bit enables the transmission. In the synchronous mode operation CREN and SREN bits of RCSTA register overrides this bit.
Bit 6 TX9 : When this bit is set it enables the 9 bit transmission otherwise 8 bit transmission is used. 9th bit in the 9 bit transmission mode is commonly used as parity bit.
Bit 7 CSRC : Clock Source Select Bit, this bit has no application in the Asynchronous mode operation of USART module. It is used to select master or slave mode in Synchronous mode operation.
 
 
 Bit 0 RX9D : This is the 9th bit of Received Data and is commonly used as Parity Bit.
Bit 1 OERR : Overrun Error bit. A high at this bit indicates that Overrun error has occured.
Bit 2 FERR : Framing Error bit. 1 at this bit stands for Framing Error while 0 stands for No Framing Error.
Bit 3 ADDEN : Address Detect Enable bit. This bit is applicable only in Asynchronous 9 bit mode. Setting this bit enables Address Detect.
Bit 4 CREN : Continuous Receive Enable bit. Setting this bit will enable Continuous Receive. In the Synchronous Mode CREN overrides SREN.
Bit 5 SREN : Single Receive Enable bit. This bit has no effect on Asynchronous mode and Synchronous Slave mode. Setting this bit will enables Single Receive. This bit will cleared after the reception is complete.
Bit 6 RX9 : Setting this bit enables 9 bit reception otherwise it will be in 8 bit reception mode.
Bit 7 SPEN : Serial Port Enable bit. Setting this bit enables serial port and configures RC7, RC6 as serial port pins.
 */