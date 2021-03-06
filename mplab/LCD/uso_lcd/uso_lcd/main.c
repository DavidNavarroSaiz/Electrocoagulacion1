/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#define _XTAL_FREQ 20000000
#if defined(__XC)
#include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
#include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#endif
#include "LcdDriver.h"

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
/*viable_name>; */
/******************************************************************************/
/* Main Program                                                               */

/******************************************************************************/

void main(void) {

    InitApp();
    initLCD();
    
           
    while (1) {
        lcdWriteMessage("HOLA");
        __delay_ms(500);
        lcdClear();
        __delay_ms(500);
        lcdHome();
        lcdWriteMessage("HI");
    }
}



