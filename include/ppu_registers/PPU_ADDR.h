#include <cstdint>


class PPU_ADDR {
private:
    bool is_msb;

    uint16_t addr;
    
public:

    PPU_ADDR();

    void reset_addr_latch();
    void update_addr(uint8_t data);
    void increment_addr(uint8_t increment_amount);


};