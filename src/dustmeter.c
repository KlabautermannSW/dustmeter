/*
    MIT License

    Copyright (c) 2018 Uwe Jantzen

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

    Klabautermann Software
    Uwe Jantzen
    Weingartener Straße 33
    76297 Stutensee
    Germany

    file        dustmeter.c

    date        02.01.2019

    author      Uwe Jantzen (jantzen@klabautermann-software.de)

    brief       Get data from a SDS011 Laser Fine Dust Sensor.

    details     This application provides
                - reading data
                - change settings
                - log data
                - push data to an ftp server

    project     dustmeter
    target      Linux
    begin       31.12.2018

    note

    todo

*/


#include <stdio.h>
#include <stdlib.h>
#include "getargs.h"
#include "version.h"
#include "globals.h"
#include "debug.h"
#include "sds011.h"
#include "serial.h"


static const char * name = "Fine Dust Scanner";


/*  function        int main( int argc, char *argv[] )

    brief           main function :
                        reads arguments
                        connect to a SDS011 device
                        read out data

    param[in]       int argc, number of command line parameters
    param[in]       char *argv[], command line parameter list

    return          int, error code
*/
int main( int argc, char *argv[] )
    {
    int handle;
    uint8_t data = 0x00;

    printf(title, name, version, compiledate);
    getargs(argc, argv);

    showerr(com_init("/dev/ttyUSB0"));
    sds011_init();

    Debug("SDS011 initialized\n");
    handle = com_open();
    if( handle < 0 )
        {
        showerr(handle);
        exit(handle);
        }
    Debug("Communication port for SDS011 opened\n");

    Debug("Set working time\n");
    if( sds011_set_working_period(1) == NOERR )
        printf("Working period is set %d minutes\n", 1);

    Debug("Get reporting mode\n");
    if( sds011_get_reporting_mode(&data) == NOERR )
        printf("Reporting mode is %s mode\n", ( data ) ? "query" : "active");

    Debug("Get sleep mode\n");
    if( sds011_get_sleep_mode(&data) == NOERR )
        printf("Sleep mode is %sing\n", ( data ) ? "work" : "sleep");

    Debug("Get working time\n");
    if( sds011_get_working_period(&data) == NOERR )
        printf("Working period is %d minutes\n", (int)data);

    com_close();

    printf("\n%s finished\n\n", name);

    return 0;
    }
