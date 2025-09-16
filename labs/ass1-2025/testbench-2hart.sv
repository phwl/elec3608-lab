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

module testbench
    #(     parameter string firmwarefile
    ) (
        clock, 
        reset
    );

localparam MEM_ADDR_WIDTH = 16;
localparam NUMCORES = 2;

input reg clock;
input reg reset;
wire trap0;
wire trap1;

wire [31:0] imem_addr0;
reg  [31:0] imem_data0;

wire        dmem_valid0;
wire        dmem_wr_is_cond0;
wire [31:0] dmem_addr0;
wire [ 3:0] dmem_wstrb0;
wire [31:0] dmem_wdata0;
reg  [31:0] dmem_rdata0;


wire [31:0] imem_addr1;
reg  [31:0] imem_data1;

wire        dmem_valid1;
wire        dmem_wr_is_cond1;
wire [31:0] dmem_addr1;
wire [ 3:0] dmem_wstrb1;
wire [31:0] dmem_wdata1;
reg  [31:0] dmem_rdata1;


wire [NUMCORES-1:0] dmem_resv;
reg  [NUMCORES-1:0] dmem_cond;







nerv dut_0 (
	.clock(clock),
	.reset(reset),
	.trap(trap0),

	.imem_addr(imem_addr0),
	.imem_data(imem_data0),

	.dmem_valid(dmem_valid0),
    .dmem_wr_is_cond(dmem_wr_is_cond0),
	.dmem_addr(dmem_addr0),
	.dmem_wstrb(dmem_wstrb0),
	.dmem_wdata(dmem_wdata0),
	.dmem_rdata(dmem_rdata0),

    .dmem_resv(dmem_resv[0]),
    .dmem_cond(dmem_cond[0])
);



nerv #(.RESET_ADDR(32'h 0001_0000)) dut_1 (
	.clock(clock),
	.reset(reset),
	.trap(trap1),

	.imem_addr(imem_addr1),
	.imem_data(imem_data1),

	.dmem_valid(dmem_valid1),
    .dmem_wr_is_cond(dmem_wr_is_cond1),
	.dmem_addr(dmem_addr1),
	.dmem_wstrb(dmem_wstrb1),
	.dmem_wdata(dmem_wdata1),
	.dmem_rdata(dmem_rdata1),

    .dmem_resv(dmem_resv[1]),
    .dmem_cond(dmem_cond[1])
);

multicore_memory   #(.fname(firmwarefile)) mem_0 (
	.clock(clock),
	.reset(reset),

    .imem_addr0(imem_addr0),
    .imem_data0(imem_data0),

	.dmem_valid0(dmem_valid0),
    .dmem_wr_is_cond0(dmem_wr_is_cond0),
	.dmem_addr0(dmem_addr0),
	.dmem_wstrb0(dmem_wstrb0),
	.dmem_wdata0(dmem_wdata0),
	.dmem_rdata0(dmem_rdata0),

    .imem_addr1(imem_addr1),
    .imem_data1(imem_data1),

	.dmem_valid1(dmem_valid1),
    .dmem_wr_is_cond1(dmem_wr_is_cond1),
	.dmem_addr1(dmem_addr1),
	.dmem_wstrb1(dmem_wstrb1),
	.dmem_wdata1(dmem_wdata1),
	.dmem_rdata1(dmem_rdata1),

    .dmem_resv(dmem_resv),
    .dmem_cond(dmem_cond)

);


reg [31:0] cycles = 0;

integer r,c;
always @(posedge clock) begin
	cycles <= cycles + 32'h1;
	if (trap0 && trap1) begin
		$display("Simulated %0d cycles", cycles);

//        $display("Hart 0:");
//        for(r=0; r<32; r+=4) begin
//            $display("  x%-2d=%-5d x%-2d=%-5d x%-2d=%-5d x%-2d=%-5d", 
//                r+0, dut_0.regfile[r+0], r+1, dut_0.regfile[r+1],
//                r+2, dut_0.regfile[r+2], r+3, dut_0.regfile[r+3]
//            );
//        end
//        $display("Hart 1:");
//        for(r=0; r<32; r+=4) begin
//            $display("  x%-2d=%-5d x%-2d=%-5d x%-2d=%-5d x%-2d=%-5d", 
//                r+0, dut_1.regfile[r+0], r+1, dut_1.regfile[r+1],
//                r+2, dut_1.regfile[r+2], r+3, dut_1.regfile[r+3]
//            );
//        end

        /* use this for make results */
        for(r=0; r<32; r++) 
            $display("h0:x%-2d=0x%-0x", r, dut_0.regfile[r]);
        for(r=0; r<32; r++) 
            $display("h1:x%-2d=0x%-0x", r, dut_1.regfile[r]);
        $finish;
	end
end



endmodule
