# Sub directories
K64_ARCH_SUB_DIRS_ALL := $(sort $(dir $(wildcard */)))
K64_ARCH_SUB_DIRS := $(filter-out scripts/,$(K64_ARCH_SUB_DIRS_ALL))

# Sub source directories
K64_ENTRY_DIR := $(K64_ARCH_DIR)/entry/

# Sub deploy directories
K64_ENTRY_DEPLOY_DIR := $(K64_ARCH_DEPLOY_DIR)/entry/

# Object files
K64_ENTRY_OBJ := $(K64_ENTRY_DEPLOY_DIR)/entry.o