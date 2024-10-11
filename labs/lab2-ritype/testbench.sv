/*
 *  NERV -- Naive Educational RISC-V Processor
 *
 *  Copyright (C) 2020  N. Engelhardt <nak@yosyshq.com>
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

module testbench(clock, reset);

localparam MEM_ADDR_WIDTH = 16;

input logic clock;
input logic reset;
wire trap;

wire [31:0] imem_addr;
logic  [31:0] imem_data;
logic  [31:0] return_reg;

logic [7:0] mem [0:(1<<MEM_ADDR_WIDTH)-1];

logic [31:0] out;
logic out_valid;
always @(posedge clock) begin
	if (out_valid) begin
		$write("%c", out[7:0]);
`ifndef VERILATOR
		$fflush();
`endif
	end
end

always @(posedge clock) begin
	if (imem_addr >= (1<<MEM_ADDR_WIDTH)) begin
		$display("Memory access out of range: imem_addr = 0x%08x", imem_addr);
	end
end

always_comb begin
        out = 32'h 0;
        out_valid = 1'b0;
        imem_data = {
                mem[{imem_addr[MEM_ADDR_WIDTH-1:2], 2'b11}],
                mem[{imem_addr[MEM_ADDR_WIDTH-1:2], 2'b10}],
                mem[{imem_addr[MEM_ADDR_WIDTH-1:2], 2'b01}],
                mem[{imem_addr[MEM_ADDR_WIDTH-1:2], 2'b00}]
        };
end

initial begin
	$readmemh("firmware.hex", mem);
end

rv3608a dut (
	.clock(clock),
	.reset(reset),
	.trap(trap),
    .return_reg(return_reg),

	.imem_addr(imem_addr),
	.imem_data(imem_data)
);

logic [31:0] cycles = 0;

always @(posedge clock) begin
	cycles <= cycles + 32'h1;
	if (trap) begin
		$display("Simulated %0d cycles", cycles);
		$finish;
	end
end



endmodule
