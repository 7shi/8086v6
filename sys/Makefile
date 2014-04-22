TARGET = rkunix

all: $(TARGET)

lib1.a:
	cd ken && v6cc -c -O *.c
	cd ken && v6ar r ../$@ main.o trap.o sig.o sysent.o
	cd ken && v6ar r ../$@ *.o

lib2.a:
	cd dmr && v6cc -c -O *.c
	cd dmr && v6ar r ../$@ *.o

conf/mkconf:
	cd conf && v6as m40.s
	cd conf && mv a.out m40.o
	cd conf && v6cc mkconf.c
	cd conf && mv a.out mkconf

rkunix: lib1.a lib2.a conf/mkconf
	cd conf && (echo rk; echo tm; echo tc; echo done) | 7run mkconf
	cd conf && v6cc -c c.c
	cd conf && v6as l.s
	cd conf && v6ld -x a.out m40.o c.o ../lib1.a ../lib2.a
	cd conf && cp a.out ../$@

clean:
	cd ken && rm -f *.o
	cd dmr && rm -f *.o
	cd conf && rm -f mkconf c.c l.s a.out *.o
	rm -f lib1.a lib2.a rkunix
