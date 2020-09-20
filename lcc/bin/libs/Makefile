#
# Makefile for building the libraries
#

LCCDIR =../..
AR = ${LCCDIR}/../binutils/bin/ar

DIRS =ctype eeprintf errno math softfloat libsoftfloat stdio stdlib string

.PHONY:		all install clean

all:
		for i in $(DIRS) ; do \
		  $(MAKE) -r -C $$i all ; \
		done
		$(AR) -r c.lib ctype/*.o
		$(AR) -r c.lib errno/*.o
		$(AR) -r c.lib libsoftfloat/*.o
		$(AR) -r c.lib math/*.o
		$(AR) -r c.lib stdio/*.o
		$(AR) -r c.lib stdlib/*.o
		$(AR) -r c.lib string/*.o
		$(AR) -rsv c.lib

clean:
		for i in $(DIRS) ; do \
		  $(MAKE) -r -C $$i clean ; \
		done
		rm -f *~
