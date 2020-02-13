/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

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

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
int a = 0;
int b = 0;
int c = 0;
int f = 0;
int h = 0;
int d = 0;
int g = 0;
int i= 0;
int k =0 ;
int r = 0;
int m = 0 ;
int j = 0 ;
void main(void) {
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    /* TODO <INSERT USER APPLICATION CODE HERE> */

    while (1) {
        if (a == 1 && b ==0 && c % 2 == 0) {
            
            NOP() ;
            LATC = (TMR1) << 1;
            LATBbits.LB2 = TMR1 >> 7;
            LATBbits.LB0 = TMR1 >> 8;
            LATBbits.LB6 = TMR1 >> 9;
            LATBbits.LB7 = TMR1 >> 10;
            LATAbits.LA0 = TMR1 >> 11;
            LATAbits.LA1 = TMR1 >> 12;
            LATAbits.LA2 = TMR1 >> 13;
            LATAbits.LA3 = TMR1 >> 14;
            LATAbits.LA4 = TMR1 >> 15 ;
            TMR1= 0 ;
            
            a = 0;
            NOP() ;


        }
        if (b == 1) {
            NOP();
            LATC = (TMR1) << 1;
            LATBbits.LB2 = TMR1 >> 7;
            LATBbits.LB0 = TMR1 >> 8;
            LATBbits.LB6 = TMR1 >> 9;
            LATBbits.LB7 = TMR1 >> 10;
            LATAbits.LA0 = TMR1 >> 11;
            LATAbits.LA1 = TMR1 >> 12;
            LATAbits.LA2 = TMR1 >> 13;
            LATAbits.LA3 = TMR1 >> 14;
            LATAbits.LA4 = TMR1 >> 15;
            

        }


        if (a == 1 && b ==0 && c % 2 != 0) {
            h++;
            if (h == 5) {
                NOP();
                LATC = (TMR1 / 5) << 1;
                LATBbits.LB2 = (TMR1 / 5) >> 7;
                LATBbits.LB0 = (TMR1 / 5) >> 8;
                LATBbits.LB6 = (TMR1 / 5) >> 9;
                LATBbits.LB7 = (TMR1 / 5) >> 10;
                LATAbits.LA0 = (TMR1 / 5) >> 11;
                LATAbits.LA1 = (TMR1 / 5) >> 12;
                LATAbits.LA2 = (TMR1 / 5) >> 13;
                LATAbits.LA3 = (TMR1 / 5) >> 14;
                LATAbits.LA4 = (TMR1 / 5) >> 15;
                h = 0;
            }
            a = 0;
        }



        if (j == 1 && f == 0 && g == 0) {
            d++ ;
            if (d == 7390) {
            NOP();
            LATAbits.LA5 = ~PORTAbits.RA5 ;
            d = 0;
            }
            j = 0 ;
        }
    
    
        if (f == 1 && j == 1){
            k++ ;
            NOP();
            if (k == 1240){
                NOP();
                LATAbits.LA5 = ~PORTAbits.RA5 ;
                k = 0 ;
            }
            
            j = 0 ;
            }
        if (g == 1  && j == 1){
            r++ ;
            NOP();
            if (r ==11870) {  
                NOP();
                LATAbits.LA5 = ~PORTAbits.RA5 ;
                r = 0 ;
            }
            
            j = 0 ;
               }
        }
    }








