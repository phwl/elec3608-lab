/**
 * @brief Test program MTVEC write
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
    addi x1, x0, 100;       /* copy value to x1 */
    csrrw x1, mtvec, x1;    /* Write MTVEC register with X1.  No read due to zero bits of x0 */
    nop;
    ebreak

/* expected result:
    expect h0:x0 = 0x0
    expect h0:x1 = 0x1000 (mtvec should not change & readback should show this)
    expect h0:mtvec = 0x1000 (ensure mtvec itself didn't change)
*/