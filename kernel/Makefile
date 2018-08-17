all: iso/boot/osix.bin
	grub-mkrescue -o osix.iso iso

boot.o: src/boot.s
	as --32 src/boot.s -o boot.o

vga.o: src/vga.c
	gcc -I ./include -m32 -c src/vga.c -o vga.o -std=c99 -ffreestanding -O2 -Wall -Wextra

string.o: src/string.c
	gcc -I ./include -m32 -c src/string.c -o string.o -std=c99 -ffreestanding -O2 -Wall -Wextra

stdio.o: src/stdio.c
	gcc -I ./include -m32 -c src/stdio.c -o stdio.o -std=c99 -ffreestanding -O2 -Wall -Wextra

registers.o: src/arch/registers.c
	gcc -I ./include -m32 -c src/arch/registers.c -o registers.o -std=c99 -ffreestanding -O2 -Wall -Wextra

kernel.o: src/kernel.c
	gcc -I ./include -m32 -c src/kernel.c -o kernel.o -std=c99 -ffreestanding -O2 -Wall -Wextra

iso/boot/osix.bin: vga.o string.o stdio.o registers.o boot.o kernel.o
	gcc -T linker.ld -m32 -o iso/boot/osix.bin -ffreestanding -O2 -nostdlib boot.o kernel.o vga.o string.o stdio.o registers.o -Wl,--build-id=none


test:
	grub-file --is-x86-multiboot iso/boot/osix.bin

clean:
	rm *.o iso/boot/osix.bin osix.iso

run:
	qemu-system-i386 -cdrom osix.iso
