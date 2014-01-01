include ../../Makefile.inc
TARGET = as1
SRC = as11.s as12.s as13.s as14.s as15.s as16.s as17.s as18.s as19.s

all: $(TARGET)

as1: $(SRC)
	$(AS) $^
	$(LD) a.out
	mv a.out $@

clean:
	rm -f $(TARGET) a.out
