CC=g++ -g -Wall -fno-builtin -std=c++17

# List of source files for your receiver
EMULATOR_SOURCES=main.cpp CPU.cpp Bus.cpp Cartridge.cpp

# Generate the names of the receiver's object files
EMULATOR_OBJS=${EMULATOR_SOURCES:.cpp=.o}

all: emulator

# Compile the receiver and tag this compilation
emulator: ${EMULATOR_OBJS}
	${CC} -o $@ $^

# Generic rules for compiling a source file to an object file
%.o: %.cpp
	${CC} -c $<
%.o: %.cc
	${CC} -c $<

clean:
	rm -f ${EMULATOR_OBJS} emulator 