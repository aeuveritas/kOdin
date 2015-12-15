all: BootLoader.bin

BootLoader.bin: BootLoader.asm
	@echo
	@echo ===== BootLoader Build Start IN =================================
	@echo
	
	mkdir -p ../OUT/bootloader
	nasm -g -o ../OUT/bootloader/BootLoader.bin BootLoader.asm
	nasm -f elf -F dwarf -g -o BootLoader.elf BootLoader.asm
	mv ./BootLoader.elf ../OUT/bootloader
	
	@echo
	@echo ===== BootLoader Build Complete IN ==============================
	@echo
	
clean:
	rm -rf ../OUT/bootloader
	