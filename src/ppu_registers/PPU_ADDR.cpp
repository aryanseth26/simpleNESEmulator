#include "../include/ppu_registers/PPU_ADDR.h"

PPU_ADDR::PPU_ADDR(): addr(0) {}


void PPU_ADDR::update_addr(uint8_t data) {
    if (is_msb) {
        addr = data;
        addr = addr << 8;
    }
    else {
        addr |= data; 
    }

    if (addr > 0x3fff) {
        addr &= 0x3fff;
    }

    is_msb = !is_msb;
}

void PPU_ADDR::increment_addr(uint8_t increment_amount) {
    addr += increment_amount;
    if (addr > 0x3fff) {
        addr &= 0x3fff;
    }
}

void PPU_ADDR::reset_addr_latch() {
    is_msb = true;
}