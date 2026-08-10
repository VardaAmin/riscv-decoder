#ifndef DECODER_H
#define DECODER_H

#include "common.h"

typedef struct {
    uint32_t opcode;
    uint32_t rd;
    uint32_t rs1;
    uint32_t rs2;
    uint32_t funct3;
    uint32_t funct7;
    int32_t immediate;
} InstructionFields;

typedef enum {
    INST_UNKNOWN,
    INST_ADD,
    INST_SUB,
    INST_AND,
    INST_OR,
    INST_XOR,
    INST_SLT,
    INST_SLTU,
    INST_SLL,
    INST_SRL,
    INST_SRA,
    INST_ADDI,
    INST_ANDI,
    INST_ORI,
    INST_XORI,
    INST_SLTI,
    INST_SLTIU,
    INST_SLLI,
    INST_SRLI,
    INST_SRAI,
    INST_LW,
    INST_SW,
    INST_BEQ,
    INST_BNE,
    INST_LUI,
    INST_AUIPC,
    INST_JAL,
    INST_JALR
} InstructionType;

InstructionFields decode_fields(uint32_t instruction);

InstructionType decode_instruction(const InstructionFields *fields);


#endif
