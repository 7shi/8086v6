TOPDIR = .
include $(TOPDIR)/Makefile.inc

all clean:
	$(MAKE) $@ -C as
	$(MAKE) $@ -C tests
	rm -rf $(DESTDIR)

dest:
	$(MAKE) $@ -C as
