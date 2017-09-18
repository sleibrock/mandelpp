# Makefile to build all binaries
# Binary 1: the Mandelbrot rendering program
# Binary 2: the Julia set rendering program
CXX=g++
CXXFLAGS=-O3 -Wall -std=gnu++11 -fdiagnostics-color
LIBS=
LDFLAGS=
RM=rm -f
MKD=mkdir -p
S=src
O=obj

# Check if GMP exists in the compiler library
# (not 100% perfect or portable (yet))
GMPC=$(CXX) -lgmp
GMPXX=$(CXX) -lgmpxx

@_=$(shell $(CXX) -lgmp)
EXIT_CODE=$$?
ifeq ($EXIT_CODE,0)
	LIBS=$(LIBS) -lgmp
endif

@_=$(shell $(CXX) -lgmpxx)
EXIT_CODE=$$?
ifeq ($EXIT_CODE,0)
	LIBS=$(LIBS) -lgmpxx
endif

# List all objects shared between all programs
# These objects serve their data and functions to be linked by
# the individual programs as needed
COREOBJS=$(addprefix $(O)/,opts.o colors.o resolutions.o complex.o rendering.o)
MOBJS=$(COREOBJS) $(O)/mandelbrot.o
JOBJS=$(COREOBJS) $(O)/julia.o

# The differente executable targets we wish to build
# Each target must have their own <target>.cpp file with a main() function
MANDEL=mandelbrot
JULIA=julia

all: build

debug:
	@echo "Compiler: $(CXX)"
	@echo "$(shell $(CXX) --version)"
	@echo "Flags: $(CXXFLAGS)"
	@echo "Libs: $(LIBS)"
	@echo "LD flags: $(LDFLAGS)"
	@echo "Objects: $(COREOBJS)"

verbose: debug $(MANDEL) $(JULIA)

build: $(MANDEL) $(JULIA)

rebuild: clean build

# Julia linking rule
$(JULIA): $(JOBJS)
	@echo "[LINK] Linking '$(JULIA)' ..."
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(JOBJS) -o $(JULIA) $(LIBS)

# Mandelbrot linking rule
$(MANDEL): $(MOBJS)
	@echo "[LINK] Linking '$(MANDEL)' ..."
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(MOBJS) -o $(MANDEL) $(LIBS)


# Object compilation rule
$(O)/%.o: $(S)/%.cpp | $(O)
	@echo "[COMPILE] Compiling '$<' ..."
	@$(CXX) $(CXXFLAGS) -o $@ -c $< $(LIBS)

# Set up the object folder if it doesn't exist
$(O):
	@echo "[SETUP] Creating object folder ..."
	@$(MKD) $(O)

# Clean up any leftover build files and image dumps
.PHONY: clean
clean:
	@echo "[CLEAN] Cleaning objects/exes/files"
	@$(RM) $(O)/*.o ./*.ppm $(JULIA) $(JULIA).exe $(MANDEL) $(MANDEL).exe
