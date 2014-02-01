TOPDIR = ../..
include $(TOPDIR)/Makefile.inc

TARGET = as2
SSRCS = as21.s as22.s as23.s as24.s as25.s as26.s as27.s as28.s as29.s
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
	mkdir -p $(DESTDIR)/lib
	cp $< $(DESTDIR)/lib

test: dest
	$(MAKE) orig -C ..
	$(RUN) -r $(DESTDIR) $(V6ROOT)/bin/as ../as1.orig/as1?.s
	$(LD) a.out
	cmp a.out ../as1.orig/as1
	$(RUN) -r $(DESTDIR) $(V6ROOT)/bin/as ../as2.orig/as2?.s
	$(LD) a.out
	cmp a.out ../as2.orig/as2

clean:
	rm -f $(TARGET) *.o a.out $(DESTDIR)/lib/as2
