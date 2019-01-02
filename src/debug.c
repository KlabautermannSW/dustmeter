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

    file        debug.c

    date        01.01.2019

    author      Uwe Jantzen (jantzen@klabautermann-software.de)

    brief       debugging gadgets

    details

    project     dustmeter
    target      Linux
    begin       30.12.2018

    note

    todo

*/


#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include "globals.h"


/*  function        void Debug( const char * format, ... )

    brief           Prints out debug data to stderr if debug is enabled.

    param[in]       const char * format, format string for printing
    param[in]       ..., parameters referenced in format string
*/
void Debug( const char * format, ... )
    {
    va_list arg;

    if( is_debug() )
        {
        va_start(arg, format);
        vfprintf(stderr, format, arg);
        va_end(arg);
        fflush(stderr);
        }
    }


/*  function        void Dump( uint8_t * buffer, int len )

    brief           Dumps a buffer as a line of hex bytes

    param[in]       uint8_t * buffer
    param[in]       int len, number of bytes in buffer
*/
void Dump( uint8_t * buffer, int len )
    {
    int i;

    for( i = 0; i < len; ++i )
        {
        printf("0x%02x ", *(buffer+i));
        }
    printf("\n");
    }


/*  function        void verbose( const char * format, ... )

    brief           Print out data if verbose is enabled.

    param[in]       const char * format, format string for printing
    param[in]       ..., parameters referenced in format string
*/
void verbose( const char * format, ... )
    {
    va_list arg;

    if( is_verbose() )
        {
        va_start(arg, format);
        vprintf(format, arg);
        va_end(arg);
        fflush(stdout);
        }
    }
