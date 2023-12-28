# Projects
PROJECTS = $(notdir $(basename $(SRC)))

# Optionally specify a project name
PROJECT_NAME ?= all

# Directories
DIR = /home/arieh/git/ds
DEBUG_OBJ_DIR = $(DIR)/bin/debug
REL_OBJ_DIR = $(DIR)/bin/release
HDR_DIR = $(DIR)/include
SRC_DIR =  $(DIR)/src
TEST_DIR =  $(DIR)/test

# Compiler flags
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -I$(HDR_DIR) 
DBG_FLAGS = -g
REL_FLAGS = -DNDEBUG -O3
PIC_FLAGS = -fPIC

# Files
SRC = $(wildcard $(SRC_DIR)/*.c)

# Paths
DEBUG_LIB = $(patsubst %,$(DEBUG_OBJ_DIR)/lib_%.so,$(PROJECTS))
REL_LIB =  $(patsubst %,$(REL_OBJ_DIR)/lib_%.so,$(PROJECTS))
DEBUG_OBJS = $(patsubst %,$(DEBUG_OBJ_DIR)/%.o,$(PROJECTS))
REL_OBJS = $(patsubst %,$(REL_OBJ_DIR)/%.o,$(PROJECTS))
EXECUTABLES = $(patsubst %,$(DIR)/%.out,$(PROJECTS))
TEST = $(patsubst %,$(TEST_DIR)/%_test.c,$(PROJECTS))

# Default #
all: debug release 

# Debug objects and libraries #
debug: $(DEBUG_LIB)

# build the libraries
$(DEBUG_LIB): $(DEBUG_OBJS)
	@ $(CC) -shared $(CFLAGS) $(DBG_FLAGS) -o $@ $^

# build the object files
$(DEBUG_OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@ $(CC) -c $(CFLAGS) $(DBG_FLAGS) $(PIC_FLAGS) -MM -MT $@ -o $@ $<

# release objects and libraries #
release: $(REL_LIB)

# build the libraries
$(REL_LIB): $(REL_OBJS)
	@ $(CC) -shared $(CFLAGS) $(REL_FLAGS) -o $@ $^ 

# build the object files
$(REL_OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@ $(CC) -c $(CFLAGS) $(REL_FLAGS) $(PIC_FLAGS) -MM -MT $@ -o $@ $<

test: $(EXECUTABLES) 

$(EXECUTABLES): $(DIR)/%_test.out : $(TEST_DIR)/%_test.c $(DEBUG_LIB)
	@ $(CC) $(CFLAGS) $(DBG_FLAGS) -L$(DEBUG_OBJ_DIR) -o $@ $< -l_$*
		
# Clean
.PHONY: clean release debug test
clean:
	@  rm -f $(DEBUG_OBJ_DIR)/* $(REL_OBJ_DIR)/* $(DIR)/*.out
	   	
open:
	@  find . -type f -name "$(PROJECT)*.c" -exec gedit {} +&
	@  find . -type f -name "$(PROJECT)*.h" -exec gedit {} +&

# Filter out the specific project if PROJECT_NAME is set
ifeq ($(PROJECT_NAME),all)
    TARGET_PROJECTS = $(PROJECTS)
else
    TARGET_PROJECTS = $(filter $(PROJECT_NAME), $(PROJECTS))
endif
