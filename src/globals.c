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

    file        globals.c

    date        02.01.2019

    author      Uwe Jantzen (Klabautermann@Klabautermann-Software.de)

    brief       Variables and functions that are needed globally in the
                project.

    details

    project     dustmeter
    target      Linux
    begin       30.12.2018

    note

    todo

*/


#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "globals.h"


#define FILENAME_LEN                        1024


static int verbose_flag = 0;
static int debug_flag = 0;
static char * the_conf_file_name = 0;
static char * the_outfile_name = 0;


/*  function        void set_verbose( int flag )

    brief           Sets the verbose flag's state

    param[in]       int flag, verbose flag
*/
void set_verbose( int flag )
    {
    verbose_flag = flag;
    }


/*  function        int is_verbose( void )

    brief           Returns verbose flag's state

    return          int, verbose flag's state
*/
int is_verbose( void )
    {
    return verbose_flag;
    }


/*  function        void set_debug( int flag )

    brief           Sets the debug flag's state

    param[in]       int flag, debug flag
*/
void set_debug( int flag )
    {
    debug_flag = flag;
    }


/*  function        int is_debug( void )

    brief           Returns debug flag's state

    return          int, debug flag's state
*/
int is_debug( void )
    {
    return debug_flag;
    }


/*  function        int set_conf_file( char * conf_file_name )

    brief           Copies the configuration file name into a global variable

    param[in]       char * conf_file_name

    return          int, error
*/
int set_conf_file( char * conf_file_name )
    {
    size_t len = strlen(conf_file_name) + 1;

    the_conf_file_name = (char *)malloc(len);
    if( !the_conf_file_name )
        return ERR_OUT_OF_MEMORY;

    strncpy(the_conf_file_name, conf_file_name, len);

    return NOERR;
    }


/*  function        int set_outfile_name( char * filename )

    brief           Copies the the log file's name from filename.

    param[in]       char * filename, log file's name
*/
int set_outfile_name( char * filename )
    {
    size_t len = strlen(filename) + 1;

    the_outfile_name = (char *)malloc(len);
    if( !the_outfile_name )
        return ERR_OUT_OF_MEMORY;

    strncpy(the_outfile_name, filename, len);

    return NOERR;
    }


/*  function        const char *  get_outfile_name( void )

    brief           Return the pointer to the log file's name.

    return          const char *, pointer to the log file's name
*/
const char *  get_outfile_name( void )
    {
    return the_outfile_name;
    }
