/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
    #include <plib.h>       /* XC8 Peripheral Libraries */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "user.h"
#include "spi_comm.h"
#include "xbee.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */

    /* Setup analog functionality and port direction */
    ADCON1 = 0b00001010;
    TRISA  = 0b00000001;
    TRISB  = 0b00000000;
    PORTB = 0x00;
    PORTBbits.RB0 = 1;

    /* Initialize peripherals */
    CloseADC();
    OpenADC(ADC_FOSC_16 & ADC_2_TAD & ADC_RIGHT_JUST,
            ADC_CH0 & ADC_INT_OFF & ADC_REF_VDD_VSS,
            ADC_0ANA);

    setupSPI();

    initXbee();
    

    // Timer0 for getting Power data
    OpenTimer0(TIMER_INT_OFF & T0_8BIT & T0_SOURCE_INT & T0_PS_1_256);
    WriteTimer0(0x0000);


    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */
    RCONbits.IPEN = 1;
    /* Enable interrupts */
    ei(); // enable interrupts


}
