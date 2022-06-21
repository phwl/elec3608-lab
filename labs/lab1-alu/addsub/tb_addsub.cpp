// a simple adder example based on https://zipcpu.com/tutorial/
//
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <random>
#include "Vaddsub.h"
#include "verilated.h"
#include <verilated_vcd_c.h>

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
    ok = test_addsub(tb, ALU_SUB, 0xe1e10, 0xdeadbeef); 

    // Exit
    delete tb;
    exit(EXIT_SUCCESS);
}
