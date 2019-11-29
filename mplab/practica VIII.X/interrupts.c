/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
#include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>
#include <pic18f252.h>        /* For true/false definition */

#endif

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* High-priority service */
extern int resultadoadc;
extern int conversionadc;
char comando[25];
int n;
int b;
int g;
extern int enter;
extern int tama;
char dato;
extern int led;
int muestreo;
int visualizacion;
#if defined(__XC) || defined(HI_TECH_C)
void interrupt high_isr(void)
#elif defined (__18CXX)
#pragma code high_isr=0x08
#pragma interrupt high_isr
void high_isr(void)
#else
#error "Invalid compiler selection for implemented ISR routines"
#endif
{

    if (PIR1bits.ADIF == 1) { //lanzar la ADC

        NOP();
        resultadoadc = (ADRESH << 8) + ADRESL;
        conversionadc = 1;
        PIR1bits.ADIF = 0;
    }

    if (PIR1bits.RCIF == 1) { //USART receive buffer//
        dato = RCREG;
        if (dato != '\r') {
            comando[n] = dato;
            n++;
            tama++;
        } else if (dato == '\r') {
            n = 0;
            enter = 1;
        }

        PIR1bits.RCIF = 0;
    }
    if (PIR2bits.TMR3IF == 1) {        
        led = 1;
        TMR3 = 3036;
        PIR2bits.TMR3IF = 0;
    }
    if (PIR1bits.TMR1IF == 1) {
        PIR1bits.TMR1IF = 0;
        NOP();
        visualizacion = 1;
        TMR1 = 3036; //100 ms

    }
    if (INTCONbits.TMR0IF == 1) {
        INTCONbits.TMR0IF = 0;
        muestreo = 1;
        NOP();
        TMR0 = 65458;//1ms

    }
}


/* Low-priority interrupt routine */
#if defined(__XC) || defined(HI_TECH_C)
void low_priority interrupt low_isr(void)
#elif defined (__18CXX)
#pragma code low_isr=0x18
#pragma interruptlow low_isr
void low_isr(void)
#else
#error "Invalid compiler selection for implemented ISR routines"
#endif
{

    /* This code stub shows general interrupt handling.  Note that these
    conditional statements are not handled within 3 seperate if blocks.
    Do not use a seperate if block for each interrupt flag to avoid run
    time errors. */

#if 0

    /* TODO Add Low Priority interrupt routine code here. */

    /* Determine which flag generated the interrupt */
    if (<Interrupt Flag 1 >) {
        <Interrupt Flag 1 = 0 >; /* Clear Interrupt Flag 1 */
    } else if (<Interrupt Flag 2 >) {
        <Interrupt Flag 2 = 0 >; /* Clear Interrupt Flag 2 */
    } else {
        /* Unhandled interrupts */
    }

#endif

}
