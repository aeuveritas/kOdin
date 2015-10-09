all: BootLoader VirtualOS Disk.img

BootLoader:
	@echo
	@echo ===== BootLoader Build Start ====================================
	@echo
	
	make -C bootloader
	
	@echo
	@echo ===== BootLoader Build Complete =================================
	@echo
	
VirtualOS:
	@echo
	@echo ===== VirtualOS Build Start ====================================
	@echo
	
	make -C kernel32
	
	@echo
	@echo ===== VirtualOS Build Complete =================================
	@echo
	
Disk.img:
	@echo
	@echo ===== Disk Image Build Start ====================================
	@echo
	
	cat ./OUT/bootloader/BootLoader.bin > ./OUT/DS.img
	cat ./OUT/kernel32/VirtualOS.bin >> ./OUT/DS.img
	
	@echo
	@echo ===== Disk Image Build Complete =================================
	@echo
	
clean:
	make -C bootloader clean
	make -C kernel32 clean
	rm -rf ./OUT

