#include <vector>
#include <cstdint>

class Bus {
public:
    Bus();

    //Read/Write 1 Byte
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t data);
    
    //Read/Write 2 Byte
    uint16_t read_16(uint16_t addr);
    void write_16(uint16_t addr, uint16_t data);

private:
    std::vector<uint8_t> memory;

};