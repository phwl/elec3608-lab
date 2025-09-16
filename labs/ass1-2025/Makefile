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

# MacOS/Windows w/ docker desktop
#RDOCKER = docker run --platform linux/amd64 -it -e DISPLAY=host.docker.internal:0 -v `pwd`:/config phwl/elec3608-cad:latest

# Linux w/o SNAP & docker desktop
RDOCKER = docker run --platform linux/amd64 -it --net host -e DISPLAY=$(DISPLAY) -v `pwd`:/config phwl/elec3608-cad:latest

# this can be simply overridden using make FIRMWAREFILE=... all
FIRMWAREFILE=test1-hart1-only.hex

# logging file name
LOGFILE=`basename $(FIRMWAREFILE) .hex`.log
ASMFILE=`basename $(FIRMWAREFILE) .hex`.s 
RESULTFILE=results.log

# all tests
ALLFIRMWARE=test1-hart1-only.hex test2-hart2-only.hex test3-samecode-bothharts.hex \
	test4-race-hart1-slowslow.hex test5-race-hart2-slowslow.hex \
	test6-race-hart1-slow.hex  test7-race-hart2-slow.hex  test8-samecode-2reserv.hex \
	test9-samecode-1reserv.hex \
	test10-hart1-inside-hart2.hex  test11-hart2-inside-hart1.hex \
	test12-hart1-interleave-hart2.hex  test13-hart2-interleave-hart1.hex

all:	$(FIRMWAREFILE) test_verilator

allresults:
	$(foreach ff, $(ALLFIRMWARE),  make result FIRMWAREFILE=$(ff);)
	@echo "---------------------------------------------------"
	@echo "Results..."
	@cat $(RESULTFILE)

result : all 
	@python checkregs.py $(LOGFILE) $(ASMFILE) | tee --append $(RESULTFILE)

test_verilator: testbench_verilator 
	@./obj_dir/Vtestbench +vcd > $(LOGFILE)

testbench_verilator: $(FIRMWAREFILE) testbench-2hart.sv nerv-atomic.sv testbench.cpp 
	@$(VERILATOR) --cc --exe -Wno-lint -trace --top-module testbench \
		-Gfirmwarefile=\"$(FIRMWAREFILE)\" \
		testbench-2hart.sv nerv-atomic.sv testbench.cpp
	@$(MAKE) -C obj_dir -f Vtestbench.mk

%.elf: %.s 
	@$(TOOLCHAIN_PREFIX)gcc -march=rv32ia -mabi=ilp32 -Os -Wall -Wextra -Wl,-Bstatic,-T,sections.lds,--strip-debug -ffreestanding -nostdlib -o $@ $^

%.hex: %.elf
	@$(TOOLCHAIN_PREFIX)objcopy -O verilog $< $@

show:
	@gtkwave testbench.vcd testbench.gtkw >> gtkwave.log 2>&1 

rundocker:
	$(RDOCKER)

clean:
	rm -rf firmware.elf firmware.hex testbench testbench.vcd gtkwave.log
	rm -rf disasm.o disasm.s checks/ cexdata/ obj_dir
	rm -rf *.log *.asc *.json *.hex
