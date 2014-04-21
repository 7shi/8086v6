TOPDIR = .
include $(TOPDIR)/Makefile.inc

all test:
	$(MAKE) $@ -C as
	$(MAKE) $@ -C tests

install dest:
	$(MAKE) $@ -C as

clean:
	$(MAKE) $@ -C as
	$(MAKE) $@ -C tests
	rm -rf $(DESTDIR)
