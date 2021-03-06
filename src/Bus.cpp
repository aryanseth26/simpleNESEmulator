#include "../include/Bus.h"

Bus::Bus(Cartridge &rom_in): memory(0x800, 0), rom(rom_in) {}

uint8_t Bus::read(uint16_t addr) {
    if (addr < 0x2000) {
        return memory[addr & MIRROR_MASK];
    }
    else if (addr < 0x4020) {
        exit(-1);
    }
    else {
        rom.read_prg(addr);
    }
    return -1;
}

void Bus::write(uint16_t addr, uint8_t data) {
    if (addr < 0x2000) {
        memory[addr] = data;
    }

    else if (addr < 0x4020) {
        exit(-1);
    }
    else {
        rom.write_prg(addr, data);
    }
}

uint16_t Bus::read_16(uint16_t addr) {
    uint16_t lo = read(addr);
    uint16_t hi = read(addr + 1);

    return hi << 8 | lo;
}
void Bus::write_16(uint16_t addr, uint16_t data) {

    uint8_t lo = data << 8;
    uint8_t hi = data & 0xFF;

    write(addr, lo);
    write(addr + 1, hi);
}
