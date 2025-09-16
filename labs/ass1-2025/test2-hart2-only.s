/*
 *  NERV -- Naive Educational RISC-V Processor
 *
 *  Copyright (C) 2020  Claire Xenia Wolf <claire@yosyshq.com>
 *
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

/**
 * @brief Hart0: Do nothing on this hart
 * @author Rich Rademacher
 */

.section .text_H0,"ax",@progbits   /* this H0 section is "allocatiable, program code, executable" */
.global main
.global _start
_start:
    nop
    nop
    ebreak

/**
 * @brief Hart1 attempts to get a single LR/SC variable from memory
 */
.section .text_H1,"ax",@progbits   /* this H1 section is "allocatiable, program code, executable" */
.global _start1
_start1:
    addi x3, zero, 1200  /* memory address 0x1200 */
    addi x5, zero, -12   /* dummy result...this should always change after SC.W */ 
    addi x4, zero, 0xc1  /* new value to put in memory, 'core1' */
    lr.w x0, (x3)   
    sc.w x5, x4, (x3) 
    lw x6, (x3)           /* read what is actually in memory */
    ebreak

/* expected result: 
    expect h1:x3 = 1200
    expect h1:x4 = 0xc1
    expect h1:x6 = 0xc1
*/
