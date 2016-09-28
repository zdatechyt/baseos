all: baseos.iso

baseos.iso: isodir baseos.bin
	cp baseos.bin isodir/boot/baseos.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o baseos.iso isodir

isodir:
	mkdir -p isodir/boot/grub

baseos.bin: boot.o kernel.o
	i686-elf-gcc -T linker.ld -o baseos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

kernel.o: bin/drivers.o bin/kernel.o bin/util.o
	i686-elf-ld -i -o kernel.o -nostdlib bin/drivers.o bin/kernel.o bin/util.o

boot.o:
	i686-elf-as boot.s -o boot.o

bin/drivers.o: bin drivers/Makefile
	cd drivers && make CCFLAGS=$(CCFLAGS)
	mv drivers/FINAL.o bin/drivers.o
	cd ..

bin/kernel.o: bin kernel/Makefile
	cd kernel && make CCFLAGS=$(CCFLAGS)
	mv kernel/FINAL.o bin/kernel.o
	cd ..

bin/util.o: bin util/Makefile
	cd util && make CCFLAGS=$(CCFLAGS)
	mv util/FINAL.o bin/util.o
	cd ..

bin:
	mkdir bin

clean: driversclean kernelclean utilclean
	rm -r isodir
	rm -r bin
	rm *.o baseos.bin
	rm *.iso

driversclean:
	cd drivers && make clean
	cd ..

kernelclean:
	cd kernel && make clean
	cd ..

utilclean:
	cd util && make clean
	cd ..

