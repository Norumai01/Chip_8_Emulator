#ifndef CHIP_8_H
#define CHIP_8_H

#include <cstdint>

class Chip_8 {
private:
    uint8_t memory[4096];
    uint8_t V[16]; // General Purpose Register

    uint16_t pc; // Program Counter
    uint16_t I; // Index Register
    uint16_t stack; // Stack

    uint8_t delay_timer;
    uint8_t sound_timer;

};

#endif