CC=g++ -g -Wall -fno-builtin -std=c++17

# List of source files for your receiver
EMULATOR_SOURCES=$(wildcard *.cpp)
PPU_SOURCES=$(wildcard ppu_registers/*.cpp)

# Generate the names of the receiver's object files
EMULATOR_OBJS=${EMULATOR_SOURCES:.cpp=.o}
PPU_OBJS=${PPU_SOURCES:.cpp=.o}

all: emulator

# Compile the receiver and tag this compilation
emulator: ${EMULATOR_OBJS}
	cd ppu_registers && make
	${CC} -o $@ $^ ${PPU_OBJS}

# Generic rules for compiling a source file to an object file
%.o: %.cpp
	${CC} -c $<
%.o: %.cc
	${CC} -c $<

clean:
	cd ppu_registers && make clean
	rm -f ${EMULATOR_OBJS} emulator 