#CXX=g++
#CPPFLAGS=-O3 -Wall -std=gnu++11
#LIBS=
#LDFLAGS=

#RM=rm -f
CXX=g++
CXXFLAGS=-O3 -Wall -std=gnu++11
LIBS=
LDFLAGS=

RM=rm -f
MKD=mkdir -p

S=src
O=obj
OBJS=$(addprefix $(O)/,mandelbrot.o)

TARGET=mandelbrot


all: $(TARGET)

build: $(TARGET)

$(TARGET): $(OBJS)
	@echo "[CLEAN] Linking '$(TARGET)' ..."
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

$(O)/%.o: $(S)/%.cpp | $(O)
	@echo "[BUILD] Compiling '$<' ..."
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(O):
	@echo "[SETUP] Creating object folder ..."
	@$(MKD) $(O)


.PHONY: clean
clean:
	@echo "[CLEAN] Cleaning objects/exes/files"
	@$(RM) $(O)/*.o *.ppm $(TARGET) $(TARGET).exe
