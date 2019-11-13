
CROSS_COMPILE	?=	arm-linux-gnueabihf-
CC		 		=	$(CROSS_COMPILE)gcc
LD 				=	$(CROSS_COMPILE)ld
OBJCOPY 		=	$(CROSS_COMPILE)objcopy 
DUMP			=	$(CROSS_COMPILE)objdump

TARGET			?=	OBJ/LED

OBJS			?=	start.o main.o

INCDIRS 		:=	IMX6ULL \
					PRO	\
					BSP/LED \
					BSP/DELAY \


SRCDIRS			:=	IMX6ULL \
					PRO \
					BSP/LED \
					BSP/DELAY \

INCLUDE			:=$(patsubst %,-I %,$(INCDIRS))  						#	为包含路径前面加	—I

OBJC			:=$(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))
OBJC 			:=$(patsubst %, OBJ/%, $(notdir $(OBJC:.c=.o)))			#获取项目文件夹下的说有.c文件并改成.o

OBJS			:=$(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.s))	
OBJS 			:=$(patsubst %, OBJ/%, $(notdir $(OBJS:.s=.o)))			#获取项目文件夹下的说有.s文件并改成.o

OBJ_S			:=$(OBJC)$(OBJS)

VPATH := $(SRCDIRS)						#依赖文件找寻路径

$(TARGET).bin : $(OBJ_S)
	$(LD) -Timx6ull.lds -o $(TARGET).elf $^
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(DUMP) -D -m arm $(TARGET).elf > $(TARGET).dis

$(OBJC):OBJ/%.o:%.c
	$(CC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<

$(OBJS):OBJ/%.o:%.s
	$(CC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<

.PHONY:print clear download 

print:
	@echo INCLUDE 	= $(INCLUDE)
	@echo OBJ_S		= $(OBJ_S)
	@echo CC		= $(CC)

clear :
	rm -rf $(TARGET).elf $(TARGET).dis $(TARGET).bin $(OBJS) $(OBJC)

download:
	./imxdownload $(TARGET).bin /dev/sdb
