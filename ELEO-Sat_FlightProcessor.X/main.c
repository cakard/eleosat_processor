/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
    #include "plib.h"      /* XC8 Peripheral Libraries */
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
#include "spi_comm.h"


/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
#define _XTAL_FREQ 20000000
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
    /*PORTBbits.RB0 = 0;
    while(WriteSPI(101));
    PORTBbits.RB0 = 1;

    __delay_us(200);*/

    while(1)
    {


        //ConvertADC();
        //while(BusyADC());

        //unsigned char aval = (ReadADC() >> 2);

        //while(WriteSPI(aval));

        sendSPI(Power, switch0_on);
        __delay_us(50);
        char val = 0x80 & recvSPI(Power);
        //PORTBbits.RB1 = recvSPI(Power);
        if(val)
            PORTBbits.RB1 = 1;
        __delay_ms(10);

        sendSPI(Power, switch1_on);
        __delay_us(50);
        PORTBbits.RB2 = recvSPI(Power);
        __delay_ms(10);

        sendSPI(Power, switch2_on);
        __delay_us(50);
        PORTBbits.RB3 = recvSPI(Power);
        __delay_ms(10);

        sendSPI(Power, switch2_off);
        __delay_us(50);
        PORTBbits.RB3 = recvSPI(Power);
        __delay_ms(10);

        sendSPI(Power, switch1_off);
        __delay_us(50);
        PORTBbits.RB2 = recvSPI(Power);
        __delay_ms(10);

        sendSPI(Power, switch0_off);
        __delay_us(50);
        PORTBbits.RB1 = recvSPI(Power);
        __delay_ms(10);

    }

}

