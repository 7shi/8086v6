TOPDIR = ../..
include $(TOPDIR)/Makefile.inc

TARGET = as1
SSRCS = as11.s as12.s as13.s as14.s as15.s as16.s as17.s as18.s as19.s
CSRCS = $(SSRCS:.s=c.c)
COBJS = $(CSRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(TARGET).o $(COBJS)
	$(CC) $^
	mv a.out $@

$(TARGET).o: $(SSRCS)
	rm -f a.out
	$(AS) - $^
	mv a.out $@

.c.o:
	$(CC) -c $<

dest: $(TARGET)
	mkdir -p $(DESTDIR)/bin
	cp $< $(DESTDIR)/bin/as

test: $(TARGET)
	$(MAKE) orig -C ..
	$(RUN) -r $(V6ROOT) as1 ../as1.orig/as1?.s
	$(LD) a.out
	cmp a.out ../as1.orig/as1
	$(RUN) -r $(V6ROOT) as1 ../as2.orig/as2?.s
	$(LD) a.out
	cmp a.out ../as2.orig/as2

clean:
	rm -f $(TARGET) *.o a.out $(DESTDIR)/bin/as
