##
## Makefile for ectool
##
## Copyright (C) 2009 by coresystems GmbH
## written by Stefan Reinauer <stepan@coresystems.de>
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; version 2 of the License.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##

CC = gcc
CFLAGS = -O2 -Wall -W
PROGRAM = ectool
INSTALL = /usr/bin/env install
PREFIX  = /usr/local
OS_ARCH = $(shell uname)

ifeq ($(shell uname -o 2>/dev/null), Cygwin)
LDFLAGS = -lioperm
endif

ifeq ($(OS_ARCH), $(filter $(OS_ARCH), NetBSD OpenBSD))
LDFLAGS = -l$(shell uname -p)
endif

all: $(PROGRAM)

$(PROGRAM): ec.o ectool.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

install: $(PROGRAM)
	$(INSTALL) $(PROGRAM) $(PREFIX)/sbin

clean:
	rm -f *.o $(PROGRAM) junit.xml

distclean: clean

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -I. -o $@

.PHONY: all install clean distclean
