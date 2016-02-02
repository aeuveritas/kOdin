# Sub directories
K64_SHELL_SUB_DIRS := $(sort $(dir $(wildcard */)))

# Sub source directories
K64_COMMAND_DIR := $(K64_SHELL_DIR)/command/

# Sub deploy directories
K64_COMMAND_DEPLOY_DIR := $(K64_SHELL_DEPLOY_DIR)/command/

# Object files
K64_COMMAND_OBJ := $(K64_COMMAND_DEPLOY_DIR)/command.o