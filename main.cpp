#include "CPU.h"

int main(int argc, char **argv) {
    std::string filename(argv[1]);

    Cartridge game_cart(filename);

    return 0;
}