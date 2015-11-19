###############################################################################
#	Set build environment and rules
###############################################################################
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))

SOURCEDIRECTORY = $(dir $(mkfile_path))
OBJECTDIRECTORY = $(SOURCEDIRECTORY)../OUT/kernel64/

NASM64 = nasm -f elf64 -g
GPP64 = x86_64-pc-linux-g++ -std=c++11 -g -c -m64 -ffreestanding -fno-exceptions -fno-rtti
LD64 = x86_64-pc-linux-ld -melf_x86_64 -T $(SOURCEDIRECTORY)./elf_x86_64.x -nostdlib -e main -Ttext 0x200000
OBJCOPY64 = x86_64-pc-linux-objcopy -j .text -j .data -j .rodata -j .bss -S -O binary

###############################################################################
#	Set build target and rules
###############################################################################
all: prepare Kernel64.bin

prepare:
	mkdir -p $(OBJECTDIRECTORY)
	
dep:
	@echo ===================== MAKE Dependency File ====================
	make -C $(OBJECTDIRECTORY) -f $(SOURCEDIRECTORY)./Makefile InternalDependency
	@echo ================== Dependency Search Complete =================

ExecuteInternalBuild: dep
	make -C $(OBJECTDIRECTORY) -f $(SOURCEDIRECTORY)./Makefile Kernel64.elf

Kernel64.bin: ExecuteInternalBuild
	$(OBJCOPY64) $(OBJECTDIRECTORY)./Kernel64.elf $(OBJECTDIRECTORY)./$@

clean:
	rm -f *.bin
	rm -rf $(OBJECTDIRECTORY)

###############################################################################
#	Part will be called by OBEJCTDIRECTORY
###############################################################################
ENTRYPOINTSOURCEFILE = $(SOURCEDIRECTORY)./entry.s
ENTRYPOINTOBJECTFILE = entry.o
CPPSOURCEFILES = $(wildcard $(SOURCEDIRECTORY)./*.cpp)
ASSEMBLYSOURCEFILES = $(wildcard $(SOURCEDIRECTORY)./*.asm)
CPPOBJECTFILES = $(notdir $(patsubst %.cpp, %.o, $(CPPSOURCEFILES)))
ASSEMBLYOBJECTFILES = $(notdir $(patsubst %.asm, %.o, $(ASSEMBLYSOURCEFILES)))

# Assembly entry point build
$(ENTRYPOINTOBJECTFILE): $(ENTRYPOINTSOURCEFILE)
	$(NASM64) -o $@ $<
	
# Change .cpp to .o
%.o: $(SOURCEDIRECTORY)./%.cpp
	$(GPP64) $<
	
# Change .asm to .o
%.o: $(SOURCEDIRECTORY)./%.asm
	$(NASM64) -o $@ $<
	
InternalDependency:
	$(GPP64) -MM $(CPPSOURCEFILES) > Dependency.dep

Kernel64.elf: $(ENTRYPOINTOBJECTFILE) $(CPPOBJECTFILES) $(ASSEMBLYOBJECTFILES)
	$(LD64) -o $@ $^

ifeq (Dependency.dep, $(wildcard Dependency.dep))
include Dependency.dep
endif
