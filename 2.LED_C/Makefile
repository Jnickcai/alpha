CC 		= arm-linux-gnueabihf-gcc
LD 		= arm-linux-gnueabihf-ld
OBJCOPY = arm-linux-gnueabihf-objcopy 
DUMP	= arm-linux-gnueabihf-objdump
OBJS	=start.o main.o

led.elf:$(OBJS)
	$(LD) 	-Timx6ull.lds $^ -o led.elf
	$(OBJCOPY) 	-O binary -S -g $@ led.bin
	$(DUMP) -D led.elf > led.dis

%.o:%.c
	$(CC) 	-Wall -nostdlib -c -O2  $< -o $@

%.o:%.s
	$(CC) 	-Wall -nostdlib -c -O2  $< -o $@



.PHONY:clear download

clear :
	rm -f *.o *.elf

download:
	./imxdownload led.bin /dev/sdb
