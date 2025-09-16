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

module nerv #(
	parameter [31:0] RESET_ADDR = 32'h 0000_0000,
	parameter integer NUMREGS = 32
) (
	input clock,
	input reset,
	output trap,

	// we have 2 external memories
	// one is instruction memory
	output [31:0] imem_addr,
	input  [31:0] imem_data,

	// the other is data memory
	output        dmem_valid,
    output        dmem_wr_is_cond,
	output [31:0] dmem_addr,
	output [ 3:0] dmem_wstrb,
	output [31:0] dmem_wdata,
	input  [31:0] dmem_rdata,

    output dmem_resv,  // reservations
    input  dmem_cond   // conditional    
);
	// registers, instruction reg, program counter, next pc
	logic [31:0] regfile [0:NUMREGS-1];
    
// YOUR CODE HERE
endmodule








/****************************************************************************************/

module multicore_memory #(
    parameter MEM_ADDR_WIDTH = 17,
    parameter string fname, 
    parameter RESV_BITS=12
) (
	input clock,
	input reset,

	
    input  [31:0] imem_addr0,
	output reg [31:0] imem_data0,

	input         dmem_valid0,
    input         dmem_wr_is_cond0,
	input  [31:0] dmem_addr0,
	input  [ 3:0] dmem_wstrb0,
	input  [31:0] dmem_wdata0,
	output [31:0] dmem_rdata0,

    input  [31:0] imem_addr1,
	output reg [31:0] imem_data1,

	input         dmem_valid1,
    input         dmem_wr_is_cond1,
	input  [31:0] dmem_addr1,
	input  [ 3:0] dmem_wstrb1,
	input  [31:0] dmem_wdata1,
	output [31:0] dmem_rdata1,

    input  [1:0] dmem_resv,  // reservations
    output [1:0] dmem_cond   // conditional        
);
    // THE ACTUAL MEMORY
    reg [7:0] mem [0:(1<<MEM_ADDR_WIDTH)-1];

    // YOUR CODE HERE
endmodule