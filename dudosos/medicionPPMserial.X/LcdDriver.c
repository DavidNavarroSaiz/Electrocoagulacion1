/*
 * File:   LcdDriver.c
 * Author: Nerio Montoya
 * Modificado por Daniel Luján
 *
 * Fecha de modificación Mayo 5 de 2012
 *
 * A continuación, se programan los drivers para manerjar la LCD. La descripcion
 * básica de cada uno de ellos se encuentra en el archivo LcdDriver.h. Cada una
 * tiene una funcion especifica. Las rutinas se hacen independientes de los
 * pines asignados al microcontrolador. Esos son definidos en el archivo
 * LcdDriver.h
 *
 * Debe primero llamarse a la rutina de incializacion del puerto y luego a la
 * rutina de inicializacion de los puertos de la LCD lcdInit y tener cuidado
 * en los pines que se estan asignado al programa
 *
 * Bibliografia
 * [1] LCD Interfacing using HD44780 Hitachi chipset compatible LCD?s
 * [2] HD44780U (LCD-II) (Dot Matrix Liquid Crystal Display Controller/Driver)
 * [3] HD44780U (LCD-II) Part ii
 *     (Dot Matrix Liquid Crystal Display Controller/Driver)
 */

// LCD driver
#include <xc.h>
#include <stdbool.h>
//#include <GenericTypeDefs.h>
//#include "ConfiguracionApp.h"
#include "LcdDriver.h"

// Variable para el control de refresco de la LCD
volatile unsigned char timerLCD;
char messajeLCD[16];

/* lcdInit
 * Inicializa los pines usados para los metodos de la lcd, ademas de realizar la rutina de inicializacion de la lcd.
 * En cada paso de la rutina se especifica la secuencia de inicialización de la lcd
 *
 * Tambien se encarga de configurar al TMR0, de forma que este sen encarga de generar las señales de tiempo necesarias
 * para refrescar adecuadamente la LCD
 */
void initLCD(void) {
    // 1.1 Configuracion del Tris
    T_LCD_DATA_DB4 = 0;
    T_LCD_DATA_DB5 = 0;
    T_LCD_DATA_DB6 = 0;
    T_LCD_DATA_DB7 = 0;
    T_LCD_RS = 0;
    T_LCD_EN = 0;

    // 1.2 Rutina de inicializacion
    __delay_ms(15);
    LCD_RS = 0; // Activar el modo para ingresar comandos
    lcdPinWrite(0x00); //Limpia los datos cargados en la lcd
    lcdPinWrite(0x03); //Se envia el dato 0x03
    lcdClockSignal(); //Hacer una señal de reloj, para cargar el dato en la lcd
    __delay_ms(5);

    lcdPinWrite(0x00); //Limpiar los pines correspondientes a las lineas de datos de la LCD
    lcdPinWrite(0x03); //Carga nuevamente el valor de 0x03 en la lcd
    lcdClockSignal(); //Hacer una señal de reloj, para cargar el dato en la LCD
    __delay_us(170); // Para pic18 con 20MHz -

    lcdPinWrite(0x00); //Limpiar los pines correspondientes a las lineas de datos de la LCD
    lcdPinWrite(0x03); //Carga nuevamente el valor de 0x03 en la lcd
    lcdClockSignal(); // Hacer una señal de reloj, para cargar el dato en la LCD
    __delay_ms(5); // Para pic18 con 20MHz -

    lcdPinWrite(0x00); //Limpiar los pines correspondientes a las lineas de datos de la LCD
    lcdPinWrite(0x02); // Se carga el valor de 0x02
    lcdClockSignal(); // Hacer una señal de reloj, para cargar el dato en la LCD
    __delay_us(170); // Para pic18 con 20MHz -

    lcdWrite(0x08); // Display apagado
    lcdWrite(0x28); // 4 bit mode, 2 lineas de 16 caracteres, matriz de 5x7 pixel
    lcdWrite(0x06); // Entry mode...
    lcdWrite(0x0F); // Display On, Cursor Blinky On
    lcdClear(); //Limpia la lcd
    lcdHome(); //Pone el cursor en la primera posición

    timerLCD = 0; // Inicial el contador en 0

} // end void lcdInit(void)

/* 2. lcdHome -
 Coloca el cursor en la primera posición de la lcd
 Según la documentación se demora aproximadamente 4ms
 */
void lcdHome(void) {
    LCD_RS = 0;
    lcdWrite(0x02);
    __delay_ms(4);
} // end void lcdHome(void)

/* 2. lcdClockSignal -
 Señal de reloj
 */
void lcdClockSignal(void) {
    LCD_EN = 1;
    Nop();
    LCD_EN = 0;
    Nop();
} // end void lcdClockSignal(void)

/* 3. lcdClear -
 Limpia la pantalla de la lcd
 Según la documentación se demora aproximadamente 4ms
 */
void lcdClear(void) {
    LCD_RS = 0;
    lcdWrite(0x01);
    __delay_ms(4);
} // end void lcdClear(void)

/* 4. lcdMoveCursorTo
 * Mueve el cursor a la posicion requerida a partir de la
 * variable de entrada posicion
 */
void lcdMoveCursorTo(unsigned char posicion) {
    LCD_RS = 0; // Modo instruccion
    // posicion = (0x80 + posicion);
    // El 0x80 es un comando que se envia para decirle a la lcd que se va a
    // configurar el DDRAM ( Direcciones en el display ) y se une con la dire-
    // cción que se desea desplazar
    lcdWrite((0x80 + posicion));
    __delay_ms(4);
} // end void lcdMoveCursorTo(unsigned char posicion)

/* 5. lcdPinWrite
 * Con este metodo se configura cada uno de los pines
 * cuando se envia un byte - Este metodo es para el modo
 * de envio de 4bits
 */
void lcdPinWrite(char reg) {
    lcd_register value; //Carga el registro de transmision y hace posible evaluar
    lcdDB4 = 0;
    lcdDB5 = 0;
    lcdDB6 = 0;
    lcdDB7 = 0;

    value.Val_lcd = reg;
    // 8.1 Para DB4
    if (value.lcd_DBS.pinDB4 == 1) lcdDB4 = 1;
    if (value.lcd_DBS.pinDB5 == 1) lcdDB5 = 1;
    if (value.lcd_DBS.pinDB6 == 1) lcdDB6 = 1;
    if (value.lcd_DBS.pinDB7 == 1) lcdDB7 = 1;
} // end void lcdPinWrite(char reg)

/* 6. lcdWrite -
 Esta rutina se encarga de escribir los bytes en la lcd
 */
void lcdWrite(char character) {
    char variable_up; // Para la parte alta de los 8 bits de transmision
    char variable_low; // Para la parte baja de los 8 bits de transmision

    variable_up = character >> 4; //Guarda la parte alta del character
    variable_low = character; //Guarda la parte baja del character

    // variable superior
    lcdPinWrite(variable_up);
    lcdClockSignal();

    // variable inferior
    lcdPinWrite(variable_low);
    lcdClockSignal();
    __delay_ms(1);
} // end void lcdWrite(char character)

/* 7, lcdWriteNumber
 * Este metodo escribe el numero en la lcd
 */
void lcdWriteNumber(char numero) {
    LCD_RS = 1;
    switch (numero) {
        case 0:
            lcdWrite('0');
            break;
        case 1:
            lcdWrite('1');
            break;
        case 2:
            lcdWrite('2');
            break;
        case 3:
            lcdWrite('3');
            break;
        case 4:
            lcdWrite('4');
            break;
        case 5:
            lcdWrite('5');
            break;
        case 6:
            lcdWrite('6');
            break;
        case 7:
            lcdWrite('7');
            break;
        case 8:
            lcdWrite('8');
            break;
        case 9:
            lcdWrite('9');
            break;
        default: NOP();
            break;
    }// end switch
} // end void lcdWriteNumber(char numero)

/* 8. lcdCursorOnOff -
 * Activa o desactiva el parpadeo que se presente en la lcd
 */
void lcdCursorOnOff(unsigned char onOff) {
    LCD_RS = 0;
    // segun el manual, el comado es 0000 1 D C B (donde D=display, C=cursor, B=Blink)
    if (onOff == CURSOR_OFF) {
        lcdWrite(0x0C);
    } else {
        lcdWrite(0x0F);
    } // end if (onOff == CURSOR_OFF)
} // end void lcdCursorOnOff(unsigned char onOff)

/* 9. lcdWriteMessaje
 * Con este metodo se escribe los mensajes en la LCD
 */
void lcdWriteMessage(const char * message) {
    LCD_RS = 1;
    while (*message) {
        lcdWrite(*message++);
    } // end while (*message)
}// end void lcdWriteMessage(const char * message)

/* 
 * 10. lcdWriteValue
 * Metodo para escribir un 
 * numero en la pantalla lcd decimal
 * 
 * value: es el valor
 * ubicacion: ubicacion de la unidad
 * 
 */
void lcdWriteDecimal(signed int value, char ubicacion) {
    signed char signo;
    char millar, centena, decena, unidad;

    signo = 0;

    // Analizamos si posee singno
    // Rutina si el valor lleva signo o no
    if (value < 0) {
        signo = 1;
        value = -1 * value;
    }// end if signo

    // Descomponemos el valor
    unidad = value % 10;
    decena = (value / 10) % 10;
    centena = (value / 100) % 10;
    millar = (value / 1000) % 10;

    // Ponemos el numero en la pantalla
    // unidad
    ubicacion = ubicacion - 5; // millar, centena, decena, punto y unidad

    // if (signo)
    ubicacion--; // Restamos una posicion en caso de signo

    lcdMoveCursorTo(ubicacion);
    // signo, en caso de tenerno lo ubicamos
    if (signo) {
        signo = 0;
        lcdWriteMessage("-");
    } else {
        lcdWriteMessage(" ");
    }// end if (!millar)

    // en el millar, en caso de ser cero no ponemos nada
    if (!millar) {
        lcdWriteMessage(" ");
    } else {
        lcdWriteNumber(millar);
    }// end if (!millar)

    lcdWriteNumber(centena); // ponemos las centena
    lcdWriteNumber(decena); // ponemos las decenas
    lcdWrite('.'); // punto
    lcdWriteNumber(unidad);
} // end void lcdWriteDecimal(signed int value, char ubicacion)


/*
 * 11. void lcdWrite2digi(BYTE value, BYTE ubicacion)
 * Metodo par escribir un
 * valor con dos digitos positivo
 *
 * ubicacion : ubicacion de la unidad
 */
void lcdWrite1digi(char value, char ubicacion) {
    char unidad;

    unidad = value % 10;

    // ubicamos la lcd y escribimos el valor
    lcdMoveCursorTo(ubicacion);
    lcdWriteNumber(unidad);
} // end void lcdWrite2digi(BYTE value, BYTE ubicacion)

/* 
 * 11. void lcdWrite2digi(BYTE value, BYTE ubicacion)
 * Metodo par escribir un
 * valor con dos digitos positivo
 *
 * ubicacion : ubicacion de la unidad
 */
void lcdWrite2digi(char value, char ubicacion) {
    char unidad, decena;

    unidad = value % 10;
    decena = (value / 10) % 10;

    // ubicamos la lcd y escribimos el valor
    lcdMoveCursorTo(ubicacion);
    lcdWriteNumber(decena);
    lcdWriteNumber(unidad);
} // end void lcdWrite2digi(BYTE value, BYTE ubicacion)

/*
 * 12. void lcdWrite3digi(BYTE value, BYTE ubicacion)
 * Metodo par escribir un
 * valor con tres digitos positivo
 *
 * ubicacion : ubicacion de la unidad
 */
void lcdWrite3digi(signed int value, char ubicacion) {
    char unidad, decena;
    signed int centena;

    unidad = value % 10;
    decena = (value / 10) % 10;
    centena = (value / 100) % 10;

    // ubicamos la lcd y escribimos el valor
    lcdMoveCursorTo(ubicacion);

    if (centena <= 0) {
        lcdWriteMessage(" ");
    } else {
        lcdWriteNumber(centena);
    }// end if(centena<= 0)

    lcdWriteNumber(decena);
    lcdWriteNumber(unidad);
} // end void lcdWrite3digi(WORD value, BYTE ubicacion)

/*
 * 13. void lcdWrite4digi(BYTE value, BYTE ubicacion)
 * Metodo par escribir un
 * valor con cuatro digitos positivo
 *
 * ubicacion : ubicacion de la unidad
 */
void lcdWrite4digi(signed int value, char ubicacion) {
    char unidad, decena, centena;
    signed int unMil;

    unidad = value % 10;
    decena = (value / 10) % 10;
    centena = (value / 100) % 10;
    unMil = (value / 1000) % 10;

    // ubicamos la lcd y escribimos el valor
    lcdMoveCursorTo(ubicacion);

    if (unMil <= 0) {
        lcdWriteMessage(" ");

        if (centena <= 0) {
            lcdWriteMessage(" ");
        } else {
            lcdWriteNumber(centena);
        }// end if(centena<= 0)

    } else {
        lcdWriteNumber(unMil);
        lcdWriteNumber(centena);
    }// end if (unMil < 0)

    lcdWriteNumber(decena);
    lcdWriteNumber(unidad);
} // end void lcdWrite4digi(WORD value, BYTE ubicacion)

//void isrTMR0(void){
//    timerLCD++;
//    LED_VENT = ~LED_VENT;
//    TMR0 = 26472;
//    INTCONbits.T0IF = 0;
//}


