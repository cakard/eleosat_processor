/* 
 * File:   xbee.h
 * Author: cakard
 *
 * Created on November 6, 2013, 4:09 PM
 */

#ifndef XBEE_H
#define	XBEE_H

char recvBuff[6];
char recvIdx = 0;
char sendBuff[41];
char sendIdx = 0;
char pollRecv = 0;

void initXbee();


#endif	/* XBEE_H */

