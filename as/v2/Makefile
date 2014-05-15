TOPDIR = ../..
include ../Makefile.inc

TARGET = as1 as2
SRCS1  = as11.s as12.s as13.s as14.s as15.s as16.s as17.s as18.s as19.s
SRCS2  = as21.s as22.s as23.s as24.s as25.s as26.s as27.s as28.s as29.s
AS     = ../cross/as
AFLAGS = -v2

all: $(TARGET)

as1: $(AS) $(SRCS1)
	$(AS) $(AFLAGS) $(SRCS1)
	$(LD) a.out
	mv a.out $@

as2: $(AS) $(SRCS2)
	$(AS) $(AFLAGS) $(SRCS2)
	$(LD) a.out
	mv a.out $@

$(AS):
	$(MAKE) -C ../cross

clean:
	rm -f $(TARGET) a.out
