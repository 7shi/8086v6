TOPDIR = .
include $(TOPDIR)/Makefile.inc

all install dest:
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
