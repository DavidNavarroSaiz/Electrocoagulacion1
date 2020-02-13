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

/* High-priority service */
int extern a;
int extern b;
int extern c;
int extern d;
int extern f;
int extern g;
int extern i ;
int extern m ;
int extern j ;
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
    
    
   if (INTCON3bits.INT1IF == 1) { //segundo pulser mostrar cada 5 seg
        c++;
        TMR0 = 46005;
NOP();
        INTCON3bits.INT1IF = 0;
    }


    else if (PIR2bits.TMR3IF == 1) { // led de estado  natural
        TMR3 = 65473;
        j = 1     ;                                                           ;
        NOP();
        
        PIR2bits.TMR3IF = 0;
    }

    else if (INTCONbits.RBIF == 1) { //algun RBchange
        
        PORTB = PORTB;
        NOP();
        if (PORTBbits.RB4 == 1) {  //flanco de subida LED estado
            f = 1;
            g = 0 ;
            i++ ; 
            TMR3 = 65473;
            NOP();
            
        }
        else if (PORTBbits.RB4 == 0 && i != 0) {//flanco de bajada LED estado
            g = 1 ;
            f= 0 ;
            TMR3 = 65473 ;
            NOP();
            
        }
        
        else if (PORTBbits.RB5 ==1) {//  # Flanco de subida frecuencia
            b = 1 ;
            NOP() ; 
            m ++ ;
        }
        else if(PORTBbits.RB5 == 0 && m != 0 ){    //# Flanco de subida Frecuencia
            b = 0 ;
            NOP();
        }
        
        INTCONbits.RBIF = 0 ;
        }
    }



#if 0

    /* TODO Add High Priority interrupt routine code here. */

    /* Determine which flag generated the interrupt */
    if (<Interrupt Flag 1 >) {
        <Interrupt Flag 1 = 0 >; /* Clear Interrupt Flag 1 */
    } else if (<Interrupt Flag 2 >) {
        <Interrupt Flag 2 = 0 >; /* Clear Interrupt Flag 2 */
    } else {
        /* Unhandled interrupts */
    }

#endif



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

        if (INTCONbits.TMR0IF == 1) { //interrupcion por timer
        NOP();
        a = 1;
        TMR0 = 46005;
        INTCONbits.TMR0IF = 0;
        }


}
