/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#define _XTAL_FREQ 20000000
#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif


#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

#include "pruebaLCD.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();
    initLCD();

    while(1)
    {
        lcdWriteMessage("HOLA");
        __delay_ms(500);
        lcdClear();
        __delay_ms(500);
        lcdHome();
        lcdWriteMessage("HI");
         
    }

}

