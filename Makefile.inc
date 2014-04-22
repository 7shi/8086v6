DESTDIR = $(TOPDIR)/dest
V6ROOT  = /usr/local/v6root
LIBC    = $(V6ROOT)/lib/libc.a
RUN     = 7run
CC      = v6cc
AS      = v6as
LD      = v6ld
STRIP   = v6strip
CFLAGS  = 

.c.o:
	$(CC) $(CFLAGS) -c $<

.s.o:
	$(AS) - $<
	mv a.out $@
