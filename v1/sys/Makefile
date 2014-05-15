TOPDIR = ../..
include $(TOPDIR)/Makefile.inc

TARGET = unix
SRCS   = u0.s u1.s u2.s u3.s u4.s u5.s u6.s u7.s u8.s u9.s ux.s
AS     = ../../as/cross/as
AFLAGS = -2

all: $(TARGET)

$(TARGET): $(AS) $(SRCS1)
	$(AS) $(AFLAGS) $(SRCS)
	mv a.out $@
	v6nm $@ > $@.sym

$(AS):
	$(MAKE) -C `dirname $@`

clean:
	rm -f $(TARGET) $(TARGET).sym a.out
