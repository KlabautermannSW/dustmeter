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

    file        globals.h

    date        01.01.2019

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


#ifndef __GLOBALS_H__
#define __GLOBALS_H__


extern int is_verbose( void );
extern void set_verbose( int flag );
extern void set_debug( int flag );
extern int is_debug( void );
extern int set_conf_file( char * conf_file_name );
extern int set_outfile_name( char * filename );
extern const char *  get_outfile_name( void );


#endif  // __GLOBALS_H__
