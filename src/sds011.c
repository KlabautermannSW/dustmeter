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

    file        sds011.c

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


#include <stdlib.h>         // *********************** for exit() only
#include <string.h>
#include "errors.h"
#include "debug.h"
#include "serial.h"
#include "sds011.h"


#define REC                              0
#define SEND                             1

#define HEAD                             0
#define COMMAND_ID                       1
#define DATA_01                          2
#define DATA_02                          3
#define DATA_03                          4
#define DATA_04                          5
#define DATA_05                          6
#define DATA_06                          7
#define DATA_07                          8
#define DATA_08                          9
#define DATA_09                         10
#define DATA_10                         11
#define DATA_11                         12
#define DATA_12                         13
#define DATA_13                         14
#define DATA_14                         15
#define DATA_15                         16
#define CRC                             17
#define TAIL                            18

#define HEAD_VAL                        0xaa
#define TAIL_VAL                        0xab


static uint8_t rec_packet[REC_BUFFER_LENGT];
static uint8_t send_packet[SEND_BUFFER_LENGTH];


/*  function        static void _checksum( int dir )

    brief           Calculates the data checksum over the given data length

    param[in]       int dir, REC (0), SEND (1)

    return          uint8_t, calculated checksum
*/
static uint8_t _checksum( int dir )
    {
    int i;
    int crc;
    int max;
    uint8_t * buffer;

    if( dir )
        {
        buffer = send_packet;
        max = CRC;
        }
    else
        {
        buffer = rec_packet;
        max = DATA_07;
        }

    Debug("Calculate checksum over %d byteś: ", max);
    for (i = DATA_01, crc = 0; i < max; ++i )
        crc += *(buffer+i);

    crc = crc & 0xff;
    if( dir )
        *(buffer + CRC) = (uint8_t)crc;

    Debug("0x%02x\n", crc);
    return (uint8_t)crc;
    }


/*  function        void sds011_init( void )

    brief           Initializes the send buffer
*/
void sds011_init( void )
    {
    send_packet[HEAD] = HEAD_VAL;
    send_packet[TAIL] = TAIL_VAL;
    }


/*  function        void sds011_set_reporting_mode( uint8_t mode )

    brief           Set data reporting mode

    param[in]       uint8_t mode

    return          int, error
*/
int sds011_set_reporting_mode( uint8_t mode )
    {
    send_packet[COMMAND_ID] = 0xb4;
    send_packet[DATA_01] = 2;
    send_packet[DATA_02] = 1;
    send_packet[DATA_03] = mode;
    memset(send_packet + DATA_04, 0, DATA_14 - DATA_04);
    send_packet[DATA_14] = 0xff;
    send_packet[DATA_15] = 0xff;
    _checksum(SEND);
    com_write(send_packet);
    com_read(rec_packet);
    return 0;
    }


/*  function        int sds011_get_reporting_mode( uint8_t * mode )

    brief           Get data reporting mode

    param[out]      uint8_t * mode

    return          int, error
*/
int sds011_get_reporting_mode( uint8_t * mode )
    {
    int error;

    send_packet[COMMAND_ID] = 0xb4;
    send_packet[DATA_01] = 2;
    send_packet[DATA_02] = 0;
    memset(send_packet + DATA_04, 0, DATA_14 - DATA_04);
    send_packet[DATA_14] = 0xff;
    send_packet[DATA_15] = 0xff;
    _checksum(SEND);
    com_write(send_packet);
    com_read(rec_packet);

    if( rec_packet[DATA_07] != _checksum(REC) )
        {
        error = ERR_CRC;
        goto err_sds011_get_reporting_mode;
        }
    if( rec_packet[COMMAND_ID] != 0xc5 )
        {
        error = ERR_ILL_COMMAND_ID;
        goto err_sds011_get_reporting_mode;
        }

    *mode = rec_packet[DATA_03];
    return NOERR;

err_sds011_get_reporting_mode:
    showerr(error);
    return error;
    }


/*  function        int sds011_get_data( double * ppm_25, double * ppm_10 )

    brief           Read measured data of fine dust from the SDS011

    param[out]      double * ppm_25
    param[out]      double * ppm_10

    return          int, error
*/
int sds011_get_data( double * ppm_25, double * ppm_10 )
    {
    int error;
    int result;

    send_packet[COMMAND_ID] = 0xb4;
    send_packet[DATA_01] = 4;
    memset(send_packet + DATA_02, 0, DATA_14 - DATA_02);
    send_packet[DATA_14] = 0xff;
    send_packet[DATA_15] = 0xff;
    _checksum(SEND);
    com_write(send_packet);
    com_read(rec_packet);

    if( rec_packet[DATA_07] != _checksum(REC) )
        {
        error = ERR_CRC;
        goto err_sds011_get_data;
        }
    if( rec_packet[COMMAND_ID] != 0xc0 )
        {
        error = ERR_ILL_COMMAND_ID;
        goto err_sds011_get_data;
        }

    result = rec_packet[DATA_02] + (rec_packet[DATA_03] * 256);
    *ppm_25 = result / 10.0;
    result = rec_packet[DATA_04] + (rec_packet[DATA_05] * 256);
    *ppm_10 = result / 10.0;

    return NOERR;

err_sds011_get_data:
    showerr(error);
    return error;
    }


/*  function        int sds011_set_id( uint8_t id1, uint8_t id2 )

    brief           Set device id

    param[in]       uint8_t id1
    param[in]       uint8_t id2

    return          int, error
*/
int sds011_set_id( uint8_t id1, uint8_t id2 )
    {
    send_packet[COMMAND_ID] = 0xb4;
    send_packet[DATA_01] = 5;
    memset(send_packet + DATA_02, 0, DATA_12 - DATA_02);
    send_packet[DATA_12] = id1;
    send_packet[DATA_13] = id2;
    send_packet[DATA_14] = 0xff;
    send_packet[DATA_15] = 0xff;
    _checksum(SEND);
    com_write(send_packet);
    com_read(rec_packet);
    return 0;
    }


/*  function        int sds011_set_sleep_mode( uint8_t mode )

    brief           Set data reporting mode

    param[in]       uint8_t mode

    return          int, error
*/
int sds011_set_sleep_mode( uint8_t mode )
    {
    send_packet[COMMAND_ID] = 0xb4;
    send_packet[DATA_01] = 6;
    send_packet[DATA_02] = 1;
    send_packet[DATA_03] = mode;
    memset(send_packet + DATA_04, 0, DATA_14 - DATA_04);
    send_packet[DATA_14] = 0xff;
    send_packet[DATA_15] = 0xff;
    _checksum(SEND);
    com_write(send_packet);
    com_read(rec_packet);
    return 0;
    }


/*  function        int sds011_get_sleep_mode( uint8_t * mode )

    brief           Get data reporting mode

    param[out]      uint8_t * mode

    return          int, error
*/
int sds011_get_sleep_mode( uint8_t * mode )
    {
    int error;

    send_packet[COMMAND_ID] = 0xb4;
    send_packet[DATA_01] = 6;
    send_packet[DATA_02] = 0;
    memset(send_packet + DATA_04, 0, DATA_14 - DATA_04);
    send_packet[DATA_14] = 0xff;
    send_packet[DATA_15] = 0xff;
    _checksum(SEND);
    com_write(send_packet);
    com_read(rec_packet);

    if( rec_packet[DATA_07] != _checksum(REC) )
        {
        error = ERR_CRC;
        goto err_sds011_get_reporting_mode;
        }
    if( rec_packet[COMMAND_ID] != 0xc5 )
        {
        error = ERR_ILL_COMMAND_ID;
        goto err_sds011_get_reporting_mode;
        }

    *mode = rec_packet[DATA_03];
    return NOERR;

err_sds011_get_reporting_mode:
    showerr(error);
    return error;
    }


/*  function        int sds011_set_working_period( uint8_t minutes )

    brief           Set working period in minutes

    param[in]       uint8_t minutes

    return          int, error
*/
int sds011_set_working_period( uint8_t minutes )
    {
    send_packet[COMMAND_ID] = 0xb4;
    send_packet[DATA_01] = 8;
    send_packet[DATA_02] = 1;
    send_packet[DATA_03] = minutes;
    memset(send_packet + DATA_04, 0, DATA_14 - DATA_04);
    send_packet[DATA_14] = 0xff;
    send_packet[DATA_15] = 0xff;
    _checksum(SEND);
    com_write(send_packet);
    com_read(rec_packet);
    return 0;
    }


/*  function        int sds011_get_working_period( uint8_t * minutes )

    brief           Get working period in minutes

    param[out]      uint8_t * minutes

    return          int, error
*/
int sds011_get_working_period( uint8_t * minutes )
    {
    int error;

    send_packet[COMMAND_ID] = 0xb4;
    send_packet[DATA_01] = 8;
    send_packet[DATA_02] = 0;
    memset(send_packet + DATA_03, 0, DATA_14 - DATA_03);
    send_packet[DATA_14] = 0xff;
    send_packet[DATA_15] = 0xff;
    _checksum(SEND);
    com_write(send_packet);
    com_read(rec_packet);

    if( rec_packet[DATA_07] != _checksum(REC) )
        {
        error = ERR_CRC;
        goto err_sds011_get_reporting_mode;
        }
    if( rec_packet[COMMAND_ID] != 0xc5 )
        {
        error = ERR_ILL_COMMAND_ID;
        goto err_sds011_get_reporting_mode;
        }

    *minutes = rec_packet[DATA_03];
    return NOERR;

err_sds011_get_reporting_mode:
    showerr(error);
    return error;
    }


/*  function        int sds011_get_working_period( uint8_t * minutes )

    brief           Get working period in minutes

    param[out]      uint8_t * minutes

    return          int, error
*/
int sds011_get_firmware_version( uint8_t * year, uint8_t * month, uint8_t * day )
    {
    int error;

    send_packet[COMMAND_ID] = 0xb4;
    send_packet[DATA_01] = 7;
    memset(send_packet + DATA_02, 0, DATA_14 - DATA_02);
    send_packet[DATA_14] = 0xff;
    send_packet[DATA_15] = 0xff;
    _checksum(SEND);
    com_write(send_packet);
    com_read(rec_packet);

    if( rec_packet[DATA_07] != _checksum(REC) )
        {
        error = ERR_CRC;
        goto err_sds011_get_reporting_mode;
        }
    if( rec_packet[COMMAND_ID] != 0xc5 )
        {
        error = ERR_ILL_COMMAND_ID;
        goto err_sds011_get_reporting_mode;
        }

    *year = rec_packet[DATA_02];
    *month = rec_packet[DATA_03];
    *day = rec_packet[DATA_04];
    return NOERR;

err_sds011_get_reporting_mode:
    showerr(error);
    return error;
    }
