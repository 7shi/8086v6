TOPDIR = .
include $(TOPDIR)/Makefile.inc

all install distrib:
	$(MAKE) $@ -C as
	$(MAKE) $@ -C sys

test:
	$(MAKE) $@ -C tests
	$(MAKE) $@ -C as

clean:
	$(MAKE) $@ -C tests
	$(MAKE) $@ -C as
	$(MAKE) $@ -C sys
	rm -rf $(DESTDIR)
