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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#endif

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "LcdDriver.h"
#include <math.h>

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
char str1[20];
char str2[20];
extern char banderaA;
float COV ;
float COC;
float CO2V ;
float CO2C;
extern int t;
const char saludo1 [] = "medicion CO";
const char saludo2 [] = "medicion CO2";
extern char A;
extern char B;
extern int n ;
char salida1 [25];
char salida2 [25];
char encendido; 
extern int d; 
extern int f;

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */

/******************************************************************************/

void enviarTrama(char *datos);
void main(void) {
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    /* TODO <INSERT USER APPLICATION CODE HERE> */
    initLCD();
        
    while (1) {
        
        if (banderaA == 1){
            COV = (5.*d)/1023.;
            COC = (COV * 27.66)-8.2128;
            CO2V = (5.*f)/1023.;
            CO2C = (CO2V * 270.66)-8.2128;
            lcdClear();
            lcdWriteMessage("CO PPM: ");
            sprintf(str1, "%.1f ",COC);
            lcdWriteMessage(str1); 
            lcdMoveCursorTo(LINEA_2);
            lcdWriteMessage("CO2 PPM: ");
            sprintf(str2, "%.1f ",CO2C);
            lcdWriteMessage(str2);     
            banderaA = 0;
            
           enviarTrama(saludo1);
        
           sprintf(salida1, "PPM: %.1f", COC);
        
           enviarTrama(salida1);
           
           enviarTrama(saludo2);
        
           sprintf(salida2, "PPM: %.1f", CO2C);
        
           enviarTrama(salida2);
        
        }
          /*if (banderaA == 1){
             n = n + 1;  
        
           banderaA = 0;
           
          }*/
          
        if (n % 2 == 0){
            LATCbits.LATC1 = 1;
            
            /*A = 1;
            B = 0;
            /*d = t;*/
            }
            else{
               LATCbits.LATC1 = 0;
               
            }
            
        
         if (n % 2 == 1){
           LATCbits.LATC2 = 1;
            
            /*A = 0;
            B = 1;
            /*f = t;*/
        }
        else {
           LATCbits.LATC2 = 0;
           
               
        } 
            
           
        
    
       }
    }


void enviarTrama(char *datos) {

    //saludo[0] = *datos

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