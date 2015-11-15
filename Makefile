all: BootLoader Kernel32 Kernel64 Utility kOdin.img 

BootLoader:
	@echo
	@echo ===== BootLoader Build Start ====================================
	@echo
	
	make -C bootloader
	
	@echo
	@echo ===== BootLoader Build Complete =================================
	@echo
	
Kernel32:
	@echo
	@echo ===== Kernel32 Build Start ====================================
	@echo
	
	make -C kernel32
	
	@echo
	@echo ===== Kernel32 Build Complete =================================
	@echo

Kernel64:
	@echo
	@echo ===== Kernel64 Build Start ====================================
	@echo
	
	make -C kernel64
	
	@echo
	@echo ===== Kernel64 Build Complete =================================
	@echo
	
kOdin.img: OUT/bootloader/BootLoader.bin OUT/kernel32/Kernel32.bin OUT/kernel64/Kernel64.bin
	@echo
	@echo ===== Disk Image Build Start ====================================
	@echo

	./OUT/imageMaker $^

	@echo
	@echo ===== Disk Image Build Complete =================================
	@echo
	
Utility:
	@echo
	@echo ===== Utility Build Start ====================================
	@echo
	
	make -C utility
	
	@echo
	@echo ===== Utility Build Complete =================================
	@echo

clean:
	make -C bootloader clean
	make -C kernel32 clean
	make -C kernel64 clean
	make -C utility clean
	rm -rf ./OUT
	rm -f ./imageMaker
