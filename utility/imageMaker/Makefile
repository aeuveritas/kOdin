# Default build list
all: imageMaker

# Build imageMaker
imageMaker: imageMaker.c
	@echo ======================= MAKE imageMaker =======================
	gcc -o $@ $<
	mv $@ ../../OUT/
	@echo ===================== imageMaker Complete =====================
	
clean:
	rm -f ../../OUT/imageMaker