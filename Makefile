# Modified to compile on the Raspberry Pi
#  also compiles on the scratchbox ARM compilers.

COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding -std=c99

gcc : bin/kernel.hex SDcard/mjw_kernel.img

clean :
	rm -f bin/*.o
	rm -f bin/*.bin
	rm -f bin/*.hex
	rm -f bin/*.elf
	rm -f *.list
	rm -f SDcard/*.img

bin/vectors.o : sources/vectors.s
	as sources/vectors.s -o bin/vectors.o

bin/armDivision.o : sources/armDivision.s
	as sources/armDivision.s -o bin/armDivision.o

bin/kernel.o : sources/kernel.c
	gcc $(COPS) -c sources/kernel.c -o bin/kernel.o

bin/framebuffer.o : sources/framebuffer.c
	gcc $(COPS) -c sources/framebuffer.c -o bin/framebuffer.o

bin/mailbox.o : sources/mailbox.c
	gcc $(COPS) -c sources/mailbox.c -o bin/mailbox.o

bin/gpio.o : sources/gpio.c
	gcc $(COPS) -c sources/gpio.c -o bin/gpio.o

bin/console.o : sources/console.c
	gcc $(COPS) -c sources/console.c -o bin/console.o

bin/atags.o : sources/atags.c
	gcc $(COPS) -c sources/atags.c -o bin/atags.o

bin/generalIO.o : sources/generalIO.c
	gcc $(COPS) -c sources/generalIO.c -o bin/generalIO.o

bin/general.o : sources/general.c
	gcc $(COPS) -c sources/general.c -o bin/general.o

bin/standardFont.o : sources/standardFont.c
	gcc $(COPS) -c sources/standardFont.c -o bin/standardFont.o

bin/kernel.elf : sources/memmap bin/vectors.o bin/armDivision.o bin/kernel.o bin/framebuffer.o bin/mailbox.o bin/gpio.o bin/console.o bin/atags.o bin/generalIO.o bin/general.o bin/standardFont.o
	ld bin/vectors.o bin/armDivision.o bin/kernel.o bin/framebuffer.o bin/mailbox.o bin/gpio.o bin/console.o bin/atags.o bin/generalIO.o bin/general.o bin/standardFont.o -T sources/memmap -o bin/kernel.elf
	objdump -D bin/kernel.elf > kernel.list

SDcard/mjw_kernel.img : bin/kernel.elf
	objcopy bin/kernel.elf -O binary SDcard/mjw_kernel.img

bin/kernel.hex : bin/kernel.elf
	objcopy bin/kernel.elf -O ihex bin/kernel.hex

