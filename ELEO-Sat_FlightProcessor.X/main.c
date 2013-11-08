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
#include "xbee.h"


/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
#define _XTAL_FREQ 20000000
unsigned int TemperatureReading;

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


    while(1)
    {

        // check to see if we were polled and send the data
        if(pollRecv)
        {
            //putsUSART((char *)sendBuff); // send data
            sendXbee();
            for(int i=0; i<6; i++) // clear receive buffer
                recvBuff[i] = 0;
            pollRecv = 0; // reset poll received flag
            PORTBbits.RB2 ^= 1;
        }

        else if(INTCONbits.TMR0IF)
        {
            // read Temperature
            ConvertADC();
            while(BusyADC());
            TemperatureReading = ReadADC();

            sendBuff[4] = 0x03 & (TemperatureReading >> 8);
            sendBuff[5] = 0xff & TemperatureReading;

//            if(TemperatureReading > 512)
//                PORTBbits.RB1 = 1;
//            else
//                PORTBbits.RB1 = 0;

            // get current through resistor from power pic
            sendSPI(Power, R_Current);
            __delay_us(50);
            sendBuff[6] = recvSPI(Power);
            sendBuff[7] = recvSPI(Power);
            __delay_ms(1);

            // get solar current from power pic
            sendSPI(Power, Solar_Current);
            __delay_us(50);
            sendBuff[8] = recvSPI(Power);
            sendBuff[9] = recvSPI(Power);
            __delay_ms(1);

            // get solar voltage from power pic
            sendSPI(Power, Solar_Voltage);
            __delay_us(50);
            sendBuff[10] = recvSPI(Power);
            sendBuff[11] = recvSPI(Power);
            __delay_ms(1);

            // get temperature from power pic
            sendSPI(Power, Temperature);
            __delay_us(50);
            sendBuff[12] = recvSPI(Power);
            sendBuff[13] = recvSPI(Power);
            __delay_ms(1);

            // get temperature from power pic
            sendSPI(Power, Processor_Voltage);
            __delay_us(50);
            sendBuff[14] = recvSPI(Power);
            sendBuff[15] = recvSPI(Power);

            INTCONbits.TMR0IF = 0;
            WriteTimer0(0x0000);
        }
    }
}

