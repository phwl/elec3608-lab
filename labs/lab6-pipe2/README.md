# Pipelined RV32 (Part 2 of 2)

In this lab you will deal with branch instructions for the 2-stage pipelined processor.

## Lab Questions
### Part 1 - Assembly Language (30%)
Using the design and ```test1.s``` code from the previous lab, rewrite the sequence of
instructions so that it is as compact as possible and uses a loop.
Verify the operation of your program using the single cycle processor 
originally provided.

### Part 2 - Pipelined Processor (70%) 
Draw a picture of a modified datapath which will allow branch instructions to also be pipelined. You are allowed to rewrite Part 1 so that pipeline bubbles are inserted to avoid control hazards (data hazards cannot occur because stage 2 of the pipeline cannot have RAW hazards), i.e. change the ISA so there is a branch delay slot.
Modify the Verilog design in Part 2 of the previous lab so that the
branch decision is moved to the second pipeline stage and the instruction in the branch delay slot is always executed. Explain in your lab book how the scheme works and illustrate it with an example and GTKWave screen shot.

This is the scheme used in the [MIPS-I](https://en.wikipedia.org/wiki/MIPS_architecture) processor. Here is a section from wikipedia:

*All MIPS I control flow instructions are followed by a branch delay slot. Unless the branch delay slot is filled by an instruction performing useful work, an nop is substituted. MIPS I branch instructions compare the contents of a GPR (rs) against zero or another GPR (rt) as signed integers and branch if the specified condition is true.*
