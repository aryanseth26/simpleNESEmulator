CC=g++ -Wall -fno-builtin -std=c++17

# List of source files for your receiver
PPU_SOURCES=$(wildcard *.cpp)

# Generate the names of the receiver's object files
PPU_OBJS=${PPU_SOURCES:.cpp=.o}

all: ppu_sources

# Compile the receiver and tag this compilation
ppu_sources: ${PPU_OBJS}

# Generic rules for compiling a source file to an object file
%.o: %.cpp
	${CC} -c $<
%.o: %.cc
	${CC} -c $<

clean:
	rm -f ${PPU_OBJS} 