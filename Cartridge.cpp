#include "Cartridge.h"

Cartridge::Cartridge(std::string filename) {
    //Want to read raw data, not the textual interpretation
    std::ifstream ifs(filename, std::ifstream::binary);
    
    if (ifs.is_open()) {
        ifs.read((char *) &header, sizeof(header));

        if (header.flags_6 & TRAINER_MASK) {
            ifs.seekg(512, std::ios_base::cur);
        }

        mapping_type = ((header.flags_7 >> 4) << 4 ) | header.flags_6 >> 4;

        
        mirror_type = (header.flags_6 & 1) ? MirroringType::VERTICAL : MirroringType::HORIZONTAL;
        mirror_type = header.flags_6 & MIRROR_TYPE_IGNORE_MASK ? MirroringType::FOUR_SCREEN : mirror_type;
        
        prg_rom.resize(header.prg_rom_size * PRG_ROM_CHUNK_SIZE);
        chr_rom.resize(header.chr_rom_size * CHR_ROM_CHUNK_SIZE);

        ifs.read((char *) prg_rom.data(), prg_rom.size());
        ifs.read((char *) chr_rom.data(), chr_rom.size());

    }
    else {
        std::cout << "ERROR OPENING FILE\n";
        exit(-1);
    }
    
}