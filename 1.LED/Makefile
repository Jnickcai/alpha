CC 		= arm-linux-gnueabihf-gcc
LD 		= arm-linux-gnueabihf-ld
OBJ 	= arm-linux-gnueabihf-objcopy 
DUMP	= arm-linux-gnueabihf-objdump
led.o : led.s
	$(CC) 	-g -c $< -o $@
	$(LD) 	-Ttext 0X87800000 $@ -o led.elf
	$(OBJ) 	-O binary -S -g led.elf led.bin
	$(DUMP) -D led.elf > led.dis

.PHONY:clear download
clear :
	rm -f *.o *.elf
download:
	./imxdownload led.bin /dev/sdb
