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
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#endif

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

extern char comando[22];
extern int nf;
extern int n;
extern int umbral[6];
extern int unSegundo;
int cont;
int cont1;
int comparacion;
long frecuenciaMedida;
int salida [6];
int i;
int segundos;
int fm;
int posicion10;
int ret = 1000;
int retf;
int retu;
int retp;
char *ptr;
int a = 0;
int b = 0;
int c = 0;
long d = 0;
long e = 0;
int g = 0;
int h = 0;
int enter = 0;
char str1[10], str2[16], str3[5], str4[22];
char mode;



/******************************************************************************/
/* Main Program                                                               */

/******************************************************************************/

void main(void) {
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    /* TODO <INSERT USER APPLICATION CODE HERE> */

    while (1) {

        strcpy(str1, "FRECUENCIA");
        strcpy(str2, "UMBRALFRECUENCIA");
        strcpy(str3, "PULSOS");
        strcpy(str4, "Comando no reconocido\n\r");
        retf = strcmp(comando, str1);
        retu = strcmp(comando, str2);
        retp = strcmp(comando, str3);

        if (retf != 0 && retu != 0 && retp != 0 && enter == 1) { //?Comando no reconocido?.                  
            for (i = 0; i < 22; i++) {
                TXREG = str4[i];
                NOP();
                while (TXSTAbits.TRMT == 0);
            }
        }


        if (retf == 0) { //Si me llegò la palabra FRECUENCIA  //
            mode = 1;
        } else if (retu == 0) { //umbral de frecuencia
            mode = 2;
        } else if (retp == 0) { //mostrar numero de pulsos
            mode = 3;
        }
        NOP();

        if (b == 1 && c == 0) {
            d++;

            if (d == 2500) {
                NOP();
                h = PORTBbits.RB7;
                LATBbits.LB7 = ~h;
                d = 0;
                NOP();
            }

            b = 0;
        }
        if (b == 1 && c == 1) {
            e++;
            if (e == 1000) {
                LATBbits.LB7 = ~PORTBbits.RB7;
                e = 0;
            }
            b = 0;
        }
        if (g != 1 && unSegundo == 1) {
            segundos++;
            NOP();
            if (segundos == 1) {
                NOP();
                frecuenciaMedida = TMR1 / segundos;
                if (frecuenciaMedida < ret) {
                    NOP();
                    sprintf(salida, "%d\n\r", frecuenciaMedida);

                    for (i = 0; i < 8; i++) {
                        TXREG = salida[i];
                        while (TXSTAbits.TRMT == 0);

                    }
                    unSegundo = 0;
                }
            }
            segundos = 0;
        }

        if (enter == 1) {
            retf = strcmp(comando, str1);
            retu = strcmp(comando, str2);
            retp = strcmp(comando, str3); //SI SE PRESIONA LA TECLA ENTER// 
            if (retf == 0) { //Si me llegò la palabra FRECUENCIA  //
            mode = 1;
        } else if (retu == 0) { //umbral de frecuencia
            mode = 2;
        } else if (retp == 0) { //mostrar numero de pulsos
            mode = 3;
        }
            if (mode == 1) {
                c = 0;
                g = 1;
                NOP();
                if (comando[10] == '1' && unSegundo == 1) {


                    segundos++;
                    NOP();
                    if (segundos == 1) {
                        NOP();
                        frecuenciaMedida = TMR1 / segundos;
                        if (frecuenciaMedida < ret) {

                            sprintf(salida, "%d\n\r", frecuenciaMedida);

                            for (i = 0; i < 8; i++) {
                                TXREG = salida[i];
                                while (TXSTAbits.TRMT == 0);

                            }
                            unSegundo = 0;
                        }
                    }
                    segundos = 0;
                }

                if (comando[10] == '2' && unSegundo == 1) {
                    segundos++;
                    if (segundos == 2) {
                        frecuenciaMedida = TMR1 / segundos;
                        if (frecuenciaMedida < ret) {
                            sprintf(salida, "%d\n\r", frecuenciaMedida);

                            for (i = 0; i < 8; i++) {
                                TXREG = salida[i];
                                while (TXSTAbits.TRMT == 0);

                            }
                            unSegundo = 0;
                        }
                    }
                    segundos = 0;
                }
                if (comando[10] == '3' && unSegundo == 1) {
                    segundos++;
                    if (segundos == 3) {
                        frecuenciaMedida = TMR1 / segundos;
                        if (frecuenciaMedida < ret) {
                            sprintf(salida, "%d\n\r", frecuenciaMedida);

                            for (i = 0; i < 8; i++) {
                                TXREG = salida[i];
                                while (TXSTAbits.TRMT == 0);

                            }
                            unSegundo = 0;
                        }
                    }
                    segundos = 0;
                }
                if (comando[10] == '4' && unSegundo == 1) {
                    segundos++;
                    if (segundos == 4) {
                        frecuenciaMedida = TMR1 / segundos;
                        if (frecuenciaMedida < ret) {
                            sprintf(salida, "%d\n\r", frecuenciaMedida);

                            for (i = 0; i < 8; i++) {
                                TXREG = salida[i];
                                while (TXSTAbits.TRMT == 0);

                            }
                            unSegundo = 0;
                        }
                    }
                    segundos = 0;
                }
                if (comando[10] == '5' && unSegundo == 1) {
                    segundos++;
                    if (segundos == 5) {
                        frecuenciaMedida = TMR1 / segundos;
                        if (frecuenciaMedida < ret) {
                            sprintf(salida, "%d\n\r", frecuenciaMedida);

                            for (i = 0; i < 6; i++) {
                                TXREG = salida[i];
                                while (TXSTAbits.TRMT == 0);

                            }
                            unSegundo = 0;
                        }
                        segundos = 0;
                    }
                }
                if (comando[10] == '6' && unSegundo == 1) {
                    segundos++;
                    if (segundos == 6) {
                        frecuenciaMedida = TMR1 / segundos;
                        if (frecuenciaMedida < ret) {
                            sprintf(salida, "%d\n\r", frecuenciaMedida);

                            for (i = 0; i < 8; i++) {
                                TXREG = salida[i];
                                while (TXSTAbits.TRMT == 0);

                            }
                            unSegundo = 0;
                        }
                    }
                    segundos = 0;
                }
                if (comando[10] == '7' && unSegundo == 1) {
                    segundos++;
                    if (segundos == 7) {
                        frecuenciaMedida = TMR1 / segundos;
                        if (frecuenciaMedida < ret) {
                            sprintf(salida, "%d\n\r", frecuenciaMedida);

                            for (i = 0; i < 8; i++) {
                                TXREG = salida[i];
                                while (TXSTAbits.TRMT == 0);

                            }
                            unSegundo = 0;
                        }
                    }
                    segundos = 0;
                }
                if (comando[10] == '8' && unSegundo == 1) {
                    segundos++;
                    if (segundos == 8) {
                        frecuenciaMedida = TMR1 / segundos;
                        if (frecuenciaMedida < ret) {
                            sprintf(salida, "%d\n\r", frecuenciaMedida);

                            for (i = 0; i < 8; i++) {
                                TXREG = salida[i];
                                while (TXSTAbits.TRMT == 0);

                            }
                            unSegundo = 0;
                        }
                    }
                    segundos = 0;
                }
                if (comando[10] == '9' && unSegundo == 1) {
                    segundos++;
                    if (segundos == 9) {
                        frecuenciaMedida = TMR1 / segundos;
                        if (frecuenciaMedida < ret) {
                            sprintf(salida, "%d\n\r", frecuenciaMedida);

                            for (i = 0; i < 8; i++) {
                                TXREG = salida[i];
                                while (TXSTAbits.TRMT == 0);

                            }
                            unSegundo = 0;
                        }
                    }
                    segundos = 0;
                }
            }
            break;
            if (mode == 2) {
                c = 0;
                g = 1;

                umbral [0] = comando [17];
                umbral [1] = comando [18];
                umbral [2] = comando [19];
                umbral [3] = comando [20];
                umbral [4] = comando [21];

                ret = strtol(umbral, &ptr, 10);

                if (comando[10] == '1' && unSegundo == 1) {


                    segundos++;
                    NOP();
                    if (segundos == 1) {
                        NOP();
                        frecuenciaMedida = TMR1 / segundos;
                        if (frecuenciaMedida < ret) {

                            sprintf(salida, "%d\n\r", frecuenciaMedida);

                            for (i = 0; i < 8; i++) {
                                TXREG = salida[i];
                                while (TXSTAbits.TRMT == 0);

                            }
                            unSegundo = 0;
                        }
                    }

                }
                segundos = 0;


                if (comando[10] == '2' && unSegundo == 1) {
                    segundos++;
                    if (segundos == 2) {
                        frecuenciaMedida = TMR1 / segundos;
                        if (frecuenciaMedida < ret) {
                            sprintf(salida, "%d\n\r", frecuenciaMedida);

                            for (i = 0; i < 8; i++) {
                                TXREG = salida[i];
                                while (TXSTAbits.TRMT == 0);

                            }
                            unSegundo = 0;
                        }
                    }
                    segundos = 0;
                }
                if (comando[10] == '3' && unSegundo == 1) {
                    segundos++;
                    if (segundos == 3) {
                        frecuenciaMedida = TMR1 / segundos;
                        if (frecuenciaMedida < ret) {
                            sprintf(salida, "%d\n\r", frecuenciaMedida);

                            for (i = 0; i < 8; i++) {
                                TXREG = salida[i];
                                while (TXSTAbits.TRMT == 0);

                            }
                            unSegundo = 0;
                        }
                    }
                    segundos = 0;
                }
                if (comando[10] == '4' && unSegundo == 1) {
                    segundos++;
                    if (segundos == 4) {
                        frecuenciaMedida = TMR1 / segundos;
                        if (frecuenciaMedida < ret) {
                            sprintf(salida, "%d\n\r", frecuenciaMedida);

                            for (i = 0; i < 8; i++) {
                                TXREG = salida[i];
                                while (TXSTAbits.TRMT == 0);

                            }
                            unSegundo = 0;
                        }
                    }
                    segundos = 0;
                }
                if (comando[10] == '5' && unSegundo == 1) {
                    segundos++;
                    if (segundos == 5) {
                        frecuenciaMedida = TMR1 / segundos;
                        if (frecuenciaMedida < ret) {
                            sprintf(salida, "%d\n\r", frecuenciaMedida);

                            for (i = 0; i < 8; i++) {
                                TXREG = salida[i];
                                while (TXSTAbits.TRMT == 0);

                            }
                            unSegundo = 0;
                        }
                        segundos = 0;
                    }
                }
                if (comando[10] == '6' && unSegundo == 1) {
                    segundos++;
                    if (segundos == 6) {
                        frecuenciaMedida = TMR1 / segundos;
                        if (frecuenciaMedida < ret) {
                            sprintf(salida, "%d\n\r", frecuenciaMedida);

                            for (i = 0; i < 8; i++) {
                                TXREG = salida[i];
                                while (TXSTAbits.TRMT == 0);

                            }
                            unSegundo = 0;
                        }
                    }
                    segundos = 0;
                }
                if (comando[10] == '7' && unSegundo == 1) {
                    segundos++;
                    if (segundos == 7) {
                        frecuenciaMedida = TMR1 / segundos;
                        if (frecuenciaMedida < ret) {
                            sprintf(salida, "%d\n\r", frecuenciaMedida);

                            for (i = 0; i < 8; i++) {
                                TXREG = salida[i];
                                while (TXSTAbits.TRMT == 0);

                            }
                            unSegundo = 0;
                        }
                    }
                    segundos = 0;
                }
                if (comando[10] == '8' && unSegundo == 1) {
                    segundos++;
                    if (segundos == 8) {
                        frecuenciaMedida = TMR1 / segundos;
                        if (frecuenciaMedida < ret) {
                            sprintf(salida, "%d\n\r", frecuenciaMedida);

                            for (i = 0; i < 8; i++) {
                                TXREG = salida[i];
                                while (TXSTAbits.TRMT == 0);

                            }
                            unSegundo = 0;
                        }
                    }
                    segundos = 0;
                }
                if (comando[10] == '9' && unSegundo == 1) {
                    segundos++;
                    if (segundos == 9) {
                        frecuenciaMedida = TMR1 / segundos;
                        if (frecuenciaMedida < ret) {
                            sprintf(salida, "%d\n\r", frecuenciaMedida);

                            for (i = 0; i < 8; i++) {
                                TXREG = salida[i];
                                while (TXSTAbits.TRMT == 0);

                            }
                            unSegundo = 0;
                        }
                    }
                    segundos = 0;
                }
            }

            if (mode == 3) {
                c = 1;
                g = 1;
                a = TMR1;
                sprintf(salida, "%d\n\r", a);
                for (i = 0; i < 8; i++) {
                    TXREG = salida[i];
                    while (TXSTAbits.TRMT == 0);


                }
            }




        }

    }

}

