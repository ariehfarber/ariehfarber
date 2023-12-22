# List of projects
PROJECTS = uid

# Binaries for each project
BINS = $(addsuffix .out, $(PROJECTS))

# Flags for Debug and Release
DEBUG_FLAG = debug
RELEASE_FLAG = release
STATIC_FLAG = static
DYNAMIC_FLAG = dynamic

# Default target to build all projects
.PHONY: all
all: $(BINS) static_all dynamic_all

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

# Target to build static libraries for all projects
.PHONY: static_all
static_all:
	@ for project in $(PROJECTS); do \
		$(MAKE) --no-print-directory -f makefile.$$project $(STATIC_FLAG); \
	done

# Cleanup target to clean all projects
.PHONY: clean_all
clean_all:
	@ for project in $(PROJECTS); do \
		$(MAKE) --no-print-directory -f makefile.$$project clean; \
	done

# Project-specific commands
$(PROJECTS):
	@ $(MAKE) --no-print-directory -f makefile.$@ \
	$(filter-out $@,$(MAKECMDGOALS))

# Catch-all target that does nothing
%:
	@:
