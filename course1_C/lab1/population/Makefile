# Compiler
CC = clang

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
EXT_DIR = ext
TEST_DIR = tests

# Compiler flags
CFLAGS = -ferror-limit=1 -gdwarf-4 -ggdb3 -O0 -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wshadow
LDFLAGS = -lcrypt -lcs50 -lm

# Source files
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Test files
TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ = $(TEST_SRC:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)

# External headers
EXT_HEADERS = $(wildcard $(EXT_DIR)/*.h)

# Binary name
BIN = $(BIN_DIR)/population

all: $(BIN)

$(BIN): $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(EXT_HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

tests: $(OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(TEST_DIR)/test_suite
	$(TEST_DIR)/test_suite

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c $(EXT_HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(TEST_DIR)/test_suite

.PHONY: all tests clean
