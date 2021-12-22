#include "../include/CPU.h"

CPU::CPU(Bus &bus_in) : bus(bus_in) {
    std::unordered_map<uint8_t, Opcode> opcode_matrix = {
        {0x00, {0x00, "BRK", 1, 7, AddressMode::NoneAddressing, nullptr}},
        {0xea, {0xea, "NOP", 1, 2, AddressMode::NoneAddressing, nullptr}},

        /* Arithmetic */
        {0x69, {0x69, "ADC", 2, 2, AddressMode::Immediate, &CPU::ADC}},
        {0x65, {0x65, "ADC", 2, 3, AddressMode::ZeroPage, &CPU::ADC}},
        {0x75, {0x75, "ADC", 2, 3, AddressMode::ZeroPage_X, &CPU::ADC}},
        {0x6d, {0x6d, "ADC", 3, 4, AddressMode::Absolute, &CPU::ADC}},
        {0x7d, {0x7d, "ADC", 3, 4/*+1 if page crossed*/, AddressMode::Absolute_X, &CPU::ADC}},
        {0x79, {0x79, "ADC", 3, 4/*+1 if page crossed*/, AddressMode::Absolute_Y, &CPU::ADC}},
        {0x61, {0x61, "ADC", 2, 6, AddressMode::Indirect_X, &CPU::ADC}},
        {0x71, {0x71, "ADC", 2, 5/*+1 if page crossed*/, AddressMode::Indirect_Y, &CPU::ADC}},
 
        {0xe9, {0xe9, "SBC", 2, 2, AddressMode::Immediate, &CPU::SBC}},
        {0xe5, {0xe5, "SBC", 2, 3, AddressMode::ZeroPage, &CPU::SBC}},
        {0xf5, {0xf5, "SBC", 2, 4, AddressMode::ZeroPage_X, &CPU::SBC}},
        {0xed, {0xed, "SBC", 3, 4, AddressMode::Absolute, &CPU::SBC}},
        {0xfd, {0xfd, "SBC", 3, 4/*+1 if page crossed*/, AddressMode::Absolute_X, &CPU::SBC}},
        {0xf9, {0xf9, "SBC", 3, 4/*+1 if page crossed*/, AddressMode::Absolute_Y, &CPU::SBC}},
        {0xe1, {0xe1, "SBC", 2, 6, AddressMode::Indirect_X, &CPU::SBC}},
        {0xf1, {0xf1, "SBC", 2, 5/*+1 if page crossed*/, AddressMode::Indirect_Y, &CPU::SBC}},
 
        {0x29, {0x29, "AND", 2, 2, AddressMode::Immediate, &CPU::AND}},
        {0x25, {0x25, "AND", 2, 3, AddressMode::ZeroPage, &CPU::AND}},
        {0x35, {0x35, "AND", 2, 4, AddressMode::ZeroPage_X, &CPU::AND}},
        {0x2d, {0x2d, "AND", 3, 4, AddressMode::Absolute, &CPU::AND}},
        {0x3d, {0x3d, "AND", 3, 4/*+1 if page crossed*/, AddressMode::Absolute_X, &CPU::AND}},
        {0x39, {0x39, "AND", 3, 4/*+1 if page crossed*/, AddressMode::Absolute_Y, &CPU::AND}},
        {0x21, {0x21, "AND", 2, 6, AddressMode::Indirect_X, &CPU::AND}},
        {0x31, {0x31, "AND", 2, 5/*+1 if page crossed*/, AddressMode::Indirect_Y, &CPU::AND}},
 
        {0x49, {0x49, "EOR", 2, 2, AddressMode::Immediate, &CPU::EOR}},
        {0x45, {0x45, "EOR", 2, 3, AddressMode::ZeroPage, &CPU::EOR}},
        {0x55, {0x55, "EOR", 2, 4, AddressMode::ZeroPage_X, &CPU::EOR}},
        {0x4d, {0x4d, "EOR", 3, 4, AddressMode::Absolute, &CPU::EOR}},
        {0x5d, {0x5d, "EOR", 3, 4/*+1 if page crossed*/, AddressMode::Absolute_X, &CPU::EOR}},
        {0x59, {0x59, "EOR", 3, 4/*+1 if page crossed*/, AddressMode::Absolute_Y, &CPU::EOR}},
        {0x41, {0x41, "EOR", 2, 6, AddressMode::Indirect_X, &CPU::EOR}},
        {0x51, {0x51, "EOR", 2, 5/*+1 if page crossed*/, AddressMode::Indirect_Y, &CPU::EOR}},
 
        {0x09, {0x09, "ORA", 2, 2, AddressMode::Immediate, &CPU::ORA}},
        {0x05, {0x05, "ORA", 2, 3, AddressMode::ZeroPage, &CPU::ORA}},
        {0x15, {0x15, "ORA", 2, 4, AddressMode::ZeroPage_X, &CPU::ORA}},
        {0x0d, {0x0d, "ORA", 3, 4, AddressMode::Absolute, &CPU::ORA}},
        {0x1d, {0x1d, "ORA", 3, 4/*+1 if page crossed*/, AddressMode::Absolute_X, &CPU::ORA}},
        {0x19, {0x19, "ORA", 3, 4/*+1 if page crossed*/, AddressMode::Absolute_Y, &CPU::ORA}},
        {0x01, {0x01, "ORA", 2, 6, AddressMode::Indirect_X, &CPU::ORA}},
        {0x11, {0x11, "ORA", 2, 5/*+1 if page crossed*/, AddressMode::Indirect_Y, &CPU::ORA}},
 
        /*  Shifts */
        {0x0a, {0x0a, "ASL", 1, 2, AddressMode::NoneAddressing, &CPU::ASL}},
        {0x06, {0x06, "ASL", 2, 5, AddressMode::ZeroPage, &CPU::ASL}},
        {0x16, {0x16, "ASL", 2, 6, AddressMode::ZeroPage_X, &CPU::ASL}},
        {0x0e, {0x0e, "ASL", 3, 6, AddressMode::Absolute, &CPU::ASL}},
        {0x1e, {0x1e, "ASL", 3, 7, AddressMode::Absolute_X, &CPU::ASL}},
 
        {0x4a, {0x4a, "LSR", 1, 2, AddressMode::NoneAddressing, &CPU::LSR}},
        {0x46, {0x46, "LSR", 2, 5, AddressMode::ZeroPage, &CPU::LSR}},
        {0x56, {0x56, "LSR", 2, 6, AddressMode::ZeroPage_X, &CPU::LSR}},
        {0x4e, {0x4e, "LSR", 3, 6, AddressMode::Absolute, &CPU::LSR}},
        {0x5e, {0x5e, "LSR", 3, 7, AddressMode::Absolute_X, &CPU::LSR}},
 
        {0x2a, {0x2a, "ROL", 1, 2, AddressMode::NoneAddressing, &CPU::ROL}},
        {0x26, {0x26, "ROL", 2, 5, AddressMode::ZeroPage, &CPU::ROL}},
        {0x36, {0x36, "ROL", 2, 6, AddressMode::ZeroPage_X, &CPU::ROL}},
        {0x2e, {0x2e, "ROL", 3, 6, AddressMode::Absolute, &CPU::ROL}},
        {0x3e, {0x3e, "ROL", 3, 7, AddressMode::Absolute_X, &CPU::ROL}},
 
        {0x6a, {0x6a, "ROR", 1, 2, AddressMode::NoneAddressing, &CPU::ROR}},
        {0x66, {0x66, "ROR", 2, 5, AddressMode::ZeroPage, &CPU::ROR}},
        {0x76, {0x76, "ROR", 2, 6, AddressMode::ZeroPage_X, &CPU::ROR}},
        {0x6e, {0x6e, "ROR", 3, 6, AddressMode::Absolute, &CPU::ROR}},
        {0x7e, {0x7e, "ROR", 3, 7, AddressMode::Absolute_X, &CPU::ROR}},
    
        {0xe6, {0xe6, "INC", 2, 5, AddressMode::ZeroPage, &CPU::INC}},
        {0xf6, {0xf6, "INC", 2, 6, AddressMode::ZeroPage_X, &CPU::INC}},
        {0xee, {0xee, "INC", 3, 6, AddressMode::Absolute, &CPU::INC}},
        {0xfe, {0xfe, "INC", 3, 7, AddressMode::Absolute_X, &CPU::INC}},
 
        {0xe8, {0xe8, "INX", 1, 2, AddressMode::NoneAddressing, &CPU::INX}},
        {0xc8, {0xc8, "INY", 1, 2, AddressMode::NoneAddressing, &CPU::INY}},
    
        {0xc6, {0xc6, "DEC", 2, 5, AddressMode::ZeroPage, &CPU::DEC}},
        {0xd6, {0xd6, "DEC", 2, 6, AddressMode::ZeroPage_X, &CPU::DEC}},
        {0xce, {0xce, "DEC", 3, 6, AddressMode::Absolute, &CPU::DEC}},
        {0xde, {0xde, "DEC", 3, 7, AddressMode::Absolute_X, &CPU::DEC}},
 
        {0xca, {0xca, "DEX", 1, 2, AddressMode::NoneAddressing, &CPU::DEX}},
        {0x88, {0x88, "DEY", 1, 2, AddressMode::NoneAddressing, &CPU::DEY}},

        {0xc9, {0xc9, "CMP", 2, 2, AddressMode::Immediate, &CPU::CMP}},
        {0xc5, {0xc5, "CMP", 2, 3, AddressMode::ZeroPage, &CPU::CMP}},
        {0xd5, {0xd5, "CMP", 2, 4, AddressMode::ZeroPage_X, &CPU::CMP}},
        {0xcd, {0xcd, "CMP", 3, 4, AddressMode::Absolute, &CPU::CMP}},
        {0xdd, {0xdd, "CMP", 3, 4/*+1 if page crossed*/, AddressMode::Absolute_X, &CPU::CMP}},
        {0xd9, {0xd9, "CMP", 3, 4/*+1 if page crossed*/, AddressMode::Absolute_Y, &CPU::CMP}},
        {0xc1, {0xc1, "CMP", 2, 6, AddressMode::Indirect_X, &CPU::CMP}},
        {0xd1, {0xd1, "CMP", 2, 5/*+1 if page crossed*/, AddressMode::Indirect_Y, &CPU::CMP}},

        {0xc0, {0xc0, "CPY", 2, 2, AddressMode::Immediate, &CPU::CPY}},
        {0xc4, {0xc4, "CPY", 2, 3, AddressMode::ZeroPage, &CPU::CPY}},
        {0xcc, {0xcc, "CPY", 3, 4, AddressMode::Absolute, &CPU::CPY}},

        {0xe0, {0xe0, "CPX", 2, 2, AddressMode::Immediate, &CPU::CPX}},
        {0xe4, {0xe4, "CPX", 2, 3, AddressMode::ZeroPage, &CPU::CPX}},
        {0xec, {0xec, "CPX", 3, 4, AddressMode::Absolute, &CPU::CPX}},
 
 
        /*  Branching */
        {0x4c, {0x4c, "JMP", 3, 3, AddressMode::NoneAddressing, &CPU::JMP}}, //AddressMode that acts as Immidiate
        {0x6c, {0x6c, "JMP", 3, 5, AddressMode::NoneAddressing, &CPU::JMPI}}, //AddressMode:Indirect with 6502 bug
 
        {0x20, {0x20, "JSR", 3, 6, AddressMode::NoneAddressing, &CPU::JSR}},
        {0x60, {0x60, "RTS", 1, 6, AddressMode::NoneAddressing, &CPU::RTS}},

        {0x40, {0x40, "RTI", 1, 6, AddressMode::NoneAddressing, &CPU::RTI}},
 
        {0xd0, {0xd0, "BNE", 2, 2 /*(+1 if branch succeeds +2 if to a new page}*/, AddressMode::NoneAddressing, &CPU::BNE}},
        {0x70, {0x70, "BVS", 2, 2 /*(+1 if branch succeeds +2 if to a new page}*/, AddressMode::NoneAddressing, &CPU::BVS}},
        {0x50, {0x50, "BVC", 2, 2 /*(+1 if branch succeeds +2 if to a new page}*/, AddressMode::NoneAddressing, &CPU::BVC}},
        {0x30, {0x30, "BMI", 2, 2 /*(+1 if branch succeeds +2 if to a new page}*/, AddressMode::NoneAddressing, &CPU::BMI}},
        {0xf0, {0xf0, "BEQ", 2, 2 /*(+1 if branch succeeds +2 if to a new page}*/, AddressMode::NoneAddressing, &CPU::BEQ}},
        {0xb0, {0xb0, "BCS", 2, 2 /*(+1 if branch succeeds +2 if to a new page}*/, AddressMode::NoneAddressing, &CPU::BCS}},
        {0x90, {0x90, "BCC", 2, 2 /*(+1 if branch succeeds +2 if to a new page}*/, AddressMode::NoneAddressing, &CPU::BCC}},
        {0x10, {0x10, "BPL", 2, 2 /*(+1 if branch succeeds +2 if to a new page}*/, AddressMode::NoneAddressing, &CPU::BPL}},
 
        {0x24, {0x24, "BIT", 2, 3, AddressMode::ZeroPage, &CPU::BIT}},
        {0x2c, {0x2c, "BIT", 3, 4, AddressMode::Absolute, &CPU::BIT}},
 
 
        /*  Stores, Loads */
        {0xa9, {0xa9, "LDA", 2, 2, AddressMode::Immediate, &CPU::LDA}},
        {0xa5, {0xa5, "LDA", 2, 3, AddressMode::ZeroPage, &CPU::LDA}},
        {0xb5, {0xb5, "LDA", 2, 4, AddressMode::ZeroPage_X, &CPU::LDA}},
        {0xad, {0xad, "LDA", 3, 4, AddressMode::Absolute, &CPU::LDA}},
        {0xbd, {0xbd, "LDA", 3, 4/*+1 if page crossed*/, AddressMode::Absolute_X, &CPU::LDA}},
        {0xb9, {0xb9, "LDA", 3, 4/*+1 if page crossed*/, AddressMode::Absolute_Y, &CPU::LDA}},
        {0xa1, {0xa1, "LDA", 2, 6, AddressMode::Indirect_X, &CPU::LDA}},
        {0xb1, {0xb1, "LDA", 2, 5/*+1 if page crossed*/, AddressMode::Indirect_Y, &CPU::LDA}},
 
        {0xa2, {0xa2, "LDX", 2, 2, AddressMode::Immediate, &CPU::LDX}},
        {0xa6, {0xa6, "LDX", 2, 3, AddressMode::ZeroPage, &CPU::LDX}},
        {0xb6, {0xb6, "LDX", 2, 4, AddressMode::ZeroPage_Y, &CPU::LDX}},
        {0xae, {0xae, "LDX", 3, 4, AddressMode::Absolute, &CPU::LDX}},
        {0xbe, {0xbe, "LDX", 3, 4/*+1 if page crossed*/, AddressMode::Absolute_Y, &CPU::LDX}},
 
        {0xa0, {0xa0, "LDY", 2, 2, AddressMode::Immediate, &CPU::LDY}},
        {0xa4, {0xa4, "LDY", 2, 3, AddressMode::ZeroPage, &CPU::LDY}},
        {0xb4, {0xb4, "LDY", 2, 4, AddressMode::ZeroPage_X, &CPU::LDY}},
        {0xac, {0xac, "LDY", 3, 4, AddressMode::Absolute, &CPU::LDY}},
        {0xbc, {0xbc, "LDY", 3, 4/*+1 if page crossed*/, AddressMode::Absolute_X, &CPU::LDY}},
 
 
        {0x85, {0x85, "STA", 2, 3, AddressMode::ZeroPage, &CPU::STA}},
        {0x95, {0x95, "STA", 2, 4, AddressMode::ZeroPage_X, &CPU::STA}},
        {0x8d, {0x8d, "STA", 3, 4, AddressMode::Absolute, &CPU::STA}},
        {0x9d, {0x9d, "STA", 3, 5, AddressMode::Absolute_X, &CPU::STA}},
        {0x99, {0x99, "STA", 3, 5, AddressMode::Absolute_Y, &CPU::STA}},
        {0x81, {0x81, "STA", 2, 6, AddressMode::Indirect_X, &CPU::STA}},
        {0x91, {0x91, "STA", 2, 6, AddressMode::Indirect_Y, &CPU::STA}},
 
        {0x86, {0x86, "STX", 2, 3, AddressMode::ZeroPage, &CPU::STX}},
        {0x96, {0x96, "STX", 2, 4, AddressMode::ZeroPage_Y, &CPU::STX}},
        {0x8e, {0x8e, "STX", 3, 4, AddressMode::Absolute, &CPU::STX}},
 
        {0x84, {0x84, "STY", 2, 3, AddressMode::ZeroPage, &CPU::STY}},
        {0x94, {0x94, "STY", 2, 4, AddressMode::ZeroPage_X, &CPU::STY}},
        {0x8c, {0x8c, "STY", 3, 4, AddressMode::Absolute, &CPU::STY}},
 
 
        /*  Flags clear */
        {0xd8, {0xd8, "CLD", 1, 2, AddressMode::NoneAddressing, &CPU::CLD}},
        {0x58, {0x58, "CLI", 1, 2, AddressMode::NoneAddressing, &CPU::CLI}},
        {0xb8, {0xb8, "CLV", 1, 2, AddressMode::NoneAddressing, &CPU::CLV}},
        {0x18, {0x18, "CLC", 1, 2, AddressMode::NoneAddressing, &CPU::CLC}},
        {0x38, {0x38, "SEC", 1, 2, AddressMode::NoneAddressing, &CPU::SEC}},
        {0x78, {0x78, "SEI", 1, 2, AddressMode::NoneAddressing, &CPU::SEI}},
        {0xf8, {0xf8, "SED", 1, 2, AddressMode::NoneAddressing, &CPU::SED}},
 
        {0xaa, {0xaa, "TAX", 1, 2, AddressMode::NoneAddressing, &CPU::TAX}},
        {0xa8, {0xa8, "TAY", 1, 2, AddressMode::NoneAddressing, &CPU::TAY}},
        {0xba, {0xba, "TSX", 1, 2, AddressMode::NoneAddressing, &CPU::TSX}},
        {0x8a, {0x8a, "TXA", 1, 2, AddressMode::NoneAddressing, &CPU::TXA}},
        {0x9a, {0x9a, "TXS", 1, 2, AddressMode::NoneAddressing, &CPU::TXS}},
        {0x98, {0x98, "TYA", 1, 2, AddressMode::NoneAddressing, &CPU::TYA}},
 
        /*  Stack */
        {0x48, {0x48, "PHA", 1, 3, AddressMode::NoneAddressing, &CPU::PHA}},
        {0x68, {0x68, "PLA", 1, 4, AddressMode::NoneAddressing, &CPU::PLP}},
        {0x08, {0x08, "PHP", 1, 3, AddressMode::NoneAddressing, &CPU::PHP}},
        {0x28, {0x28, "PLP", 1, 4, AddressMode::NoneAddressing, &CPU::PLP}}
    };
}

void CPU::reset() {
    reg_a = reg_x = reg_y = 0;
    flag_i = true;
    flag_c = flag_d = flag_n = flag_v = false;
    pc = bus.read_16(PC_RESET);
    sp = STACK_RESET; 
}

uint16_t CPU::get_address(AddressMode mode) {
    switch (mode){
    case Accumulator:
        return (uint16_t)reg_a;
        break;
    case Immediate:
        return pc;
        break;
    case ZeroPage:
        return bus.read(pc);
        break;
    case ZeroPage_X:
        return (reg_x + bus.read(pc)) & 0xFF;
        break;
    case ZeroPage_Y:
        return (reg_y + bus.read(pc)) & 0xFF;
        break;
    case Absolute:
        return bus.read_16(pc);
        break;
    case Absolute_X:
        return reg_x + bus.read_16(pc);
        break;
    case Absolute_Y:
        return reg_y + bus.read_16(pc);
        break;
    case Indirect_X:
        {
            uint8_t zero_page_addr = reg_x + bus.read(pc);
            uint16_t lsb = (uint16_t)bus.read((zero_page_addr) & 0xFF);
            uint16_t msb = (uint16_t)bus.read((zero_page_addr + 1) & 0xFF);
            return (msb << 8) | lsb;
        }
        break;
    case Indirect_Y:
        {
            uint8_t zero_page_addr = bus.read(pc);
            uint16_t lsb = (uint16_t)bus.read((zero_page_addr) & 0xFF);
            uint16_t msb = (uint16_t)bus.read((zero_page_addr + 1) & 0xFF);
            return (reg_y + ((msb << 8) | lsb)) & 0xFF;
        }
        break;
    case NoneAddressing:
        std::cout << "Unsupported Memory Addressing Mode\n";
        exit(-1);
        break;
    default:
        break;
    }
}

bool CPU::is_page_crossed(uint16_t start, uint16_t end) {
    return (start & 0xff00) == (end & 0xff00);
}

void CPU::push_stack(uint8_t data) {
    bus.write(STACK_START | sp--, data);
}

uint8_t CPU::pop_stack() {
    return bus.read(STACK_START | sp++);
}

void CPU::push_stack16(uint16_t data) {
    bus.write_16(STACK_START | sp--, data);
}

uint16_t CPU::pop_stack16() {
    return bus.read_16(STACK_START | sp++);
}

void CPU::interrupt_handler(Interrupt type) {
    push_stack16(pc);
    uint8_t flags = flag_n << 7 |
                    flag_v << 6 |
                        1 << 5  |
            (type == BRK_) << 4  |
                    flag_d << 3 |
                    flag_i << 2 |
                    flag_z << 1 |
                    flag_c;
    push_stack(flags);
    flag_i = true;

    switch (type)  {
    case IRQ_:
    case BRK_:
        pc = bus.read_16(BRK_IRQ_Handler);
        break;
    case NMI_:
        pc = bus.read_16(NMI_Handler);
    default:
        break;
    }
}

void CPU::step() {

    //TODO: update cycle counts for bus


    uint8_t instruction = bus.read(pc++);
    if (opcode_matrix.find(instruction) == opcode_matrix.end()) {
        std::cout << "Unsupported Operation\n";
        exit(-1);
    }

    Opcode opcode = opcode_matrix[instruction];

    if ( (opcode.mode == AddressMode::Indirect_Y || opcode.mode == AddressMode::Absolute_X || opcode.mode == AddressMode::Absolute_Y ) && opcode.name != "STA") {
        extra_cycles = 1;
    }
    cycle_count = opcode_matrix[instruction].cycles + extra_cycles;

    pc += opcode_matrix[instruction].len - 1;

}


//Loads
void CPU::LDA(AddressMode mode) {
    uint16_t address = get_address(mode);
    reg_a = bus.read(address);
    
    flag_z = !reg_a;
    flag_n = reg_a & 0x80;
}

void CPU::LDX(AddressMode mode) {
    uint16_t address = get_address(mode);
    reg_x = bus.read(address);
    
    flag_z = !reg_x;
    flag_n = reg_x & 0x80;
}

void CPU::LDY(AddressMode mode) {
    uint16_t address = get_address(mode);
    reg_y = bus.read(address);
    
    flag_z = !reg_y;
    flag_n = reg_y & 0x80;
}


//Stores
void CPU::STA(AddressMode mode) {
    uint16_t address = get_address(mode);
    bus.write(address, reg_y);
}

void CPU::STX(AddressMode mode) {
    uint16_t address = get_address(mode);
    bus.write(address, reg_x);
}

void CPU::STY(AddressMode mode) {
    uint16_t address = get_address(mode);
    bus.write(address, reg_x);
}


//Transfer
void CPU::TAX(AddressMode mode) {
    reg_x = reg_a;
    
    flag_z = !reg_x;
    flag_n = reg_x & 0x80;
}

void CPU::TAY(AddressMode mode) {
    reg_y = reg_a;
    
    flag_z = !reg_y;
    flag_n = reg_y & 0x80;
}

void CPU::TXA(AddressMode mode) {
    reg_a = reg_x;
    
    flag_z = !reg_a;
    flag_n = reg_a & 0x80;
}

void CPU::TYA(AddressMode mode) {
    reg_a = reg_y;
    
    flag_z = !reg_y;
    flag_n = reg_y & 0x80;
}


//Stack    
void CPU::TSX(AddressMode mode) {
    reg_x = sp;

    flag_z = !reg_x;
    flag_n = reg_x & 0x80;
}

void CPU::TXS(AddressMode mode) {
    sp = reg_x;
}

void CPU::PHA(AddressMode mode) {
    push_stack(reg_a);
}

void CPU::PHP(AddressMode mode) {
    uint8_t flags = flag_n << 7 |
                    flag_v << 6 |
                        1 << 5  |
                        1 << 4  |
                    flag_d << 3 |
                    flag_i << 2 |
                    flag_z << 1 |
                    flag_c;
    push_stack(flags);
}

void CPU::PLA(AddressMode mode) {
    reg_a = pop_stack();

    flag_z = !reg_a;
    flag_n = reg_a & 0x80;
}

void CPU::PLP(AddressMode mode) {
    uint8_t flags = pop_stack();
        flag_n = flags & 0x80;
        flag_v = flags & 0x40;
        flag_d = flags & 0x8;
        flag_i = flags & 0x4;
        flag_z = flags & 0x2;
        flag_c = flags & 0x1;
}


//Logical  
void CPU::AND(AddressMode mode) {
    uint16_t address = get_address(mode);

    reg_a &= bus.read(address);

    flag_z = !reg_a;
    flag_n = reg_a & 0x80;
}

void CPU::EOR(AddressMode mode) {
    uint16_t address = get_address(mode);

    reg_a ^= bus.read(address);

    flag_z = !reg_a;
    flag_n = reg_a & 0x80;
}

void CPU::ORA(AddressMode mode) {
    uint16_t address = get_address(mode);

    reg_a |= bus.read(address);

    flag_z = !reg_a;
    flag_n = reg_a & 0x80;
}

void CPU::BIT(AddressMode mode) {
    uint16_t address = get_address(mode);
    uint8_t data = bus.read(address);

    flag_z = !(reg_a & data);
    flag_v = data & 0x40;
    flag_n = data & 0x80;
}


//Arithmetic
void CPU::ADC(AddressMode mode) {
    uint16_t address = get_address(mode);
    uint8_t data = bus.read(address);

    uint16_t sum = reg_a + data + flag_c;

    flag_c = sum > 0xFF;
    flag_v = ~(reg_a ^ data) & (reg_a ^ sum) & 0x80;
    flag_z = !sum;
    flag_n = sum & 0x80;

    reg_a = (uint8_t) sum;
}

void CPU::SBC(AddressMode mode) {
    uint16_t address = get_address(mode);
    uint8_t data = bus.read(address);

    uint16_t diff = reg_a - data - !flag_c;

    flag_c = !(diff > 0xFF);
    flag_v = ~(reg_a ^ ~data) & (reg_a ^ diff) & 0x80;
    flag_z = !diff;
    flag_n = diff & 0x80;

    reg_a = (uint8_t) diff;
}

void CPU::CMP(AddressMode mode) {
    uint16_t address = get_address(mode);
    uint8_t data = bus.read(address);
    
    uint16_t diff = reg_a - data;
    flag_c = diff >= 0xFF;
    flag_z = !diff;
    flag_n = diff & 0x80;
}

void CPU::CPX(AddressMode mode) {
    uint16_t address = get_address(mode);
    uint8_t data = bus.read(address);
    
    uint16_t diff = reg_x - data;
    flag_c = diff >= 0xFF;
    flag_z = !diff;
    flag_n = diff & 0x80;
}
void CPU::CPY(AddressMode mode) {
    uint16_t address = get_address(mode);
    uint8_t data = bus.read(address);
    
    uint16_t diff = reg_y - data;
    flag_c = diff >= 0xFF;
    flag_z = !diff;
    flag_n = diff & 0x80;    
}


//Increments  Decrements   
void CPU::INC(AddressMode mode) {
    uint16_t address = get_address(mode);
    
    uint8_t data = bus.read(address) + 1;
    bus.write(address, data);

    flag_z = !data;
    flag_n = data & 0x80;
}

void CPU::INX(AddressMode mode) {
    reg_x +=1;

    flag_z = !reg_x;
    flag_n = reg_x & 0x80;
}

void CPU::INY(AddressMode mode) {
    reg_y +=1;

    flag_z = !reg_y;
    flag_n = reg_y & 0x80;
}

void CPU::DEC(AddressMode mode) {
    uint16_t address = get_address(mode);
    
    uint8_t data = bus.read(address) - 1;
    bus.write(address, data);

    flag_z = !data;
    flag_n = data & 0x80;
}

void CPU::DEX(AddressMode mode) {
    reg_x -=1;

    flag_z = !reg_x;
    flag_n = reg_x & 0x80;
}

void CPU::DEY(AddressMode mode) {
    reg_y -=1;

    flag_z = !reg_y;
    flag_n = reg_y & 0x80;

}


//Bit Shifts
void CPU::ASL(AddressMode mode) {
    if(mode == AddressMode::Accumulator) {
        
        flag_c = reg_a & 0x80;

        reg_a <<= 1;

        flag_z = !reg_a;
        flag_n = reg_a & 0x80;

    }
    else {
        uint16_t address = get_address(mode);
        uint8_t data = bus.read(address);
       
        flag_c = data & 0x80;
        
        data <<= 1;

        flag_z = !data;
        flag_n = data & 0x80;
        bus.write(address, data);
    }
}

void CPU::LSR(AddressMode mode) {
    if(mode == AddressMode::Accumulator) {
        
        flag_c = reg_a & 1;

        reg_a >>= 1;

        flag_z = !reg_a;
        flag_n = reg_a & 0x80;

    }
    else {
        uint16_t address = get_address(mode);
        uint8_t data = bus.read(address);
       
        flag_c = data & 1;
        
        data <<= 1;

        flag_z = !data;
        flag_n = data & 0x80;
        bus.write(address, data);
    }
}

void CPU::ROL(AddressMode mode) {
    if(mode == AddressMode::Accumulator) {
        
        bool prev_carry_flag = flag_c;

        flag_c = reg_a & 0x80;


        reg_a = (reg_a << 1) | prev_carry_flag;

        flag_z = !reg_a;
        flag_n = reg_a & 0x80;

    }
    else {
        uint16_t address = get_address(mode);
        uint8_t data = bus.read(address);
       
        bool prev_carry_flag = flag_c;
        flag_c = data & 0x80;
        
        data = (data << 1) | prev_carry_flag;

        flag_z = !data;
        flag_n = data & 0x80;
        bus.write(address, data);
    }
}

void CPU::ROR(AddressMode mode) {
    if(mode == AddressMode::Accumulator) {
        
        bool prev_carry_flag = flag_c;
        flag_c = reg_a & 1;

        reg_a = (reg_a >> 1) | prev_carry_flag << 7;

        flag_z = !reg_a;
        flag_n = reg_a & 0x80;

    }
    else {
        uint16_t address = get_address(mode);
        uint8_t data = bus.read(address);
       
        bool prev_carry_flag = flag_c;
        flag_c = data & 1;
        
        data = (data >> 1) | prev_carry_flag << 7;

        flag_z = !data;
        flag_n = data & 0x80;
        bus.write(address, data);
    }

}


//Jumps  Calls    
void CPU::JMP(AddressMode mode) {
    uint16_t address = get_address(AddressMode::Absolute);
    pc = address;
}

void CPU::JMPI(AddressMode mode) {
    uint16_t address = get_address(AddressMode::Absolute);

    if ((address & 0x00ff) == 0x00ff) {
        uint16_t lo = (uint16_t)bus.read(address);
        uint16_t hi = (uint16_t)bus.read(address & 0xff00);
        address = hi << 8 | lo;
    }
    pc = address;
}

void CPU::JSR(AddressMode mode) {
    push_stack16(pc + 1);
    uint16_t address = get_address(mode);
    pc = address;
    
}
void CPU::RTS(AddressMode mode) {
    pc = pop_stack16() + 1;
}


//Branches  
void CPU::BCC(AddressMode mode) {
    if (!flag_c) {
        uint16_t address = get_address(AddressMode::ZeroPage);
        uint8_t offset = bus.read(address);
        pc = pc + offset;
    }
    else {
        pc++;
    }
}

void CPU::BCS(AddressMode mode) {
    if (flag_c) {
        uint16_t address = get_address(AddressMode::ZeroPage);
        uint8_t offset = bus.read(address);
        pc = pc + offset;
    }
    else {
        pc++;
    }
}

void CPU::BEQ(AddressMode mode) {
    if (flag_z) {
        uint16_t address = get_address(AddressMode::ZeroPage);
        uint8_t offset = bus.read(address);
        pc = pc + offset;
    }
    else {
        pc++;
    }
}

void CPU::BMI(AddressMode mode) {
    if (flag_n) {
        uint16_t address = get_address(AddressMode::ZeroPage);
        uint8_t offset = bus.read(address);
        pc = pc + offset;
    }
    else {
        pc++;
    }
}

void CPU::BNE(AddressMode mode) {
    if (!flag_z) {
        uint16_t address = get_address(AddressMode::ZeroPage);
        uint8_t offset = bus.read(address);
        pc = pc + offset;
    }
    else {
        pc++;
    }
}

void CPU::BPL(AddressMode mode) {
    if (!flag_n) {
        uint16_t address = get_address(AddressMode::ZeroPage);
        uint8_t offset = bus.read(address);
        pc = pc + offset;
    }
    else {
        pc++;
    }
}

void CPU::BVC(AddressMode mode) {
    if (!flag_v) {
        uint16_t address = get_address(AddressMode::ZeroPage);
        uint8_t offset = bus.read(address);
        pc = pc + offset;
    }
    else {
        pc++;
    }
}

void CPU::BVS(AddressMode mode) {
    if (flag_v) {
        uint16_t address = get_address(AddressMode::ZeroPage);
        uint8_t offset = bus.read(address);
        pc = pc + offset;
    }
    else {
        pc++;
    }
}


//Status Flag Changes   
void CPU::CLC(AddressMode mode) {
    flag_c = 0;
}

void CPU::CLD(AddressMode mode) {
    flag_d = 0;
}

void CPU::CLI(AddressMode mode) {
    flag_i = 0;
}

void CPU::CLV(AddressMode mode) {
    flag_v = 0;
}

void CPU::SEC(AddressMode mode) {
    flag_c = 1;
}

void CPU::SED(AddressMode mode) {
    flag_d = 1;
}

void CPU::SEI(AddressMode mode) {
    flag_i = 1;
}


//System Functions   
void CPU::BRK(AddressMode mode) {
    CPU::interrupt_handler(Interrupt::BRK_);
}

void CPU::NOP(AddressMode mode) {}

void CPU::RTI(AddressMode mode) {
    uint8_t flags = pop_stack();

    flag_n = flags & 0x80;
    flag_v = flags & 0x40;
    flag_d = flags & 0x8;
    flag_i = flags & 0x4;
    flag_z = flags & 0x2;
    flag_c = flags & 0x1;

    pc = pop_stack16();
}