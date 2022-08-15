.section .text
.global _start
_start:
    # these first three instructions are I-type
    xori x1, zero, 0xe1
    addi x2, x1, 11
    ori x3, zero, 0x36

    # remaining instruction types
    slli x2, x2, 16
    slli x10, x1, 24
    add x10, x10, x2
    slli x3, x3, 8
    addi x3, x3, 8
    add x10, x3, x10

    ebreak
