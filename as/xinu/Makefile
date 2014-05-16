TOPDIR = ../..
include ../Makefile.inc

TARGET = as1 as2
CSRCS1 = as11.c as12.c as13.c as14.c as15.c as16.c as17.c as18.c as19.c win32.c
CSRCS2 = as21.c as22.c as23.c as24.c as25.c as26.c as27.c as28.c as29.c win32.c
COBJS1 = $(CSRCS1:.c=.o)
COBJS2 = $(CSRCS2:.c=.o)
CC     = gcc

all: $(TARGET)

as1: $(COBJS1)
	$(CC) -o $@ $^

as2: $(COBJS2)
	$(CC) -o $@ $^

test: $(TARGET)
	$(MAKE) all-orig -C ..
	./as1 ../orig/as1?.s
	$(LD) a.out
	cmp a.out ../orig/as1
	./as1 ../orig/as2?.s
	$(LD) a.out
	cmp a.out ../orig/as2

clean:
	rm -f $(TARGET) *.exe *.o a.out
