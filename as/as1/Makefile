include ../../Makefile.inc
TARGET = as1

SSRCS = as11.s as12.s as13.s as14.s as15.s \
		as16.s as17.s as18.s as19.s
CSRCS = as11c.c as12c.c as13c.c as14c.c as15c.c \
		as16c.c as17c.c as18c.c as19c.c
CASMS = $(CSRCS:.c=.s)
ASMS  = $(SSRCS) $(CASMS)

all: $(TARGET)

as1: $(ASMS)
	$(AS) - $^
	$(LD) a.out $(LIBC)
	mv a.out $@

.c.s:
	$(CC) -S $<

test: as1
	$(MAKE) -C ../as2
	$(RUN) -r $(V6ROOT) as1 ../as2/as2?.s
	$(LD) a.out
	cmp a.out ../as2/as2

clean:
	rm -f $(TARGET) $(COBJS) a.out 
