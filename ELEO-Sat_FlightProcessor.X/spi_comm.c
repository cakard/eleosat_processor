/******************************************************************************/
/* Files to Include                                                           */
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

#include "spi_comm.h"
#include "plib.h"

/**
 * setupSPI() initializes the SPI module.
 */
void setupSPI()
{
    DESELECT_POWER;
    CloseSPI();
    OpenSPI(SPI_FOSC_4 & SLV_SSOFF, MODE_01, SMPMID);
}

/**
 * sendSPI() sends a command to the specified slave unit and
 * receives whatever the slave sends for the command.
 *
 * @param slave - slave to communicate with
 * @param command - command to be sent to slave
 * @return - value received back from slave
 */
void sendSPI(Slaves slave, Commands command)
{
    char retval = 0x00;

    switch(slave)
    {
        case Power:
            //SSPBUF = 0x00; // clear the SPI buffer
            //SSPSTATbits.BF = 0; // clear the Buffer Flag
            SELECT_POWER;
            while(WriteSPI(command));
            //__delay_us(10); // wait for slave to process command
            //WriteSPI(null); // send dummy data
            //while(!SSPSTATbits.BF); // wait for receive to finish
            //retval = SSPBUF; // save the received value
            //retval = ReadSPI();
            DESELECT_POWER;
            break;
        case Instrument:
            break;
        case Communication:
            break;
    }

    //return retval;
}

char recvSPI(Slaves slave)
{
    SELECT_POWER;
    //WriteSPI(null);
    //while(!SSPSTATbits.BF);
    ReadSPI();
    DESELECT_POWER;
    return SSPBUF;
}