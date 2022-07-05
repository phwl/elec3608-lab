// constants
`define ZERO        32'b0
`define	RESET_ADDR	32'h 0000_0000,
`define NUMREGS     32

// ALU operations
`define ALU_ADD     5'b00001
`define ALU_SUB     5'b00010
`define ALU_SLL     5'b00011
`define ALU_SRL     5'b00100
`define ALU_SRA     5'b00101
`define ALU_SEQ     5'b00110
`define ALU_SLT     5'b00111
`define ALU_SLTU    5'b01000
`define ALU_XOR     5'b01001
`define ALU_OR      5'b01010
`define ALU_AND     5'b01011
`define ALU_MUL     5'b01100
`define ALU_MULH    5'b01101
`define ALU_MULHSU  5'b01110
`define ALU_MULHU   5'b01111
`define ALU_DIV     5'b10000
`define ALU_DIVU    5'b10001
`define ALU_REM     5'b10010
`define ALU_REMU    5'b10011

// OPCODES
`define OPCODE_OP_IMM   7'b00_100_11
`define OPCODE_OP       7'b01_100_11

// 10-bit {insn_funct7, insn_funct3} opcodes
`define OPCODE_SLLI 10'b0000000_001 
`define OPCODE_SRLI 10'b0000000_101 
`define OPCODE_SRAI 10'b0100000_101 
