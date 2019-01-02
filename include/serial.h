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

    file        serial.h

    date        02.01.2019

    author      Uwe Jantzen (jantzen@klabautermann-software.de)

    brief       Handle serial communication to a SERIAL Laser Fine Dust Sensor.

    details     This driver provides low level access functions to a SERIAL
                port.
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


#ifndef __H_SERIAL__
#define __H_SERIAL__


#include <stddef.h>
#include <stdint.h>
#include "errors.h"


extern int com_init( char * name );
extern int com_open( void );
extern int com_close( void );
extern size_t com_read( uint8_t * dst );
extern size_t com_write( uint8_t * src );
extern int com_flush( void );
extern int com_clear( void );


#endif  // __H_SERIAL__
