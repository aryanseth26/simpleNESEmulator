#include "../include/PPU_CTRL.h"

PPU_CTRL::PPU_CTRL(): control_bits(0) {}

    void PPU_CTRL::set_ctrl_bits(uint8_t data) {
        control_bits = data;
    }

    uint16_t PPU_CTRL::nametable_addr() {
        switch (control_bits & 0b11){
        case 0:
            return 0x2000;
        case 1:
            return 0x2400;
        case 2:
            return 0x2800;
        case 3:
            return 0x2c00;
        default:
            break;
        }

    }

    uint8_t PPU_CTRL::vram_addr_increment_val() {
        return control_bits & 0b100 ? 32 : 1;
    }

    uint16_t PPU_CTRL::sprite_table_addr() {
        return control_bits & 0b1000 ? 0x1000 : 0;
    }

    uint16_t PPU_CTRL::background_table_addr() {
        return control_bits & 0b10000 ? 0x1000 : 0;
        
    }

    uint8_t PPU_CTRL::sprite_size() {
        return control_bits & 0b100000 ? 16 : 8;
    }

    uint8_t PPU_CTRL::master_slave_select() {
        return control_bits & 0b1000000 ? 1 : 0;
    }

    bool PPU_CTRL::generate_nmi_vblank() {
        return control_bits & 0b10000000;
    }