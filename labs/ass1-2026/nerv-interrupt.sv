/*
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
 `default_nettype none
	// CSR numbers per Privileged ISA sec 2.2.4 table 7
	localparam CSR_MSTATUS	= 12'h 300;
	localparam CSR_MIE  	= 12'h 304;
	localparam CSR_MTVEC 	= 12'h 305;
	localparam CSR_MSCRATCH = 12'h 340;
	localparam CSR_MEPC		= 12'h 341;
	localparam CSR_MCAUSE 	= 12'h 342;
	localparam CSR_MIP		= 12'h 344;

module nerv #(
	parameter [31:0] RESET_ADDR = 32'h 0000_0000,
	parameter integer NUMREGS = 32,
	parameter integer MTVEC_ADDR = 32'h 0000_1000 // Interrupt/trap vector address
) (
	input clock,
	input reset,
	output trap,
	input intr,	// interrupt request

	// we have 2 external memories
	// one is instruction memory
	output [31:0] imem_addr,
	input  [31:0] imem_data,

	// the other is data memory
	output        dmem_valid,
	output [31:0] dmem_addr,
	output [ 3:0] dmem_wstrb,
	output [31:0] dmem_wdata,
	input  [31:0] dmem_rdata
);
	// your processor goes here

	// instantiate the CSR file
	csrfile csr_file (
		// add your code here
	);


endmodule


// CSR file.  Slightly different than register file since it's bit addressable
// this skeleton provides bit addressable read & write.
// Some CSRs are marked read-only, some write only, and some read/write
// It's intended that you connect the addr, re, we, wdata and rdata to the
// instruction decoder logic, while the "bits" ports connect to internal "wire" or "logic" signals
module csrfile
(
	input  wire clock,			// clock input
	input  wire reset,			// reset signal
	input  wire [11:0] addr,	// CSR address (CSR ID number)
	input  wire [31:0] re,		// bit-addressable write enable
	input  wire [31:0] we,		// bit-addressable read enable
	output wire [31:0] rdata,	// CSR bits  for read out (use w/ re lines)
	input  wire [31:0] wdata,	// CSR bits for write input (use w/ we lines)

	// raw bits
	input  wire [31:0] ro_mepc_bits,	// actual internal bits of MEPC register
	inout  wire [31:0] rw_mstatus_bits,	// ... etc
	output wire [31:0] rw_mie_bits,
	input  wire [31:0] ro_mtvec_bits,
	input  wire [31:0] ro_mip_bits,
	input  wire [31:0] ro_mcause_bits,
	output wire [31:0] rw_mscratch_bits
);
	// internal flipflops
	// these will hold logic that is for read-write and write only registers
	// the rest of the CSRs are read-only, and so the actual FF is contained
	// inside the processor logic, not here.
	logic [31:0] mie_bits;
	logic [31:0] mscratch_bits;
	logic [31:0] mstatus_bits;
	genvar i;

	// combinational read
	assign rdata = (addr == CSR_MEPC) 		? ro_mepc_bits 		& re :
					(addr == CSR_MSTATUS) 	? rw_mstatus_bits	& re :
					(addr == CSR_MIE) 		? rw_mie_bits 		& re :
					(addr == CSR_MTVEC) 	? ro_mtvec_bits 	& re :
					(addr == CSR_MIP) 		? ro_mip_bits 		& re :
					(addr == CSR_MCAUSE) 	? ro_mcause_bits 	& re:
					(addr == CSR_MSCRATCH) 	? rw_mscratch_bits 	& re:
					31'h x;

	// map the internal FFs into ports that can be used by your processor's controller
	assign rw_mie_bits = mie_bits;
	assign rw_mscratch_bits = mscratch_bits;
	assign rw_mstatus_bits = mstatus_bits;

	// construct  bitwise those CSRs that are read-write
	// the rest not listed here are read-only, and thus controlled
	// outside this module
	generate
		for (i = 0; i<32; i++) begin : gen_write_bits

			always @(posedge clock) begin
				if(reset == 1) begin
					mie_bits[i] <= 0;
					mscratch_bits[i] <= 0;
				end
				else if(addr == CSR_MIE && we[i])
					mie_bits[i] <= wdata[i];
				else if(addr == CSR_MSCRATCH && we[i])
					mscratch_bits[i] <= wdata[i];
				else if(addr == CSR_MSTATUS && we[i])
					mstatus_bits[i] <= wdata[i];
			end
		end: gen_write_bits
	endgenerate


endmodule

