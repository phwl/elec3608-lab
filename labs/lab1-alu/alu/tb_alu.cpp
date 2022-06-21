// a simple adder example based on https://zipcpu.com/tutorial/
//
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <random>
#include "Valu.h"
#include "verilated.h"
#include <verilated_vcd_c.h>

// The different alu_function codes
#define ALU_ADD     0x01
#define ALU_SUB     0x02

// This is the function we are trying to emulate in our system verilog 
int alu(int alu_function, int32_t a, int32_t b, int32_t *result_eq_zero) {
    int32_t result;

    switch (alu_function) {
        case ALU_ADD:   
            result = a + b;
            break;
        case ALU_SUB:   
            result = a - b;
            break;
        default:
            result = 0;
            break;
    }
    *result_eq_zero = result == 0 ? 1 : 0;
    return result;
}

// Try some inputs and compare with alu()
int test_alu(Valu *tb, int alu_function, int32_t a, int32_t b) {
    int32_t cresult_eq_zero;

    int32_t cresult = alu(alu_function, a, b, &cresult_eq_zero);

    // run Verilator
    tb->op_a = a;
    tb->op_b = b;
    tb->alu_function = alu_function;
    tb->eval();

    // Check answer is correct
    int ok = tb->result == cresult && 
        tb->result_eq_zero == cresult_eq_zero;
    char function_char = alu_function == ALU_ADD ? '+' : '-';

    // Display results
    printf("%08x %c %08x\t", tb->op_a, function_char, tb->op_b);
    printf("result=%08x,%01x (cresult=%08x,%01x) %c\n", 
            tb->result, tb->result_eq_zero, 
            cresult, cresult_eq_zero, ok ? 'Y' : 'N');
    return ok;
}

int main(int argc, char **argv) {
	int ok;

    // This must be called first
    Verilated::commandArgs(argc, argv);

    // Instantiate design
    Valu *tb = new Valu;

    // Here are the tests
    ok = test_alu(tb, ALU_ADD, 1, 2); 
    ok = test_alu(tb, ALU_ADD, 0xffffffff, 2); 
    ok = test_alu(tb, ALU_ADD, 0x7fffffff, 0xFF); 
    ok = test_alu(tb, ALU_SUB, 0xdeadbeef, 0xdeadbeef); 
    ok = test_alu(tb, ALU_SUB, 0xdeadbeef, 2); 
    ok = test_alu(tb, ALU_SUB, 0xe1e10, 0xdeadbeef); 

    // Exit
    delete tb;
    exit(EXIT_SUCCESS);
}
