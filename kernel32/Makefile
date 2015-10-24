###############################################################################
#	Set build environment and rules
###############################################################################
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))

SOURCEDIRECTORY = $(dir $(mkfile_path))
OBJECTDIRECTORY = $(SOURCEDIRECTORY)../OUT/kernel32/

NASM32 = nasm
GPP32 = x86_64-pc-linux-g++ -c -m32 -ffreestanding
LD32 = x86_64-pc-linux-ld -melf_i386 -T $(SOURCEDIRECTORY)./elf_i386.x -nostdlib -e main -Ttext 0x10200
OBJCOPY32 = x86_64-pc-linux-objcopy -j .text -j .data -j .rodata -j .bss -S -O binary

###############################################################################
#	Set build target and rules
###############################################################################
all: prepare Kernel32.bin

prepare:
	mkdir -p $(OBJECTDIRECTORY)
	
$(OBJECTDIRECTORY)/entry.bin: $(SOURCEDIRECTORY)/entry.s
	$(NASM32) -o $@ $<
	
dep:
	@echo ===================== MAKE Dependency File ====================
	make -C $(OBJECTDIRECTORY) -f $(SOURCEDIRECTORY)./Makefile InternalDependency
	@echo ================== Dependency Search Complete =================

ExecuteInternalBuild: dep
	make -C $(OBJECTDIRECTORY) -f $(SOURCEDIRECTORY)./Makefile Kernel32.elf

$(OBJECTDIRECTORY)/Kernel32.elf.bin: ExecuteInternalBuild
	$(OBJCOPY32) $(OBJECTDIRECTORY)./Kernel32.elf $@

Kernel32.bin: $(OBJECTDIRECTORY)/entry.bin $(OBJECTDIRECTORY)/Kernel32.elf.bin
	cat $^ > $@
	mv $@ $(OBJECTDIRECTORY)
	
clean:
	rm -f *.bin
	rm -rf $(OBJECTDIRECTORY)

###############################################################################
#	Part will be called by OBEJCTDIRECTORY
###############################################################################
CPPENTERYPOINTOBEJCTFILE = main.o
CPPSOURCEFILES = $(wildcard $(SOURCEDIRECTORY)/*.cpp)
ASSEMBLYSOURCEFILES = $(wildcard $(SOURCEDIRECTORY)/*.asm)
CPPOBJECTFILES = $(subst main.o, , $(notdir $(patsubst %.cpp, %.o, $(CPPSOURCEFILES))))
ASSEMBLYOBJECTFILES = $(notdir $(patsubst %.asm, %.o, $(ASSEMBLYSOURCEFILES)))

# Change .cpp to .o
%.o: $(SOURCEDIRECTORY)./%.cpp
	$(GPP32) -c $<
	
# Change .asm to .o
%.o: $(SOURCEDIRECTORY)./%.asm
	$(NASM32) -f elf32 -o $@ $<
	
InternalDependency:
	$(GPP32) -MM $(CPPSOURCEFILES) > Dependency.dep

Kernel32.elf: $(CPPENTERYPOINTOBEJCTFILE) $(CPPOBJECTFILES) $(ASSEMBLYOBJECTFILES)
	$(LD32) -o $@ $^

ifeq (Dependency.dep, $(wildcard Dependency.dep))
include Dependency.dep
endif
