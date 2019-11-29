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

int resultadoadc;
int conversionadc;
const char MODONORMAL[] = "MODONORMAL";
const char MODORAPIDO[] = "MODORAPIDO";
const char MUESTREO1[] = "MUESTREO1";
const char MUESTREO2[] = "MUESTREO2";
const char MUESTREO3[] = "MUESTREO3";
const char VISUALIZACION1 [] = "VISUALIZACION1";
const char VISUALIZACION2 [] = "VISUALIZACION2";
const char VISUALIZACION3 [] = "VISUALIZACION3";
const char estadoactualnormal[] = "Modo de muestreo normal";
const char estadoactualrapido[] = "Modo de muestreo rapido";
const char muestreonoaplica[] = "Muestreo NO APLICA";
const char visualizacionnoaplica[] = "visualizacion NO APLICA";
const char INFO [] = "INFO";
extern char comando[25];
extern int n;
int unSegundo;
const char saludo[] = "BIENVENIDO A LA CONVERSION ADC";
const char noreconocido[] = "COMANDO NO RECONOCIDO";
const char canal2[] = "canal 2 :";
int i = 0;
int led;
int d = 0;
int modo = 0;
int e = 0;
int enter;
int h0;
int h1;
int h2;
int NORMAL = 0;
int RAPIDO = 1;
char tam[40];
int tama;
extern int visualizacion;
extern int muestreo;
int promedio;
int suma0 = 0;
int suma1 = 0;
int suma2 = 0;
char salida [30];
float promediovolt1;
int promediovolt2;
int promediovolt3;
int tmues = 10;
int a;
int tvis = 5;
int muestreo1 = 1;
int muestreo2 = 1;
int muestreo3 = 1;
int visualizacion1 = 1;
int visualizacion2 = 1;
int visualizacion3 = 1;
int info = 1;
int modoestado;
int promedio1;
int promedio2;
int promedio3;
int binnum = 0b0000000001;
char bin [10];
int tvisualizacion;
extern int led2;


void ledestado(int tiempoled);
void enviarTrama(char *datos);
void enviarTramaSE(char *datos);
int conversionADMues(int canal);

/******************************************************************************/
/* Main Program                                                               */

/******************************************************************************/

void main(void) {
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    /* TODO <INSERT USER APPLICATION CODE HERE> */
    enviarTrama(saludo);
    while (1) {
        if (led == 1 && modoestado == 1) { //modo normal
            ledestado(10);
        }
        if (led == 1 && modoestado == 0) { //modo rapido
            ledestado(5);
        }
        if (enter == 1) {
            enviarTrama(comando);
            if (tama == 10) {
                NORMAL = strcmp(comando, MODONORMAL);
                RAPIDO = strcmp(comando, MODORAPIDO);

            } else if (tama == 9) {
                muestreo1 = strcmp(comando, MUESTREO1);
                muestreo2 = strcmp(comando, MUESTREO2);
                muestreo3 = strcmp(comando, MUESTREO3);

            } else if (tama == 14) {
                visualizacion1 = strcmp(comando, VISUALIZACION1);
                visualizacion2 = strcmp(comando, VISUALIZACION2);
                visualizacion3 = strcmp(comando, VISUALIZACION3);

            } else if (tama == 4) {
                info = strcmp(comando, INFO);                
            }
            else {
                enviarTrama(noreconocido);
            }
            if (NORMAL != 0 && RAPIDO != 0) {
                enviarTrama(noreconocido);
                NORMAL = 0 ;
                RAPIDO = 1 ;
            }
            for (i = 0; i < 25; i++) { //limpio comando
                comando[i] = '\0';
            }
            if (muestreo1 == 0) {
                tmues = 10;
            }
            if (muestreo2 == 0) {
                tmues = 12;
            }
            if (muestreo3 == 0) {
                tmues = 20;
            }
            if (visualizacion1 == 0) {
                tvis = 5;
            }
            if (visualizacion2 == 0) {
                tvis = 10;
            }
            if (visualizacion3 == 0) {
                tvis = 20;
            }
            enter = 0;
            
            tama = 0 ;
        }
        if (info == 0) {
            NOP();
//                enviarTrama(stringref);
//    enviarTrama(comando) ;
            sprintf(salida, "%d", modoestado);
            enviarTrama(salida);
            if (modoestado == 1) {
                enviarTrama(estadoactualnormal);
                sprintf(salida, "muestreo %d ms.", tmues);
                enviarTrama(salida);
                tvisualizacion = tvis * 100;
                sprintf(salida, "visualizacion %d ms.", tvisualizacion);
                enviarTrama(salida);
            }
            if (modoestado == 0) {
                enviarTrama(estadoactualrapido);
                enviarTrama(muestreonoaplica);
                enviarTrama(visualizacionnoaplica);
            }
            info = 1;
        }
        if (NORMAL == 0) {
            modoestado = 1;
            if (muestreo == 1) {
                e++;
                if (e == tmues) {
                    promedio1 = conversionADMues(0);
                    promedio2 = conversionADMues(1);
                    promedio3 = conversionADMues(2);
                    e = 0;
                }
                muestreo = 0;
            }
            if (visualizacion == 1) {
                a++;
                if (a == tvis) {
                    promediovolt1 = promedio1 * 5.0 / 1024; //imprimir canal 1 
                    sprintf(salida, "canal 1: %f V  ", promediovolt1);
                    enviarTramaSE(salida);
                    for (i = 0; i < 10; i++) {//imprimir canal 2
                        if ((promedio2 & binnum << (9 - i)) == 0) {
                            bin[i] = '0';
                        } else {
                            bin[i] = '1';
                        }
                    }
                    for (i = 0; i < 10; i++) {
                        TXREG = canal2[i];
                        while (TXSTAbits.TRMT == 0);
                    }
                    for (i = 0; i < 10; i++) {
                        TXREG = bin[i];
                        while (TXSTAbits.TRMT == 0);
                    }
                    for (i = 0; i < 10; i++) {
                        bin[i] = 0;
                    }
                    sprintf(salida, "  canal 3: 0x%04X.\n\r", promedio3); //imprimir canal 3
                    enviarTramaSE(salida);
                    a = 0;
                }
                visualizacion = 0;
                h0 = 0;
                suma0 = 0;
                h1 = 0;
                suma1 = 0;
                h2 = 0;
                suma2 = 0;
            }
        }
        if (RAPIDO == 0) {
            modoestado = 0;
            ADCON0bits.CHS = 0b011;
            if (muestreo == 1) {
                ADCON0bits.GODONE = 1;
                while (conversionadc == 0) {
                }
                sprintf(salida, "%d", resultadoadc);
                enviarTrama(salida);
                conversionadc = 0;
                muestreo = 0;
                LATBbits.LB7 = ~PORTBbits.RB7;
            }
        }

    }

}


/**
 * Controla el led de estado.
 * 
 * @param tiempoled Cantidad de desbordamientos
 */
void ledestado(int tiempoled) {
    d++;
    if (d >= tiempoled) {
        NOP();
        //LATBbits.LB7 = ~PORTBbits.RB7;
        d = 0;
    }
    led = 0;
}

/**
 * 
 * @param datos
 */
void enviarTrama(char *datos) {

    //saludo[0] = *datos:

    while (*datos != 0) {
        TXREG = *datos;
        while (TXSTAbits.TRMT == 0);
        *datos++;
    }

    TXREG = 0x0A;
    while (TXSTAbits.TRMT == 0);
    TXREG = 0x0D;
    while (TXSTAbits.TRMT == 0);

}


void enviarTramaSE(char *datos) {

    //saludo[0] = *datos:

    while (*datos != 0) {
        TXREG = *datos;
        while (TXSTAbits.TRMT == 0);
        *datos++;
    }
}

/**
 * 
 * @param canal Canal ADC
 * @return Promedio hasta el momento de los datos
 */
int conversionADMues(int canal) {
    if (canal == 0) {
        ADCON0bits.CHS = 0b000; //recibir señales del canal AN0
        for (int i = 0; i < 20; i++) {
            NOP();
        }
        ADCON0bits.GODONE = 1;
        while (conversionadc == 0) {
            NOP();
        }
        h0++;
        suma0 = suma0 + resultadoadc;
        resultadoadc = 0;
        promedio = suma0 / h0;
        conversionadc = 0;

        return promedio;
    }
    if (canal == 1) {
        ADCON0bits.CHS = 0b001; //recibir señales del canal AN1
        for (int i = 0; i < 20; i++) {
            NOP();
        }
        ADCON0bits.GODONE = 1;
        while (conversionadc == 0) {
            NOP();
        }
        h1++;
        suma1 = suma1 + resultadoadc;
        resultadoadc = 0;
        promedio = suma1 / h1;
        conversionadc = 0;

        return promedio;
    }
    if (canal == 2) {
        ADCON0bits.CHS = 0b010; //recibir señales del canal AN2
        for (int i = 0; i < 20; i++) {
            NOP();
        }
        ADCON0bits.GODONE = 1;
        while (conversionadc == 0) {
            NOP();
        }
        h2++;
        suma2 = suma2 + resultadoadc;
        resultadoadc = 0;
        promedio = suma2 / h2;
        conversionadc = 0;

        return promedio;
    }


}

