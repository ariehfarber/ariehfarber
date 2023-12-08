# List of projects
PROJECTS = bitarray stack vector sll sll_ext queue

# Binaries for each project
BINS = $(addsuffix .out, $(PROJECTS))

# Flags for Debug and Release
DEBUG_FLAG = debug
RELEASE_FLAG = release

# Default target to build all projects
.PHONY: all
all: $(BINS)

$(BINS):
	@ $(MAKE) --no-print-directory -f makefile.$(@:.out=)

# Target to build all projects in debug mode
.PHONY: debug_all
debug_all:
	@ for project in $(PROJECTS); do \
		$(MAKE) --no-print-directory -f makefile.$$project $(DEBUG_FLAG); \
	done

# Target to build all projects in release mode
.PHONY: release_all
release_all:
	@ for project in $(PROJECTS); do \
		$(MAKE) --no-print-directory -f makefile.$$project $(RELEASE_FLAG); \
	done

# Cleanup target to clean all projects
.PHONY: clean_all
clean_all:
	@ for project in $(PROJECTS); do \
		$(MAKE) --no-print-directory -f makefile.$$project clean; \
	done
