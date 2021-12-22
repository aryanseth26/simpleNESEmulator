#include <cstdint>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

#include "../include/Bus.h"

enum AddressMode {
    Accumulator,
    Immediate,
    ZeroPage,
    ZeroPage_X,
    ZeroPage_Y,
    Absolute,
    Absolute_X,
    Absolute_Y,
    Indirect_X,
    Indirect_Y,
    NoneAddressing
};

enum Interrupt {
    NMI_,
    RESET_,
    BRK_,
    IRQ_
};


class CPU {
private:

    struct Opcode {
        uint8_t code;
        std::string name;
        uint8_t len;
        uint8_t cycles;
        AddressMode mode;
        void (CPU::*operation)(AddressMode);
    };

    std::unordered_map<uint8_t, Opcode> opcode_matrix;
    
    //Reset Locations
    const uint16_t STACK_START = 0x100;
    const uint8_t STACK_RESET = 0xFD; //See https://www.pagetable.com/?p=410 for explanation
    const uint16_t PC_RESET = 0xFFCD;
    
    //Interrupt Vector Locations
    const uint16_t BRK_IRQ_Handler = 0xFFFE;
    const uint16_t NMI_Handler = 0xFFFA;

    //Timing
    int cycle_count;
    int extra_cycles;

    //Registers
    uint16_t pc;
    uint8_t sp;
    uint8_t reg_a;
    uint8_t reg_x;
    uint8_t reg_y;
    
    //Flags
    bool flag_c;
    bool flag_z;
    bool flag_i;
    bool flag_b;
    bool flag_d;
    bool flag_v;
    bool flag_n;
    
    Bus &bus;

public:
    CPU(Bus &bus_in);
    
    void reset();
    void step();

    uint16_t get_address(AddressMode mode);
    void push_stack(uint8_t data);
    uint8_t pop_stack();

    void push_stack16(uint16_t data);
    uint16_t pop_stack16();

    bool is_page_crossed(uint16_t start, uint16_t end);

    void interrupt_handler(Interrupt type);
    //Loads
    void LDA(AddressMode mode);
    void LDX(AddressMode mode);
    void LDY(AddressMode mode);
    
    //Stores
    void STA(AddressMode mode);
    void STX(AddressMode mode);
    void STY(AddressMode mode);

    //Transfer
    void TAX(AddressMode mode);
    void TAY(AddressMode mode);
    void TXA(AddressMode mode);
    void TYA(AddressMode mode);

    //Stack
    void TSX(AddressMode mode);
    void TXS(AddressMode mode);
    void PHA(AddressMode mode);
    void PHP(AddressMode mode);
    void PLA(AddressMode mode);
    void PLP(AddressMode mode);

    //Logical
    void AND(AddressMode mode);
    void EOR(AddressMode mode);
    void ORA(AddressMode mode);
    void BIT(AddressMode mode);

    //Arithmetic
    void ADC(AddressMode mode);
    void SBC(AddressMode mode);
    void CMP(AddressMode mode);
    void CPX(AddressMode mode);
    void CPY(AddressMode mode);

    //Increments  Decrements
    void INC(AddressMode mode);
    void INX(AddressMode mode);
    void INY(AddressMode mode);
    void DEC(AddressMode mode);
    void DEX(AddressMode mode);
    void DEY(AddressMode mode);

    //Bit Shifts
    void ASL(AddressMode mode);
    void LSR(AddressMode mode);
    void ROL(AddressMode mode);
    void ROR(AddressMode mode);

    //Jumps  Calls
    void JMP(AddressMode mode);
    void JMPI(AddressMode mode);
    void JSR(AddressMode mode);
    void RTS(AddressMode mode);

    //Branches
    void BCC(AddressMode mode);
    void BCS(AddressMode mode);
    void BEQ(AddressMode mode);
    void BMI(AddressMode mode);
    void BNE(AddressMode mode);
    void BPL(AddressMode mode);
    void BVC(AddressMode mode);
    void BVS(AddressMode mode);

    //Status Flag Changes
    void CLC(AddressMode mode);
    void CLD(AddressMode mode);
    void CLI(AddressMode mode);
    void CLV(AddressMode mode);
    void SEC(AddressMode mode);
    void SED(AddressMode mode);
    void SEI(AddressMode mode);

    //System Functions
    void BRK(AddressMode mode);
    void NOP(AddressMode mode);
    void RTI(AddressMode mode);


};