/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef pruebaLCD_H
#define	pruebaLCD_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdbool.h>
#define _XTAL_FREQ 20000000


/* 1. Deficion de los pines del microcontrolador usado */
// 1.1 Nombramiento de los pines que manerajar la lcd

/*Pines de LCD para la board (Circuito en la board)*/
#define lcdDB4 LATBbits.LATB5// Maneja el pin DB4 de la LCD
#define lcdDB5 LATBbits.LATB4// Maneja el pin DB5 de la LCD
#define lcdDB6 LATBbits.LATB3// Maneja el pin DB6 de la LCD
#define lcdDB7 LATBbits.LATB2// Maneja el pin DB7 de la LCD
#define LCD_RS  LATBbits.LATB1// Maneja el pin R/S de la LCD
#define LCD_EN  LATBbits.LATB0// Maneja el pin Enable de la LCD

// 1.2 Configuracion de los Tris manejados por los pines de comunicación a la
//      LCD
#define T_LCD_DATA_DB4 TRISBbits.TRISB5//Para DB4
#define T_LCD_DATA_DB5 TRISBbits.TRISB4//Para DB5
#define T_LCD_DATA_DB6 TRISBbits.TRISB3//Para DB6
#define T_LCD_DATA_DB7 TRISBbits.TRISB2//Para DB7
#define T_LCD_RS  TRISBbits.TRISB1 // Para R/S
#define T_LCD_EN  TRISBbits.TRISB0 // Para Enable

/*2. Definicion de las variables usadas en el programa
  Esta es la definicion de la variable tipo _lcd_register.
  Es una union, primero tipo char para poder ser compatible y cargar
  el valor asigando para escribir, y tambien es una estructura para
  poder evaluar cada bit y poner cada DB# en alto o en bajo segun
  sea el caso
 */

typedef union _lcd_register {
    char Val_lcd;

    struct _lcd_DBS {
        unsigned pinDB4 : 1;
        unsigned pinDB5 : 1;
        unsigned pinDB6 : 1;
        unsigned pinDB7 : 1;
    } lcd_DBS;
} lcd_register;

// 3. Declaracion de las varibles de las rutinas de los drivers de la lcd


// para determinar que DB# se pone en alto o en bajo. vease lcdPinWrite();

//3.4 Definicion de la variable auxiliares
//3.4.1 Para el cursor
#ifndef	CURSOR_OFF
#define CURSOR_OFF	0
#endif

#ifndef CURSOR_ON
#define CURSOR_ON 	1
#endif

//3.4.2 Banderas TRUE and FALSE
#ifndef TRUE
#define TRUE     1
#define FALSE    0
#endif

// Posiciones del inicio de los mensajes
#define LINEA_1 0x00
#define LINEA_2 0x40
#define LINEA_3 0x14
#define LINEA_4 0x54

// Definimos la variable punto y sin punto
#define onPunto 1
#define offPunto 0

// Definimos la variable si el sistema es de signo o no
#define onSigno 1
#define offSigno 0

// Definimos variables usadas
#define menos 0b00101101
#define espacio 0b00000010
#define punto_lcd 0b00101110
#define grado_lcd 0b11011111

// 4. Prototipo de los drivers de la lcd
void initLCD(void); // Inicializa la lcd
void lcdWrite(char character); //Para escribir el byte en la lcd
void lcdPinWrite(char reg); // Configura que pines DB# se configuran
void lcdClockSignal(void); // Para la señal de reloj
void lcdHome(void); //Retorna el cursor al inicio
void lcdClear(void); //Limpia la pantalla
void lcdWriteMessage(const char * message); // Permite escribir mensajes
void lcdCursorOnOff(unsigned char onOff); //Congura si se ve el cursor o no
void lcdMoveCursorTo(unsigned char posicion); //Mueve el cursor a la posicion
void lcdWriteNumber(char numero); // escribe el numero en la lcd

// escribe un numero del -9999 al 9999
void lcdWriteDecimal(signed int value, char ubicacion);

// Escritura de un valor con dos digitos positivo
void lcdWrite1digi(char value, char ubicacion);
void lcdWrite2digi(char value, char ubicacion);

// Escritura de un valor con tres digitos positivo
void lcdWrite3digi(signed int value, char ubicacion);

// Escritura de un valor con cuatro digitos positivo
void lcdWrite4digi(signed int value, char ubicacion);
void isrTMR0(void);
#endif

//
//#ifdef	__cplusplus
//extern "C" {
//#endif /* __cplusplus */
//
//    // TODO If C++ is being used, regular C code needs function names to have C 
//    // linkage so the functions can be used by the c code. 
//
//#ifdef	__cplusplus
//}
//#endif /* __cplusplus */
//
//#endif	/* XC_HEADER_TEMPLATE_H */

