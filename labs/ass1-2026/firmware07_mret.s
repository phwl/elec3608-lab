/**
 * @brief Test program to mret instruction
 * @course University of Sydney ELEC3608 2026 Assignment 1
 * @author Rich Rademacher
 *
 */




/* Special note: see Unprivileged ISR pg 49, indicating the assembly writers created their own
   instruction, that is not consistent with the ISA */
.section .text
.global main
.global _start
_start:
    addi x1, x0, 0x8;       /* enable MIE bit */    /* addr 0x00 */
    csrrs x0, mstatus, x1;                          /* addr 0x04 */
    addi x1, x0, 1;                                 /* addr 0x08 */
    slli x1, x1, 11;       /* enable MEIE bit */    /* addr 0x0c */
    csrrs x0, mie, x1;                              /* addr 0x10 */
    nop;                                            /* addr 0x14 */
    addi x4, x0, 50;                                /* addr 0x18 */
    nop;                                            /* addr 0x1c */
loop:
    addi x4, x4, -1;                                /* addr 0x20 */
    bne  x4, x0, loop;                              /* addr 0x24 */
    nop;                                            /* addr 0x28 */
    ebreak;                                         /* addr 0x2c */



/* Interrupt/Trap Vector (see sections.lds file for details) */
.section mtvec_section ,"ax",@progbits   /* this H0 section is "allocatiable, program code, executable" */

.global _mtvec

_mtvec:
    nop;
    addi x30, x0, 10;   /* addr 0x1000  (proof we got here!) */
    nop;                /* addr 0x1004 */
    nop;                /* addr 0x1008 */
    nop;                /* addr 0x100c */
    nop;                /* addr 0x1010 */
    nop;                /* addr 0x1014 */
    nop;                /* addr 0x1018 */
    nop;                /* addr 0x101c */
    nop;                /* addr 0x1020 */
    nop;                /* addr 0x1024 */
    nop;                /* addr 0x1028 */
    mret;               /* addr 0x102c */
    nop;                /* addr 0x1030 */

    ebreak;             /* addr 0x1034 */



/* expected result:
    expect h0:pc = 0x30 (PC after ebreak)
    expect h0:x4 = 0x0 (count)
    expect h0:x30 = 10 (proof)
    expect h0:mcause = 0x8000000B (int=1,cause=16)
    expect h0:mip = 0x000 (external interrupt cleared)
*/