TOPDIR = ../..
include ../Makefile.inc

TARGET = as
CSRCS = as11.c as12.c as13.c as14.c as15.c as18.c as19.c \
        as21.c as22.c as23.c as24.c as26.c as27.c as28.c utils.c
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
