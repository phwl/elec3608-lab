.section .text
.global _start
_start:
    # these first three instructions are I-type
    addi x10, zero, 0xd0
    addi x2, zero, 2
loop:
    addi x2, x2, -1
    addi x10,x10, 1
    bne x2, zero, loop
    ebreak
