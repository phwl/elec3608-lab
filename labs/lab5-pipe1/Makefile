#  NERV -- Naive Educational RISC-V Processor
#
#  Copyright (C) 2020  N. Engelhardt <nak@yosyshq.com>
#  Copyright (C) 2020  Claire Xenia Wolf <claire@yosyshq.com>
#
#  Permission to use, copy, modify, and/or distribute this software for any
#  purpose with or without fee is hereby granted, provided that the above
#  copyright notice and this permission notice appear in all copies.
#
#  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
#  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
#  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
#  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
#  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
#  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
#  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

TOOLCHAIN_PREFIX?=riscv64-unknown-elf-
VERILATOR = verilator
RDOCKER = ../common/rundocker

all:	firmware.out

firmware.out:	firmware.hex
	python testbench.py -t testbench.sv

test_verilator: testbench_verilator 
	./obj_dir/Vtestbench +vcd

%.asc: %.json
	nextpnr-ice40 --hx8k --pcf $*.pcf --json $*.json --asc $*.asc --pcf-allow-unconstrained -l $*-pnr.log

%.json: %.sv
	yosys -s $*.yosys -l $*-yosys.log

testbench_verilator: firmware.hex testbench.sv nerv.sv testbench.cpp 
	$(VERILATOR) --cc --exe -Wno-lint -trace --top-module testbench testbench.sv nerv.sv testbench.cpp 
	$(MAKE) -C obj_dir -f Vtestbench.mk

%.elf: %.s 
	$(TOOLCHAIN_PREFIX)gcc -march=rv32i -mabi=ilp32 -Os -Wall -Wextra -Wl,-Bstatic,-T,sections.lds,--strip-debug -ffreestanding -nostdlib -o $@ $^

%.hex: %.elf
	$(TOOLCHAIN_PREFIX)objcopy -O verilog $< $@

show:
	gtkwave testbench.vcd testbench.gtkw >> gtkwave.log 2>&1 &

rundocker:
	$(RDOCKER)

clean:
	rm -rf firmware.elf firmware.hex testbench testbench.vcd gtkwave.log
	rm -rf disasm.o disasm.s checks/ cexdata/ obj_dir
	rm -rf *.log *.asc *.json
