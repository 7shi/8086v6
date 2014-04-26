TOPDIR = ../..
include ../Makefile.inc

TARGET = as1 as2
SRCS1 = as11.s as12.s as13.s as14.s as15.s as16.s as17.s as18.s as19.s
SRCS2 = as21.s as22.s as23.s as24.s as25.s as26.s as27.s as28.s as29.s

all: $(TARGET)

as1: $(SRCS1)
	$(AS) $^
	$(LD) a.out
	mv a.out $@

as2: $(SRCS2)
	$(AS) $^
	$(LD) a.out
	mv a.out $@

install: $(TARGET)
	cp as1 $(V6ROOT)/bin/as
	cp as2 $(V6ROOT)/lib/as2
	$(STRIP) $(V6ROOT)/bin/as
	$(STRIP) $(V6ROOT)/lib/as2

clean:
	rm -f $(TARGET) a.out
