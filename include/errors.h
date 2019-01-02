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

    file        errors.h

    date        02.01.2019

    author      Uwe Jantzen (Klabautermann@Klabautermann-Software.de)

    brief       Defines application specific erros.

    details

    project     dustmeter
    target      Linux
    begin       30.12.2018

    note

    todo

*/


#ifndef __ERRORS_H__
#define __ERRORS_H__


#include <errno.h>


#define NOERR                                         0

#define ERR_NAME                                    -256                        // port name too long
#define ERR_NO_PORT                                 -257                        // no port given
#define ERR_NO_HANDLE                               -258                        // opening serial port failed
#define ERR_LOCKED                                  -259                        // serial port is locked
#define ERR_INIT_PORT                               -260                        // Unable to initialize serial port

#define ERR_COMM_ERR                                -261                        // general serial communications error
#define ERR_COMM_READ                               -262                        // error reading from SDS011
#define ERR_COMM_WRITE                              -263                        // error writng to SDS011

#define ERR_CRC                                     -264                        // crc erro in packet read from SDS011
#define ERR_ILL_COMMAND_ID                          -265

#define ERR_OUT_OF_MEMORY                           -266                        // malloc error


extern void showerr( int err );


#endif  // __ERRORS_H__
