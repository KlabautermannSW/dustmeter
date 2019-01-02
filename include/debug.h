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

    file        debug.h

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


#ifndef __DEBUG_H__
#define __DEBUG_H__


#include <stdint.h>


#ifdef _DEBUG_
 #define debug(...)                         Debug(__VA_ARGS__)
 #define dump(buffer, len)                  Dump((buffer), (len))
#else
 #define debug(...)
 #define dump(buffer, len)
#endif

extern void Debug( const char * format, ... );
extern void Dump( uint8_t * buffer, int len );
extern void verbose( const char * format, ... );


#endif  // __DEBUG_H__
