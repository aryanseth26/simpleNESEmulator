#include <cstdint>

class PPU_CTRL {
private:

/*
    7  bit  0
    ---- ----
    VPHB SINN
    |||| ||||
    |||| ||++- Base nametable address
    |||| ||    (0 = $2000; 1 = $2400; 2 = $2800; 3 = $2C00)
    |||| |+--- VRAM address increment per CPU read/write of PPUDATA
    |||| |     (0: add 1, going across; 1: add 32, going down)
    |||| +---- Sprite pattern table address for 8x8 sprites
    ||||       (0: $0000; 1: $1000; ignored in 8x16 mode)
    |||+------ Background pattern table address (0: $0000; 1: $1000)
    ||+------- Sprite size (0: 8x8 pixels; 1: 8x16 pixels)
    |+-------- PPU master/slave select
    |          (0: read backdrop from EXT pins; 1: output color on EXT pins)
    +--------- Generate an NMI at the start of the
            vertical blanking interval (0: off; 1: on)

*/
    uint8_t control_bits;

public:
    PPU_CTRL();

    void set_ctrl_bits(uint8_t data);
    uint16_t nametable_addr();
    uint8_t vram_addr_increment_val();
    uint16_t sprite_table_addr();
    uint16_t background_table_addr();
    uint8_t sprite_size();
    uint8_t master_slave_select();
    bool generate_nmi_vblank();

};