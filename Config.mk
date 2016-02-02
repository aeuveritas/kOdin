# Deploy directories
TOP_DEPLOY_DIR := $(TOP_DIR)/DEPLOY/

# Sub directories
TOP_SUB_DIRS_ALL := $(sort $(dir $(wildcard */)))
TOP_SUB_DIRS := $(filter-out DEPLOY/,$(TOP_SUB_DIRS_ALL))

# Sub source directories
KBL_SOURCE_DIR := $(TOP_DIR)/bootloader/
K32_SOURCE_DIR := $(TOP_DIR)/kernel32/
K64_SOURCE_DIR := $(TOP_DIR)/kernel64/

# Sub deploy directories
KBL_DEPLOY_DIR := $(TOP_DEPLOY_DIR)/bootloader/
K32_DEPLOY_DIR := $(TOP_DEPLOY_DIR)/kernel32/
K64_DEPLOY_DIR := $(TOP_DEPLOY_DIR)/kernel64/

# Binary files
TOP_BINARIES := $(KBL_DEPLOY_DIR)/BootLoader.bin $(K32_DEPLOY_DIR)/Kernel32.bin $(K64_DEPLOY_DIR)/Kernel64.bin