include ../Makefile.inc
TARGET = as1 as2

SRC1 = as11.s as12.s as13.s as14.s as15.s as16.s as17.s as18.s as19.s as1.s
SRC2 = as21.s as22.s as23.s as24.s as25.s as26.s as27.s as28.s as29.s

all: $(TARGET)

as1: $(SRC1)
	$(AS) - $^
	$(LD) a.out $(LIBC)
	mv a.out $@

as1.s: as1.c
	$(CC) -S $<

as2: $(SRC2)
	$(AS) $^
	$(LD) a.out
	mv a.out $@

test: as1 as2
	$(RUN) -r $(V6ROOT) as1 $(SRC2)
	$(LD) a.out
	cmp a.out as2

clean:
	rm -f $(TARGET) a.out
