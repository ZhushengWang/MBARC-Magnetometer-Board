/*
pe_vectors_MCF51ACx.c
Vector Table and ISRs
(C)opyright 2008, P&E Microcomputer Systems, Inc.
Visit us at http://www.pemicro.com 
*/

#include "includes.h"


extern CDH_IO_t *cdhio;

uint8 yIntCnt=0;

//ISR runs every 250ms
static void __attribute__ ((interrupt)) 
QB50_Isr() 
{
  if (cdhio->INT_CTL & 0x01)  //Check for INT0 (TIMER 1)
  {
    cdhio->CONTROL1 = cdhio->CONTROL1 ^ CTL1_CDH_LED2;  //Toggle the LED
    yIntCnt++;
    Set250msFlag();
    if ((yIntCnt % 4) == 0)
    {
      increment_time();
      OP_SetTimecodeFromISR(get_time());
      SetOneHzFlag();     
    }
    
    cdhio->INT_CTL = 0x01;  //End the interrupt
  }
}

static void __attribute__ ((interrupt))
AccessErrorIsr()
{
  ;
}

static void __attribute__ ((interrupt))
AddressErrorIsr()
{
  ;
}

static void __attribute__ ((interrupt))
IllegalInstructionIsr()
{
  ;
}

static void __attribute__ ((interrupt))
UnhandledInterrupt()
{
  ;
}

static void __attribute__ ((interrupt))
PrivilegeViolationIsr()
{
  ;
}

static void __attribute__ ((interrupt))
TraceIsr()
{
  ;
}

static void __attribute__ ((interrupt))
UnimpOpcodeAIsr()
{
  ;
}

static void __attribute__ ((interrupt))
UnimpOpcodeFIsr()
{
  ;
}

static void __attribute__ ((interrupt))
DebugIsr()
{
  ;
}

static void __attribute__ ((interrupt))
FormatErrorIsr()
{
  ;
}

static void __attribute__ ((interrupt))
SpuriousInterrupt()
{
  ;
}

static void __attribute__ ((interrupt)) 
TrapIsr() 
{
  ;
}	 

static void __attribute__ ((interrupt)) 
UnsupportedInstruction() 
{
  ;
}	 

static void __attribute__ ((interrupt))   
IRQpinIsr() 
{
  ;
}


static void __attribute__ ((interrupt)) 
MCGlockIsr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
FTM1Ch0Isr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
FTM1Ch1Isr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
FTM1Ch2Isr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
FTM1Ch3Isr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
FTM1Ch4Isr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
FTM1Ch5Isr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
FTM1OvflIsr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
FTM2Ch0Isr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
FTM2Ch1Isr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
FTM2Ch2Isr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
FTM2Ch3Isr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
FTM2Ch4Isr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
FTM2Ch5Isr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
FTM2OvflIsr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
SPI1Isr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
SCI1errIsr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
SCI1rxIsr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
SCI1txIsr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
SCI2errIsr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
SCI2rxIsr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
SCI2txIsr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
KBI1Isr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
ADCIsr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
IICisr() 
{

}

static void __attribute__ ((interrupt)) 
RTIisr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
TPM3Ch0Isr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
TPM3Ch1Isr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
Level7SoftwareIsr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
Level6SoftwareIsr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
Level5SoftwareIsr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
Level4SoftwareIsr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
Level3SoftwareIsr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
Level2SoftwareIsr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
Level1SoftwareIsr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
TPM3OvflIsr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
SPI2Isr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
FTM1FaultIsr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
FTM2FaultIsr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
MSCANwakeupIsr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
MSCANerrorsIsr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
MSCANrxIsr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
MSCANtxIsr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
ACMP1Isr() 
{
  ;
}

static void __attribute__ ((interrupt)) 
ACMP2Isr() 
{
  ;
}


/* Vector Table */
const static volatile unsigned long pe_vector_table[254] __attribute__ ((section (".pevector"))) = 
{
/* The linker scipt specifies the initial SP and PC values
   See the linker section ".pevector"
   We omit the first two vector table entries here */
(long) &AccessErrorIsr,  //vector 2
(long) &AddressErrorIsr, 
(long) &IllegalInstructionIsr,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &PrivilegeViolationIsr,
(long) &TraceIsr,
(long) &UnimpOpcodeAIsr,  //vector 10
(long) &UnimpOpcodeFIsr,
(long) &DebugIsr,  
(long) &UnhandledInterrupt,
(long) &FormatErrorIsr,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  //vector 20
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,
(long) &SpuriousInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  //vector 30
(long) &UnhandledInterrupt,
(long) &TrapIsr,  
(long) &TrapIsr,
(long) &TrapIsr,
(long) &TrapIsr,
(long) &TrapIsr,
(long) &TrapIsr,
(long) &TrapIsr,
(long) &TrapIsr,
(long) &TrapIsr,  //vector 40
(long) &TrapIsr,
(long) &TrapIsr,  
(long) &TrapIsr,
(long) &TrapIsr,
(long) &TrapIsr,
(long) &TrapIsr,
(long) &TrapIsr,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  //vector 50
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  //vector 60
(long) &UnsupportedInstruction,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,
(long) &IRQpinIsr,  //MCF51ACx interrupt sources begin here
(long) &QB50_Isr,
(long) &MCGlockIsr,  
(long) &FTM1Ch0Isr,
(long) &FTM1Ch1Isr,
(long) &FTM1Ch2Isr,
(long) &FTM1Ch3Isr,  //vector 70
(long) &FTM1Ch4Isr,
(long) &FTM1Ch5Isr,
(long) &FTM1OvflIsr,
(long) &FTM2Ch0Isr,
(long) &FTM2Ch1Isr,
(long) &FTM2Ch2Isr,
(long) &FTM2Ch3Isr,
(long) &FTM2Ch4Isr,  
(long) &FTM2Ch5Isr,
(long) &FTM2OvflIsr,  //vector 80
(long) &SPI1Isr,
(long) &SCI1errIsr,
(long) &SCI1rxIsr,
(long) &SCI1txIsr,
(long) &SCI2errIsr,
(long) &SCI2rxIsr,
(long) &SCI2txIsr,
(long) &KBI1Isr,
(long) &ADCIsr,
(long) &IICisr,  //vector 90
(long) &RTIisr,  
(long) &TPM3Ch0Isr,
(long) &TPM3Ch1Isr,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  //vector 100
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt, 
(long) &Level7SoftwareIsr,
(long) &Level6SoftwareIsr,
(long) &Level5SoftwareIsr,
(long) &Level4SoftwareIsr,
(long) &Level3SoftwareIsr,
(long) &Level2SoftwareIsr,
(long) &Level1SoftwareIsr,
(long) &TPM3OvflIsr,  //vector 110
(long) &SPI2Isr,
(long) &FTM1FaultIsr,  
(long) &FTM2FaultIsr,
(long) &MSCANwakeupIsr,
(long) &MSCANerrorsIsr,
(long) &MSCANrxIsr,
(long) &MSCANtxIsr,
(long) &ACMP1Isr,
(long) &ACMP2Isr,  
(long) &UnhandledInterrupt,  //vector 120
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,  //vector 130
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,  //vector 140
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,  //vector 150
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,  //vector 160
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,  //vector 170
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,  //vector 180
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,  //vector 190
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,  //vector 200
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,  //vector 210
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,  //vector 220
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,  //vector 230
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,  //vector 240
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,  //vector 250
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,  
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt,
(long) &UnhandledInterrupt

};

