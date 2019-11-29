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
     TRISAbits.TRISA0=1;
     ANSELAbits.ANSA0=1;
     WPUAbits.WPUA0 = 0;
     ADCON1bits.ADCS=0b011;
     ADCON1bits.ADPREF= 0;
     ADCON1bits.ADNREF = 0;
     ADCON0bits.CHS = 0;
     ADCON0bits.ADON=1;
     
     

    /* Initialize peripherals */
     
    /* Enable interrupts */
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    PIE1bits.ADIE=1;
    
}

