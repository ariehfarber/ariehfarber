# Project Name - modify as needed
PROJECT = sll

# Directories
DIR = /home/arieh/git/ds
DBG_OBJ_DIR = $(DIR)/bin/debug
REL_OBJ_DIR = $(DIR)/bin/release
HDR_DIR = $(DIR)/include
SRC_DIR =  $(DIR)/src
TEST_DIR = $(DIR)/test

# Compiler
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -I$(HDR_DIR)
DBG_FLAGS = -g
REL_FLAGS = -O3

# Source files
SRC_FILE = $(SRC_DIR)/$(PROJECT).c
TEST_FILE = $(TEST_DIR)/$(PROJECT)_test.c

# Object files for debug and release
DBG_OBJ = $(DBG_OBJ_DIR)/$(PROJECT).o
DBG_TEST_OBJ = $(DBG_OBJ_DIR)/test_$(PROJECT).o
REL_OBJ = $(REL_OBJ_DIR)/$(PROJECT).o
REL_TEST_OBJ = $(REL_OBJ_DIR)/test_$(PROJECT).o

# Default target
all: debug

# Debug and Release targets
debug: $(DBG_OBJ) $(DBG_TEST_OBJ)
	$(CC) $(DBG_FLAGS) $^ -o $(DIR)/$(PROJECT).out

release: $(REL_OBJ) $(REL_TEST_OBJ)
	$(CC) $(REL_FLAGS) $^ -o $(DIR)/$(PROJECT).out

# Rule to generate object file for project in debug
$(DBG_OBJ): $(SRC_FILE)
	$(CC) $(CFLAGS) $(DBG_FLAGS) -c $< -o $@
$(DBG_TEST_OBJ): $(TEST_FILE)
	$(CC) $(CFLAGS) $(DBG_FLAGS) -c $< -o $@

# Rule to generate object file for project in release
$(REL_OBJ): $(SRC_FILE)
	$(CC) $(CFLAGS) $(REL_FLAGS) -c $< -o $@
$(REL_TEST_OBJ): $(TEST_FILE)
	$(CC) $(CFLAGS) $(REL_FLAGS) -c $< -o $@	

# Clean
.PHONY: clean
clean:
	rm -f $(DBG_OBJ_DIR)/*.o $(REL_OBJ_DIR)/*.o $(PROJECT).out
	
open:
	find . -type f -name "$(PROJECT)*.c" -exec gedit {} +&
	find . -type f -name "$(PROJECT)*.h" -exec gedit {} +&
