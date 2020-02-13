/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>






#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"           /* User funct/params, such as InitApp */
#include <math.h>


/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern int band_aux;
int led;
int i = 0;
int cont_led;
char str1[10], str2[16], str3[5], str4[22];
extern int AD_almacenado;
float v_sensor;// voltaje sensor por bit 
float temp; //temperatura del sensor
//const char mensaje [] = "valor temp en C:" ;
char salida [25];
const char saludo[] = "Bienvenido, ya puede controlar el desplazador XY ";
/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void enviarTrama(char *datos);
void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();
    
    
    while(1)
    {
       
       
        /* TODO <INSERT USER APPLICATION CODE HERE> */
//        if (band_aux == 1){
            band_aux = 0;
            strcpy(str4, "Comando no reconocido\n\r");
            if(led>10){
                LATAbits.LATA1= ~LATAbits.LATA1;
                led=0;
//                sprintf(salida, "grados");
                
                
                 for (i = 0; i < 22; i++) {
                TX1REG = str4[i];
                while (TXSTAbits.TRMT == 0);
                NOP();
            }
        
        }
   
    }
    

}

