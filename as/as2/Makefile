TOPDIR = ../..
include ../Makefile.inc

TARGET = as2
SSRCS  = as21.s as22.s as23.s as24.s as26.s as27.s as28.s as29.s
CSRCS  = $(SSRCS:.s=c.c) utils.c
COBJS  = $(CSRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(COBJS)
	$(CC) $^
	mv a.out $@

utils.o: ../utils.c

install: $(TARGET)
	cp $(TARGET) $(V6ROOT)/lib/as2
	$(STRIP) $(V6ROOT)/lib/as2

distrib: $(TARGET)
	mkdir -p $(DESTDIR)/lib
	cp $< $(DESTDIR)/lib

test: distrib
	$(MAKE) all-orig -C ..
	cd ../orig && $(RUN) -r $(DESTDIR) $(V6ROOT)/bin/as as1?.s
	mv ../orig/a.out .
	$(LD) a.out
	cmp a.out ../orig/as1
	cd ../orig && $(RUN) -r $(DESTDIR) $(V6ROOT)/bin/as as2?.s
	mv ../orig/a.out .
	$(LD) a.out
	cmp a.out ../orig/as2

clean:
	rm -f $(TARGET) *.o a.out $(DESTDIR)/lib/as2
