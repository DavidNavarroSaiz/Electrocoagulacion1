/*
 * File:   funcionesDavid.c
 * Author: equipo5-if
 *
 * Created on 12 de octubre de 2017, 12:58
 */


#include <xc.h>
//
///**
// * Controla el led de estado.
// * 
// * @param tiempoled Cantidad de desbordamientos
// */
//void ledestado(int tiempoled) {
//    d++;
//    if (d >= tiempoled) {
//        NOP();
//        LATBbits.LB7 = ~PORTBbits.RB7;
//        d = 0;
//    }
//    led = 0;
//}
//
///**
// * 
// * @param datos
// */
//void enviarTrama(char *datos) {
//
//    //saludo[0] = *datos:
//
//    while (*datos != 0) {
//        TXREG = *datos;
//        while (TXSTAbits.TRMT == 0);
//        *datos++;
//    }
//
//    TXREG = 0x0A;
//    while (TXSTAbits.TRMT == 0);
//    TXREG = 0x0D;
//    while (TXSTAbits.TRMT == 0);
//
//}
//
//
//void enviarTramaSE(char *datos) {
//
//    //saludo[0] = *datos:
//
//    while (*datos != 0) {
//        TXREG = *datos;
//        while (TXSTAbits.TRMT == 0);
//        *datos++;
//    }
//}
//
///**
// * 
// * @param canal Canal ADC
// * @return Promedio hasta el momento de los datos
// */
//int conversionADMues(int canal) {
//    if (canal == 0) {
//        ADCON0bits.CHS = 0b000; //recibir señales del canal AN0
//        for (int i = 0; i < 20; i++) {
//            NOP();
//        }
//        ADCON0bits.GODONE = 1;
//        while (conversionadc == 0) {
//            NOP();
//        }
//        h0++;
//        suma0 = suma0 + resultadoadc;
//        resultadoadc = 0;
//        promedio = suma0 / h0;
//        conversionadc = 0;
//
//        return promedio;
//    }
//    if (canal == 1) {
//        ADCON0bits.CHS = 0b001; //recibir señales del canal AN1
//        for (int i = 0; i < 20; i++) {
//            NOP();
//        }
//        ADCON0bits.GODONE = 1;
//        while (conversionadc == 0) {
//            NOP();
//        }
//        h1++;
//        suma1 = suma1 + resultadoadc;
//        resultadoadc = 0;
//        promedio = suma1 / h1;
//        conversionadc = 0;
//
//        return promedio;
//    }
//    if (canal == 2) {
//        ADCON0bits.CHS = 0b010; //recibir señales del canal AN2
//        for (int i = 0; i < 20; i++) {
//            NOP();
//        }
//        ADCON0bits.GODONE = 1;
//        while (conversionadc == 0) {
//            NOP();
//        }
//        h2++;
//        suma2 = suma2 + resultadoadc;
//        resultadoadc = 0;
//        promedio = suma2 / h2;
//        conversionadc = 0;
//
//        return promedio;
//    }
//
//
//}
