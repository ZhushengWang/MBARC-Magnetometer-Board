/*
 pe_MCF51ACxA_MCF51ACxB.ld
 GNU m68k-elf Linker Script for the ColdFire MCF51AC256A/B and MCF51AC128A
 (C)opyright 2008, P&E Microcomputer Systems, Inc.
 Visit us at http://www.pemicro.com 
 */

 
/* Set the address of executable code at load time */
__application_load_addr = 0x00800000;  


/* Address of executable code at run time */
/* __application_run_addr = 0x00000000;*/ 
/* Optionally define this variable.
   If defined, startup code will copy 
   executable code and variables to this location.
   Set to 1MB boundary. */  


/* Location of global & static variables at run time */
/*__global_data_run_addr = 0x00800000;*/
/* Optionally define this variable.  
   If defined, startup code will copy 
   global/static variables to this location */  


/* Set the location of stack */
__stack_start = 0x00BEDFF0;

    
/* Location of heap */
/* __heap_start = 0x00804000; */   
/* Optionally define this variable.  
   If not defined, the default heap 
   location is after .bss section.  */
 
 
/* Flash module nonvolatile registers */
BACKDOORKEY03_NVR = 0x00000000;   
BACKDOORKEY47_NVR = 0x00000000;
NVPROT_NVR = 0xFF;
NVOPT_NVR = 0x00;
 

/*************************************************************************
 ***** DO NOT CHANGE BELOW THIS LINE *****
 *************************************************************************/ 
  
OUTPUT_ARCH(m68k)
SEARCH_DIR(.)
GROUP(-ldbug -lc -lgcc -lm -lstdc++)
__DYNAMIC  =  0;
 
/* ELF program headers */
PHDRS
{
 load1_phdr PT_LOAD FLAGS (0x7) ;
 load2_phdr PT_LOAD FLAGS (0x7) ;
 load3_phdr PT_LOAD FLAGS (0x7) ;
 load4_phdr PT_LOAD FLAGS (0x7) ;
 load5_phdr PT_LOAD FLAGS (0x7) ;
 load6_phdr PT_LOAD FLAGS (0x7) ;
}

/* Set the entry point to after the vector table load address */
start = ((__application_load_addr)+(0x420));

/* Set the vector table address */
VBR = ( DEFINED(__application_run_addr) ? __application_run_addr : __application_load_addr );

PROVIDE (memory_init_hook = 0); 
PROVIDE (hardware_init_hook = 0);
PROVIDE (software_init_hook = 0);
PROVIDE (_memory_init_hook = 0); 
PROVIDE (_hardware_init_hook = 0);
PROVIDE (_software_init_hook = 0);

SECTIONS
{
  /* Vector table */
  .pevector ( DEFINED(__application_run_addr) ? __application_run_addr : __application_load_addr ) : AT (__application_load_addr) 
  {
    LONG(__stack_start);
    LONG((__application_load_addr)+(0x420));
    *(.pevector)    
    PEFILL = .;
  } :load1_phdr

  NEXT_LOAD_ADDR = (LOADADDR(.pevector)+(0x400));
  NEXT_RUN_ADDR = (ADDR(.pevector)+(0x400));  

  /* Flash module nonvolatile registers */
  .pecfmconfig (NEXT_RUN_ADDR) : AT (NEXT_LOAD_ADDR) 
  { 
    LONG(BACKDOORKEY03_NVR);
    LONG(BACKDOORKEY47_NVR);
    . = . + 0x4;
    . = . + 0x1;
    BYTE(NVPROT_NVR);
    . = . + 0x1;
    BYTE(NVOPT_NVR);
    . = . + 0x10;
  } :load2_phdr      
    
  NEXT_LOAD_ADDR = ((NEXT_LOAD_ADDR)+SIZEOF(.pecfmconfig));
  NEXT_RUN_ADDR = ((NEXT_RUN_ADDR)+SIZEOF(.pecfmconfig));    
    
  /* CRT0 Startup Code */
  .pecrt0 (NEXT_RUN_ADDR) : AT (NEXT_LOAD_ADDR) 
  { 
    . = ALIGN (16);
    *(.pecrt0)
    PEFILL = .;
    . = ALIGN(16);
  } :load3_phdr      
    
  NEXT_LOAD_ADDR = ((NEXT_LOAD_ADDR)+SIZEOF(.pecrt0));
  NEXT_RUN_ADDR = ((NEXT_RUN_ADDR)+SIZEOF(.pecrt0)); 
    
  .text (NEXT_RUN_ADDR) : AT (NEXT_LOAD_ADDR) 
  {
    . = ALIGN (16);
    *(.text)
    . = ALIGN (16);

    *(.eh_frame)
    . = ALIGN (16);

    *(.gnu.linkonce.t.*) 

    . = ALIGN(0x4);
     __CTOR_LIST__ = .;
    ___CTOR_LIST__ = .;
    LONG((__CTOR_END__ - __CTOR_LIST__) / 4 - 2)
    *(.ctors)
    LONG(0)
    __CTOR_END__ = .;
    __DTOR_LIST__ = .;
    ___DTOR_LIST__ = .;
    LONG((__DTOR_END__ - __DTOR_LIST__) / 4 - 2)
    *(.dtors)
     LONG(0)
    __DTOR_END__ = .;
    *(.rodata)
    *(.gcc_except_table) 

    . = ALIGN(0x4);
    __INIT_SECTION__ = . ;
    LONG (0x4e560000)	/* linkw %fp,#0 */
    *(.init)
    SHORT (0x4e5e)	/* unlk %fp */
    SHORT (0x4e75)	/* rts */

    . = ALIGN(0x4);
    __FINI_SECTION__ = . ;
    LONG (0x4e560000)	/* linkw %fp,#0 */
    *(.fini)
    SHORT (0x4e5e)	/* unlk %fp */
    SHORT (0x4e75)	/* rts */

    *(.lit)
    . = ALIGN(16);
    _etext = .;
    etext = .;
    copy_text_end = .;
  } :load4_phdr  
  
  
  NEXT_LOAD_ADDR = ((NEXT_LOAD_ADDR)+SIZEOF(.text));
  NEXT_RUN_ADDR = ((NEXT_RUN_ADDR)+SIZEOF(.text));   
  
  __global_data_load_addr = (NEXT_LOAD_ADDR);    
  __global_data_run_addr = DEFINED(__global_data_run_addr) ? __global_data_run_addr : ( DEFINED(__application_run_addr) ? (NEXT_RUN_ADDR) : (NEXT_LOAD_ADDR) );
  
  .data (__global_data_run_addr) : AT (__global_data_load_addr)
  {
    . = ALIGN(16);
    copy_start = .;
    *(.shdata)
    *(.data)
    *(.gnu.linkonce.d.*)
    . = ALIGN (16);
    _edata = .;
    copy_data_end = .;
  } :load5_phdr  
  
  /* .data section is contiguous with .bss section */
  
  .bss (NOLOAD) :
  {
    . = ALIGN(16);
    __bss_start = . ;
    *(.shbss)
    *(.bss)
    *(COMMON)
    _end =  ALIGN (16);
    __end = _end;
    __bss_end = _end;
  } :load6_phdr
  
  _end = DEFINED (__heap_start) ? __heap_start : _end;
  __end = _end;
  
  /* Debug information */  
  
  .stab 0 (NOLOAD) :
  {
    *(.stab)
  }

  .stabstr 0 (NOLOAD) :
  {
    *(.stabstr)
  }
  
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }  

  __application_run_addr = ADDR(.pevector); 

}
  

