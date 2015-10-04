all: BootLoader Disk.img

BootLoader:
	@echo
	@echo ===== BootLoader Build Start ====================================
	@echo
	
	make -C bootloader
	
	@echo
	@echo ===== BootLoader Build Complete =================================
	@echo
	
Disk.img:
	@echo
	@echo ===== Disk Image Build Start ====================================
	@echo
	
	cp ./OUT/bootloader/BootLoader.bin ./OUT/Disk.img
	
	@echo
	@echo ===== Disk Image Build Complete =================================
	@echo
	
clean:
	make -C bootloader clean
	rm -rf OUT/bootloader/
	rm -f OUT/Disk.img

