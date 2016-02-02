###############################################################################
#	Set build environment and rules
###############################################################################
TARGET_DIR = $(K32_SOURCE_DIR)
TARGET_DEPLOY_DIR = $(K32_DEPLOY_DIR)

include $(TARGET_DIR)/Config.mk

###############################################################################
#	Set build target and rules
###############################################################################

all: prepare Kernel32.bin

prepare:
	mkdir -p $(TARGET_DEPLOY_DIR)
	
$(TARGET_DEPLOY_DIR)/entry.bin: $(TARGET_DIR)/entry.s
	$(K32_NASM) $(K32_NASM_FLAGS) -o $@ $<
	
dep:
	@echo ===================== MAKE Dependency File ====================
	make -C $(TARGET_DEPLOY_DIR) -f $(TARGET_DIR)./Makefile InternalDependency
	@echo ================== Dependency Search Complete =================

ExecuteInternalBuild: dep
	make -C $(TARGET_DEPLOY_DIR) -f $(TARGET_DIR)./Makefile Kernel32.elf

$(TARGET_DEPLOY_DIR)/Kernel32.elf.bin: ExecuteInternalBuild
	$(K32_OBJCOPY) $(K32_OBJCOPY_FLAGS) $(TARGET_DEPLOY_DIR)./Kernel32.elf $@

Kernel32.bin: $(TARGET_DEPLOY_DIR)/entry.bin $(TARGET_DEPLOY_DIR)/Kernel32.elf.bin
	cat $^ > $@
	mv $@ $(TARGET_DEPLOY_DIR)
	
clean:
	rm -rf $(TARGET_DEPLOY_DIR)

###############################################################################
#	Part will be called by OBEJCTDIRECTORY
###############################################################################
CPPENTERYPOINTOBEJCTFILE = main.o
CPPSOURCEFILES = $(wildcard $(TARGET_DIR)./*.cpp)
ASSEMBLYSOURCEFILES = $(wildcard $(TARGET_DIR)./*.asm)
CPPOBJECTFILES = $(subst main.o, , $(notdir $(patsubst %.cpp, %.o, $(CPPSOURCEFILES))))
ASSEMBLYOBJECTFILES = $(notdir $(patsubst %.asm, %.o, $(ASSEMBLYSOURCEFILES)))

# Change .cpp to .o
%.o: $(TARGET_DIR)./%.cpp
	$(K32_GXX) $(K32_GXX_FLAGS) $<
	
# Change .asm to .o
%.o: $(TARGET_DIR)./%.asm
	$(K32_NASM) $(K32_NASM_FLAGS) -f elf32 -o $@ $<
	
InternalDependency:
	$(K32_GXX) $(K32_GXX_FLAGS) -MM $(CPPSOURCEFILES) > Dependency.dep

Kernel32.elf: $(CPPENTERYPOINTOBEJCTFILE) $(CPPOBJECTFILES) $(ASSEMBLYOBJECTFILES)
	$(K32_LD) $(K32_LD_FLAGS) -o $@ $^

ifeq (Dependency.dep, $(wildcard Dependency.dep))
include Dependency.dep
endif
