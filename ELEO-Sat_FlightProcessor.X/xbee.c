/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
    #include "plib.h"
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "xbee.h"

void initXbee()
{
    for(int i=0; i<6; i++)
        recvBuff[i] = 0;
    for(int i=0; i<41; i++)
        sendBuff[i] = 0;

    OpenUSART(USART_TX_INT_OFF & USART_RX_INT_ON & USART_ASYNCH_MODE
              & USART_EIGHT_BIT & USART_SINGLE_RX & USART_BRGH_HIGH
              & USART_ADDEN_OFF, 32);
}