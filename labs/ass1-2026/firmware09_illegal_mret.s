/**
 * @brief Test program to illegal instruction trap with recovery
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
    nop;                            /* addr 0x00 */
    nop;                            /* addr 0x04 */
    nop;                            /* addr 0x08 */
    addi x1, x0, 20                 /* addr 0x0c */
    fence;      /* unimplemented */ /* addr 0x10 */
    addi x1, x0, 25                 /* addr 0x14 */
    nop;                            /* addr 0x18 */
    nop;                            /* addr 0x1c */
    ebreak;                         /* addr 0x20 */



/* Interrupt/Trap Vector (see sections.lds file for details) */
.section mtvec_section ,"ax",@progbits   /* this H0 section is "allocatiable, program code, executable" */

.global _mtvec

_mtvec:
    nop;                /* addr 0x1000 */
    mret;               /* addr 0x1004 */
    nop;                /* addr 0x1008 */
    ebreak;             /* addr 0x100C */



/* expected result:
    expect h0:pc = 0x24 (PC after ebreak)
    expect h0:x1 = 25 (PC after recovery)
    expect h0:mcause = 0x00000002 (int=0,cause=2)
    expect h0:mepc = 0x14 (return address after )
*/