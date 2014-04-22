TOPDIR = ..
include $(TOPDIR)/Makefile.inc

TARGET = rkunix
CFLAGS = -O

all: $(TARGET)

lib1.a:
	cd ken && $(CC) $(CFLAGS) -c *.c
	cd ken && $(AR) r ../$@ main.o trap.o sig.o sysent.o
	cd ken && $(AR) r ../$@ *.o

lib2.a:
	cd dmr && $(CC) $(CFLAGS) -c *.c
	cd dmr && $(AR) r ../$@ *.o

conf/mkconf:
	cd conf && $(AS) m40.s
	cd conf && mv a.out m40.o
	cd conf && $(CC) mkconf.c
	cd conf && mv a.out mkconf

rkunix: lib1.a lib2.a conf/mkconf
	cd conf && (echo rk; echo tm; echo tc; echo done) | 7run mkconf
	cd conf && $(CC) -c c.c
	cd conf && $(AS) l.s
	cd conf && $(LD) -x a.out m40.o c.o ../lib1.a ../lib2.a
	cd conf && cp a.out ../$@

distrib: $(TARGET)
	cp $(TARGET) $(DESTDIR)

install: $(TARGET)
	cp $(TARGET) $(V6ROOT)
	$(STRIP) $(V6ROOT)/$(TARGET)

clean:
	cd ken && rm -f *.o
	cd dmr && rm -f *.o
	cd conf && rm -f mkconf c.c l.s a.out *.o
	rm -f lib1.a lib2.a rkunix
