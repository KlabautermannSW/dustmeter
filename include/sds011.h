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

    file        sds011.h

    date        02.01.2019

    author      Uwe Jantzen (jantzen@klabautermann-software.de)

    brief       Handle access to a SDS011 Laser Fine Dust Sensor.

    details     This driver provides access functions to a SDS011 Laser Fine
                Dust Sensor.

    project     dustmeter
    target      Linux
    begin       31.12.2018

    note

    todo

*/


#ifndef __SDS011_H__
#define __SDS011_H__


#include <stdint.h>


#define REC_BUFFER_LENGT                            10
#define SEND_BUFFER_LENGTH                          19

#define DATA_REPORTING_MODE_ACTIVE                  0
#define DATA_REPORTING_MODE_QUERY                   1


extern void sds011_init( void );
extern int sds011_set_reporting_mode( uint8_t mode );
extern int sds011_get_reporting_mode( uint8_t * mode );
extern int sds011_get_data( double * ppm_25, double * ppm_10 );
extern int sds011_set_id( uint8_t id1, uint8_t id2 );
extern int sds011_set_sleep_mode( uint8_t mode );
extern int sds011_get_sleep_mode( uint8_t * mode );
extern int sds011_set_working_period( uint8_t minutes );
extern int sds011_get_working_period( uint8_t * minutes );
extern int sds011_get_firmware_version( uint8_t * year, uint8_t * month, uint8_t * day );


#endif  // __SDS011_H__
