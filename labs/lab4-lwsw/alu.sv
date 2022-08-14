// branch and jump instructions
//
`include "constants.svh"

`default_nettype none

//
module alu(alu_function, op_a, op_b, result, result_eq_zero);
    input [4:0] alu_function;
    input [31:0] op_a;
    input [31:0] op_b;
    output logic [31:0] result;
    output logic result_eq_zero;

    // Implement the zero flag
    assign result_eq_zero = (result == `ZERO);    // true if output is true

    // Compute result
    always_comb begin
        case (alu_function)
            `ALU_ADD:   result = op_a + op_b;
            default: result = `ZERO;
        endcase
    end

endmodule
