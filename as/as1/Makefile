TOPDIR = ../..
include ../Makefile.inc

TARGET = as1
SSRCS  = as11.s as12.s as13.s as14.s as15.s as16.s as17.s as18.s as19.s
CSRCS  = $(SSRCS:.s=c.c) utils.c
COBJS  = $(CSRCS:.c=.o)

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
	cd ../orig && $(RUN) -r $(V6ROOT) ../as1/as1 as1?.s
	mv ../orig/a.out .
	$(LD) a.out
	cmp a.out ../orig/as1
	cd ../orig && $(RUN) -r $(V6ROOT) ../as1/as1 as2?.s
	mv ../orig/a.out .
	$(LD) a.out
	cmp a.out ../orig/as2

clean:
	rm -f $(TARGET) *.o a.out $(DESTDIR)/bin/as
