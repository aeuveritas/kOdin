# Default build list
all: imageMaker

# Build imageMaker
imageMaker: imageMaker.c
	@echo ======================= MAKE imageMaker =======================
	gcc -o $@ $<
	cp $@ ../../
	@echo ===================== imageMaker Complete =====================
	
clean:
	rm -rf imageMaker
	rm -f ../../imageMaker