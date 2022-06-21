// a simple add/sub ALU
//
`include "constants.svh"

`default_nettype none

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
