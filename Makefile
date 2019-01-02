#
#   MIT License
#
#   Copyright (c) 2018 Uwe Jantzen
#
#   Permission is hereby granted, free of charge, to any person obtaining a copy
#   of this software and associated documentation files (the "Software"), to deal
#   in the Software without restriction, including without limitation the rights
#   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#   copies of the Software, and to permit persons to whom the Software is
#   furnished to do so, subject to the following conditions:
#
#   The above copyright notice and this permission notice shall be included in all
#   copies or substantial portions of the Software.
#
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#   SOFTWARE.
#
#   Klabautermann Software
#   Uwe Jantzen
#   Weingartener Straße 33
#   76297 Stutensee
#   Germany
#
#   file        Makefile
#
#   date        02.01.2019
#
#   author      Uwe Jantzen (jantzen@klabautermann-software.de)
#
#   brief       Makefile for dustmeter
#
#   details     Rebuilds all necessary files to create dustmeter executable.
#
#   project     dustmeter
#   target      Linux
#   begin       31.12.2018
#
#   note
#
#   todo
#

# debug code
# .PHONY: printvars
# printvars:
#	@$(foreach V,$(sort $(.VARIABLES)), \
	$(if $(filter-out environ% default automatic, \
	$(origin $V)),$(info $V=$($V) ($(value $V)))))

vpath %.h include
vpath %.c src
vpath %.o obj

CC  := gcc

DSRC := src
DINC := include
DOBJ := obj
DBIN := bin

OBJ := dustmeter.o sds011.o serial.o debug.o utils.o errors.o getargs.o globals.o version.o

VERSION := 0.01

CC_LDFLAGS = -lm
# use this for the release version
#CFLAGS = `-I $(DINC) -Wall -O3 -DVERSION=\"$(VERSION)\"
# use this for the debug version
CFLAGS = -I $(DINC) -Wall -O3 -DVERSION=\"$(VERSION)\" -D_DEBUG_

.c.o: $(DOBJ)
	$(CC) $(CFLAGS) -c $< -o $(DOBJ)/$@

####### Build rules

all: install dustmeter


dustmeter : $(OBJ) $(DBIN)
	$(CC) $(CC_LDFLAGS) -o $(DBIN)/$@ \
		$(DOBJ)/dustmeter.o \
		$(DOBJ)/sds011.o \
		$(DOBJ)/serial.o \
		$(DOBJ)/debug.o \
		$(DOBJ)/utils.o \
		$(DOBJ)/errors.o \
		$(DOBJ)/getargs.o \
		$(DOBJ)/globals.o \
		$(DOBJ)/version.o


dustmeteri.o : dustmeter.c getargs.h version.h globals.h sds011.h serial.h debug.h

sds011.o : sds011.c errors.h globals.h debug.h serial.h sds011.h

serial.o : serial.c serial.h debug.h sds011.h

debug.o : debug.c globals.h

utils.o : utils.c globals.h

errors.o : errors.c errors.h globals.h

getargs.o : getargs.c globals.h debug.h utils.h getargs.h

globals.o : globals.c globals.h debug.h

version.o : FORCE

FORCE:

####### create object and executable directory if missing
install:
	@if [ ! -d  $(DBIN) ]; then mkdir $(DBIN); fi
	@if [ ! -e  $(DOBJ) ]; then mkdir $(DOBJ); fi

####### cleanup all objects and executables
.PHONY clean:
clean:
	-rm -v -f $(DOBJ)/* $(DBIN)/*
	-rmdir $(DOBJ) $(DBIN)
