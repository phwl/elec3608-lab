/*
 *  Single cycle RV32 processor supporting R-type and I-type instructions
 *  Parts derived from NERV
 *  Copyright (C) 2022  Philip Leong <philip.leong@sydney.edu.au>

 *  NERV -- Naive Educational RISC-V Processor
 *
 *  Copyright (C) 2020  Claire Xenia Wolf <claire@yosyshq.com>
 *
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

`include "constants.svh"

`default_nettype none

module rv3608a (
    input clock,
    input reset,
    output trap,
    output logic [31:0] return_reg,

    // we have 2 external memories
    // one is instruction memory
    output  [31:0] imem_addr,
    input   [31:0] imem_data
);
    // instruction memory pointer
    assign  imem_addr = pc;
    assign  insn = imem_data;

    // ALU 
	wire   alu_eq_zero;
    wire   [31:0] alu_result;
    wire   alu_eq;
    wire   [31:0] alu_op_a = regfile[insn_rs1];
	wire   [31:0] alu_op_b = insn_opcode == `OPCODE_OP_IMM ? 
                                imm_val : regfile[insn_rs2];

    // instantiate ALU here
	alu alu_1 (
		.alu_function(alu_op),
		.op_a(alu_op_a),
		.op_b(alu_op_b),
		.result(alu_result),
		.result_eq_zero(alu_eq_zero)
	);

    
	// combinational assignment of alu_op
	logic  [4:0] alu_op;
    always_comb begin
		illegalinsn = 0;
		case (insn_opcode)
			0: alu_op = `ALU_ADD;	// NOP

			`OPCODE_OP_IMM: begin
				casez ({insn_funct7, insn_funct3})
					10'b zzzzzzz_000 /* ADDI  */: alu_op = `ALU_ADD;
				endcase
			end
		endcase
	end

    // components of the instruction
    wire [6:0] insn_funct7;
    wire [4:0] insn_rs2;
    wire [4:0] insn_rs1;
    wire [2:0] insn_funct3;
    wire [4:0] insn_rd;
    wire [6:0] insn_opcode;

    // split R-type instruction - see section 2.2 of RiscV spec
    assign {insn_funct7, insn_rs2, insn_rs1, insn_funct3, insn_rd, insn_opcode} = insn;


    // setup for I, S, B & J type instructions
    // I - short immediates and loads
    wire [11:0] imm_i;
    assign imm_i = insn[31:20];
    // sign extended imm_i
    wire [31:0] imm_i_sext = 32'(signed'(imm_i));
    // sign extended short immediate for shifts
    wire [31:0] imm_shift = 32'(signed'({1'b0, insn[24:20]}));
    // use the 5-bit immediate for shifts otherwise the 12-bit one
    wire [31:0] imm_val;
    assign imm_val = 
        ({insn_funct7, insn_funct3} == `OPCODE_SLLI ||
         {insn_funct7, insn_funct3} == `OPCODE_SRLI ||
         {insn_funct7, insn_funct3} == `OPCODE_SRAI)
         ? imm_shift : imm_i_sext; // either a shift or an imm

    // trap is an output to show that execution has halted 
    logic illegalinsn;
    logic trapped;
    assign trap = trapped;

    // registers, instruction reg, program counter, next pc
    logic   [31:0] regfile [0:`NUMREGS-1];
    logic   [31:0] pc;
    wire   [31:0] insn;

    // every cycle
    always_ff @(posedge clock) begin
		if (!trapped && !reset) begin
			if (illegalinsn)
				trapped <= 1;
	
			pc <= pc + 4;
        	regfile[insn_rd] <= alu_result;
            return_reg <= regfile[10];

    	end
        // reset
        if (reset) begin
		    pc <= 0;
           	trapped <= 0;
        end
    end

endmodule
