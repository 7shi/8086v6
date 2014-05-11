TOPDIR = ../..
include ../Makefile.inc

TARGET = as
CSRCS  = as1.c as2.c as3.c as4.c as5.c as6.c as7.c as8.c as9.c utils.c
COBJS  = $(CSRCS:.c=.o)
CC     = gcc

all: $(TARGET)

$(TARGET): $(COBJS)
	$(CC) -o $@ $^

#install: $(TARGET)
#	cp $(TARGET) $(V6ROOT)/bin/as
#	$(STRIP) $(V6ROOT)/bin/as

test: $(TARGET)
	$(MAKE) all-orig -C ..
	cd ../orig && ../as/as as1?.s
	mv ../orig/a.out .
	$(LD) a.out
	cmp a.out ../orig/as1
	cd ../orig && ../as/as as2?.s
	mv ../orig/a.out .
	$(LD) a.out
	cmp a.out ../orig/as2

clean:
	rm -f $(TARGET) *.o a.out

#conv:
#	perl -pi -e "s/=([\+\-\*\/|\&])/\$$1=/g" *.c
