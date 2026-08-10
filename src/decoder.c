#include "decoder.h"

static int32_t sign_extend(uint32_t value, unsigned int bits)
{
    uint32_t sign_bit = 1U << (bits - 1U);

    if (value & sign_bit)
    {
        value |= ~((1U << bits) - 1U);
    }

    return (int32_t)value;
}

InstructionFields decode_fields(uint32_t instruction)
{
    InstructionFields fields;

    fields.opcode = EXTRACT_BITS(instruction, 6, 0);
    fields.rd     = EXTRACT_BITS(instruction, 11, 7);
    fields.funct3 = EXTRACT_BITS(instruction, 14, 12);
    fields.rs1    = EXTRACT_BITS(instruction, 19, 15);
    fields.rs2    = EXTRACT_BITS(instruction, 24, 20);
    fields.funct7 = EXTRACT_BITS(instruction, 31, 25);

        if (fields.opcode == 0x23)
    {
        uint32_t immediate =
            (EXTRACT_BITS(instruction, 31, 25) << 5) |
            EXTRACT_BITS(instruction, 11, 7);

        fields.immediate = sign_extend(immediate, 12);
    }
    else
    {
        fields.immediate = sign_extend(
            EXTRACT_BITS(instruction, 31, 20),
            12
        );
    }
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

        case 0x13:
            switch (fields->funct3)
            {
                case 0x0:
                    return INST_ADDI;

                case 0x1:
                    if (fields->funct7 == 0x00)
                    {
                        return INST_SLLI;
                    }

                    break;

                case 0x2:
                    return INST_SLTI;

                case 0x3:
                    return INST_SLTIU;

                case 0x4:
                    return INST_XORI;

                case 0x5:
                    if (fields->funct7 == 0x00)
                    {
                        return INST_SRLI;
                    }

                    if (fields->funct7 == 0x20)
                    {
                        return INST_SRAI;
                    }

                    break;

                case 0x6:
                    return INST_ORI;

                case 0x7:
                    return INST_ANDI;

                default:
                    break;
            }

            break;

        case 0x03:
            switch (fields->funct3)
            {
                case 0x2:
                    return INST_LW;

                default:
                    break;
            }

            break;

        case 0x23:
            switch (fields->funct3)
            {
                case 0x2:
                    return INST_SW;

                default:
                    break;
            }

            break;



        default:
            break;
    }

    return INST_UNKNOWN;
}
