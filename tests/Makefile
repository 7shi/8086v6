TARGET = 1.out 2.out
CC     = v6cc
AS     = v6as
LD     = v6ld
RUN    = 7run
V6ROOT = /usr/local/v6root

all: $(TARGET)

1.out: 1-s.o 1-c.o
	$(LD) $^ $(V6ROOT)/lib/libc.a
	mv a.out $@

1-s.o: 1-s.s
	$(AS) - $<
	mv a.out $@

1-c.o: 1-c.c
	$(CC) -c $<

2.out: 2-c.o 2-s.o
	$(CC) $^
	mv a.out $@

2-c.o: 2-c.c
	$(CC) -c $<

2-s.o: 2-s.s
	$(AS) $<
	mv a.out $@

test: $(TARGET)
	$(RUN) 1.out
	$(RUN) 2.out

clean:
	rm -f $(TARGET) *.o a.out
