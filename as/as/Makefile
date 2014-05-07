TOPDIR = ../..
include ../Makefile.inc

TARGET = as
CSRCS = as1.c as2.c as3.c as4.c as5.c as6.c as7.c as8.c as9.c utils.c
COBJS = $(CSRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(COBJS)
	$(CC) $^
	mv a.out $@

utils.o: ../utils.c

install: $(TARGET)
	cp $(TARGET) $(V6ROOT)/bin/as
	$(STRIP) $(V6ROOT)/bin/as

distrib: $(TARGET)
	mkdir -p $(DESTDIR)/bin
	cp $< $(DESTDIR)/bin/as

test: $(TARGET)
	$(MAKE) all-orig -C ..
	cd ../orig && $(RUN) ../as/as as1?.s
	mv ../orig/a.out .
	$(LD) a.out
	cmp a.out ../orig/as1
	cd ../orig && $(RUN) ../as/as as2?.s
	mv ../orig/a.out .
	$(LD) a.out
	cmp a.out ../orig/as2

clean:
	rm -f $(TARGET) *.o a.out $(DESTDIR)/bin/as
