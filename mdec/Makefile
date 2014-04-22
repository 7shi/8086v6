TOPDIR = ..
include $(TOPDIR)/Makefile.inc

TARGET = rkuboot rpuboot hpuboot \
         tboot mboot hboot \
         tcf rkf reset dldr \
         tmrk tmrp tmhp htrk htrp hthp

all: $(TARGET)

rkuboot:
	$(AS) fsboot.s tty.s rrk.s rk.s
	$(STRIP) a.out
	ls -l a.out
	mv a.out $@

rpuboot:
	$(AS) fsboot.s tty.s rrp.s rp.s
	$(STRIP) a.out
	ls -l a.out
	mv a.out $@

hpuboot:
	$(AS) fsboot.s tty.s rhp.s hp.s
	$(STRIP) a.out
	ls -l a.out
	mv a.out $@

tboot:
	$(AS) tpboot.s tty.s tc.s
	$(STRIP) a.out
	ls -l a.out
	mv a.out $@

mboot:
	$(AS) tpboot.s tty.s tm.s
	$(STRIP) a.out
	ls -l a.out
	mv a.out $@

hboot:
	$(AS) tpboot.s tty.s ht.s
	$(STRIP) a.out
	ls -l a.out
	mv a.out $@

tcf rkf reset dldr:
	$(AS) $@.s
	$(STRIP) a.out
	mv a.out $@

tmrk:
	$(AS) mcopy.s tm.s wrk.s rk.s
	$(STRIP) a.out
	mv a.out $@

tmrp:
	$(AS) mcopy.s tm.s wrp.s rp.s
	$(STRIP) a.out
	mv a.out $@

tmhp:
	$(AS) mcopy.s tm.s whp.s hp.s
	$(STRIP) a.out
	mv a.out $@

htrk:
	$(AS) mcopy.s ht.s wrk.s rk.s
	$(STRIP) a.out
	mv a.out $@

htrp:
	$(AS) mcopy.s ht.s wrp.s rp.s
	$(STRIP) a.out
	mv a.out $@

hthp:
	$(AS) mcopy.s ht.s whp.s hp.s
	$(STRIP) a.out
	mv a.out $@

clean:
	rm -f $(TARGET) a.out
