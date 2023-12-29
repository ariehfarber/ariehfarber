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
EXECUTABLES =  $(addprefix $(DIR)/, $(addsuffix .out, $(PROJECTS)))
DEPENDENCIES = $(DEBUG_OBJS:.o=.d)

# Include dependency files
-include $(DEPENDENCIES)

all: debug release

# DEBUG #
debug: $(DEBUG_OBJS) $(DEBUG_LIBS)

# Build object files
$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.c
	@ $(CC) $(CFLAGS) -g -fPIC $(DEPENDENCIES_FLAGS) -c $< -o $@

# Build dynamic libraries
$(DEBUG_DIR)/lib_%.so: $(REL_DIR)/%.o
	 @ $(CC) -shared -o $@ $^ 
	
# RELEASE #
release: $(REL_OBJS) $(REL_LIBS)

# Build object files
$(REL_DIR)/%.o: $(SRC_DIR)/%.c
	@ $(CC) $(CFLAGS) $(REL_FLAGS) -fPIC $(DEPENDENCIES_FLAGS) -c $< -o $@

# Build dynamic libraries
$(REL_DIR)/lib_%.so: $(REL_DIR)/%.o
	 @ $(CC) -shared -o $@ $^ 
	
# TEST #
test: $(EXECUTABLES)

# Function to generate library dependencies from .d files
define generate_lib_dependencies
$(shell cat $(DEBUG_DIR)/$1.d | \
    tr ' ' '\n' | \
    grep '\.h' | \
    sed -e 's,^$(HDR_DIR)/,,;s,\.h$$,,;s,:$$,,;s,^,-l_,' | \
    grep -v '\.h$$')
endef

# Build the executables
$(DIR)/%.out: $(TEST_DIR)/%_test.c
	$(eval LIB_DEPENDENCIES=$(call generate_lib_dependencies,$*))
	@ $(CC) $(CFLAGS) -g -o $@ $< -Wl,-rpath,$(DEBUG_DIR) \
	-L$(DEBUG_DIR) $(LIB_DEPENDENCIES)

# CLEAN #
clean:
	@ rm -r $(DEBUG_DIR)/* $(REL_DIR)/* $(DIR)/*.out

.PHONY: clean debug release test
