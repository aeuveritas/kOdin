###############################################################################
#	Stable
###############################################################################
# Sub directories
K32_SUB_DIRS_ALL := $(sort $(dir $(wildcard */)))
K32_SUB_DIRS := $(filter-out include/,$(K32_SUB_DIRS_ALL))

# Build tools
K32_NASM := nasm
K32_GXX = x86_64-pc-linux-g++ -std=c++11
K32_LD = x86_64-pc-linux-ld
K32_OBJCOPY = x86_64-pc-linux-objcopy

# Build options
K32_NASM_FLAGS = -g
K32_GXX_FLAGS = -g -c -m32 -ffreestanding -fno-exceptions -fno-rtti
K32_LD_FLAGS = -melf_i386 -T $(K32_SOURCE_DIR)./elf_i386.x -nostdlib -e main -Ttext 0x10200
K32_OBJCOPY_FLAGS = -j .text -j .data -j .rodata -j .bss -S -O binary
