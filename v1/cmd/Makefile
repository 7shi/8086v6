TOPDIR = ../..
include $(TOPDIR)/Makefile.inc

TARGET = init sh
AS     = ../../as/cross/as
AFLAGS = -2

all: $(TARGET)

init: $(AS) init.s
sh: $(AS) sh.s

init sh:
	$(AS) $(AFLAGS) init.s
	mv a.out $@

$(AS):
	$(MAKE) -C `dirname $@`

clean:
	rm -f $(TARGET)
