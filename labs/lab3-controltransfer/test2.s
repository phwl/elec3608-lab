.section .text
.global _start
_start:
    # these first three instructions are I-type
    addi x4, zero, 1
    addi x10, zero, 0
    addi x2, zero, 20
loop:
    add x10, x4, x10
    addi x4, x4, 1
    addi x2, x2, -1
    bne x2, zero, loop
    
    ebreak
