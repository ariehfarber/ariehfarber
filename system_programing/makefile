# Projects
PROJECTS = $(notdir $(basename $(SRC)))

# Directories
DIR = $(CURDIR)
DEBUG_DIR = $(DIR)/bin/debug
REL_DIR = $(DIR)/bin/release
HDR_DIR = $(DIR)/include
SRC_DIR =  $(DIR)/src
TEST_DIR =  $(DIR)/test

# Compiler flags
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -I$(HDR_DIR)
REL_FLAGS = -DNDEBUG -O3
DEPENDENCIES_FLAGS = -MMD -MP

# Files
SRC = $(wildcard $(SRC_DIR)/*.c)
DEBUG_OBJS = $(SRC:$(SRC_DIR)/%.c=$(DEBUG_DIR)/%.o)
DEBUG_LIBS = $(DEBUG_OBJS:$(DEBUG_DIR)/%.o=$(DEBUG_DIR)/lib_%.so)
REL_OBJS = $(SRC:$(SRC_DIR)/%.c=$(REL_DIR)/%.o)
REL_LIBS = $(REL_OBJS:$(REL_DIR)/%.o=$(REL_DIR)/lib_%.so)
DEBUG_EXECUTABLES =  $(addprefix $(DIR)/, $(addsuffix .out, $(PROJECTS)))
REL_EXECUTABLES =  $(addprefix $(DIR)/, $(addsuffix _release.out, $(PROJECTS)))
DEPENDENCIES = $(DEBUG_OBJS:.o=.d) $(REL_OBJS:.o=.d)

# Function to generate debug library objects
define DebugGenerateLibraryObjects
$(shell cat $(DEBUG_DIR)/$1.d | \
    tr ' ' '\n' | \
    grep '\.h' | \
    sed -e 's,^$(HDR_DIR)/,,;s,\.h$$,.o,;s,^,$(DEBUG_DIR)/,' | \
    grep -v '\.h:$$')
endef

# Function to generate release library objects
define ReleaseGenerateLibraryObjects
$(shell cat $(REL_DIR)/$1.d | \
    tr ' ' '\n' | \
    grep '\.h' | \
    sed -e 's,^$(HDR_DIR)/,,;s,\.h$$,.o,;s,^,$(REL_DIR)/,' | \
    grep -v '\.h:$$')
endef

all: debug release test

# DEBUG #
debug: $(DEBUG_OBJS) $(DEBUG_LIBS)

# Build object files
$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.c 
	@ $(CC) $(CFLAGS) -g -fPIC $(DEPENDENCIES_FLAGS) -c $< -o $@

# Build dynamic libraries
$(DEBUG_DIR)/lib_%.so: $(DEBUG_DIR)/%.o 
	@ $(CC) -shared -o $@ $(call DebugGenerateLibraryObjects,$*)
	
# RELEASE #
release: $(REL_OBJS) $(REL_LIBS)

# Build object files
$(REL_DIR)/%.o: $(SRC_DIR)/%.c
	@ $(CC) $(CFLAGS) $(REL_FLAGS) -fPIC $(DEPENDENCIES_FLAGS) -c $< -o $@

# Build dynamic libraries
$(REL_DIR)/lib_%.so: $(REL_DIR)/%.o
	 @ $(CC) -shared -o $@ $(call ReleaseGenerateLibraryObjects,$*) 
	
# TEST DEBUG#
test: $(DEBUG_EXECUTABLES)

# Build the executables
$(DIR)/%.out: $(TEST_DIR)/%_test.c $(DEBUG_DIR)/lib_%.so
	@ $(CC) $(CFLAGS) -g -o $@ $< -Wl,-rpath,$(DEBUG_DIR) \
	-L$(DEBUG_DIR) -l_$(notdir $(basename $@))

# CLEAN #
clean:
	@ rm -r $(DEBUG_DIR)/* $(REL_DIR)/* $(DIR)/*.out 

# Open a Spacific project #
open:
	@ $(eval PROJECT := $(filter-out $@,$(MAKECMDGOALS)))
	@ if echo "$(PROJECTS)" | grep -wq "$(PROJECT)"; then \
		 gedit $(TEST_DIR)/$(PROJECT)_t*.c $(SRC_DIR)/$(PROJECT).c \
		 $(HDR_DIR)/$(PROJECT).h & \
    fi
# Disable Implicit Rule Search
%:
	@:
	
.PHONY: clean debug release test open final

# Include dependency files
-include $(DEPENDENCIES)
