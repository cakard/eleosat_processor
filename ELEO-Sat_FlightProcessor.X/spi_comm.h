/* 
 * File:   spi_comm.h
 * Author: cakard
 *
 * Created on November 5, 2013, 2:31 PM
 */

#ifndef SPI_COMM_H
#define	SPI_COMM_H

#define SELECT_POWER    (PORTBbits.RB0 = 0)
#define DESELECT_POWER  (PORTBbits.RB0 = 1)
#define _XTAL_FREQ 20000000

typedef enum {
   Power,
   Instrument,
   Communication
} Slaves;

typedef enum {
    null =                  0x00,
    switch0_on  =           0x01, // switch0_on
    switch0_off =           0x02, // switch0_off
    switch1_on  =           0x03, // switch1_on
    switch1_off =           0x04, // switch1_off
    switch2_on  =           0x05, // switch2_on
    switch2_off =           0x06, // switch2_off
    switch3_on  =           0x07, // switch3_on
    switch3_off =           0x08, // switch3_off
    R_Current =             0x09,
    Solar_Current =         0x0a,
    Solar_Voltage =         0x0b,
    Temperature =           0x0c,
    Processor_Voltage =     0x0d
} Commands;

void setupSPI();
void sendSPI(Slaves slave, Commands command);
char recvSPI(Slaves slave);


#endif	/* SPI_COMM_H */

