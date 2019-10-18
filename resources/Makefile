PREFIX			?= arm-none-eabi
TOP_DIR 		:= $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
SOURCE_DIR      := $(abspath $(dir $(abspath $(lastword $(MAKEFILE_LIST))))/src)
RTOS_DIR        := $(abspath $(dir $(abspath $(lastword $(MAKEFILE_LIST))))/rtos)
OPENCM3_DIR 	:= $(abspath $(dir $(abspath $(lastword $(MAKEFILE_LIST))))/libopencm3)
LIBNAME			= opencm3_stm32f1
DEFS			+= -DSTM32F1

PROJECTNAME		= BBB

FP_FLAGS	?= -msoft-float
ARCH_FLAGS	= -mthumb -mcpu=cortex-m3 $(FP_FLAGS) -mfix-cortex-m3-ldrd
ASFLAGS		= -mthumb -mcpu=cortex-m3

CC		:= $(PREFIX)-gcc
CXX		:= $(PREFIX)-g++
LD		:= $(PREFIX)-ld
AR		:= $(PREFIX)-ar
AS		:= $(PREFIX)-as
OBJCOPY		:= $(PREFIX)-objcopy
SIZE		:= $(PREFIX)-size
OBJDUMP		:= $(PREFIX)-objdump
GDB		:= $(PREFIX)-gdb

OPT		:= -Os -g
CSTD	?= -std=c11
CXXSTD	?= -std=c++14

LDSCRIPT	?= $(TOP_DIR)/STM32F103C8T6.ld

include ./into.mk

TGT_CFLAGS	+= $(OPT) $(CSTD)
TGT_CFLAGS	+= $(ARCH_FLAGS)
TGT_CFLAGS	+= -Wextra -Wshadow -Wimplicit-function-declaration
TGT_CFLAGS	+= -Wredundant-decls -Wmissing-prototypes -Wstrict-prototypes
TGT_CFLAGS	+= -fno-common -ffunction-sections -fdata-sections
TGT_CFLAGS	+= -I$(OPENCM3_DIR)/include

TGT_CXXFLAGS	+= $(OPT) $(CXXSTD)
TGT_CXXFLAGS	+= $(ARCH_FLAGS)
TGT_CXXFLAGS	+= -Wextra -Wshadow -Wredundant-decls  -Weffc++
TGT_CXXFLAGS	+= -fno-common -ffunction-sections -fdata-sections

TGT_CPPFLAGS	+= -MD
TGT_CPPFLAGS	+= -Wall -Wundef
TGT_CPPFLAGS	+= $(DEFS)
TGT_CPPFLAGS	+= -I$(OPENCM3_DIR)/include

TGT_LDFLAGS	+= --static -nostartfiles
TGT_LDFLAGS	+= -T$(LDSCRIPT)
TGT_LDFLAGS	+= $(ARCH_FLAGS)
TGT_LDFLAGS	+= -Wl,-Map=$(*).map
TGT_LDFLAGS	+= -Wl,--gc-sections

LDLIBS		+= -specs=nosys.specs
LDLIBS		+= -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group
LDLIBS		+= -L$(OPENCM3_DIR)/lib -l$(LIBNAME)

.SUFFIXES:	.elf .bin .hex .srec .list .map .images

TGT_CFLAGS		+= -I$(RTOS_DIR)/include -I$(RTOS_DIR)/portable/GCC/ARM_CM3 -I$(RTOS_DIR)/config
TGT_CFLAGS		+= -I./src
TGT_CXXFLAGS	+= -I$(RTOS_DIR)/include -I$(RTOS_DIR)/portable/GCC/ARM_CM3 -I$(RTOS_DIR)/config
TGT_CXXFLAGS	+= -I./src

SRCFILES	+= $(SOURCE_DIR)/main.cpp
SRCFILES    += $(RTOS_DIR)/portable/MemMang/heap_4.c \
                $(RTOS_DIR)/list.c $(RTOS_DIR)/queue.c $(RTOS_DIR)/tasks.c $(RTOS_DIR)/isrs.c \
                $(RTOS_DIR)/portable/GCC/ARM_CM3/port.c

ASRC =
OBJ  = $(SRCFILES:.c=.o) $(ASRC:.s=.o) $(SRCFILES:.cpp=.o)

all: $(LIBNAME) $(OBJ)
	$(CXX) $(TGT_CXXFLAGS) $(CXXFLAGS) $(TGT_CPPFLAGS) $(CPPFLAGS) $(OBJ) \
	    -o build/$(PROJECTNAME).elf $(TGT_LDFLAGS) $(LDFLAGS) $(LDLIBS)
	$(OBJCOPY) -O binary build/$(PROJECTNAME).elf build/$(PROJECTNAME).bin
	$(OBJCOPY) -O ihex build/$(PROJECTNAME).elf build/$(PROJECTNAME).hex
	arm-none-eabi-size build/$(PROJECTNAME).elf
	ls -al output/$(PROJECTNAME).bin

clean:	clean_libopencm3
	rm -f $(RTOS_DIR)/*.o $(RTOS_DIR)/*.d
	rm -f $(RTOS_DIR)/portable/MemMang/*.o $(RTOS_DIR)/portable/MemMang/*.d
	rm -f $(RTOS_DIR)/portable/GCC/ARM_CM3/*.o $(RTOS_DIR)/portable/GCC/ARM_CM3/*.d

clean_libopencm3:
	cd $(OPENCM3_DIR) && $(MAKE) clean

$(LIBNAME): stm32f1.a

stm32f1.a:
	$(MAKE) -C libopencm3 TARGETS=stm32/f1

