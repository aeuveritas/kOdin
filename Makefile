all: BootLoader Kernel32 DS.img

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
	
DS.img: OUT/bootloader/BootLoader.bin OUT/kernel32/Kernel32.bin
	@echo
	@echo ===== Disk Image Build Start ====================================
	@echo

	make -C utility/imageMaker
	./imageMaker $^

	@echo
	@echo ===== Disk Image Build Complete =================================
	@echo
	
clean:
	make -C bootloader clean
	make -C kernel32 clean
	make -C utility/imageMaker clean
	rm -rf ./OUT
	rm -f ./imageMaker
