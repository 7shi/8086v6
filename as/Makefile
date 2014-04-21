TOPDIR = ..
include $(TOPDIR)/Makefile.inc

all:
	$(MAKE) $@ -C as1.orig
	$(MAKE) $@ -C as2.orig
	$(MAKE) $@ -C as1
	$(MAKE) $@ -C as2

install dest:
	$(MAKE) $@ -C as1
	$(MAKE) $@ -C as2

orig:
	$(MAKE) all -C as1.orig
	$(MAKE) all -C as2.orig

test: dest orig
	cd as1.orig && $(RUN) -r ../$(DESTDIR) ../$(DESTDIR)/bin/as as1?.s
	mv as1.orig/a.out .
	$(LD) a.out
	cmp a.out as1.orig/as1
	cd as2.orig && $(RUN) -r ../$(DESTDIR) ../$(DESTDIR)/bin/as as2?.s
	mv as2.orig/a.out .
	$(LD) a.out
	cmp a.out as2.orig/as2

clean:
	$(MAKE) $@ -C as1.orig
	$(MAKE) $@ -C as2.orig
	$(MAKE) $@ -C as1
	$(MAKE) $@ -C as2
	rm -f a.out
