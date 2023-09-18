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

input reg clock;
input reg reset;
wire trap;

reg [31:0] x10;

wire [31:0] imem_addr;
reg  [31:0] imem_data;

wire        dmem_valid;
wire [31:0] dmem_addr;
wire [ 3:0] dmem_wstrb;
wire [31:0] dmem_wdata;
reg  [31:0] dmem_rdata;

reg [7:0] mem [0:(1<<MEM_ADDR_WIDTH)-1];

wire wr_in_mem_range = (dmem_addr[31:2] < (1<<MEM_ADDR_WIDTH));
wire wr_in_output = (dmem_addr == 32'h 02000000);

reg [31:0] out;
reg out_valid;
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
	if (dmem_valid && !(wr_in_mem_range || wr_in_output)) begin
		$display("Memory access out of range: dmem_addr = 0x%08x", dmem_addr);
	end
end

integer i;
always @(posedge clock) begin
	out <= 32'h 0;
	out_valid <= 1'b0;
	imem_data <= {
		mem[{imem_addr[MEM_ADDR_WIDTH-1:2], 2'b11}],
		mem[{imem_addr[MEM_ADDR_WIDTH-1:2], 2'b10}],
		mem[{imem_addr[MEM_ADDR_WIDTH-1:2], 2'b01}],
		mem[{imem_addr[MEM_ADDR_WIDTH-1:2], 2'b00}]
	};
	if (!reset) begin

		if (dmem_valid) begin
			dmem_rdata <= {
				mem[{dmem_addr[MEM_ADDR_WIDTH-1:2], 2'b11}],
				mem[{dmem_addr[MEM_ADDR_WIDTH-1:2], 2'b10}],
				mem[{dmem_addr[MEM_ADDR_WIDTH-1:2], 2'b01}],
				mem[{dmem_addr[MEM_ADDR_WIDTH-1:2], 2'b00}]
			};
			for (i=0;i<4;i=i+1) begin
				if (dmem_wstrb[i]) begin
					if (wr_in_mem_range) begin
						mem[{dmem_addr[MEM_ADDR_WIDTH-1:2], i[1:0]}] <= dmem_wdata[(i*8)+: 8];
					end
					if (wr_in_output) begin
						out[(i*8)+: 8] <= dmem_wdata[(i*8)+: 8];
						out_valid <= 1'b1;
					end
					dmem_rdata <= 'hx;
				end
			end
		end else begin
			dmem_rdata <= 32'h XXXX_XXXX;
		end
	end
end

initial begin
	$readmemh("firmware.hex", mem);
end

nerv dut (
	.clock(clock),
	.reset(reset),
	.trap(trap),
	.x10(x10),

	.imem_addr(imem_addr),
	.imem_data(imem_data),

	.dmem_valid(dmem_valid),
	.dmem_addr(dmem_addr),
	.dmem_wstrb(dmem_wstrb),
	.dmem_wdata(dmem_wdata),
	.dmem_rdata(dmem_rdata)
);

reg [31:0] cycles = 0;

always @(posedge clock) begin
	cycles <= cycles + 32'h1;
	if (trap) begin
		$display("Simulated %0d cycles", cycles);
		$finish;
	end
end



endmodule
