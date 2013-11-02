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

#endif

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "plib.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
#define _XTAL_FREQ 20000000
unsigned char config = ADC_FOSC_16 & ADC_2_TAD & ADC_RIGHT_JUST;
unsigned char config2 = ADC_CH0 & ADC_INT_OFF & ADC_REF_VDD_VSS;
unsigned char portconfig = ADC_0ANA;
/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    /* TODO <INSERT USER APPLICATION CODE HERE> */

    OpenADC(config, config2, portconfig);
    
    while(1)
    {


        ConvertADC();
        while(BusyADC());

        unsigned int aval = ReadADC();
        if(aval > 512)
            PORTB = 0xff;
        else
            PORTB = 0x00;
    }

}

