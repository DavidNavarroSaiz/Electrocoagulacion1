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
extern char band_aux;
extern int AD_almacenado;
float v_sensor;// voltaje sensor por bit 
float temp; //temperatura del sensor
const char mensaje [] = "valor temp en C:" ;
char salida [25];
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
        if (band_aux == 1){
            v_sensor = (5000.*AD_almacenado)/1023;
            temp = (v_sensor/10)-3.8;
            band_aux = 0;
            
            enviarTrama(mensaje);
            sprintf(salida, "grados: %.1f C", temp);
            enviarTrama(salida);
            
            
        
        
        }
        
        
    }
    

}

void enviarTrama(char *datos) {

    //saludo[0] = *datos:

    while (*datos != 0) {
        TX1REG = *datos;
        while (TX1STAbits.TRMT == 0);
        *datos++;
    }

    TX1REG = 0x0A;
    while (TX1STAbits.TRMT == 0);
    TX1REG = 0x0D;
    while (TX1STAbits.TRMT == 0);
}