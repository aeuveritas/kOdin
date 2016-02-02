.EXPORT_ALL_VARIABLES:

TARGET_DIR = $(K64_ENTRY_DIR)
TARGET_DEPLOY_DIR = $(K64_ENTRY_DEPLOY_DIR)
SUB_DIRS = $(K64_ENTRY_SUB_DIRS)

TARGET = entry.o
###############################################################################
#	Set build target and rules
###############################################################################

all: prepare Object

prepare:
	mkdir -p $(TARGET_DEPLOY_DIR)
	
Object:
	@echo ===== Build ENTRY ================================================
	
	make -C $(TARGET_DEPLOY_DIR) -f $(TARGET_DIR)./Makefile Build
	
	@echo ===== Complete ENTRY =============================================

clean:
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

# Change .asm to .o
$(K64_ENTRY_OBJECTS): $(K64_ENTRY_SOURCES)
	$(K64_NASM) $(K64_NASM_FLAGS) -o $@ $<
	
Build: $(K64_ENTRY_OBJECTS)
	$(K64_LD) -r -o $(TARGET) $^

include $(TOP_DIR)/Rules.mk
