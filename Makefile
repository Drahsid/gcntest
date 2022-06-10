CROSS = mips-n64-
AS = $(CROSS)as
CC = $(CROSS)gcc
LD = $(CROSS)ld
OBJDUMP = $(CROSS)objdump
OBJCOPY = $(CROSS)objcopy
PYTHON = python3
N64CRC = $(TOOLS_DIR)/n64crc

PROJECTNAME = gcntest

BUILD_DIR = build
TOOLS_DIR = tools

SRC_DIR = src
INC_DIR = include
BIN_DIR = bin
LIB_DIR = lib

SRC_DIRS = $(SRC_DIR) $(SRC_DIR)/usb
ASM_DIRS = $(SRC_DIR)/asm
BIN_DIRS = $(BIN_DIR)
# N64_INCDIR is /usr/include/n64 by default on crash's sdk
INCLUDE_DIRS = -I$(INC_DIR) -Iultralib/include -I$(N64_INCDIR)/nustd -I$(N64_LIBGCCDIR)/include

S_FILES   = $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/*.s))
C_FILES   = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
BIN_FILES = $(foreach dir,$(BIN_DIRS),$(wildcard $(dir)/*.bin))
O_FILES = $(foreach file,$(S_FILES),$(BUILD_DIR)/$(file).o) \
           $(foreach file,$(C_FILES),$(BUILD_DIR)/$(file).o) \
           $(foreach file,$(BIN_FILES),$(BUILD_DIR)/$(file).o)

ABI ?= 32
RELEASE_BUILD ?= 0

ULTRA_PRE:=o

GBI_DEFINE = -DF3DEX_GBI_2
CDEF_FLAGS = -D_LANGUAGE_C -D_MIPS_SZLONG=32 $(GBI_DEFINE)
ADEF_FLAGS = -DMIPSEB -D_LANGUAGE_ASSEMBLY -D_ULTRA64
ARCH_FLAGS = -mips3 -mtune=vr4300 -march=vr4300
ABI_FLAG = -mabi=$(ABI)

ifeq ($(RELEASE_BUILD),1)
OPT_FLAGS = -Os
OPT_FLAGS2 = -mfix4300 -mno-check-zero-division -mframe-header-opt -fno-inline-functions -falign-functions=32 -fwrapv -fmerge-all-constants -ffast-math -fno-stack-protector -fmodulo-sched -fmodulo-sched-allow-regmoves -fira-hoist-pressure -fweb -floop-interchange -fsplit-paths
CDEF_FLAGS += -D_FINALROM -DNDEBUG
ULTRA_LIB = -lgultra_rom_$(ULTRA_PRE)$(ABI)
NUSTD_LIB = -lnustd
else
OPT_FLAGS = -g3
OPT_FLAGS2 = -mfix4300 -mno-check-zero-division -mframe-header-opt -fno-inline-functions -falign-functions=64 -fwrapv -fmerge-all-constants
CDEF_FLAGS += -DDEBUG
ULTRA_LIB = -lgultra_d_$(ULTRA_PRE)$(ABI)
NUSTD_LIB = -lnustd_d
endif

TARGET = $(BUILD_DIR)/$(PROJECTNAME)_$(ULTRA_PRE)$(ABI)
ROMSIZE = 0x00200000
CC_FLAGS = -G 0 -nostdlib -nostdinc $(OPT_FLAGS) $(OPT_FLAGS2) $(ABI_FLAG) $(CDEF_FLAGS) $(ARCH_FLAGS) -mno-shared -mno-abicalls -fno-common -fno-PIC -ffreestanding -Wall -Wno-missing-braces -Wno-incompatible-pointer-types -Wno-int-conversion -Wno-pointer-sign $(INCLUDE_DIRS)
AS_FLAGS = -EB $(OPT_FLAGS) $(ARCH_FLAGS) $(ABI_FLAG) #$(ADEF_FLAGS)
# N64_LIBDIR is /usr/lib/n64 by default on crash's sdk
LD_FLAGS = -T $(PROJECTNAME)_$(ABI).ld -Map $(TARGET).map --accept-unknown-input-arch --no-check-sections -L$(LIB_DIR) -L$(N64_LIBGCCDIR) -L$(N64_LIBDIR) $(ULTRA_LIB) $(NUSTD_LIB) -lgcc
OBJCOPY_FLAGS = --pad-to $(ROMSIZE) --gap-fill 0xFF -O binary

default: dirs $(TARGET).z64

dirs:
	$(foreach dir,$(SRC_DIRS) $(ASM_DIRS) $(BIN_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))

clean:
	rm -rf $(BUILD_DIR)

tools:
	make -C $(TOOLS_DIR)

ultralib:
	make -C ultralib distclean
	make -C ultralib clean
	make -C ultralib setup
ifeq ($(RELEASE_BUILD),1)
	make -C ultralib TARGET=libgultra_rom
	cp -f ultralib/build/libgultra_rom.a $(LIB_DIR)/libgultra_rom_o32.a
else
	make -C ultralib TARGET=libgultra_d
	cp -f ultralib/build/libgultra_d.a $(LIB_DIR)/libgultra_d_o32.a
endif

$(BUILD_DIR)/boot.6102.o: $(LIB_DIR)/boot.6102
	$(OBJCOPY) -I binary -O elf32-big $< $@

$(BUILD_DIR)/%.c.o: %.c
	$(CC) -c $(CC_FLAGS) -o $@ $< -w

$(BUILD_DIR)/%.s.o: %.s
	$(AS) $(AS_FLAGS) -o $@ $<

$(BUILD_DIR)/%.bin.o: %.bin
	$(LD) -r -b binary -o $@ $<

$(TARGET).elf: dirs tools $(O_FILES) $(BUILD_DIR)/boot.6102.o
	$(LD) $(O_FILES) -o $@ $(LD_FLAGS)

$(TARGET).z64: $(TARGET).elf
	$(OBJCOPY) $(OBJCOPY_FLAGS) $< $@
	$(N64CRC) $@

.SECONDARY:
.PHONY: clean default dirs tools ultralib
SHELL = /bin/bash -e -o pipefail

