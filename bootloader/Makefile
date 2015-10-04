all: BootLoader.bin

BootLoader.bin: BootLoader.asm
	@echo
	@echo ===== BootLoader Build Start IN =================================
	@echo
	
	mkdir -p ../OUT/bootloader
	nasm -o ../OUT/bootloader/BootLoader.bin BootLoader.asm
	
	@echo
	@echo ===== BootLoader Build Complete IN ==============================
	@echo
	
clean:
	rm -rf BootLoader.bin
	