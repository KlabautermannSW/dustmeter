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

    file        errors.c

    date        02.01.2019

    author      Uwe Jantzen (Klabautermann@Klabautermann-Software.de)

    brief       Show error message to stderr.

    details

    project     dustmeter
    target      Linux
    begin       30.12.2018

    note

    todo

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "errors.h"


#define START_OF_SDS011_ERRORS                          256


static const char * errors[] =
    {
    "port name too long",
    "no port given",
    "opening serial port failed",
    "serial port is locked",
    "unable to initialize serial port",
    "general communication",
    "serial port read",
    "serial port read",
    "SDS011 CRC",
    "SDS011 illegal command id received",
    "out of memory",
    0
    };


/*  function        void showerr( int err )

    brief           Shows error description if available and verbose mode is
                    enabled.

    param[in]       int err, error code
*/
void showerr( int err )
    {
    int idx;
    int count;

    if( err == NOERR )
        return;

    if( err > NOERR )
        strerror(err);

    idx = (err * -1) - START_OF_SDS011_ERRORS;                                  // switch error code to index into the text array

    if( is_verbose() )
        {
        for( count = 0; errors[count]; ++count )
            {
            if( idx == count )
                break;
            }

        if( errors[count] )
            fprintf(stderr, "Error %3d : %s\n", err, errors[count]);
        else
            fprintf(stderr, "Error %3d : unknown error code !\n", err);
        }
    }
