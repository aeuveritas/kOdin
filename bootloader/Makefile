TARGET_DIR = $(KBL_SOURCE_DIR)
TARGET_DEPLOY_DIR = $(KBL_DEPLOY_DIR)

all: prepare BootLoader.bin

prepare:
	mkdir -p $(TARGET_DEPLOY_DIR)

BootLoader.bin: BootLoader.asm
	@echo
	@echo ===== BootLoader Build Start ====================================
	@echo
	
	nasm -g -o $(TARGET_DEPLOY_DIR)/BootLoader.bin BootLoader.asm
	nasm -f elf -F dwarf -g -o BootLoader.elf BootLoader.asm
	mv ./BootLoader.elf $(TARGET_DEPLOY_DIR)
	
	@echo
	@echo ===== BootLoader Build Complete =================================
	@echo
	
clean:
	rm -rf $(TARGET_DEPLOY_DIR)
	
include $(TOP_DIR)/Rules.mk
