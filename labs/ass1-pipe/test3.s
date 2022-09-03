.section .text
.global _start
_start:
    j main

    # a simple subroutine that increments x4
inc:    
    addi x4, x4, 1
    jalr x0, 0(ra)

main:
    # these first three instructions are I-type
    addi x4, zero, 1
    addi x10, zero, 0
    addi x2, zero, 19
loop:
    add x10, x4, x10
    jal ra, inc
    addi x2, x2, -1
    bge x2, zero, loop

    ebreak
