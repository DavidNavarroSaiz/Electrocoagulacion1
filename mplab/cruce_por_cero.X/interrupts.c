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
extern int led;
/* Baseline devices don't have interrupts. Note that some PIC16's 
 * are baseline devices.  Unfortunately the baseline detection macro is 
 * _PIC12 */
#ifndef _PIC12

void interrupt isr(void)
{
    //Zero Cross detection
    if (PIR3bits.ZCDIF == 1){
        
        if (LATAbits.LATA1==1){
            
            PIR3bits.ZCDIF=0; // bajo la bandera 
//            LATAbits.LATA1 = 0 ; 
        }
        else{
            PIR3bits.ZCDIF=0; // bajo la bandera 
//            LATAbits.LATA1=1;
            
        }   
    }
    
    // TMR0 OVERFLOW
    if (INTCONbits.TMR0IF==1){  
         
         INTCONbits.TMR0IF=0; //baja la bandera del timer0
         led= led+1;
//         ADCON0bits.GO= 0; //Inicia la conversion AD
                       
            }
    
    // AD Converter
//     if (PIR1bits.ADIF==1){
////        AD_almacenado= ADRES;
//        PIR1bits.ADIF=0;
     
     
//     }


}
#endif


