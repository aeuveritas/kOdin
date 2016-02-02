# Default build list
all: imageMaker

# Build imageMaker
imageMaker: imageMaker.c
	@echo ======================= MAKE imageMaker =======================
	gcc -o $@ $<
	mv $@ $(TOP_DEPLOY_DIR)
	@echo ===================== imageMaker Complete =====================
	
clean:
	rm -f $(TOP_DEPLOY_DIR)/imageMaker