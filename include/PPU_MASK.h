#include <cstdint>
#include <vector>

class PPU_MASK {
private:
    /*

        7  bit  0
        ---- ----
        BGRs bMmG
        |||| ||||
        |||| |||+- Greyscale (0: normal color, 1: produce a greyscale display)
        |||| ||+-- 1: Show background in leftmost 8 pixels of screen, 0: Hide
        |||| |+--- 1: Show sprites in leftmost 8 pixels of screen, 0: Hide
        |||| +---- 1: Show background
        |||+------ 1: Show sprites
        ||+------- Emphasize red (green on PAL/Dendy)
        |+-------- Emphasize green (red on PAL/Dendy)
        +--------- Emphasize blue
    */

    uint8_t mask_bits;

public:

    PPU_MASK();
    void set_bits(uint8_t data);
    
    uint8_t show_greyscale();
    uint8_t show_left_background();
    uint8_t show_left_sprite();
    uint8_t show_background();
    uint8_t show_sprites();
    std::vector<int> emphasize_colors();
};