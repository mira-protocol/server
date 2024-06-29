# paths
SERVER_LIB_DIR = mira_server
SERVER_DIR     = server
BIN_DIR        = bin
BIN_DIRS       = $(BIN_DIR) $(addprefix $(BIN_DIR)/,$(SERVER_LIB_DIR) $(SERVER_DIR))

# library
# path to generated libraries. Must have forward slash postfix if not left
# empty (root).
LIB_PATH =
LIB_EXT  =

OS ?= $(shell uname -s)
ifeq ($(OS),Darwin)
	LIB_EXT = dylib
endif
ifeq ($(OS),Linux)
	LIB_EXT = so
endif
ifeq ($(OS),Windows_NT)
	$(error "Platform support not implemented")
endif

# server library
SERVER_LIB_SRC  = $(wildcard $(SERVER_LIB_DIR)/*.c)
SERVER_LIB_DEPS = $(wildcard $(SERVER_LIB_DIR)/*.h)
SERVER_LIB_OBJ  = $(patsubst $(SERVER_LIB_DIR)/%.c,$(BIN_DIR)/$(SERVER_LIB_DIR)/%.o,$(SERVER_LIB_SRC))
SERVER_LIB_PATH = $(LIB_PATH)
SERVER_LIB_NAME = miraserver
SERVER_LIB_FULL = $(SERVER_LIB_PATH)lib$(SERVER_LIB_NAME).$(LIB_EXT)

# server
SERVER_SRC  = $(wildcard $(SERVER_DIR)/*.c)
SERVER_DEPS = $(wildcard $(SERVER_DIR)/*.h)
SERVER_OBJ  = $(patsubst $(SERVER_DIR)/%.c,$(BIN_DIR)/$(SERVER_DIR)/%.o,$(SERVER_SRC))
SERVER_EXE  = mira-server

# compiler flags
FLAGS = -std=c11 -Wall -Wextra -pedantic -g -I.
LIBS  = -lpthread -L. -l$(SERVER_LIB_NAME)

compile: $(BIN_DIRS) $(SERVER_LIB_FULL) $(SERVER_EXE)

clean:
	-rm -rf $(BIN_DIR) $(SERVER_LIB_FULL) $(SERVER_EXE)

dump:
	@echo "src: $(SERVER_LIB_SRC)"
	@echo "deps: $(SERVER_LIB_DEPS)"
	@echo "obj: $(SERVER_LIB_OBJ)"
	@echo "lib: $(SERVER_LIB_FULL)"

$(BIN_DIR)/$(SERVER_DIR)/%.o: $(SERVER_DIR)/%.c $(BIN_DIRS)
	$(CC) $(FLAGS) -c $< -o $@

$(SERVER_EXE): $(SERVER_OBJ) $(SERVER_LIB_FULL)
	$(CC) $(FLAGS) $^ -o $@ $(LIBS)

$(BIN_DIR)/$(SERVER_LIB_DIR)/%.o: $(SERVER_LIB_DIR)/%.c $(BIN_DIRS)
	$(CC) $(FLAGS) -fpic -c $< -o $@

$(SERVER_LIB_FULL): $(BIN_DIRS) $(SERVER_LIB_OBJ) $(SERVER_LIB_DEPS)
	$(CC) $(FLAGS) -shared $(SERVER_LIB_OBJ) -o $@

$(BIN_DIRS):
	-mkdir $@
