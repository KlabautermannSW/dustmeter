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

    file        serial.c

    date        02.01.2019

    author      Uwe Jantzen (jantzen@klabautermann-software.de)

    brief       Handle serial communication to a SDS011 Laser Fine Dust Sensor.

    details     This driver provides low level access functions to a SERIAL port.
                The API includes
                - com_init
                - com_open
                - com_close
                - com_read
                - com_write
                - com_flush
                - com_clear

    project     dustmeter
    target      Linux
    begin       31.12.2018

    note

    todo

*/


#include <error.h>
#include <sys/file.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include "debug.h"
#include "sds011.h"
#include "serial.h"


#define PORTNAME_LEN                                255
static int the_handle = -1;                                                     // the serial port's handle
static char the_port[PORTNAME_LEN+1] = {0 };                                    // the serial port's name


/*  function        int com_init( char * name )

    brief           Initializes the serial line connection to the SDS011
                    Sensor connected to <name>

    param[in]       char * name, a string containing a device name like
                    /dev/ttyS0 or /dev/ttyUSB1

    return          int
*/
int com_init( char * name )
    {
    if( name == 0 )
        showerr(ERR_NO_PORT);

    Debug("Port name: %s\n", name);
    if( strlen(name) > 255 )
        return ERR_NAME;

    strncpy(the_port, name, PORTNAME_LEN);

    return NOERR;
    }


/*  function        int com_open( void )

    brief           opens a serial connection to a SDS011 Sensor using
                    the port given by com_init()

    return          int
*/
int com_open( void )
    {
    struct termios control;
    int err = NOERR;

    if( strlen(the_port) == 0 )
        return ERR_NO_PORT;

    the_handle = open(the_port, O_RDWR | O_NOCTTY);
    if( the_handle < 0 )
        return ERR_NO_HANDLE;

    if( flock(the_handle, LOCK_EX) < 0 )
        {
        err = ERR_LOCKED;
        goto finish_com_open;
        }

    memset(&control, 0, sizeof(control));

    // Serial control options
    control.c_cflag &= ~PARENB;                         // No parity
    control.c_cflag &= ~CSTOPB;                         // One stop bit
    control.c_cflag &= ~CSIZE;                          // Character size mask
    control.c_cflag |= CS8;                             // character size 8 bits
    control.c_cflag |= CREAD;                           // enable receiver
    control.c_cflag &= ~HUPCL;                          // No "hangup"
    control.c_cflag &= ~CRTSCTS;                        // No flowcontrol
    control.c_cflag |= CLOCAL;                          // ignore modem control lines

    cfsetispeed(&control, B9600);
    cfsetospeed(&control, B9600);

    control.c_lflag = 0;
    control.c_iflag = IGNBRK|IGNPAR;
    control.c_oflag &= ~OPOST;
    control.c_cc[VTIME] = 10;                           // 1 sec timeout
    control.c_cc[VMIN] = 0;                             // block read to first char

    if( tcsetattr(the_handle, TCSANOW, &control) < 0 )
        {
        err = ERR_INIT_PORT;
        goto finish_com_open;
        }

    tcflush(the_handle, TCIOFLUSH);

    return err;

finish_com_open:
    close(the_handle);
    return err;
    }


/*  function        int com_close( void )

    brief           close the connection to the SDS011 Sensor.

    return          int
*/
int com_close( void )
    {
    int portstatus;

    // simulate the heavyweather behaviour
    tcflush(the_handle, TCIOFLUSH);

    usleep(100000);

    ioctl(the_handle, TIOCMGET, &portstatus);           // get current port status
    portstatus |= TIOCM_DTR;
    ioctl(the_handle, TIOCMSET, &portstatus);           // set current port status
    usleep(3000);
    portstatus &= ~TIOCM_DTR;
    portstatus &= ~TIOCM_RTS;
    ioctl(the_handle, TIOCMSET, &portstatus);           // set current port status

    tcflush(the_handle, TCIOFLUSH);

    close(the_handle);

    return NOERR;
    }


/*  function        size_t com_read( uint8_t * dst )

    brief           reads bytes from the SDS011 Sensor until no more bytes are
                    sent or the destination buffer is full

    param[out]      uint8_t * dst, buffer to read into

    return          size_t, number of bytes really read
*/
size_t com_read( uint8_t * dst )
    {
    int i;

//    do
//        {
        i = read(the_handle, (uint8_t *)dst, REC_BUFFER_LENGT);
//        dst += i;
//        }
//    while( i == 0 && errno == EINTR );
    Dump(dst, i);

    return i;
    }


/*  function        size_t com_write( uint8_t * src )

    brief           writes the contents of src to the SDS011 Sensor

    param[in]       data_t * src, buffer to write

    return          size_t, number of bytes really written
*/
size_t com_write( uint8_t * src )
    {
    int n = SEND_BUFFER_LENGTH;

    Dump(src, SEND_BUFFER_LENGTH);
    n = write(the_handle, src, n);

    tcdrain(the_handle);                                // wait for all output written

    return n;
    }


/*  function        int com_flush( void )

    brief           flushes output buffer

    return          int
*/
int com_flush( void )
    {
    if( tcflush(the_handle, TCOFLUSH) )
        return ERR_COMM_ERR;

    return NOERR;
    }


/*  function        int com_clear( void )

    brief           flushes input buffer

    return          int
*/
int com_clear( void )
    {
    if( tcflush(the_handle, TCIFLUSH) )
        return ERR_COMM_ERR;

    return NOERR;
    }
