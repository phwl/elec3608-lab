# Lab 1 - Arithmetic Logic Unit

In this laboratory we will design an arithmetic logic unit (ALU)
which performs ```op_a +/- op_b```, returning two outputs: the 32-bit
value ```result``` and a single bit value ```result_eq_zero```
(which is asserted when ```result == 32'b0```).

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
    input signed [31:0] op_a;
    input signed [31:0] op_b;
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

It should also be noted that op_a and op_b are chosen to be signed
values. This will make some of the other ALU functions easier
to implement. If we were to declare the inputs as ```logic``` or
```unsigned```, then some unsigned operations such as comparisons will
be treated differently.

## Verilator test bench

Every verilog module should have a corresponding unit test to verify
its correctness. The ```addsub/tb_addsub.cpp```
[Verilator](https://www.veripool.org/verilator/) testbench defines a
C equivalent add/sub function in ```addsub()```.

```C++
// The different alu_function codes
#define ALU_ADD     0x01
#define ALU_SUB     0x02

// This is the function we are trying to emulate in our system verilog 
int addsub(int alu_function, int32_t a, int32_t b) {
    switch (alu_function) {
        case ALU_ADD:   
            return a + b;
        case ALU_SUB:   
            return a - b;
        default:
            return 0;
    }
}
```

We first compute the output of ```addsub(alu_function, a, b)```.
and assign it to the variable ```cresult```. Next we run Verilator
by assigning the ```alu_function, a, b``` inputs to the corresponding
fields of the ```tb``` pointer. We then call ```tb_eval()``` to compute
the output which appears in ```tb->result```. Following that we verify
that the result is correct, i.e. ```cresult``` matches ```tb->result```
and print some diagnostic output.

```C++
// Try some inputs and compare with addsub()
int test_addsub(Vaddsub *tb, int alu_function, int32_t a, int32_t b) {
    int32_t cresult = addsub(alu_function, a, b);

    // run Verilator
    tb->op_a = a;
    tb->op_b = b;
    tb->alu_function = alu_function;
    tb->eval();

    // Check answer is correct
    int ok = tb->result == cresult;
    char function_char = alu_function == ALU_ADD ? '+' : '-';

    // Display results
    printf("%08x %c %08x\t", tb->op_a, function_char, tb->op_b);
    printf("result=%08x (cresult=%08x) %c\n",
            tb->result, cresult, ok ? 'Y' : 'N');
    return ok;
}
```

The ```main()``` function is then called to initialise Verilator and
test the add/sub ALU on a few simple examples.
```C++
int main(int argc, char **argv) {
	int ok;

    // This must be called first
    Verilated::commandArgs(argc, argv);

    // Instantiate design
    Vaddsub *tb = new Vaddsub;

    // Here are the tests
    ok = test_addsub(tb, ALU_ADD, 1, 2); 
    ok = test_addsub(tb, ALU_ADD, 0xffffffff, 2); 
    ok = test_addsub(tb, ALU_ADD, 0x7fffffff, 0xFF); 
    ok = test_addsub(tb, ALU_SUB, 0xdeadbeef, 0xdeadbeef); 
    ok = test_addsub(tb, ALU_SUB, 0xdeadbeef, 2); 
    ok = test_addsub(tb, ALU_SUB, 0xdeadbeef, 0xe1e10); 

    // Exit
    delete tb;
    exit(EXIT_SUCCESS);
}
```

One can execute the addsub example using the commands below. Note that the ```%``` prompt is a prompt on the host machine (a Mac in the example below) whereas the ```$``` prompt corresponds to the docker execution. This involves the following process
* ```make``` is executed which reads the ```Makefile``` containing the instructions on how to build the example
* VERILATING: The command ```verilator -Wall --trace --x-assign unique --x-initial unique -cc addsub.sv -    -exe tb_addsub.cpp``` translates ```addsub.sv``` into ```obj_dir/Vaddsub.cpp```.
* BUILDING SIM: ```obj_dir/Vaddsub.cpp``` is compiled (along with some other files) with ```tb_addsub.cpp``` to produce the executable ```obj_dir/Vaddsub```. All the files are generated in ```obj_dir```.
* SIMULATING: ```obj_dir/Vaddsub``` is executed and runs the testbench that we created (which in turn runs the verilog simulation). For each test, the operands are printed, then the verilog result and the C result. A 'Y' is printed on the right hand side if the two results match, otherwise an 'N' is printed.

```bash
(base) phwl@AHJ7LDH57JP lab1-alu % docker run --platform linux/amd64 -it -e DISPLAY=$DISPLAY -v `pwd`:/config phwl/elec3608-base
To run a command as administrator (user "root"), use "sudo <command>".
See "man sudo_root" for details.

elec3608@470497ea6c2b:~$ ls
README.md  addsub  alu
elec3608@470497ea6c2b:~$ cd addsub/
elec3608@470497ea6c2b:~/addsub$ make

### VERILATING ###
verilator -Wall --trace --x-assign unique --x-initial unique -cc addsub.sv --exe tb_addsub.cpp

### BUILDING SIM ###
make -C obj_dir -f Vaddsub.mk Vaddsub
make[1]: Entering directory '/config/addsub/obj_dir'
g++  -I.  -MMD -I/usr/share/verilator/include -I/usr/share/verilator/include/vltstd -DVM_COVERAGE=0 -DVM_SC=0 -DVM_TRACE=1 -faligned-new -fcf-protection=none -Wno-bool-operation -Wno-sign-compare -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-shadow       -c -o tb_addsub.o ../tb_addsub.cpp
g++  -I.  -MMD -I/usr/share/verilator/include -I/usr/share/verilator/include/vltstd -DVM_COVERAGE=0 -DVM_SC=0 -DVM_TRACE=1 -faligned-new -fcf-protection=none -Wno-bool-operation -Wno-sign-compare -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-shadow       -c -o verilated.o /usr/share/verilator/include/verilated.cpp
g++  -I.  -MMD -I/usr/share/verilator/include -I/usr/share/verilator/include/vltstd -DVM_COVERAGE=0 -DVM_SC=0 -DVM_TRACE=1 -faligned-new -fcf-protection=none -Wno-bool-operation -Wno-sign-compare -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-shadow       -c -o verilated_vcd_c.o /usr/share/verilator/include/verilated_vcd_c.cpp
/usr/bin/perl /usr/share/verilator/bin/verilator_includer -DVL_INCLUDE_OPT=include Vaddsub.cpp > Vaddsub__ALLcls.cpp
g++  -I.  -MMD -I/usr/share/verilator/include -I/usr/share/verilator/include/vltstd -DVM_COVERAGE=0 -DVM_SC=0 -DVM_TRACE=1 -faligned-new -fcf-protection=none -Wno-bool-operation -Wno-sign-compare -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-shadow       -c -o Vaddsub__ALLcls.o Vaddsub__ALLcls.cpp
/usr/bin/perl /usr/share/verilator/bin/verilator_includer -DVL_INCLUDE_OPT=include Vaddsub__Trace.cpp Vaddsub__Syms.cpp Vaddsub__Trace__Slow.cpp > Vaddsub__ALLsup.cpp
g++  -I.  -MMD -I/usr/share/verilator/include -I/usr/share/verilator/include/vltstd -DVM_COVERAGE=0 -DVM_SC=0 -DVM_TRACE=1 -faligned-new -fcf-protection=none -Wno-bool-operation -Wno-sign-compare -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-shadow       -c -o Vaddsub__ALLsup.o Vaddsub__ALLsup.cpp
ar -cr Vaddsub__ALL.a Vaddsub__ALLcls.o Vaddsub__ALLsup.o
ranlib Vaddsub__ALL.a
g++    tb_addsub.o verilated.o verilated_vcd_c.o Vaddsub__ALL.a    -o Vaddsub -lm -lstdc++ 
make[1]: Leaving directory '/config/addsub/obj_dir'

### SIMULATING ###
./obj_dir/Vaddsub +verilator+rand+reset+2 
00000001 + 00000002	result=00000003 (cresult=00000003) Y
ffffffff + 00000002	result=00000001 (cresult=00000001) Y
7fffffff + 000000ff	result=800000fe (cresult=800000fe) Y
deadbeef - deadbeef	result=00000000 (cresult=00000000) Y
deadbeef - 00000002	result=deadbeed (cresult=deadbeed) Y
000e1e10 - deadbeef	result=21605f21 (cresult=21605f21) Y
elec3608@470497ea6c2b:~/addsub$
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
Modify ```alu.sv``` so that it implements the ```result_eq_zero``` output
and passes the appropriate tests in the supplied ```alu/tb_alu.cpp```.
Create your own tests to check you get the correct answer for other cases.

```sv
module alu(alu_function, op_a, op_b, result, result_eq_zero);
    input [4:0] alu_function;
    input signed [31:0] op_a;
    input signed [31:0] op_b;
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
`define ALU_SEQ     5'b00110
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

