# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -I../../inc -I.

# Directories
SRC_DIR = ../src/expander
TEST_DIR = .

# Source files
UNITY_SRC = unity.c
TEST_SRC = test_expansion.c
SRC = $(SRC_DIR)/var_expansion.c \
	 ../src/expander/expand_exit_status.c \
	  ../src/expander/expand_env_var.c \
	  ../src/expander/update_expanded_value.c \

# Object files
OBJECTS = $(UNITY_SRC:.c=.o) $(TEST_SRC:.c=.o) $(SRC:.c=.o)

# Target executable
TARGET = run_tests

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

# Compiling
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run tests
test: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all test clean

