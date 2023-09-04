# Assignment 1 - Two Stage Pipelined Processor

## Goals
 *  Use the knowledge gained from earlier labs to implement a complete pipelined RV32I processor which can execute a real program.
 *  Gain experience writing technical reports.

In the labs for this course, you have developed a series of RV32I processors
culminating in a simple pipelined processor. In this assignment, you will extend and optimise the microarchitecture to achieve higher performance.

# Question
Create a pipelined RV32I processor which implements enough of the instructions specified in Volume 1 Sections 2.1-2.6 of the RISC-V ISA Specification <https://riscv.org/technical/specifications/> to execute the programs supplied with this assignment and add the following features (with each improvement including the functionality from previous part):
 1. (4 marks) A 2-stage pipelined processor with high clock frequency on a [Lattice iCE40-HX8k](https://www.latticesemi.com/iCE40) FPGA. This should be achieved by placing registers in the best position to execute the test programs. Marks for this question do not involve resolving hazards.
 1. (3 marks) Incorporate hardware interlocks, i.e.  any stalling of the processor to resolve hazards is done within the processor so the original test programs can be executed correctly irrespective of what hazards are in
the program..
 1. (5 marks) Report (see below).

The machine marked parts will consider correctness and performance. 
Performance will be measured using the ```make result``` target as shown below
```bash
$ make result
...
Test summary
period: 2.701242571582928e-08
test1.result: x10=55 cycles=18 extime=4.86223662884927e-07 normextime=1.0
test2.result: x10=3790353928 cycles=15 extime=4.051863857374392e-07 normextime=1.0
test3.result: x10=45 cycles=40 extime=1.0804970286331712e-06 normextime=1.0
test4.result: x10=210 cycles=130 extime=3.5116153430578064e-06 normextime=1.0
test5.result: x10=21 cycles=942 extime=2.5445705024311184e-05 normextime=1.0
Geometric mean=1.0
```

Note that test0.s gives the right answer only for a machine with one branch delay slot (it is an infinite loop on a machine with hardware interlocks and won't be included in the machine marking). Credit for changing the assembly files to resolve hazards will be given for the report but not machine marking.

The output gives the minimum clock period (period), value of the x10 register (x10), the number of cycles (cycles), execution time (extime), execution time normalised to the original design (normextime), and the gemetric mean of normextime. The geometric mean is the mean speedup over the nerv single
cycle processor (note that it is used because it
is the only correct mean when averaging normalized results see
<https://en.wikipedia.org/wiki/Geometric_mean>).

## Reports
 * Your report should be a 4 page document explaining your design (appendices with no page limit can be included). It should be in [A4 IEEE format](https://www.ieee.org/conferences/publishing/templates.html) with the default font sizes, and organized under the following section headings: Introduction, Background, Architecture, Results, Discussion, Conclusion, References, Appendices.
 * In your report, focus on describing the pipelining parts and the changes that *you* made on the supplied version of the processor. While it should have a short summary of the original RISC-V design, this will only count towards the report completeness and no marks will be awarded for describing the design that was supplied.
 * The main part of your report should focus on: (1) how you determined where to place the pipeline stages, including a full datapath figure, and (2) how you achieve stalling, explanation of all the relevant boolean expressions for control signals used to resolve data and control hazards, and timing diagrams with explanations showing your solution resolves the hazards. Your explanation should refer to your appendix which contains well commented verilog code.
 *  Include a performance description which includes maximum clock frequency and number of cycles required to execute each program you test. You need to provide supporting evidence which can convince the reader that you have completed the design and it works via appendices containing code listings, simulations and log files. The appendices don't count in the page limit. Comment on whether your result is a good one and what could be done to further improve performance.
 *  [Dennis et al.](https://ieeexplore.ieee.org/abstract/document/8303926) and [Miyazaki et al.](https://arxiv.org/abs/2002.03568) are two examples of well-written papers describing a RISC-V processor (you could following a similar style for your report). [Singh et al.](https://ieeexplore.ieee.org/document/9250850) is an example of a poorly written paper.
 *  You should assume that the reader is familiar computer architecture in general, but not necessarily the the RISC-V instruction set or your architecture. Write the report as an academic-style paper like the examples provided.
 *  If you don't finish the entire question, still report on your answer. Partial marks will be awarded.
 *  No extensions will be granted and penalty for a late submission is deduction of 5% of the maximum mark for each calendar day after the due date. After ten calendar days late, a mark of zero will be awarded.

# Submission 
Your assignment should be submitted online as two separate files (a .pdf and .sv file) before the due date. Refer to Canvas for the rubric and submission instructions.
 * Report: a pdf report as described below.
 * Design: a System Verilog file containing your pipelined processor.
