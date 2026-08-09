#include "decoder.h"

InstructionFields decode_fields(uint32_t instruction)
{
    InstructionFields fields;

    fields.opcode = EXTRACT_BITS(instruction, 6, 0);
    fields.rd     = EXTRACT_BITS(instruction, 11, 7);
    fields.funct3 = EXTRACT_BITS(instruction, 14, 12);
    fields.rs1    = EXTRACT_BITS(instruction, 19, 15);
    fields.rs2    = EXTRACT_BITS(instruction, 24, 20);
    fields.funct7 = EXTRACT_BITS(instruction, 31, 25);

    fields.immediate = 0;

    return fields;
}
