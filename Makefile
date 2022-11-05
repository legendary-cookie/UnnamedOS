.PHONY: all
all: OS.iso

.PHONY: run
run: OS.iso
	qemu-system-x86_64 -M q35 -m 512M -boot d -cdrom OS.iso

.PHONY: build
build:
ifeq ("$(wildcard build/)", "")
	mkdir build/
	cmake -GNinja -S MicroKernel/ -B build/
	make -C limine
endif
	cmake --build build/ || true

.PHONY: clean
clean:
	rm -rf build/

.PHONY: OS.iso
OS.iso: build
	mkdir -p iso_root
	cp build/kernel.elf limine/limine-cd.bin limine/limine-cd-efi.bin limine/limine.sys limine.cfg iso_root
	xorriso -as mkisofs -b limine-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot limine-cd-efi.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		iso_root -o OS.iso
	limine/limine-deploy OS.iso
	rm -rf iso_root
