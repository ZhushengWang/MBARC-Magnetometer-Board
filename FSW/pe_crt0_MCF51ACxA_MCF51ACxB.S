/* 
pe_crt0_MCF51ACxA_MCF51ACxB                                                   
GNU m68k-elf startup code for the ColdFire MCF51AC256A/B and MCF51AC128A    		
Modified 2008, P&E Microcomputer Systems, Inc.
Visit us at http://www.pemicro.com 
*/

/*
 * crt0.S -- startup file for m68k-elf
 *
 * Copyright (c) 1995, 1996, 1998 Cygnus Support
 *
 * The authors hereby grant permission to use, copy, modify, distribute,
 * and license this software and its documentation for any purpose, provided
 * that existing copyright notices are retained in all copies and that this
 * notice is included verbatim in any distributions. No written agreement,
 * license, or royalty fee is required for any of the authorized uses.
 * Modifications to this software may be copyrighted by their authors
 * and need not follow the licensing terms described here, provided that
 * the new terms are clearly indicated on the first page of each file where
 * they apply.
 */

#include "asm.h"
	.title "crt0.S for m68k-elf"

/*
 * Define an empty environment.
 */
	.data
	.align 2
SYM (environ):
	.long 0
 	.align	2
	.text
        
/*
 * These symbols are defined in C code
 */
	.extern SYM (main)
	.extern SYM (memory_init_hook)
	.extern SYM (hardware_init_hook)
	.extern SYM (software_init_hook)
	.extern SYM (atexit)
	.extern SYM (__do_global_dtors)
        
/* 
 * These values are set in the linker script
 */
	.extern __application_load_addr
	.extern __application_run_addr
	.extern __global_data_load_addr
	.extern __global_data_run_addr
                
	.extern copy_data_end
	.extern copy_text_end
	.extern __bss_start
	.extern __bss_end 
 
	.extern VBR
	.extern __stack_start
        
/************************************************/                
/* Place startup code in output section .pecrt0 */   
        .section .pecrt0,"ax",@progbits
/************************************************/                
 
	.global SYM (start)
	.global TEMP_STACK

SYM (start):

	/* Disable watchdog */
	/* Set SOPT1 */
	/* move.l  #0x0,d0 */
	/* move.l #0xFFFF9802,a0 */
	/* move.b  d0,(a0) */
     
	/* Set VBR */
        movel #VBR,a0 
        movec a0,#0x801                  
        
	/*Set temporary stack to top (high address) of SRAM */
	.set TEMP_STACK,0xBEDFF0  
	movel #TEMP_STACK,sp                 
	link a6, IMM(-8)         

	/* Call configuration routine in hooks.c */
	lea	SYM (memory_init_hook), a0
	cmpl	IMM(0),a0
	jbeq	SKIP_HOOK_1

	/* Adjust subroutine address if needed */        
	lea     __application_load_addr,a2
	lea     __application_run_addr,a3
	subal    a2,a3
	subal    a3,a0
	jsr     (a0)

SKIP_HOOK_1:        
        
	//Set stack location, defined in linker script
	movel #__stack_start,sp             
	link a6, IMM(-8) 
                                         
/*
 * Copy .data in ROM to RAM if necessary
 * Assume that DATA and BSS sizes are multiples of 4.
 * (put an . = ALIGN(0x04) in your linker script to ensure this)
 */
	lea	__global_data_run_addr,a0      | Get start of .data (RAM?) 
	lea	__global_data_load_addr,a2	| Get start of .data (ROM?) 
	cmpl	a0,a2			| Are they the same?
	beq.s	NOCOPY			| Yes, no copy necessary
	lea	copy_data_end,a1	| Get end of .data in RAM
	bra.s	COPYLOOPTEST	        | Branch into copy loop
COPYLOOP:
	movel	a2@+,a0@+		| Copy word from ROM to RAM
COPYLOOPTEST:
	cmpl	a1,a0			| Done?
	bcs.s	COPYLOOP		| No, skip
NOCOPY:

/*
 * Copy .text in ROM to RAM if necessary
 */
	lea	__application_run_addr,a0      | Get start of .text (RAM?) 
	lea	__application_load_addr,a2	| Get start of .text (ROM?) 
	cmpl	a0,a2			| Are they the same?
	beq.s	NOCOPY2			| Yes, no copy necessary
	lea	copy_text_end,a1	| Get end of .text in RAM
	bra.s	COPYLOOPTEST2	        | Branch into copy loop
COPYLOOP2:
	movel	a2@+,a0@+		| Copy word from ROM to RAM
COPYLOOPTEST2:
	cmpl	a1,a0			| Done?
	bcs.s	COPYLOOP2		| No, skip
NOCOPY2:

/*
 * zero out the bss section.
 */
	lea	SYM(__bss_start), a0
	lea	SYM(__bss_end), a1
	clrl	d0			| Value to set
	bra.s	ZEROLOOPTEST		| Branch into clear loop
ZEROLOOP:
	movel	d0,a0@+			| Clear a word
ZEROLOOPTEST:
	cmpl	a1,a0			| Done?
	bcs.s	ZEROLOOP		| No, skip
	
/*
 * Call configuration routines 
 */

	lea	SYM (hardware_init_hook), a0
	cmpl	IMM(0),a0
	jbeq    SKIP_HOOK_2
	jsr     (a0)

SKIP_HOOK_2:

	lea	SYM (software_init_hook), a0
	cmpl	IMM(0),a0
	jbeq    SKIP_HOOK_3
	jsr     (a0)

SKIP_HOOK_3:

	jsr	SYM (main)

