#include "../include/PPU_MASK.h"

PPU_MASK::PPU_MASK(): mask_bits(0) {}

    void PPU_MASK::set_bits(uint8_t data) {
        mask_bits = data;
    }

    uint8_t PPU_MASK::show_greyscale() {
        return mask_bits & 0b1;
    }

    uint8_t PPU_MASK::show_left_background() {
        return mask_bits & 0b10;
    }

    uint8_t PPU_MASK::show_left_sprite() {
        return mask_bits & 0b100;
    }

    uint8_t PPU_MASK::show_background() {
        return mask_bits & 0b1000;
    }

    uint8_t PPU_MASK::show_sprites() {
        return mask_bits & 0b10000;
    }

    std::vector<int> PPU_MASK::emphasize_colors() {
        std::vector<int> emphasized_colors;

        if (mask_bits & 0b100000) {
            emphasized_colors.push_back(0);
        }

        if (mask_bits & 0b1000000) {
            emphasized_colors.push_back(1);
        }
        if (mask_bits & 0b10000000) {
            emphasized_colors.push_back(2);
        }

        return emphasized_colors;
    }
