include ../../Makefile.inc
TARGET = as2
SRC = as21.s as22.s as23.s as24.s as25.s as26.s as27.s as28.s as29.s

all: $(TARGET)

as2: $(SRC)
	$(AS) $^
	$(LD) a.out
	mv a.out $@

clean:
	rm -f $(TARGET) a.out
