# RV32 Load and Store instructions

In this lab you will implement the load and store instructions for
a single-cycle RISC-V (RV) processor.

If you have previously downloaded all the labs using ```git clone https://github.com/phwl/elec3608-lab.git```, you should first type ```git pull``` to download any recent changes.

In your lab book, clearly explain the changes that you needed to make
to answer each question and include screen shots of your simulations
and terminal output.

## Lab Questions
### Part 1 - Datapath (20%)
Using the figures from the lectures as a starting point, modify the datapath of ```rv3608c.sv``` so it has the additional parts required to implement the ```lw``` and ```sw``` instructions. In a table, describe the operation of each of the original and new control signals. Put this information in your lab book.

### Part 2 - sw instruction (20%) 
Study the ```test1.s``` program, listed below. 

```assembly
.section .text
.global _start
_start:
    addi x1, zero, 0xd0
    addi sp, zero, 0x24
    sw x1,0(sp)
    addi sp,sp,-4
    lw x10,4(sp)
    ebreak
```
The first 3 instructions simply initialises the x1 and sp registers and then does a ```sw``` to write 0xd0 to address 0x24. 

Note that ```sw``` uses the S-type format for the immediate value and the code is not present in the ```rv3608c.sv```. You can call this offset ```imm_s_sext```.

Modify ```rv3608c.sv``` so it implements the ```sw``` instruction and show either with System Verilog
```$display()``` statements or the waveform display that it is operating
on the correct value and address. 

### Part 3 - lw instruction (40%) 
The next step is to implement the ```lw``` and other instructions so that the test1.s program runs correctly. Modify ```rv3608c.sv``` so it
gives the correct return value of 0xd0 (208 in decimal) as below.

```bash
elec3608@418aecef30c6:~$ make
make: *** No rule to make target 'lab1.out', needed by 'all'.  Stop.
elec3608@418aecef30c6:~$ vi Makefile 
elec3608@418aecef30c6:~$ make
riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -Os -Wall -Wextra -Wl,-Bstatic,-T,sections.lds,--strip-debug -ffreestanding -nostdlib -o test1.elf test1.s
riscv64-unknown-elf-as -march=rv32i -mabi=ilp32 -a test1.s > test1.lst
riscv64-unknown-elf-objcopy -O verilog test1.elf test1.hex
cp test1.hex firmware.hex
python testbench.py 
%Warning-UNOPTFLAT: rv3608c.sv:122: Signal unoptimizable: Feedback to clock or circular logic: 'testbench.dut.alu_result'
    logic   [31:0] alu_result;
                   ^~~~~~~~~~
                    testbench.sv:68: ... note: In file included from testbench.sv
                    ... Use "/* verilator lint_off UNOPTFLAT */" and lint_on around source to disable this message.
                    rv3608c.sv:122:      Example path: testbench.dut.alu_result
                    rv3608c.sv:194:      Example path: ALWAYS
                    rv3608c.sv:127:      Example path: testbench.dut.alu_op
                    alu.sv:19:      Example path: ALWAYS
                    rv3608c.sv:122:      Example path: testbench.dut.alu_result
make[1]: Entering directory '/config/obj_dir'
g++  -I.  -MMD -I/usr/share/verilator/include -I/usr/share/verilator/include/vltstd -DVM_COVERAGE=0 -DVM_SC=0 -DVM_TRACE=1 -faligned-new -fcf-protection=none -Wno-bool-operation -Wno-sign-compare -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-shadow     -fPIC -shared --std=c++11 -DVL_USER_FINISH   -c -o pyverilator_wrapper.o ../obj_dir/pyverilator_wrapper.cpp
g++  -I.  -MMD -I/usr/share/verilator/include -I/usr/share/verilator/include/vltstd -DVM_COVERAGE=0 -DVM_SC=0 -DVM_TRACE=1 -faligned-new -fcf-protection=none -Wno-bool-operation -Wno-sign-compare -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-shadow     -fPIC -shared --std=c++11 -DVL_USER_FINISH   -c -o verilated.o /usr/share/verilator/include/verilated.cpp
g++  -I.  -MMD -I/usr/share/verilator/include -I/usr/share/verilator/include/vltstd -DVM_COVERAGE=0 -DVM_SC=0 -DVM_TRACE=1 -faligned-new -fcf-protection=none -Wno-bool-operation -Wno-sign-compare -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-shadow     -fPIC -shared --std=c++11 -DVL_USER_FINISH   -c -o verilated_vcd_c.o /usr/share/verilator/include/verilated_vcd_c.cpp
/usr/bin/perl /usr/share/verilator/bin/verilator_includer -DVL_INCLUDE_OPT=include Vtestbench.cpp > Vtestbench__ALLcls.cpp
g++  -I.  -MMD -I/usr/share/verilator/include -I/usr/share/verilator/include/vltstd -DVM_COVERAGE=0 -DVM_SC=0 -DVM_TRACE=1 -faligned-new -fcf-protection=none -Wno-bool-operation -Wno-sign-compare -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-shadow     -fPIC -shared --std=c++11 -DVL_USER_FINISH   -c -o Vtestbench__ALLcls.o Vtestbench__ALLcls.cpp
/usr/bin/perl /usr/share/verilator/bin/verilator_includer -DVL_INCLUDE_OPT=include Vtestbench__Trace.cpp Vtestbench__Syms.cpp Vtestbench__Trace__Slow.cpp > Vtestbench__ALLsup.cpp
g++  -I.  -MMD -I/usr/share/verilator/include -I/usr/share/verilator/include/vltstd -DVM_COVERAGE=0 -DVM_SC=0 -DVM_TRACE=1 -faligned-new -fcf-protection=none -Wno-bool-operation -Wno-sign-compare -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-shadow     -fPIC -shared --std=c++11 -DVL_USER_FINISH   -c -o Vtestbench__ALLsup.o Vtestbench__ALLsup.cpp
ar -cr Vtestbench__ALL.a Vtestbench__ALLcls.o Vtestbench__ALLsup.o
ranlib Vtestbench__ALL.a
g++ -fPIC -shared pyverilator_wrapper.o verilated.o verilated_vcd_c.o Vtestbench__ALL.a    -o Vtestbench -lm -lstdc++ 
make[1]: Leaving directory '/config/obj_dir'
pc = 0x00000000, insn_opcode = 0x13
pc = 0x00000000, insn_opcode = 0x13
pc = 0x00000000, insn_opcode = 0x13
pc = 0x00000004, insn_opcode = 0x13
sw 0x000000d0 to = 0x00000024
sw 0x000000d0 to = 0x00000024
sw 0x000000d0 to = 0x00000024
sw 0x000000d0 to = 0x00000024
pc = 0x00000008, insn_opcode = 0x23
pc = 0x0000000c, insn_opcode = 0x13
lw from 0x00000024 = 0x000000d0
lw from 0x00000024 = 0x000000d0
lw from 0x00000024 = 0x000000d0
pc = 0x00000010, insn_opcode = 0x03
pc = 0x00000014, insn_opcode = 0x0f
Return_reg 208 (8 cycles)
touch test1.out
rm test1.hex test1.elf
```

### Part 4 - Fibonnacci Program (20%) 
The following program, provided in ```fib.s```, is a recursive program to compute the n'th Fibonnacci
number. The value of ```n``` is placed in the ```a0``` register before the subroutine is called. Note that while this is an interesting program for testing load and store operations, it is a super-inefficient way to compute the Fibonnacci sequence.

Simulate it using the [RISC-V Graphic Datapath Simulator](https://jesse-r-s-hines.github.io/RISC-V-Graphical-Datapath-Simulator/). This is a useful
tool for verifying software and datapath execution.

Then modify ```rv3608c.sv``` so this program can execute on your processor (you
will need to use work from previous labs).

```assembly
    # place SP at the end of RAM
    li sp, 0x100

	li	a0,10
	jal ra,fib
	j quit

fib:
	addi	sp,sp,-16
	sw	s0,8(sp)
	sw	s1,4(sp)
	sw	s2,0(sp)
	sw	ra,12(sp)
	mv	s0,a0
	li	s1,0
	li	s2,1
L3:
	beq	zero,s0,L2
	beq	s0,s2,L2
	addi	a0,s0,-1
	jal ra,fib
	addi	s0,s0,-2
	add	s1,s1,a0
	j	L3
L2:
	add	a0,s0,s1
	lw	ra,12(sp)
	lw	s0,8(sp)
	lw	s1,4(sp)
	lw	s2,0(sp)
	addi	sp,sp,16
	jalr	x0,0(ra)

quit:
    ebreak
```
