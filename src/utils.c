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

    file        utils.c

    date        02.01.2019

    author      Uwe Jantzen (Klabautermann@Klabautermann-Software.de)

    brief       Some useful functions

    details

    project     dustmeter
    target      Linux
    begin       30.12.2018

    note

    todo

*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "globals.h"


/*  function        void showhelp( char * name )

    brief           Print out help text

    param[in]       char * name, the application's name
*/
void showhelp( char * name )
    {
    printf("Usage:\n");
//    printf("        %s [options] [-o <outfile>] [-f <conffile>]\n", name);
    printf("        %s [options] [-f <conffile>]\n", name);
    printf("Options:\n");
    printf("        -f <conffile> configuration file,\n");
    printf("                      if no configuration file name is given the file \"conf/sds011.conf\" is used\n");
//    printf("        -o <outfile>  file to put the data in,\n");
//    printf("                      if not set data is printed to screen\n");
    printf("        -v            enable verbose mode\n");
#ifdef _DEBUG_
    printf("        -d            enable debug mode\n");
#endif  //  _DEBUG_
    printf("\n");
    printf("        -h / -?       show this help then stop without doing anything more\n");
    printf("\n");
    printf("\n");
    exit(0);
    }
