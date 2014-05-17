TOPDIR = ..
include Makefile.inc

all:
	$(MAKE) $@ -C orig
	$(MAKE) $@ -C as1
	$(MAKE) $@ -C as2
	$(MAKE) $@ -C as
	$(MAKE) $@ -C cross
	$(MAKE) $@ -C v2

all-orig:
	$(MAKE) all -C orig

install distrib:
	$(MAKE) $@ -C as1
	$(MAKE) $@ -C as2

install-orig:
	$(MAKE) install -C orig

test: distrib orig
	cd orig && $(RUN) -r ../$(DESTDIR) ../$(DESTDIR)/bin/as as1?.s
	mv orig/a.out .
	$(LD) a.out
	cmp a.out orig/as1
	cd orig && $(RUN) -r ../$(DESTDIR) ../$(DESTDIR)/bin/as as2?.s
	mv orig/a.out .
	$(LD) a.out
	cmp a.out orig/as2

clean:
	$(MAKE) $@ -C orig
	$(MAKE) $@ -C as1
	$(MAKE) $@ -C as2
	$(MAKE) $@ -C as
	$(MAKE) $@ -C cross
	$(MAKE) $@ -C v2
	$(MAKE) $@ -C xinu
	rm -f a.out
