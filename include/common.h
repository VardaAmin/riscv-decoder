#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stddef.h>

#define INSTRUCTION_SIZE 4U
#define REGISTER_COUNT 32U
#define OPCODE_MASK 0x7FU
#define REGISTER_MASK 0x1FU

#define EXTRACT_BITS(value, high, low) \
    (((value) >> (low)) & ((1U << ((high) - (low) + 1U)) - 1U))

#endif
