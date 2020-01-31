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
    
    TRISAbits.TRISA1 = 0; // se seleciona el puerto como salida
    ANSELAbits.ANSA1= 1; // se seleciona como salida digital 
    WPUAbits.WPUA1 = 0 ; 
    
    // LED de estado
    
    TRISAbits.TRISA2=0;
    ANSELAbits.ANSA1= 1;
    WPUAbits.WPUA2=0; 
    

    // configuracion de las interrupciones
    // se configuras las propiedades generales de las interrupciones 
    
    //se permite que las configuracion sea global 
    INTCONbits.GIE = 1;
    INTCONbits.PEIE =1; // se activan las ainterrupciones perifericas
    
    // configuraccion de la interrupcion por cruce por cero 
    ZCD1CONbits.ZCD1EN=1 ; //  abilito el puerto y como tal el cruce por cero
    ZCD1CONbits.ZCD1INTN=1; // abilitamos que la interrupcion se a por flanco de bajada 
    ZCD1CONbits.ZCD1POL= 0; // estoy diciendo que no hay inversion en la salida de la corriente 
    ZCD1CONbits.ZCD1OUT=0; // indica que la corriente es de la fuente y no va hacia el sumidero 
    
    
    PIE3bits.ZCDIE = 1; // abilito la interrupcion por cruce por cero 
    PIR3bits.ZCDIF= 0; // interrupcion pendiente o no pendiente 
        

   
}

