all: VirtualOS.bin

VirtualOS.bin: VirtualOS.asm
	@echo
	@echo ===== VirtualOS Build Start IN =================================
	@echo
	
	mkdir -p ../OUT/kernel32
	nasm -o ../OUT/kernel32/VirtualOS.bin VirtualOS.asm
		
	@echo
	@echo ===== VirtualOS Build Complete IN ==============================
	@echo
clean:
	rm -rf ../OUT/kernel32