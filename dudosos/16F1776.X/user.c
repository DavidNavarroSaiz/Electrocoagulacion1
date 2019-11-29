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
#include <stdbool.h>
#include <pic16f1776.h>        /* For true/false definition */

#endif

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */
    LATA=LATB=LATC=0x00;

    /* Setup analog functionality and port direction */
    TRISAbits.TRISA0=0;
    ANSELA=0x00;

    /* Initialize peripherals */

    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    
    

    /* Enable interrupts */
    
    //MODULO TIMMER0
    
    
    OPTION_REGbits.PSA=0;//NO HAY PRESCALER
    OPTION_REGbits.T0CS=0;
    OPTION_REGbits.PS=3;
    INTCONbits.TMR0IE=1;
}

