/* 
pe_hooks.c                                                      
The code in the file pe_crt0*.S calls this initialization code 
(C)opyright 2008, P&E Microcomputer Systems, Inc.
Visit us at http://www.pemicro.com 
*/

  
/* Linker script places this code in                            */ 
/*        output linker section .pecrt0                         */
void memory_init_hook(void) __attribute__ ((section (".pecrt0")));
void hardware_init_hook(void) __attribute__ ((section (".pecrt0")));
void software_init_hook(void) __attribute__ ((section (".pecrt0")));

void memory_init_hook(void) {  

/* This example uses internal RAM and internal Flash. */      

}


void hardware_init_hook(void) {
  ;
}


void software_init_hook(void) {
  ;
}
