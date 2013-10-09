/*
 * File:   main.c
 * Author: Colin
 *
 * Created on October 7, 2013, 8:55 PM
 */

#include <p18cxxx.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


void main(void) {

    /*if(FIRST_STARTUP == true)
    {
        initial_detumble();
    }
    */
    time_t currTime;
    time_t prevSendDataTime;
    time_t prevGetDataTime;
    time_t sendInterval;
    time_t getInterval;
    time_t prevReadGPSTime;
    time_t gpsInterval;

    if(first_run = 1)
    {
        while()
        {
            
        }

        first_run = 0;
    }

    while(1)
    {
        currTime = time((time_t *));

        if(currTime >= prevSendDataTime + sendInterval)
        {
            prevSendDataTime = currTime;
            //sendComm(data);
        }

        else if(currTime >= prevGetDataTime + getInterval)
        {
            prevGetDataTime = currTime;
        }

        else if(currTime >= prevReadGPSTime + gpsInterval)
        {
            readGPS();
            determineVelocity();
            prevReadGPSTime = currTime;
        }

        else if(correctAttitude == 1)
        {
            correct_attitude(angle);

            correctAttitude = 0;
        }

        else if(commandReady == 1)
        {
            process_command(command);

            commandReady = 0;
        }

        else if(actuateBooms = 1)
        {
            actuate_booms(angle);

            actuateBooms = 0;
        }

        else if(currTime >= prevTempReadTime + tempReadInterval)
        {
            prevTempReadTime = currTime;

            read_temperature();
        }


    }
    
}
