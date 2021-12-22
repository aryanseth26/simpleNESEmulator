#include "../../include/ppu_registers/PPU_STATUS.h"

PPU_STATUS::PPU_STATUS(): status_bits(0) {}

    void PPU_STATUS::reset() {
        status_bits = 0;
    }

    uint8_t PPU_STATUS::set_sprite_ovrflw(uint8_t value) {
        if (value) {
            status_bits |= 0b00100000;
        }
        else {
            status_bits |= 0b00000000;
        }
        
    }

    uint8_t PPU_STATUS::set_sprite_zero_hit(uint8_t value) {
        if (value) {
            status_bits |= 0b01000000;
        }
        else {
            status_bits |= 0b00000000;
        }
    }

    uint8_t PPU_STATUS::set_vblank(uint8_t value) {
        
        if (value) {
            status_bits |= 0b10000000;
        }
        else {
            status_bits |= 0b00000000;
        }

    }

    bool PPU_STATUS::is_vblank() {
        return status_bits & 0b10000000;
    }

    uint8_t PPU_STATUS::get_status_bits() {
        return status_bits;
    }
