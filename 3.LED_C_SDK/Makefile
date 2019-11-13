
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
					PRO	\
					BSP/LED \

INCLUDE			:=$(patsubst %,-I %,$(INCDIRS))

OBJC			:=$(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))
OBJC 			:=$(patsubst %, OBJ/%, $(notdir $(OBJC:.c=.o)))

OBJS			:=$(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.s))
OBJS 			:=$(patsubst %, OBJ/%, $(notdir $(OBJS:.s=.o)))

OBJ_S			:=$(OBJC)$(OBJS)




.PHONY:print clear download 

print:
	@echo INCLUDE 	= $(INCLUDE)
	@echo OBJ_S		= $(OBJ_S)


clear :
	rm -f OBJ/*.o *.elf

download:
	./imxdownload led.bin /dev/sdb
