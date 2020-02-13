/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/
int AD_almacenado;
int band_aux;
int led;
const char mensaje [] = "valor temp en C:" ;
int i ;
extern char salida [25];
/* Baseline devices don't have interrupts. Note that some PIC16's 
 * are baseline devices.  Unfortunately the baseline detection macro is 
 * _PIC12 */
#ifndef _PIC12
void enviarTrama(char *datos);

void interrupt isr(void)
{
    /* This code stub shows general interrupt handling.  Note that these
    conditional statements are not handled within 3 seperate if blocks.
    Do not use a seperate if block for each interrupt flag to avoid run
    time errors. */
   
    
    /* TODO Add interrupt routine code here. */
     if (INTCONbits.TMR0IF==1){  
         
         INTCONbits.TMR0IF=0; //baja la bandera del timer0
         led= led+1;
//         ADCON0bits.GO= 0; //Inicia la conversion AD
         band_aux= 1;
         
         
              
            }
    /* Determine which flag generated the interrupt */
//     if (PIR1bits.ADIF==1){
////        AD_almacenado= ADRES;
//        PIR1bits.ADIF=0;
     
     
     }
    
#endif


//}


void enviarTrama(char *datos) {

    //saludo[0] = *datos:

    while (*datos != 0) {
        TX1REG = *datos;
        while (TXSTAbits.TRMT == 0);
        *datos++;
    }

    TX1REG = 0x0A;
    while (TXSTAbits.TRMT == 0);
    TX1REG = 0x0D;
    while (TXSTAbits.TRMT == 0);
}
