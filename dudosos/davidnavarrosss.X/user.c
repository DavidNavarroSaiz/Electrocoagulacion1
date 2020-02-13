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
#include <stdbool.h>        /* For true/false definition */

#endif

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void) {
    /* TODO Initialize User Ports/Peripherals/Project here */
    TRISA = 0b0011111;
    TRISB = 0b11100000;
    TRISC = 0b10110000;
    LATA = 0;
    LATB = 0;
    LATC = 0;
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    /* Setup analog functionality and port direction */
    ADCON1bits.PCFG = 0b0111;
    /* Initialize peripherals */

    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */

    /* Enable interrupts */
}

