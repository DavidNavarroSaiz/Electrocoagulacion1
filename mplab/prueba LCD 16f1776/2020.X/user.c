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
    TRISB=0b11111111;//selecciona todo el puerto B como entrada 
    ANSELB=0b111111;//selecciona todo el puerto B como digital(solo se puede cofigurar 6 bits))
    WPUB= 0;// pull up disable
            
    /* Setup analog functionality and port direction */

    /* Initialize peripherals */

    /* Enable interrupts */
}

