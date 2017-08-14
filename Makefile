CXX=g++
CPPFLAGS=-O3 -Wall -std=gnu++11
LIBS=
LDFLAGS=

RM=rm -f
SRC=src
O=$(SRC)
OUTPUT=main.exe

OBJS=

$(O)/%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

all: $(O)/mandelbrot

clean:
	$(RM) *.ppm $(SRC)/*.o $(SRC)/*~

rebuild: clean all

$(O)/mandelbrot: $(OBJS) $(O)/mandelbrot.o
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(OBJS) $(O)/mandelbrot.o -o $(OUTPUT) $(LIBS) 

