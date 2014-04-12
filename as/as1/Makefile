TOPDIR = ../..
include $(TOPDIR)/Makefile.inc

TARGET = as1
SSRCS = as11.s as12.s as13.s as14.s as15.s as16.s as17.s as18.s as19.s
CSRCS = $(SSRCS:.s=c.c) utils.c
COBJS = $(CSRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(COBJS)
	$(CC) $^
	mv a.out $@

.c.o:
	$(CC) -c $<

utils.o: ../utils.c

dest: $(TARGET)
	mkdir -p $(DESTDIR)/bin
	cp $< $(DESTDIR)/bin/as

test: $(TARGET)
	$(MAKE) orig -C ..
	cd ../as1.orig && $(RUN) -r $(V6ROOT) ../as1/as1 as1?.s
	mv ../as1.orig/a.out .
	$(LD) a.out
	cmp a.out ../as1.orig/as1
	cd ../as2.orig && $(RUN) -r $(V6ROOT) ../as1/as1 as2?.s
	mv ../as2.orig/a.out .
	$(LD) a.out
	cmp a.out ../as2.orig/as2

clean:
	rm -f $(TARGET) *.o a.out $(DESTDIR)/bin/as
