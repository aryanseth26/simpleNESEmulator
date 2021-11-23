#include "Bus.h"

Bus::Bus(): memory(0x800, 0) {}

uint8_t Bus::read(uint16_t addr) {
    return memory[addr];
}

void Bus::write(uint16_t addr, uint8_t data) {
    memory[addr] = data;
}

uint16_t Bus::read_16(uint16_t addr) {
    uint16_t lo = memory[addr];
    uint16_t hi = memory[addr + 1];

    return hi << 8 | lo;
}
void Bus::write_16(uint16_t addr, uint16_t data) {

    uint8_t lo = data << 8;
    uint8_t hi = data & 0xFF;

    memory[addr] = lo;
    memory[addr + 1] = hi;
}