.EXPORT_ALL_VARIABLES:

TARGET_DIR = $(K64_SOURCE_DIR)
TARGET_DEPLOY_DIR = $(K64_DEPLOY_DIR)
SUB_DIRS = $(K64_SUB_DIRS)

include $(TARGET_DIR)/Config.mk

###############################################################################
#	Set build target and rules
###############################################################################

all: prepare Kernel64.bin

prepare:
	mkdir -p $(TARGET_DEPLOY_DIR)
	
dep:
	@echo ===================== MAKE Dependency File ====================
	make -C $(TARGET_DEPLOY_DIR) -f $(TARGET_DIR)./Makefile InternalDependency
	@echo ================== Dependency Search Complete =================

ExecuteInternalBuild: dep sub_build
	make -C $(TARGET_DEPLOY_DIR) -f $(TARGET_DIR)./Makefile Kernel64.elf

Kernel64.bin: ExecuteInternalBuild
	$(K64_OBJCOPY) $(K64_OBJCOPY_FLAGS) $(TARGET_DEPLOY_DIR)./Kernel64.elf $(TARGET_DEPLOY_DIR)./$@

clean: sub_clean
	rm -rf $(TARGET_DEPLOY_DIR)

###############################################################################
#	Part will be called by OBEJCTDIRECTORY
###############################################################################
# Targets
K64_ENTRY_SOURCES = $(wildcard $(TARGET_DIR)./*.s)
K64_ENTRY_OBJECTS = $(notdir $(patsubst %.s, %.o, $(K64_ENTRY_SOURCES)))

K64_CXX_SOURCES = $(wildcard $(TARGET_DIR)./*.cpp)
K64_CXX_OBJECTS = $(notdir $(patsubst %.cpp, %.o, $(K64_CXX_SOURCES)))

K64_ASSEMBLY_SOURCES = $(wildcard $(TARGET_DIR)./*.asm)
K64_ASSEMBLY_OBJECTS = $(notdir $(patsubst %.asm, %.o, $(K64_ASSEMBLY_SOURCES)))
	
# Change .cpp to .o
%.o: $(TARGET_DIR)./%.cpp
	$(K64_GXX) $(K64_GXX_FLAGS) $<
	
InternalDependency:
	$(K64_GXX) $(K64_GXX_FLAGS) -MM $(K64_CXX_SOURCES) > Dependency.dep

Kernel64.elf: $(ALL_TARGETS)
	$(K64_LD) $(K64_LD_FLAGS) -o $@ $^ $(K64_LIB)

ifeq (Dependency.dep, $(wildcard Dependency.dep))
include Dependency.dep
endif

include $(TOP_DIR)/Rules.mk
