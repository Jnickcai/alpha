
CROSS_COMPILE	?=	arm-linux-gnueabihf-
CC		 		?=	$(CROSS_COMPILE)gcc
LD 				?=	$(CROSS_COMPILE)ld
OBJCOPY 		?=	$(CROSS_COMPILE)objcopy 
DUMP			?=	$(CROSS_COMPILE)bjdump

TARGET			?=	LED

OBJS			?=	start.o main.o

INCDIRS 		:=	IMX6ULL \
					PRO	\
					BSP/LED \


SRCDIRS			:=	IMX6ULL \
					PRO \
					BSP/LED \

INCLUDE			:=$(patsubst %,-I %,$(INCDIRS))  						#	为包含路径前面加	—I

OBJC			:=$(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))	#	寻找包含文件下的.c文件
OBJC 			:=$(patsubst %, OBJ/%, $(notdir $(OBJC:.c=.o)))			#	.c文件改成.o文件

OBJS			:=$(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.s))
OBJS 			:=$(patsubst %, OBJ/%, $(notdir $(OBJS:.s=.o)))

OBJ_S			:=$(OBJC)$(OBJS)

VPATH := $(SRCDIRS)


$(TARGET).bin : $(OBJS)
	$(LD) -Timx6ul.lds -o $(TARGET).elf $^
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis

$(OBJS) : OBJ/%.o : %.s
	$(CC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<

$(OBJC) : OBJ/%.o : %.c
	$(CC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<


.PHONY:print clear download 

print:
	@echo INCLUDE 	= $(INCLUDE)
	@echo OBJ_S		= $(OBJ_S)


clear :
	rm -f OBJ/*.o *.elf

download:
	./imxdownload led.bin /dev/sdb
