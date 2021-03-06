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
#include <stdbool.h>        /* For true/false definition */

#endif

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/
int t;
int f;
int d;
int n = 0;
char banderaA = 0;

/* High-priority service */

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

    /* This code stub shows general interrupt handling.  Note that these
    conditional statements are not handled within 3 seperate if blocks.
    Do not use a seperate if block for each interrupt flag to avoid run
    time errors. */

    /* TODO Add High Priority interrupt routine code here. */

    /* Determine which flag generated the interrupt */
    if (INTCONbits.TMR0IF == 1) {
        INTCONbits.TMR0IF = 0;
        TMR0 = 45005;
        LATCbits.LATC0 = !PORTCbits.RC0;
        n = n + 1;  
        banderaA = 1;
        ADCON0bits.GODONE = 1;
    }
    else if (PIR1bits.ADIF==1 && n % 2 == 0){
         ADCON0bits.CHS0= 1;
         ADCON0bits.CHS1= 0; 
          d = ADRES;
          PIR1bits.ADIF=0;
         
    }
        if(PIR1bits.ADIF==1 && n % 2 == 1){
            ADCON0bits.CHS0= 0;
            ADCON0bits.CHS1= 1;
            f = ADRES;
          PIR1bits.ADIF=0;
    
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
