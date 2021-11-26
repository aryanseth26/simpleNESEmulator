#include <vector>
#include <cstdint>

class Bus {
private:
    std::vector<uint8_t> memory;

    uint16_t MIRROR_MASK = 0x07FF;

    
public:
    Bus();

    
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t data);
    
    uint16_t read_16(uint16_t addr);
    void write_16(uint16_t addr, uint16_t data);

};