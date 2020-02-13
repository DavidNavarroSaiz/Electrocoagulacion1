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
#include <stdbool.h>
#include <pic18f252.h>       /* For true/false definition */

#endif

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

/******************************************************************************/
/* User Global Variable Declaration     
 
 * 
 *   
 */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

int sum = 32;

int comp;
/******************************************************************************/
/* Main Program                                                               */

/******************************************************************************/

void main(void) {

    InitApp();


    while (1) {
        LATB = sum;
        while (PORTCbits.RC4 == 1 && PORTCbits.RC5 == 1) {
            NOP();

            comp = PORTA;
            if (comp < sum) {
                LATCbits.LC0 = 1;
                LATCbits.LC1 = 1;
                LATCbits.LC2 = 0;
                LATCbits.LC3 = 0;


                if (sum == 0) {
                    sum = 32;
                }
                sum = sum - 1;
                LATB = sum;

                for (long a = 1; a < 217392; a++) {
                    NOP();
                }

                if (PORTCbits.RC4 != 1 || PORTCbits.RC5 != 1) {
                    continue;
                }

            }
            NOP();
            comp = PORTA;
            if (comp < sum) {
                LATCbits.LC0 = 0;
                LATCbits.LC1 = 1;
                LATCbits.LC2 = 1;
                LATCbits.LC3 = 0;
                if (sum == 0) {
                    sum = 32;
                }
                sum = sum - 1;
                LATB = sum;
                for (long a = 1; a < 217392; a++) {
                    NOP();
                }

                if (PORTCbits.RC4 != 1 || PORTCbits.RC5 != 1) {
                    continue;
                }
            }
            NOP();
            comp = PORTA;
            if (comp < sum) {
                LATCbits.LC0 = 0;
                LATCbits.LC1 = 0;
                LATCbits.LC2 = 1;
                LATCbits.LC3 = 1;
                if (sum == 0) {
                    sum = 32;
                }
                sum = sum - 1;
                LATB = sum;
                for (long a = 1; a < 217392; a++) {
                    NOP();
                }
                if (PORTCbits.RC4 != 1 || PORTCbits.RC5 != 1) {
                    continue;
                }
            }
            comp = PORTA;
            if (comp < sum) {
                LATCbits.LC0 = 1;
                LATCbits.LC1 = 0;
                LATCbits.LC2 = 0;
                LATCbits.LC3 = 1;
                if (sum == 0) {
                    sum = 32;
                }
                sum = sum - 1;
                LATB = sum;
                for (long a = 1; a < 217392; a++) {
                    NOP();
                }
                if (PORTCbits.RC4 != 1 || PORTCbits.RC5 != 1) {
                    continue;
                }
                NOP();
            }

        }

        while (PORTCbits.RC4 == 1 && PORTCbits.RC5 == 0) {
            comp = PORTA;
            if (comp < sum) {
                LATCbits.LC0 = 1;
                LATCbits.LC1 = 0;
                LATCbits.LC2 = 0;
                LATCbits.LC3 = 0;
                if (sum == 0) {
                    sum = 32;
                }
                sum = sum - 1;
                LATB = sum;
                for (long a = 1; a < 217392; a++) {
                    NOP();
                }
                if (PORTCbits.RC4 != 1 || PORTCbits.RC5 != 0) {
                    continue;
                }
            }
            comp = PORTA;
            NOP();
            if (comp < sum) {
                LATCbits.LC0 = 1;
                LATCbits.LC1 = 1;
                LATCbits.LC2 = 0;
                LATCbits.LC3 = 0;
                if (sum == 0) {
                    sum = 32;
                }
                sum = sum - 1;
                LATB = sum;
                for (long a = 1; a < 217392; a++) {
                    NOP();
                }
                if (PORTCbits.RC4 != 1 || PORTCbits.RC5 != 0) {
                    continue;
                }
            }
            comp = PORTA;
            if (comp < sum) {
                LATCbits.LC0 = 0;
                LATCbits.LC1 = 1;
                LATCbits.LC2 = 0;
                LATCbits.LC3 = 0;
                if (sum == 0) {
                    sum = 32;
                }
                sum = sum - 1;
                LATB = sum;
                for (long a = 1; a < 217392; a++) {
                    NOP();
                }

                if (PORTCbits.RC4 != 1 || PORTCbits.RC5 != 0) {
                    continue;
                }
            }
            comp = PORTA;
            if (comp < sum) {
                LATCbits.LC0 = 0;
                LATCbits.LC1 = 1;
                LATCbits.LC2 = 1;
                LATCbits.LC3 = 0;
                if (sum == 0) {
                    sum = 32;
                }
                sum = sum - 1;
                LATB = sum;
                for (long a = 1; a < 217392; a++) {
                    NOP();
                }
                if (PORTCbits.RC4 != 1 || PORTCbits.RC5 != 0) {
                    continue;
                }
            }
            comp = PORTA;
            if (comp < sum) {
                LATCbits.LC0 = 0;
                LATCbits.LC1 = 0;
                LATCbits.LC2 = 1;
                LATCbits.LC3 = 0;
                if (sum == 0) {
                    sum = 32;
                }
                sum = sum - 1;
                LATB = sum;
                for (long a = 1; a < 217392; a++) {
                    NOP();
                }
                if (PORTCbits.RC4 != 1 || PORTCbits.RC5 != 0) {
                    continue;
                }
            }
            comp = PORTA;
            if (comp < sum) {
                LATCbits.LC0 = 0;
                LATCbits.LC1 = 0;
                LATCbits.LC2 = 1;
                LATCbits.LC3 = 1;
                if (sum == 0) {
                    sum = 32;
                }
                sum = sum - 1;
                LATB = sum;
                for (long a = 1; a < 217392; a++) {
                    NOP();
                }
                if (PORTCbits.RC4 != 1 || PORTCbits.RC5 != 0) {
                    continue;
                }
            }
            comp = PORTA;
            if (comp < sum) {

                LATCbits.LC0 = 0;
                LATCbits.LC1 = 0;
                LATCbits.LC2 = 0;
                LATCbits.LC3 = 1;
                if (sum == 0) {
                    sum = 32;
                }
                sum = sum - 1;
                LATB = sum;
                for (long a = 1; a < 217392; a++) {
                    NOP();
                }
                if (PORTCbits.RC4 != 1 || PORTCbits.RC5 != 0) {
                    continue;
                }
            }
            comp = PORTA;
            if (comp < sum) {
                LATCbits.LC0 = 1;
                LATCbits.LC1 = 0;
                LATCbits.LC2 = 0;
                LATCbits.LC3 = 1;
                if (sum == 0) {
                    sum = 32;
                }
                sum = sum - 1;
                LATB = sum;
                for (long a = 1; a < 217392; a++) {
                    NOP();
                }
                if (PORTCbits.RC4 != 1 || PORTCbits.RC5 != 0) {
                    continue;
                }
            }
        }


        while (PORTCbits.RC4 == 0 && PORTCbits.RC5 == 1) {
            comp = PORTA;
            if (comp < sum) {
                LATCbits.LC0 = 1;
                LATCbits.LC1 = 0;
                LATCbits.LC2 = 0;
                LATCbits.LC3 = 0;
                if (sum == 0) {
                    sum = 32;
                }
                sum = sum - 1;
                LATB = sum;
                for (long a = 1; a < 217392; a++) {
                    NOP();
                }
                if (PORTCbits.RC4 != 0 || PORTCbits.RC5 != 1) {
                    continue;
                }
            }
            comp = PORTA;
            if (comp < sum) {
                LATCbits.LC0 = 0;
                LATCbits.LC1 = 1;
                LATCbits.LC2 = 0;
                LATCbits.LC3 = 0;
                if (sum == 0) {
                    sum = 32;
                }
                sum = sum - 1;
                LATB = sum;
                for (long a = 1; a < 217392; a++) {
                    NOP();
                }
                if (PORTCbits.RC4 != 0 || PORTCbits.RC5 != 1) {
                    continue;
                }
            }
            comp = PORTA;
            if (comp < sum) {
                LATCbits.LC0 = 0;
                LATCbits.LC1 = 0;
                LATCbits.LC2 = 1;
                LATCbits.LC3 = 0;
                if (sum == 0) {
                    sum = 32;
                }
                sum = sum - 1;
                LATB = sum;
                for (long a = 1; a < 217392; a++) {
                    NOP();
                }
                if (PORTCbits.RC4 != 0 || PORTCbits.RC5 != 1) {
                    continue;
                }
            }
            comp = PORTA;
            if (comp < sum) {
                LATCbits.LC0 = 0;
                LATCbits.LC1 = 0;
                LATCbits.LC2 = 0;
                LATCbits.LC3 = 1;
                if (sum == 0) {
                    sum = 32;
                }
                sum = sum - 1;
                LATB = sum;
                for (long a = 1; a < 217392; a++) {
                    NOP();
                }
                if (PORTCbits.RC4 != 0 || PORTCbits.RC5 != 1) {
                    continue;

                }
            }
        }
    }

}