# Assignment 1 - Two Stage Pipelined Processor

## Goals
 *  Use the knowledge gained from earlier labs to implement a complete pipelined RV32I processor which can execute a real program.
 *  Gain experience writing technical reports.

In the labs for this course, you have developed a series of RV32I processors
culminating in a simple pipelined processor. In this assignment, you will extend and optimise the microarchitecture to achieve higher performance.

# Question
Create a pipelined RV32I processor which implements enough of the instructions specified in Volume 1 Sections 2.1-2.6 of the RISC-V ISA Specification <https://riscv.org/technical/specifications/> to execute the programs supplied with this assignment.

Then add the following features:
 1. (30%) Achieve a high clock frequency on a [Lattice iCE40-HX8k](https://www.latticesemi.com/iCE40) FPGA for the programs provided by placing a pipeline register in the best position for a 2-stage pipeline and modifying the test programs to resolve hazards via ```nop``` instructions. 
 1. (40%) Incorporate hardware interlocks, i.e.  any stalling of the processor to resolve hazards is done within the processor so the original test programs can be executed.
 1. (20%) Incorporate forwarding. 
 1. (10%) Incorporate branch prediction. 

The percentages above are the maximum mark achievable for both the Design and Report parts of this assignment if you incorporate this feature correctly.

Performance will be measured using the ```make result``` target as shown below
```bash
$ make result
...
Test summary
period: 2.701242571582928e-08
test1.result: x10=55 cycles=18 extime=4.86223662884927e-07 normextime=1.0
test2.result: x10=3790353928 cycles=15 extime=4.051863857374392e-07 normextime=1.0
test3.result: x10=210 cycles=130 extime=3.5116153430578064e-06 normextime=1.0
test4.result: x10=55 cycles=2461 extime=6.647757968665586e-05 normextime=1.0
Geometric mean=1.0
```

The output gives the minimum clock period (period), value of the x10 register (x10), the number of cycles (cycles), execution time (extime), execution time normalised to the original design (normextime), and the gemetric mean of normextime. The geometric mean is the mean speedup over the nerv single
cycle processor (note that it is used because it
is the only correct mean when averaging normalized results see
<https://en.wikipedia.org/wiki/Geometric_mean>).

Machine marking of this assignment will expect exactly the same System Verilog interfaces as in the sample files. The same Makefile will also be used.

# Submission 
Your assignment should be submitted online to the Canvas site as two separate files (a pdf and sv file) before the due date.
 * Report (60% of assignment mark): a pdf report as described below.
 * Design (40% of assignment mark): a single System Verilog file ```rv32i-sid.sv``` which will be machine marked.

**Marking scheme to be added here.**

## Reports
 * Your report should be a document explaining your design.
 *  Your report should be in [A4 IEEE format](https://www.ieee.org/conferences/publishing/templates.html) with the default font sizes, and organized under the following section headings: Introduction, Background, Architecture, Results, Discussion, Conclusion, References, Appendices.
 *  Include a performance description which includes maximum clock frequency and number of cycles required to execute each program you test. You need to provide supporting evidence which can convince the reader that you have completed the design and it works via appendices containing code listings, simulations and log files. The appendices don't count in the page limit. Comment on whether your result is a good one and what could be done to further improve performance.
 *  [Dennis et al.](https://ieeexplore.ieee.org/abstract/document/8303926) and [Miyazaki et al.](https://arxiv.org/abs/2002.03568) are two examples of well-written papers describing a RISC-V processor (you could following a similar style for your report). [Singh et al.](https://ieeexplore.ieee.org/document/9250850) is an example of a poorly written paper.
 *  You should assume that the reader is familiar computer architecture in general, but not necessarily the the RISC-V instruction set or your architecture. Write the report as an academic-style paper like the examples provided.
 *  If you don't finish the entire question, still report on your answer. Partial marks will be awarded.
 *  No extensions will be granted and penalty for a late submission is deduction of 5% of the maximum mark for each calendar day after the due date. After ten calendar days late, a mark of zero will be awarded.

