CXX_STANDARD = c++17
CXX_WARNINGS = -Wall -Wextra -Wpwendatic
CXX = $(CROSS_COMPILE)gcc
CXX_FLAGS = $(CXX_WARNINGS) -std=$(CXX_STANDARD)

CXX_COMPILER_CALL = $(CXX) $(CXXFLAGS)

all: build

build:
	$(CXX_COMPILER_CALL) -c -o writer.o writer.c
	$(CXX_COMPILER_CALL) -o writer writer.o

clean:
	rm -f *.o writer *.elf *.map