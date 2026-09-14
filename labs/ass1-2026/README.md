# Assignment 1 - Interrupt controller

## Goals
* Use the knowledge gained from earlier labs to implement an interrupt controller on a pipelined RV32I processor.
* Gain experience writing technical reports.

In the labs for this course, you have successfully built up the capability for a simple RV32I instruction set microprocessor.  We have not included the ability for the processor to handle external events, peripherals, or to handle any sort of errors.  Now we will extend your work to add __exception handling__.  You will add new instructions to the RV32I instruction, specifically the ```*CSR``` and ```mret``` instructions, and add a new set of rules for the Program Counter ```PC```.

Notice we will be using some of the Machine-mode instructions, which are located in the Privleged Instructions specifications.

# Requirements
Create a single-cycle and a pipelined RV32I processor that implements enough of the RISC-V ISA Specification <https://riscv.org/technical/specifications/> to execute the programs supplied with this assignment, and add the following features:

1. (2 marks) Add all six (6) of the instructions in the ```Zicsr``` extension.
  * Implementation will be for one mark for single-cycle ISA, and one mark for 2-step pipelined ISA.  If you run out of time, submit only the single-cycle version for partial credit.

2. (1 mark) Add a set of 32-bit registers, known as Control-and-Status Registers (CSRs), only accessible from the ```Zicsr``` instructions.  These will implement the following CSRs:
    * ```mepc``` Machine exception PC
    * ```mstatus``` Machine status (read only)
    * ```mie``` Machine interrupt enable
    * ```mtvec``` Machine trap vector
    * ```mip```  Machine interrupt pending
    * ```mcause``` Machine exception cause
    * ```mscratch``` Machine scratch register

1. (1 mark)  Implement the ```mret``` instruction, which will restore the state of the processor to whatever instruction was executing when the exception occurred.

1. (1 mark)  Modify the PC multiplexor and logic to support exceptions for the following:
    * illegal instruction traps (intr=0, cause=2)
    * external platform interrupt interrupt (intr=1,cause=11).

1. (5 marks) Report.  See below.

## Test files
The machine marked parts will consider correctness and performance.  In Docker, use the command ```make result FIRMWARE=filename.hex``` to test a single case, and use ```make allresults``` to run the whole test suite.

You are encouraged to extend the testsuites with your own files, and discuss in the report how thorough the coverage is.

The tutors will mark against the test files given, as well as additional files that are not part of the repository.  The additional tests will be similar to those given to you, but may change registers, timing, or add a few user instructions from the base RV32I you've been using.  _These will examine the completeness of your implementation, but are not designed to trick you--they are simple extensions of the given tests._

## Code format
The GitHub repository ```ass1-interrupts``` contains a skeleton file for the processor module.  You may use your own work from previous labs to fill in the processor operation.

Note you will have to connect external ports for some of the CSR bits for testing, and you must connect the external interrupt port input to test that an unexpected interrupt continues code as expected.

## Design Details
We have given in the skeleton code a specification for a CSR register.  Note the special use of bitwise read and write enables.  This should help the processor conform to the specific rules of the CSR instructions outlined in the ISA.  Read the rules carefully, as these have different consideration than the general purpose registers ```x0-x31```.

The ```MSTATUS``` register will contain only a single global interrupt enable (GIE) bit at position 0.  Setting this bit will enable interrupts, while clearing it will ignore all interrupts.  Setting all other bits have no effect and always read as zero.  Note that GIE and the appropriate bit in ```MIE``` register must _both_ be set to enable interrupts.

The ```MIE``` register will also contain only a single bit at position 11 (MEIE).  Setting this bit will enable the external interrupt only when the GIE is also set.

The ```MTVEC``` register will be write only and hard wired to the address 0x1000.  Writes are ignored.

The ```MIP``` register will contain a single bit at position 11 (MEIE), indicating if there is an external interrupt pending, meaning that the INTR port has been set for at least one cycle.  This bit is read-only, and cleared when the ```mret``` instruction is executed.  All other bits always read zero and writes have no effect on any bits.

The ```MSCRATCH``` register is a free 32-bit CSR.  It can be read or written to with the CSR instructions.

Up till this point, the ```ebreak``` instruction has been deemed "illegal", and use to stop the simulation.  To avoid problems with distinguishing truly illegal instructions from those meant to stop the code, you will need to develop a means of safely halting the processor that does not invoke the illegal trap.  Note that previous labs showed how to flag illegal instructions, and you can use this technique to invoke the Trap exception, with the appropriate ```mcause```.

## Reports
 * Your report should be a 4 page document explaining your design (appendices with no page limit can be included).
 *  Your report should be in [A4 IEEE format](https://www.ieee.org/conferences/publishing/templates.html) with the default font sizes, and organized under the following section headings: Introduction, Background, Architecture, Results, Discussion, Conclusion, References, Appendices.
 *  Your report should document the datapath design of all the major components, including a high-level description, a dataflow diagram, and specific implementation of the major subsystems.  This is a narrative description to as given to a fellow engineer, and not merely a copy of code.  _Your design should show that the SystemVerilog code follows the datapath design, not the other way around._
 *  Include a performance description which includes the number of cycles required to execute each program you test. You need to provide supporting evidence which can convince the reader that you have completed the design and it works via appendices containing code listings, simulations and log files. The appendices don't count in the page limit.
 * Discuss what hazards exist in the pipelined design, and how they are tested and mitigated
 * Comment on whether your result is a good one and what could be done to further improve performance.
 *  [Dennis et al.](https://ieeexplore.ieee.org/abstract/document/8303926) and [Miyazaki et al.](https://arxiv.org/abs/2002.03568) are two examples of well-written papers describing a RISC-V processor (you could following a similar style for your report). [Singh et al.](https://ieeexplore.ieee.org/document/9250850) is an example of a poorly written paper.
 *  You should assume that the reader is familiar computer architecture in general, but not necessarily the the RISC-V instruction set or your architecture. Write the report as an academic-style paper like the examples provided.
 *  If you don't finish the entire question, still report on your answer. Partial marks will be awarded.
 *  No extensions will be granted and penalty for a late submission is deduction of 5% of the maximum mark for each calendar day after the due date. After ten calendar days late, a mark of zero will be awarded.


# Submission
Your assignment should be submitted online as two separate files (a .pdf and  two .sv files) before the due date. Refer to Canvas for the rubric and submission instructions.
 * Report: a pdf report as described above.
 * Design:  System Verilog files containing your  processors, using the names ```singlecycle-interrupt.sv``` and ```nerv-interrupt.sv```.

# Background
Normally, a program will run on a microprocessor in the way that the compiler-generated assembly code describes it; that is, the Program Counter ```PC``` will increment by four after each instruction, unless chaged by Jump or Branch instructions.  In this way, the compiler completely predicts all the code paths.

## Unpredicatable code paths
In a practical processor, two situations can occur where the processor executes code that was not specified by the compiler: __traps__ occur when an instruction does not execute the way the compiler intended, and __interrupts__ occur when something entirely outside the program requires the code path to change.  Collectively, traps and interrupts are called __processor exceptions__.  _Note: do not confuse processor exceptions with Python or C++ exceptions._

The key difference between traps and interrupts is the source of the change:  traps are triggered by an instruction, while interrupts are some other event.  This is important in a pipelined processor, since the interrupt can occur in any of the pipeline stages, while a trap generally occurs at the Execute (EX) or Memory (MEM) phases.  In contrast, a trap is the result of an instruction somewhere in the pipeline, so the micro-architecture has some control of the problem, even if the compiler did not.

## Exception handling
An important aspect of exception handling is the ability for the processor to resume execution after the exception occurs.

For example, an interrupt may occur in an operating system to signal the handling of a driver event, like the arrival of an Ethernet packet.  The processor may have been in the middle of user code, and must stop that program, run the driver code, then resume back at the user program.  The user program must run as if it had never been interrupted.

An example of a trap exception might be where the program executes an illegal (or unimplemented) instruction, or where a computation results in an illegal state, such as divide-by-zero.  In this case, perhaps the user code can recover (as is the case with software exceptions such as C++ ```try/except``` blocks).  In other cases, the user program is terminated with an error message like ```segmentation fault```.

## RISC-V Implementation
In the RISC-V ISA, exceptions invoke a _priviliged_ instruction mode.  The reason is usually exception handling is performed by an OS kernel, and so elevated privileges are allowed.  We will use the most powerful privileged mode, known as __machine mode__ (M).

An exception is handled similarly to a ```JALR``` or ```JAL``` instruction, in that the ```PC``` is saved and the processor jumps to a new location.  Upon completion of the exception handler, control is returned to the user program by jumping back to the saved location.

Unlike ```JALR/JALR```, however, exceptions do not save the ```PC``` to a normal register, like ```x1```.  Since the compliler didn't know an exception would occur, changing any of the normal registers would trash their contents, possibly making continued operation impossible.  Instead, a special register, described below, is used.

## Control and Status Registers (CSRs)
The [RISC-V Privileged Instruction Set Architecture](https://docs.riscv.org/reference/isa/v20260120/priv/priv-csrs.html) defines a number of registers that are not part of the RV32I we have been implementing.  Unlike the ```x0-x31``` general-purpose registers we normally use, the CSRs cannot be accessed as part of arithmetic, logic, or other calculations.

Some processor ISAs may access CSRs through memory using Load and Store instructions.  In RISC-V, CSRs are accessed through special instructions in the [_Zicsr_](https://docs.riscv.org/reference/isa/v20260120/unpriv/zicsr.html) extension.  These six instructions allow one to copy values in CSRs into normal registers, and to make changes.  The instructions are shown in [section 6.1](https://docs.riscv.org/reference/isa/v20260120/unpriv/zicsr.html) of the Unprivileged ISA.

Each CSR is given a numeric ID, as shown in [table 7, section 2.2.4](https://docs.riscv.org/reference/isa/v20260120/priv/machine.html) of the Privileged ISA.  Note that _access_ to the CSRs is what makes them priviliged or not, and there are a number of CSRs with different levels of privilege.  We will only work within the Machine (M) privilege, the highest level.  There is no need to implement privilege switching in this assignment.

## CSRs for Exception Handling
For exception handling, the CSRs required are:
* ```mepc``` Machine exception PC
* ```mstatus``` Machine status
* ```mie``` Machine interrupt enable
* ```mtvec``` Machine trap vector
* ```mip```  Machine interrupt pending
* ```mcause``` Machine exception cause


### ```MEPC``` register
The ```mepc``` is the location of the return address, that is the place where the exception must return to.  For an interrupt, ```mepc``` indicates the instruction that was aborted when the interrupt occurs, since the aborted instruction must be re-run.  For a trap, ```mepc``` indicates the _next_ instruction, since traps occur for illegal states and therefore are skipped over.  When the ```mret``` instruction is executed, the ```PC``` is restored to this value.

### ```MSTATUS``` register
The ```mstatus``` register contains the global interrupt enable bit.  This single bit takes priority over the bits in the ```mie``` register, where there may be many sources.

### ```MIE``` register
The ```mie``` register has bits that enable the individual interrupts.  An interrupt that is disabled is "masked out" (usually), and the user code will not stop.  Otherwise, user code is stopped, and the processor jumps to the ```mtvec``` address.  Trap exceptions usually cannot be disabled, because they are from invalid instructions.  Although MIE and GIE may seem redundant, in a larger processor there will likely be many interrupt sources.

### ```MTVEC``` register
The ```mtvec``` register contains the value of the ```PC``` is to take when the exception occurs.  There are two possible modes: individualised handlers, and shared handlers.  We will use the BASE mode, meaning all traps take the same address.  We will use a hard-coded value of ```0x1000```, so ```mtvec``` will be read-only, however good programming practice is to make this a SystemVerilog parameter or constant.

### ```MIP``` register
The ```mip``` register is read-only, and contains bits signalling an interrupt is pending.  If the interrupt is disabled in ```mie```, the pending bit will indicate that it needs to be handled, but the processor will not stop the user code automatically.  When the ```mret``` instruction is executed, the bit will be cleared.

### ```MCAUSE``` register
The ```mcause``` register is used when the ```mtvec``` is shared (BASE) mode to determine what caused the exception.  That way a single handler with, say if/then/else logic, can handle all exceptions in one block of code.

## ```MRET``` instruction
A [privileged instruction](https://docs.riscv.org/reference/isa/v20260120/priv/machine.html#otherpriv), ```mret``` returns control back to the user code.  This instruction will clear the appropriate ```mip``` bit (for interrupts), and sets the ```mstatus``` bit back to user mode.  It will return control back to the user code, using the ```PC``` value stored in ```mepc```.

## ```INTR``` pin
A hardware pin, ```intr``` has been added to the skeleton code.  This port will be stimulated for 1 cycle to trigger an external interrupt, with ```1``` indicating the activation.  This will be synchronous to the clock.