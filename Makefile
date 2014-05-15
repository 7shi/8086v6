all install distrib:
	$(MAKE) $@ -C as
	$(MAKE) $@ -C sys
	$(MAKE) $@ -C v1

test:
	$(MAKE) $@ -C tests
	$(MAKE) $@ -C as

clean:
	$(MAKE) $@ -C tests
	$(MAKE) $@ -C as
	$(MAKE) $@ -C sys
	$(MAKE) $@ -C v1
	rm -rf $(DESTDIR)
