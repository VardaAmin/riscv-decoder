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

InstructionType decode_instruction(const InstructionFields *fields)
{
    switch (fields->opcode)
    {
        case 0x33:
            switch (fields->funct3)
            {
                case 0x0:
                    if (fields->funct7 == 0x00)
                    {
                        return INST_ADD;
                    }

                    if (fields->funct7 == 0x20)
                    {
                        return INST_SUB;
                    }

                    break;

                case 0x1:
                    if (fields->funct7 == 0x00)
                    {
                        return INST_SLL;
                    }

                    break;

                case 0x2:
                    if (fields->funct7 == 0x00)
                    {
                        return INST_SLT;
                    }

                    break;

                case 0x3:
                    if (fields->funct7 == 0x00)
                    {
                        return INST_SLTU;
                    }

                    break;

                case 0x4:
                    if (fields->funct7 == 0x00)
                    {
                        return INST_XOR;
                    }

                    break;

                case 0x5:
                    if (fields->funct7 == 0x00)
                    {
                        return INST_SRL;
                    }

                    if (fields->funct7 == 0x20)
                    {
                        return INST_SRA;
                    }

                    break;

                case 0x6:
                    if (fields->funct7 == 0x00)
                    {
                        return INST_OR;
                    }

                    break;

                case 0x7:
                    if (fields->funct7 == 0x00)
                    {
                        return INST_AND;
                    }

                    break;

                default:
                    break;
            }

            break;

        default:
            break;
    }

    return INST_UNKNOWN;
}
