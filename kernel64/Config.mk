###############################################################################
#	Stable
###############################################################################
# Sub directories
K64_SUB_DIRS_ALL := $(sort $(dir $(wildcard */)))
K64_SUB_DIRS := $(filter-out include/,$(K64_SUB_DIRS_ALL))

# Build tools
K64_NASM := nasm
K64_GXX = x86_64-pc-linux-g++ -std=c++11
K64_LD = x86_64-pc-linux-ld -melf_x86_64
K64_OBJCOPY = x86_64-pc-linux-objcopy
K64_AR = x86_64-pc-linux-ar

# Build options
K64_NASM_FLAGS = -f elf64 -g
K64_GXX_FLAGS = -g -c -W -Wall -nostartfiles -m64 -ffreestanding -fno-exceptions -fno-rtti $(K64_INC_PATH)
K64_LD_FLAGS = -T $(K64_SCRIPTS_DIR)/elf_x86_64.x -nostdlib -e main -Ttext 0x200000 $(K64_LIB_PATH)
K64_OBJCOPY_FLAGS = -j .text -j .data -j .rodata -j .bss -S -O binary
K64_AR_FLAGS = rscv

###############################################################################
#	Developing
###############################################################################

# Sub source directories
K64_KERNEL_DIR := $(K64_SOURCE_DIR)/kernel/
K64_INCLUDE_DIR := $(K64_SOURCE_DIR)/include/
K64_ARCH_DIR := $(K64_SOURCE_DIR)/arch/
K64_LIB_DIR := $(K64_SOURCE_DIR)/lib/
K64_DRIVER_DIR := $(K64_SOURCE_DIR)/driver/
K64_DESCRIPTOR_DIR := $(K64_SOURCE_DIR)/descriptor/
K64_SHELL_DIR := $(K64_SOURCE_DIR)/shell/
K64_DEBUG_DIR := $(K64_SOURCE_DIR)/debug/

# Sub deploy directories
K64_KERNEL_DEPLOY_DIR := $(K64_DEPLOY_DIR)/kernel/
K64_ARCH_DEPLOY_DIR := $(K64_DEPLOY_DIR)/arch/
K64_LIB_DEPLOY_DIR := $(K64_DEPLOY_DIR)/lib/
K64_DRIVER_DEPLOY_DIR := $(K64_DEPLOY_DIR)/driver/
K64_DESCRIPTOR_DEPLOY_DIR := $(K64_DEPLOY_DIR)/descriptor/
K64_SHELL_DEPLOY_DIR := $(K64_DEPLOY_DIR)/shell/
K64_DEBUG_DEPLOY_DIR := $(K64_DEPLOY_DIR)/debug/

# Include directories
K64_INC_PATH := -I$(K64_KERNEL_DIR) -I$(K64_INCLUDE_DIR) -I$(K64_LIB_DIR) -I$(K64_ARCH_DIR) -I$(K64_DRIVER_DIR) -I$(K64_DESCRIPTOR_DIR) -I$(K64_SHELL_DIR) -I$(K64_DEBUG_DIR) -I$(K64_SOURCE_DIR)

# Object files
K64_KERNEL_OBJ := $(K64_KERNEL_DEPLOY_DIR)/kernel.o
K64_ARCH_OBJ := $(K64_ARCH_DEPLOY_DIR)/arch.o
K64_DRIVER_OBJ := $(K64_DRIVER_DEPLOY_DIR)/driver.o
K64_SHELL_OBJ := $(K64_SHELL_DEPLOY_DIR)/shell.o
K64_DESCRIPTR_OBJ := $(K64_DESCRIPTOR_DEPLOY_DIR)/descriptor.o
K64_DEBUG_OBJ := $(K64_DEBUG_DEPLOY_DIR)/debug.o
K64_ALL_OBJ := $(K64_KERNEL_OBJ) $(K64_DRIVER_OBJ) $(K64_SHELL_OBJ) $(K64_DESCRIPTR_OBJ) $(K64_DEBUG_OBJ)

# Library directories
K64_LIB_PATH = -L$(K64_LIB_DEPLOY_DIR)

#Library files
K64_KODIN_LIB = $(K64_LIB_DEPLOY_DIR)/libkodin.a
K64_ALL_LIB = $(K64_KODIN_LIB)

# Library
K64_LIB = -lkodin

# Scripts
K64_SCRIPTS_DIR := $(K64_ARCH_DIR)/scripts/

# All target files
ALL_TARGETS = $(K64_ARCH_OBJ) $(K64_CXX_OBJECTS) $(K64_ALL_OBJ) 