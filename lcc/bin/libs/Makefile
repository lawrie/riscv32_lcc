#
# Makefile for building the libraries
#

LCCDIR =../..
AR = ${LCCDIR}/../binutils/bin/ar
AS = ${LCCDIR}/../binutils/bin/as

DIRS =ctype eeprintf errno math softfloat libsoftfloat stdio stdlib string time

.PHONY:		all clean

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
		$(AR) -r c.lib time/*.o
		$(AR) -rsv c.lib
		$(AS) -o crt0.o crt0.s

clean:
		for i in $(DIRS) ; do \
		  $(MAKE) -r -C $$i clean ; \
		done
		rm -f *.o
		rm -f *~
