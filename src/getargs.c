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

    file        getargs.c

    date        02.01.2019

    author      Uwe Jantzen (jantzen@klabautermann-software.de)

    brief       Read command line arguments

    details

    project     dustmeter
    target      Linux
    begin       30.12.2018

    note

    todo

*/


#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "globals.h"
#include "debug.h"
#include "utils.h"
#include "getargs.h"


/*  function        void getargs( int argc, char *argv[] )

    brief           Handles command line parameters

    param[in]       int argc, number of command line parameters
    param[in]       char *argv[], command line parameter list

    return          int
*/
void getargs( int argc, char *argv[] )
    {
    int option = 0;

    while( ( option = getopt(argc, argv, "f:o:vdh?") ) != -1 )
        {
        switch( option )
            {
            case 'f':
                set_conf_file(optarg);                                          // error handling missing !!
                break;
            case 'o':
                set_outfile_name(optarg);                                       // error handling missing !!
                break;
            case 'v':
                set_verbose(1);
                break;
#ifdef _DEBUG_
            case 'd':
                set_debug(1);
                break;
#endif  // _DEBUG_
            case 'h':
            case '?':
            default:
                showhelp(argv[0]);
                break;
            }
        }
    }
