all: Kernel32.bin

Kernel32.bin: Entry.s
	@echo
	@echo ===== Kernel32 Build Start IN =================================
	@echo
	
	mkdir -p ../OUT/kernel32
	nasm -o ../OUT/kernel32/Kernel32.bin $<
		
	@echo
	@echo ===== Kernel32 Build Complete IN ==============================
	@echo
clean:
	rm -rf ../OUT/kernel32
