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
extern int AD_almacenado;
float v_sensor;// voltaje sensor por bit 
float temp; //temperatura del sensor
const char mensaje [] = "1" ;
char salida [25];
//char get_value;
//extern int o ;
/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void enviarTrama(char *datos);
void UART_send_char(char bt);
void UART_send_string(char* st_pt);
//char UART_get_char;

char UART_get_char() 
{
    if(OERR) // check for Error 
    {
        CREN = 0; //If error -> Reset 
        CREN = 1; //If error -> Reset 
    }
    
    while(!RCIF);  // hold the program till RX buffer is free
    
    return RCREG; //receive the value and send it to main function
}
//_____________End of function________________//

void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();
    enviarTrama(mensaje);
//    
    while(1)
    {
        if(band_aux == 8){
             
            
//            int get_value = UART_get_char(); 
            band_aux=0;
            ADCON0bits.GO= 1; //Inicia la conversion AD
//            if (get_value == '1') //If the user sends "1"
//        {
            LATAbits.LATA1 = !LATAbits.LATA1;//led visualizador del timer

            UART_send_string("1a a"); //Send notification to the computer 
            UART_send_char(10);//ASCII value 10 is used for carriage return (to print in new line)
//        }
            
//            sprintf(salida, "grados: %.1f C", temp);
//            enviarTrama(salida);
            
            
         }
        
    }
//        /* TODO <INSERT USER APPLICATION CODE HERE> */
//        if (band_aux == 1){
//            v_sensor = (5000.*AD_almacenado)/1023;
//            temp = (v_sensor/10)-3.8;
//            band_aux = 0;
//            
//            enviarTrama(mensaje);
//            sprintf(salida, "grados: %.1f C", temp);
//            enviarTrama(salida);
//            
//            
        
        
//        }
//        
//        
//    }
//    
//
//}
//
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


//**Function to send one byte of date to UART**//
void UART_send_char(char bt)  
{
    while(!TXIF);  // hold the program till TX buffer is free
    TXREG = bt; //Load the transmitter buffer with the received value
}
//_____________End of function________________//


//**Function to get one byte of date from UART**//

//**Function to convert string to byte**//
void UART_send_string(char* st_pt)
{
    while(*st_pt) //if there is a char
        UART_send_char(*st_pt++); //process it as a byte data
}
//___________End of function______________//



