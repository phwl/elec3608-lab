# Assignment 1 - RV32IM Single Cycle Processor

## Goals
 *  Use the knowledge gained from earlier labs to implement a single-cycle RV32I processor with 'M' extensions.
 *  Gain experience writing technical reports.

In the labs for this course, you have developed a series of RV32I processors
culminating in a simple pipelined processor. In this assignment, you will extend the microarchitecture to design and test a complete RV32IM processor. 

# Question
Starting with the complete single cycle processor that you developed in the labs, add the M extensions, i.e. create a single-cycle RV32IM processor. The M Extensions are described in Section 13 of Volume 1, Unprivileged Specification version 20240411  <https://riscv.org/technical/specifications/>. 

## (5 marks) Part 1: Implementation.
Develop a complete single cycle RV32IM processor using nerv.sv in this directory as a starting point.
This question will be machine marked based on execution time and correctness. We will run your processor using the ```make result``` target as explained below with that are not provided to you. 

The sample test programs provided in this directory don't have instructions from the M extensions. It is your job to create your own test programs to verify your RV32IM meets the full specification. If you find mistakes in the starting RV32I processor, these should be fixed and noted in your report (you will receive extra credit). 
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
The output gives the minimum clock period (period), value of the x10 register (x10), the number of cycles (cycles), execution time (extime), execution time normalised to the original design (normextime), and the gemetric mean of normextime. The geometric mean is the mean speedup over the nerv single
cycle processor (note that it is used because it
is the only correct mean when averaging normalized results see
<https://en.wikipedia.org/wiki/Geometric_mean>). We will not be running any of these tests in machine marking (and hence not use the normalized execution time or mean), they are just used as examples of how to create a test suite.

## (5 marks) Part 2: Report.
 * Your report should be a document with maximum of 6 pages explaining your design (appendices with no page limit can be included).
 *  The report should be in [A4 IEEE format](https://www.ieee.org/conferences/publishing/templates.html) with the default font sizes, and organized under the following section headings: Introduction, Background, Architecture, Results, Discussion, Conclusion, References, Appendices.
 * It should include a full datapath description and matching control table like that given in the "Hardwired Control Table (Excerpt)" slide in Lecture 4 Single Cycle Processor.
 * Create a table of your test programs and explain their functionality in your report. Also explain how they provide good coverage of the 'M' extensions, what is the correct x10 result and why.
 *  Include a performance description which includes maximum clock frequency of your processor and number of cycles required to execute each program you test. You need to provide supporting evidence which can convince the reader that you have completed the design and it works via appendices containing code listings, simulations and log files. The appendices don't count in the page limit. 
 *  [Dennis et al.](https://ieeexplore.ieee.org/abstract/document/8303926) and [Miyazaki et al.](https://arxiv.org/abs/2002.03568) are two examples of well-written papers describing a RISC-V processor (you could following a similar style for your report). [Singh et al.](https://ieeexplore.ieee.org/document/9250850) is an example of a poorly written paper.
 *  You should assume that the reader is familiar computer architecture in general, but not necessarily the the RISC-V instruction set or your architecture. Write the report as an academic-style paper like the examples provided.
 *  If you don't finish the entire question, still report on your answer. Partial marks will be awarded.
 *  No extensions will be granted and penalty for a late submission is deduction of 5% of the maximum mark for each calendar day after the due date. After ten calendar days late, a mark of zero will be awarded.

# Submission 
Your assignment should be submitted online as two separate files (a .pdf and .tgz file) before the due date. Refer to Canvas for the rubric and submission instructions.
 * Report: a pdf report as described below.
 * Design: a .tgz file created using "make submit". The main design should be a Verilog file which must be called nerv.sv and contain your processor. The remaining files should include your test programs.
