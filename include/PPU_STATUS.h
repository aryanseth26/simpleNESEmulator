#include <cstdint>


class PPU_STATUS {
private:
    /*
        7  bit  0
        ---- ----
        VSO. ....
        |||| ||||
        |||+-++++- Least significant bits previously written into a PPU register
        |||        (due to register not being updated for this address)
        ||+------- Sprite overflow. The intent was for this flag to be set
        ||         whenever more than eight sprites appear on a scanline, but a
        ||         hardware bug causes the actual behavior to be more complicated
        ||         and generate false positives as well as false negatives; see
        ||         PPU sprite evaluation. This flag is set during sprite
        ||         evaluation and cleared at dot 1 (the second dot) of the
        ||         pre-render line.
        |+-------- Sprite 0 Hit.  Set when a nonzero pixel of sprite 0 overlaps
        |          a nonzero background pixel; cleared at dot 1 of the pre-render
        |          line.  Used for raster timing.
        +--------- Vertical blank has started (0: not in vblank; 1: in vblank).
                Set at dot 1 of line 241 (the line *after* the post-render
                line); cleared after reading $2002 and at dot 1 of the
                pre-render line.
    */

    uint8_t status_bits;

public:
    PPU_STATUS();

    void reset();
    uint8_t get_status_bits();
    uint8_t set_sprite_ovrflw(uint8_t value);
    uint8_t set_sprite_zero_hit(uint8_t value);
    uint8_t set_vblank(uint8_t value);
    bool is_vblank();




};