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

/* Baseline devices don't have interrupts. Note that some PIC16's 
 * are baseline devices.  Unfortunately the baseline detection macro is 
 * _PIC12 */
#ifndef _PIC12

void interrupt isr(void)
{
    
    if (PIR3bits.ZCDIF == 1){
        
        if (LATAbits.LATA1==1){
            
            PIR3bits.ZCDIF=0; // bajo la bandera 
            LATAbits.LATA1 = 0 ; 
        }
        else{
            PIR3bits.ZCDIF=0; // bajo la bandera 
            LATAbits.LATA1=1;
            
        }   
    }
    

}
#endif


