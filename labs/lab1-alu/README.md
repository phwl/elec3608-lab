# Lab 1 - Arithmetic Logic Unit

In this laboratory we will design an arithmetic logic unit (ALU)
which performs ```op_a alu_function op_b```, where ```alu_function'''  specifies the 
operation that the ALU performs which is one of the following:
```sv
`define ALU_ADD     5'b00001
`define ALU_SUB     5'b00010
`define ALU_SLL     5'b00011
`define ALU_SRL     5'b00100
`define ALU_SRA     5'b00101
`define ALU_SLT     5'b00111
`define ALU_SLTU    5'b01000
`define ALU_XOR     5'b01001
`define ALU_OR      5'b01010
`define ALU_AND     5'b01011
```

The corresponding instructions are explained in Section 2.4 Integer Computational Instructions of the [The RISC-V Instruction Set Manual
Volume I: Unprivileged ISA](https://github.com/riscv/riscv-isa-manual/releases/download/Ratified-IMAFDQC/riscv-spec-20191213.pdf).

The ALU has two outputs: the 32-bit
value ```result``` and a single bit value ```result_eq_zero```
(which is asserted when ```result == 32'b0```)

If you need more of an introduction to Verilator and System Verilog,
please refer to the excellent tutorial at <https://zipcpu.com/tutorial/>.

## Verilog Description of an ALU

An ALU that only supports the ADD/SUB operations is available in 
```addsub/addsub.sv``` and can be described 
in system verilog as follows
```sv
// a simple add/sub ALU
//
`include "constants.svh"

`default_nettype none

//
module addsub(alu_function, op_a, op_b, result);
    input [4:0] alu_function;
    input [31:0] op_a;
    input [31:0] op_b;
    output logic [31:0] result;

    // Compute result
    always_comb begin
        case (alu_function)
            `ALU_ADD:   result = op_a + op_b;
            `ALU_SUB:   result = op_a - op_b;
            default: result = `ZERO;
        endcase
    end
endmodule
```

In the example, the ```always_comb``` construct says that the code
within is all combinational logic. The case statement thus looks like a
multiplexor with the select input being ```alu_function```, the different
inputs the ```op_a alu_function op_b``` values, and the output result.

## Verilator test bench

Every verilog module should have a corresponding unit test to verify
its correctness. We will use [pyverilator](https://github.com/phwl/pyverilator) which simplifies this process.

The ```addsub/testbench.py``` testbench defines an
equivalent add/sub function.

```python3
# This is the function we are trying to emulate in our system verilog 
def addsub(alu_function, a, b):
    if alu_function == ALU_ADD:
        r = a + b
    elif alu_function == ALU_SUB:   
        r = a - b
    else:
        r = 0
    return uint32(r)
```

The ```test_addsub()``` function takes ```tb``` (a
testbench object used to control the verilator simulation) 
and ```alu_function, a, b``` which are the same inputs as the ALU.
The function executes the ALU simulation placing the result in
```vresult```. It also executes ```addsub``` and places that
result in ```cresult```. Finally, we verify
that the result is correct, i.e. ```vresult``` matches ```cresult```
and print some diagnostic output.

```python3
def test_addsub(tb, alu_function, a, b):
    tb.io.alu_function = alu_function
    tb.io.op_a = a
    tb.io.op_b = b

    cresult = addsub(alu_function, a, b)    # computer result
    vresult = uint32(tb.io.result)             # verilog result
    ok = cresult == vresult
    print("{:08x} {} {:08x}\tresult={:08x} (cresult={:08x}) {}".\
            format(a, ALUSYM[alu_function], b, vresult, cresult, ok));
    return ok
```

Finally, we can run a number of tests using this ```pyverilator``` testbench.
```python3
tb = pyverilator.PyVerilator.build('addsub.sv')
ok = test_addsub(tb, ALU_ADD, 1, 2); 
ok = test_addsub(tb, ALU_ADD, 0xffffffff, 2); 
ok = test_addsub(tb, ALU_ADD, 0x7fffffff, 0xFF); 
ok = test_addsub(tb, ALU_SUB, 0xdeadbeef, 0xdeadbeef); 
ok = test_addsub(tb, ALU_SUB, 0xdeadbeef, 2); 
ok = test_addsub(tb, ALU_SUB, 0xe1e10, 0xdeadbeef); 
```

One can execute the addsub example using the commands below. Note that the ```%``` prompt is a prompt on the host machine (a Mac in the example below) whereas the ```$``` prompt corresponds to the docker execution. This involves the following process
* ```ls``` just lists the files in the directory (you should start in the addsub subdirectory)
* ```make rundocker``` simply executes the command to run docker. You may need to edit the appropriate line in ```Makefile``` on a Windows system
* ```make``` executes ```python testbench.py``` from within Docker which
will compile the Verilog code to C and run the testbench.

```bash
(base) phwl@AHJ7LDH57JP addsub % ls
Makefile	addsub.sv	constants.svh	testbench.py
(base) phwl@AHJ7LDH57JP addsub % make rundocker
docker run --platform linux/amd64 -it -e DISPLAY=host.docker.internal:0 -v `pwd`:/config phwl/elec3608-base:latest
To run a command as administrator (user "root"), use "sudo <command>".
See "man sudo_root" for details.

elec3608@a6fdcffe7ee1:~$ make
python testbench.py
make[1]: Entering directory '/config/obj_dir'
g++  -I.  -MMD -I/usr/share/verilator/include -I/usr/share/verilator/include/vltstd -DVM_COVERAGE=0 -DVM_SC=0 -DVM_TRACE=1 -faligned-new -fcf-protection=none -Wno-bool-operation -Wno-sign-compare -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-shadow     -fPIC -shared --std=c++11 -DVL_USER_FINISH   -c -o pyverilator_wrapper.o ../obj_dir/pyverilator_wrapper.cpp
g++  -I.  -MMD -I/usr/share/verilator/include -I/usr/share/verilator/include/vltstd -DVM_COVERAGE=0 -DVM_SC=0 -DVM_TRACE=1 -faligned-new -fcf-protection=none -Wno-bool-operation -Wno-sign-compare -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-shadow     -fPIC -shared --std=c++11 -DVL_USER_FINISH   -c -o verilated.o /usr/share/verilator/include/verilated.cpp
g++  -I.  -MMD -I/usr/share/verilator/include -I/usr/share/verilator/include/vltstd -DVM_COVERAGE=0 -DVM_SC=0 -DVM_TRACE=1 -faligned-new -fcf-protection=none -Wno-bool-operation -Wno-sign-compare -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-shadow     -fPIC -shared --std=c++11 -DVL_USER_FINISH   -c -o verilated_vcd_c.o /usr/share/verilator/include/verilated_vcd_c.cpp
/usr/bin/perl /usr/share/verilator/bin/verilator_includer -DVL_INCLUDE_OPT=include Vaddsub.cpp > Vaddsub__ALLcls.cpp
g++  -I.  -MMD -I/usr/share/verilator/include -I/usr/share/verilator/include/vltstd -DVM_COVERAGE=0 -DVM_SC=0 -DVM_TRACE=1 -faligned-new -fcf-protection=none -Wno-bool-operation -Wno-sign-compare -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-shadow     -fPIC -shared --std=c++11 -DVL_USER_FINISH   -c -o Vaddsub__ALLcls.o Vaddsub__ALLcls.cpp
/usr/bin/perl /usr/share/verilator/bin/verilator_includer -DVL_INCLUDE_OPT=include Vaddsub__Trace.cpp Vaddsub__Syms.cpp Vaddsub__Trace__Slow.cpp > Vaddsub__ALLsup.cpp
g++  -I.  -MMD -I/usr/share/verilator/include -I/usr/share/verilator/include/vltstd -DVM_COVERAGE=0 -DVM_SC=0 -DVM_TRACE=1 -faligned-new -fcf-protection=none -Wno-bool-operation -Wno-sign-compare -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-shadow     -fPIC -shared --std=c++11 -DVL_USER_FINISH   -c -o Vaddsub__ALLsup.o Vaddsub__ALLsup.cpp
ar -cr Vaddsub__ALL.a Vaddsub__ALLcls.o Vaddsub__ALLsup.o
ranlib Vaddsub__ALL.a
g++ -fPIC -shared pyverilator_wrapper.o verilated.o verilated_vcd_c.o Vaddsub__ALL.a    -o Vaddsub -lm -lstdc++ 
make[1]: Leaving directory '/config/obj_dir'
00000001 + 00000002	result=00000003 (cresult=00000003) True
ffffffff + 00000002	result=00000001 (cresult=00000001) True
7fffffff + 000000ff	result=800000fe (cresult=800000fe) True
deadbeef - deadbeef	result=00000000 (cresult=00000000) True
deadbeef - 00000002	result=deadbeed (cresult=deadbeed) True
000e1e10 - deadbeef	result=21605f21 (cresult=21605f21) True
```

### Lab Questions
To complete the lab, you need to update and submit ```alu/alu.sv```.
A single machine test will be executed (after the deadline) to
compute your mark for this lab, with specific tests included to
check the questions below.

While a small test bench is included you will
need to add your own to ensure good coverage. The machine test will
use a combination of hand-picked and random values.

It is expected that you keep a lab book with a description of all 
experiments that you conduct in this lab. Moreover, clear comments 
should be included in your code.

#### Lab Question 1 - (20%)
Inspect the ALU in ```alu/alu.sv```. It supports an additional output called
```result_eq_zero``` which should be set to zero if the result is zero.
Note that if you run the testbench as below, one of the test cases is wrong
because the current design always returns ```result_eq_zero=0```.

```bash
(base) phwl@AHJ7LDH57JP alu % make rundocker
docker run --platform linux/amd64 -it -e DISPLAY=host.docker.internal:0 -v `pwd`:/config phwl/elec3608-base:latest
To run a command as administrator (user "root"), use "sudo <command>".
See "man sudo_root" for details.

elec3608@3fda6a0d2789:~$ make 
python testbench.py
make[1]: Entering directory '/config/obj_dir'
g++  -I.  -MMD -I/usr/share/verilator/include -I/usr/share/verilator/include/vltstd -DVM_COVERAGE=0 -DVM_SC=0 -DVM_TRACE=1 -faligned-new -fcf-protection=none -Wno-bool-operation -Wno-sign-compare -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-shadow     -fPIC -shared --std=c++11 -DVL_USER_FINISH   -c -o pyverilator_wrapper.o ../obj_dir/pyverilator_wrapper.cpp
g++  -I.  -MMD -I/usr/share/verilator/include -I/usr/share/verilator/include/vltstd -DVM_COVERAGE=0 -DVM_SC=0 -DVM_TRACE=1 -faligned-new -fcf-protection=none -Wno-bool-operation -Wno-sign-compare -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-shadow     -fPIC -shared --std=c++11 -DVL_USER_FINISH   -c -o verilated.o /usr/share/verilator/include/verilated.cpp
g++  -I.  -MMD -I/usr/share/verilator/include -I/usr/share/verilator/include/vltstd -DVM_COVERAGE=0 -DVM_SC=0 -DVM_TRACE=1 -faligned-new -fcf-protection=none -Wno-bool-operation -Wno-sign-compare -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-shadow     -fPIC -shared --std=c++11 -DVL_USER_FINISH   -c -o verilated_vcd_c.o /usr/share/verilator/include/verilated_vcd_c.cpp
/usr/bin/perl /usr/share/verilator/bin/verilator_includer -DVL_INCLUDE_OPT=include Valu.cpp > Valu__ALLcls.cpp
g++  -I.  -MMD -I/usr/share/verilator/include -I/usr/share/verilator/include/vltstd -DVM_COVERAGE=0 -DVM_SC=0 -DVM_TRACE=1 -faligned-new -fcf-protection=none -Wno-bool-operation -Wno-sign-compare -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-shadow     -fPIC -shared --std=c++11 -DVL_USER_FINISH   -c -o Valu__ALLcls.o Valu__ALLcls.cpp
/usr/bin/perl /usr/share/verilator/bin/verilator_includer -DVL_INCLUDE_OPT=include Valu__Trace.cpp Valu__Syms.cpp Valu__Trace__Slow.cpp > Valu__ALLsup.cpp
g++  -I.  -MMD -I/usr/share/verilator/include -I/usr/share/verilator/include/vltstd -DVM_COVERAGE=0 -DVM_SC=0 -DVM_TRACE=1 -faligned-new -fcf-protection=none -Wno-bool-operation -Wno-sign-compare -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-shadow     -fPIC -shared --std=c++11 -DVL_USER_FINISH   -c -o Valu__ALLsup.o Valu__ALLsup.cpp
ar -cr Valu__ALL.a Valu__ALLcls.o Valu__ALLsup.o
ranlib Valu__ALL.a
g++ -fPIC -shared pyverilator_wrapper.o verilated.o verilated_vcd_c.o Valu__ALL.a    -o Valu -lm -lstdc++ 
make[1]: Leaving directory '/config/obj_dir'
00000001 + 00000002	result=00000003,0 (cresult=00000003,0) True
ffffffff + 00000002	result=00000001,0 (cresult=00000001,0) True
7fffffff + 000000ff	result=800000fe,0 (cresult=800000fe,0) True
deadbeef - deadbeef	result=00000000,0 (cresult=00000000,1) False
deadbeef - 00000002	result=deadbeed,0 (cresult=deadbeed,0) True
000e1e10 - deadbeef	result=21605f21,0 (cresult=21605f21,0) True
```

Modify ```alu/alu.sv``` so that it implements the ```result_eq_zero``` output
and passes the appropriate test in ```testbench.py```.
Create your own tests to check you get the correct answer for other cases.

```sv
module alu(alu_function, op_a, op_b, result, result_eq_zero);
    input [4:0] alu_function;
    input [31:0] op_a;
    input [31:0] op_b;
    output logic [31:0] result;
    output logic result_eq_zero;

...
```

In your lab book, draw a complete schematic of the ALU with your change.
The primitive symbols you should use should only consists of simple logic gates, adders, subtactors and multiplexers.

#### Lab Question 2 - (40%)
Modify the ALU in ```alu/alu.sv``` to support all of the following ```alu_function``` operations below. 

```sv
`define ALU_ADD     5'b00001
`define ALU_SUB     5'b00010
`define ALU_XOR     5'b01001
`define ALU_OR      5'b01010
`define ALU_AND     5'b01011
```

#### Lab Question 3 - (40%)
Modify the ALU in ```alu/alu.sv``` to support the remaining ```alu_function``` values listed below.
Create your own tests for each operation. You will be asked to submit
your file as ```alu.sv```. 

```sv
`define ALU_SLL     5'b00011
`define ALU_SRL     5'b00100
`define ALU_SRA     5'b00101
`define ALU_SLT     5'b00111
`define ALU_SLTU    5'b01000
```

Make sure you understand the difference between ```SRA``` and ```SRL```. For numbers where the most significant bit of ```op_a``` is ```0```, their behaviour is exactly the same. When it is ```1```, then the result should fill the bits from the left with ```1``` values. Thus
```
0xFFFFFFFF SRL 2 = 0x3FFFFFF
0xFFFFFFFF SRA 2 = 0xFFFFFFF
```

Also note the difference between ```SLT``` and ```SLTU```. One is for signed numbers whereas the other is for unsigned numbers. Thus
```
0xFFFFFFFF SLT 1 = 1
0xFFFFFFFF SLTU 1 = 0
```

