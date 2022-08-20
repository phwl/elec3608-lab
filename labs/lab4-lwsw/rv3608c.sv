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

module rv3608c (
    input clock,
    input reset,
    output trap,
    output logic [31:0] x10,

    // we have 2 external memories
    // one is instruction memory
    output  [31:0] imem_addr,
    input   [31:0] imem_data
);
    // instruction memory pointer
    assign  imem_addr = pc;
    assign  insn = imem_data;

    // data memory
    logic [31:0] dmem [0:1023];
    logic dmem_wr_enable;
    logic [31:0] dmem_wr_addr;
    logic [31:0] dmem_wr_data;
                          
    logic [31:0] dmem_rd_addr;
    logic [31:0] dmem_rd_data;

    // Debugging
    logic   [4:0] d_rd;
    logic   [31:0] d_x0;
    logic   [31:0] d_x1;
    logic   [31:0] d_x2;
    logic   [31:0] d_x3;
    logic   [31:0] d_x4;
    logic   [6:0] d_opcode;

    // trap is an output to show that execution has halted 
    logic illegalinsn;
    logic trapped;
    assign trap = trapped;

    // registers, instruction reg, program counter, next pc
    logic   [31:0] regfile [0:`NUMREGS-1];
    logic   [31:0] pc;
    logic   [31:0] insn;

    // components of the instruction
    logic   [6:0] insn_funct7;
    logic   [4:0] insn_rs2;
    logic   [4:0] insn_rs1;
    logic   [2:0] insn_funct3;
    logic   [4:0] insn_rd;
    logic   [6:0] insn_opcode;

    // split R-type instruction - see section 2.2 of RiscV spec
    assign {insn_funct7, insn_rs2, insn_rs1, insn_funct3, insn_rd, insn_opcode} = insn;

    // setup for I, S, B & J type instructions
    // I - short immediates and loads
    logic   [11:0] imm_i;
    assign  imm_i = insn[31:20];
    // sign extended imm_i
    wire    [31:0] imm_i_sext = { {20{imm_i[11]}}, imm_i };
    // sign extended short immediate for shifts
    wire    [31:0] imm_shift = 32'(signed'({1'b0, insn[24:20]}));
    // use the 5-bit immediate for shifts otherwise the 12-bit one
    logic   [31:0] imm_val;
    assign imm_val = 
        ({insn_funct7, insn_funct3} == `OPCODE_SLLI ||
         {insn_funct7, insn_funct3} == `OPCODE_SRLI ||
         {insn_funct7, insn_funct3} == `OPCODE_SRAI)
         ? imm_shift : imm_i_sext; // either a shift or an imm

	// B - conditionals
	logic   [12:0] imm_b;
	assign {imm_b[12], imm_b[10:5]} = insn_funct7, {imm_b[4:1], imm_b[11]} = insn_rd, imm_b[0] = 1'b0;

	// J - unconditional jumps
	logic   [20:0] imm_j;
	assign  {imm_j[20], imm_j[10:1], imm_j[11], imm_j[19:12], imm_j[0]} = {insn[31:12], 1'b0};

	wire    [31:0] imm_b_sext = 32'(signed'(imm_b));
	wire    [31:0] imm_j_sext = 32'(signed'(imm_j));

    // ALU 
	logic  alu_eq_zero;
    logic  [31:0] alu_result;
    logic  alu_eq;
    wire   [31:0] alu_op_a = regfile[insn_rs1];
	wire   [31:0] alu_op_b = insn_opcode == `OPCODE_OP_IMM ? 
                                imm_val : regfile[insn_rs2];
	logic   [4:0] alu_op;

    // Code below sets alu_op
    always_comb begin
		case (insn_opcode)
			`OPCODE_OP_IMM: begin
				casez ({insn_funct7, insn_funct3})
					10'b zzzzzzz_000 /* ADDI  */: alu_op = `ALU_ADD;
					10'b zzzzzzz_010 /* SLTI  */: alu_op = `ALU_SLT;
					10'b zzzzzzz_011 /* SLTIU */: alu_op = `ALU_SLTU;
					10'b zzzzzzz_100 /* XORI  */: alu_op = `ALU_XOR;
					10'b zzzzzzz_110 /* ORI   */: alu_op = `ALU_OR;
					10'b zzzzzzz_111 /* ANDI  */: alu_op = `ALU_AND;
					10'b 0000000_001 /* SLLI  */: alu_op = `ALU_SLL;
					10'b 0000000_101 /* SRLI  */: alu_op = `ALU_SRL;
					10'b 0100000_101 /* SRAI  */: alu_op = `ALU_SRA;
					default: illegalinsn = 1;
				endcase
			end

			`OPCODE_OP: begin
				casez ({insn_funct7, insn_funct3})
					10'b 0000000_000 /* ADD  */: alu_op = `ALU_ADD;
					10'b 0100000_000 /* SUB  */: alu_op = `ALU_SUB;
					10'b 0000000_001 /* SLL  */: alu_op = `ALU_SLL;
					10'b 0000000_010 /* SLT  */: alu_op = `ALU_SLT;
					10'b 0000000_011 /* SLTU */: alu_op = `ALU_SLTU;
					10'b 0000000_100 /* XOR  */: alu_op = `ALU_XOR;
					10'b 0000000_101 /* SRL  */: alu_op = `ALU_SRL;
					10'b 0100000_101 /* SRA  */: alu_op = `ALU_SRA;
					10'b 0000000_110 /* OR   */: alu_op = `ALU_OR;
					10'b 0000000_111 /* AND  */: alu_op = `ALU_AND;
					default: illegalinsn = 1;
				endcase
            end

            `OPCODE_BRANCH: begin
				case (insn_funct3)
                    // LAB need to map branches to ALU operations here
					3'b 000 /* BEQ  */: alu_op = `ALU_SUB;
                endcase
            end

			default: illegalinsn = 1;
        endcase
    end

    // instantiate ALU
	alu alu_1 (
		.alu_function(alu_op),
		.op_a(alu_op_a),
		.op_b(alu_op_b),
		.result(alu_result),
		.result_eq_zero(alu_eq_zero)
	);

	// combinational assignment of control signals
    logic   regwrite;
    logic   [31:0] npc;
    logic   [31:0] rfilewdata;

	// control signals for CPU
    always_comb begin
		illegalinsn = 0;
		regwrite = 0;
		npc = pc + 4;
        rfilewdata = alu_result;
		case (insn_opcode)
			0: alu_op = `ALU_ADD;	// NOP

			`OPCODE_OP_IMM: begin
                regwrite = 1;
			end

			`OPCODE_OP: begin
                regwrite = 1;
			end

            `OPCODE_JAL: begin
                // LAB implement JAL control signals here
            end

            `OPCODE_JALR: begin
                // LAB implement JALR control signals here
            end

			// branch instructions: Branch If Equal, Branch Not Equal, Branch Less Than, Branch Greater Than, Branch Less Than Unsigned, Branch Greater Than Unsigned
		    `OPCODE_BRANCH: begin
                case (insn_funct3)
                    // handle different branch types here
					3'b 000 /* BEQ  */: begin if (alu_eq_zero) npc = pc + imm_b_sext; end
                    // LAB implement missing branch types
					default: illegalinsn = 1;
				endcase
			end

            `OPCODE_LOAD: begin
                // LAB implement LW here
		        $display("lw from 0x%08x = 0x%08x", dmem_rd_addr, dmem_rd_data);
            end

            `OPCODE_STORE: begin
                // LAB implement SW here
		        $display("sw 0x%08x to = 0x%08x", rs2_value, dmem_wr_addr);
            end

			default: illegalinsn = 1;
		endcase
        // check that branches etc weren't to an unaligned address
		if ((npc & 32'b11) != 0) begin
			illegalinsn = 1;
			npc = pc & ~32'b 11;
		end
	end

    // every cycle
    always_ff @(posedge clock) begin
		if (!trapped && !reset) begin
			if (illegalinsn)
				trapped <= 1;
	
        pc <= npc;
        if (regwrite && insn_rd > 0) 
            regfile[insn_rd] <= rfilewdata;
            x10 <= regfile[10];
    	end

        // LAB update the data memory here
        
        // reset
        if (reset) begin
		    pc <= 0;
           	trapped <= 0;
        end

        // debugging signals, note these are updated with 1 cycle delay
        d_x0 = regfile[0];
        d_x1 = regfile[1];
        d_x2 = regfile[2];
        d_x3 = regfile[3];
        d_x4 = regfile[4];
        d_rd = insn_rd;
        d_opcode <= insn_opcode;

    end

endmodule
