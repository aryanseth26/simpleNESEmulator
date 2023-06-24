.PHONY: all clean
CC=g++ -g -Wall -fno-builtin -std=c++17

# List of source files for your receiver
SRC=$(wildcard *.cpp)

# Generate the names of the receiver's object files
SRC_OBJ=${SRC:.cpp=.o}

all: emulator

# Compile the receiver and tag this compilation
emulator: ${SRC_OBJ}

	${CC} -o $@ $^ -L /opt/homebrew/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Generic rules for compiling a source file to an object file
%.o: %.cpp
	${CC} -c $< -I/opt/homebrew/Cellar/sfml/2.5.1_2/include
%.o: %.cc
	${CC} -c $< -I/opt/homebrew/Cellar/sfml/2.5.1_2/include

clean:
	
	rm -f ${SRC_OBJ} emulator 