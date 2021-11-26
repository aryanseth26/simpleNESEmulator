#include <fstream>
#include <iostream>
#include <vector>

enum MirroringType {
    VERTICAL,
    HORIZONTAL,
    FOUR_SCREEN,
};

class Cartridge {
private:

    //Header
    struct Header {
        char nes_tag[4];
        uint8_t prg_rom_size;
        uint8_t chr_rom_size;
        uint8_t flags_6;
        uint8_t flags_7;
        uint8_t prg_ram_size;
        uint8_t flags_9;
        uint8_t flags_10;
        char unused_padding[4];
    };

    Header header;

    //Masks
    uint8_t TRAINER_MASK = 0x04;
    uint8_t MIRROR_TYPE_IGNORE_MASK = 0x08;

    //Mirror Type
    MirroringType mirror_type;

    //Mapping Type
    uint8_t mapping_type;

    //Rom chunk sizes
    int PRG_ROM_CHUNK_SIZE = 0x4000;
    int CHR_ROM_CHUNK_SIZE = 0x2000;

    //Rom Data
    std::vector<uint8_t> prg_rom;
    std::vector<uint8_t> chr_rom;


public:
    Cartridge(std::string filename);

};