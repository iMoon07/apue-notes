.RECIPEPREFIX := >

CC := gcc
CPPFLAGS := -Iinclude
CFLAGS := -Wall -Wextra -Wpedantic -g
LDLIBS := -lm -lreadline

BIN_DIR := bin
BUILD_DIR := build
CMD_DIR := cmd
LIB_DIR := lib
INC_DIR := include

COMMAND_SOURCES := $(wildcard $(CMD_DIR)/*.c)
COMMANDS := $(patsubst $(CMD_DIR)/%.c,%,$(COMMAND_SOURCES))

LIB_SOURCES := $(wildcard $(LIB_DIR)/*.c)
LIBRARIES := $(patsubst $(LIB_DIR)/%.c,%,$(LIB_SOURCES))

BINARIES := $(COMMANDS:%=$(BIN_DIR)/%)
LIB_OBJECTS := $(LIBRARIES:%=$(BUILD_DIR)/lib/%.o)

all: $(BINARIES)

$(BIN_DIR) $(BUILD_DIR)/cmd $(BUILD_DIR)/lib:
>mkdir -p $@

$(BUILD_DIR)/cmd/%.o: $(CMD_DIR)/%.c $(INC_DIR)/moon.h | $(BUILD_DIR)/cmd
>$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/lib/%.o: $(LIB_DIR)/%.c $(INC_DIR)/moon.h | $(BUILD_DIR)/lib
>$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/%: $(BUILD_DIR)/cmd/%.o $(LIB_OBJECTS) | $(BIN_DIR)
>$(CC) $^ -o $@ $(LDLIBS)

clean:
>rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean
