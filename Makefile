.EXPORT_ALL_VARIABLES:

TOP_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))

TOP_DIR := $(dir $(TOP_PATH))

SUB_DIRS = $(TOP_SUB_DIRS)
###############################################################################

include $(TOP_DIR)/Config.mk

all: prepare sub_build kOdin.img

prepare:
	mkdir -p $(TOP_DEPLOY_DIR)

kOdin.img: $(TOP_BINARIES)
	@echo
	@echo ===== Disk Image Build Start ====================================
	@echo

	$(TOP_DEPLOY_DIR)/imageMaker $^

	@echo
	@echo ===== Disk Image Build Complete =================================
	@echo

clean: sub_clean
	rm -rf $(TOP_DEPLOY_DIR)
	
include $(TOP_DIR)/Rules.mk
