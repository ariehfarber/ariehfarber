# Project Name
PROJECT = pq
SORTED_LIST_PROJECT = sorted_list
DLL_PROJECT = dll

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
DBG_LDFLAGS = -L$(DBG_OBJ_DIR)
REL_LDFLAGS = -L$(REL_OBJ_DIR)

# Source files
SRC_FILE = $(SRC_DIR)/$(PROJECT).c
# Test files
TEST_FILE = $(TEST_DIR)/$(PROJECT)_test.c
# Header files
HDR_FILES = $(HDR_DIR)/$(PROJECT).h

# Object files for debug and release
DBG_SRC_OBJ = $(DBG_OBJ_DIR)/$(PROJECT).o
DBG_TEST_OBJ = $(DBG_OBJ_DIR)/$(PROJECT)_test.o
REL_SRC_OBJ = $(REL_OBJ_DIR)/$(PROJECT).o
REL_TEST_OBJ = $(REL_OBJ_DIR)/$(PROJECT)_test.o

# Static library paths
LIBS = -l_$(SORTED_LIST_PROJECT) -l_$(DLL_PROJECT)

# Default target
all: debug 

# Debug target
debug: $(DIR)/$(PROJECT).out

$(DIR)/$(PROJECT).out: $(DBG_SRC_OBJ) $(DBG_TEST_OBJ)
	@ $(CC) $(DBG_FLAGS) $(DBG_LDFLAGS) $^ -o $@ $(LIBS)

$(DBG_SRC_OBJ): $(SRC_FILE) $(HDR_FILES)
	@ $(CC) $(CFLAGS) $(DBG_FLAGS) -c $< -o $@

$(DBG_TEST_OBJ): $(TEST_FILE) $(HDR_FILES)
	@ $(CC) $(CFLAGS) $(DBG_FLAGS) -c $< -o $@

# Release target
release: $(DIR)/$(PROJECT)_release.out

$(DIR)/$(PROJECT)_release.out: $(REL_SRC_OBJ) $(REL_TEST_OBJ)
	@ $(CC) $(REL_FLAGS) $(REL_LDFLAGS) $^ -o $@ $(LIBS)

$(REL_SRC_OBJ): $(SRC_FILE) $(HDR_FILES)
	@ $(CC) $(CFLAGS) $(REL_FLAGS) -c $< -o $@

$(REL_TEST_OBJ): $(TEST_FILE) $(HDR_FILES)
	@ $(CC) $(CFLAGS) $(REL_FLAGS) -c $< -o $@	

# Clean
.PHONY: clean
clean:
	@ rm -f $(DBG_OBJ_DIR)/* $(REL_OBJ_DIR)/* $(DIR)/*$(PROJECT)*.out 

open:
	@ find . -type f -name "$(PROJECT)*.c" -exec gedit {} +&
	@ find . -type f -name "$(PROJECT)*.h" -exec gedit {} +&
