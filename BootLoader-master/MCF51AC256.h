
/***************************************************
File   : MCF51AC256.h
Purpose: Register Address Definition
Version: 0.1
Date   : 11/24/2008
Note   :
**************************************************/

#ifndef _MCF51AC256_H_
#define _MCF51AC256_H_
typedef unsigned char uint8;

/*************************************************
Ports A-F Data and Direction
*************************************************/
#define PTAD_REG                  0xFFFF8000
#define PTAD_SET_DATA_REG(DATA)   *((volatile uint8 *)(PTAD_REG)) = (DATA)
#define PTAD_GET_DATA_REG()       *((volatile uint8 *)(PTAD_REG))
#define PTADD_REG                 0xFFFF8001
#define PTADD_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTADD_REG)) = (DATA)
#define PTADD_GET_DATA_REG()      *((volatile uint8 *)(PTADD_REG))
#define PTBD_REG                  0xFFFF8002
#define PTBD_SET_DATA_REG(DATA)   *((volatile uint8 *)(PTBD_REG)) = (DATA)
#define PTBD_GET_DATA_REG()       *((volatile uint8 *)(PTBD_REG))
#define PTBDD_REG                 0xFFFF8003
#define PTBDD_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTBDD_REG)) = (DATA)
#define PTBDD_GET_DATA_REG()      *((volatile uint8 *)(PTBDD_REG))
#define PTCD_REG                  0xFFFF8004
#define PTCD_SET_DATA_REG(DATA)   *((volatile uint8 *)(PTCD_REG)) = (DATA)
#define PTCD_GET_DATA_REG()       *((volatile uint8 *)(PTCD_REG))
#define PTCDD_REG                 0xFFFF8005
#define PTCDD_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTCDD_REG)) = (DATA)
#define PTCDD_GET_DATA_REG()      *((volatile uint8 *)(PTCDD_REG))
#define PTDD_REG                  0xFFFF8006
#define PTDD_SET_DATA_REG(DATA)   *((volatile uint8 *)(PTDD_REG)) = (DATA)
#define PTDD_GET_DATA_REG()       *((volatile uint8 *)(PTDD_REG))
#define PTDDD_REG                 0xFFFF8007
#define PTDDD_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTDDD_REG)) = (DATA)
#define PTDDD_GET_DATA_REG()      *((volatile uint8 *)(PTDDD_REG))
#define PTED_REG                  0xFFFF8008
#define PTED_SET_DATA_REG(DATA)   *((volatile uint8 *)(PTED_REG)) = (DATA)
#define PTED_GET_DATA_REG()       *((volatile uint8 *)(PTED_REG))
#define PTEDD_REG                 0xFFFF8009
#define PTEDD_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTEDD_REG)) = (DATA)
#define PTEDD_GET_DATA_REG()      *((volatile uint8 *)(PTEDD_REG))
#define PTFD_REG                  0xFFFF800A
#define PTFD_SET_DATA_REG(DATA)   *((volatile uint8 *)(PTFD_REG)) = (DATA)
#define PTFD_GET_DATA_REG()       *((volatile uint8 *)(PTFD_REG))
#define PTFDD_REG                 0xFFFF800B
#define PTFDD_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTFDD_REG)) = (DATA)
#define PTFDD_GET_DATA_REG()      *((volatile uint8 *)(PTFDD_REG))
#define PTGD_REG                  0xFFFF800C
#define PTGD_SET_DATA_REG(DATA)   *((volatile uint8 *)(PTGD_REG)) = (DATA)
#define PTGD_GET_DATA_REG()       *((volatile uint8 *)(PTGD_REG))
#define PTGDD_REG                 0xFFFF800D
#define PTGDD_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTGDD_REG)) = (DATA)
#define PTGDD_GET_DATA_REG()      *((volatile uint8 *)(PTGDD_REG))
#define PTHD_REG                  0xFFFF800E
#define PTHD_SET_DATA_REG(DATA)   *((volatile uint8 *)(PTHD_REG)) = (DATA)
#define PTHD_GET_DATA_REG()       *((volatile uint8 *)(PTHD_REG))
#define PTHDD_REG                 0xFFFF800F
#define PTHDD_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTHDD_REG)) = (DATA)
#define PTHDD_GET_DATA_REG()      *((volatile uint8 *)(PTHDD_REG))


/*************************************************
Analog To Digital Converter (ADC12V1)
*************************************************/
#define ADCSC1_REG                0xFFFF8010
#define ADCSC1_SET_DATA_REG(DATA) *((volatile uint8 *)(ADCSC1_REG)) = (DATA)
#define ADCSC1_GET_DATA_REG()     *((volatile uint8 *)(ADCSC1_REG))
#define ADCSC2_REG                0xFFFF8011
#define ADCSC2_SET_DATA_REG(DATA) *((volatile uint8 *)(ADCSC2_REG)) = (DATA)
#define ADCSC2_GET_DATA_REG()     *((volatile uint8 *)(ADCSC2_REG))
#define ADCRH_REG                 0xFFFF8012
#define ADCRH_SET_DATA_REG(DATA)  *((volatile uint8 *)(ADCRH_REG)) = (DATA)
#define ADCRH_GET_DATA_REG()      *((volatile uint8 *)(ADCRH_REG))
#define ADCRL_REG                 0xFFFF8013
#define ADCRL_SET_DATA_REG(DATA)  *((volatile uint8 *)(ADCRL_REG)) = (DATA)
#define ADCRL_GET_DATA_REG()      *((volatile uint8 *)(ADCRL_REG))
#define ADCCVH_REG                0xFFFF8014
#define ADCCVH_SET_DATA_REG(DATA) *((volatile uint8 *)(ADCCVH_REG)) = (DATA)
#define ADCCVH_GET_DATA_REG()     *((volatile uint8 *)(ADCCVH_REG))
#define ADCCVL_REG                0xFFFF8015
#define ADCCVL_SET_DATA_REG(DATA) *((volatile uint8 *)(ADCCVL_REG)) = (DATA)
#define ADCCVL_GET_DATA_REG()     *((volatile uint8 *)(ADCCVL_REG))
#define ADCCFG_REG                0xFFFF8016
#define ADCCFG_SET_DATA_REG(DATA) *((volatile uint8 *)(ADCCFG_REG)) = (DATA)
#define ADCCFG_GET_DATA_REG()     *((volatile uint8 *)(ADCCFG_REG))
#define APCTL1_REG                0xFFFF8017
#define APCTL1_SET_DATA_REG(DATA) *((volatile uint8 *)(APCTL1_REG)) = (DATA)
#define APCTL1_GET_DATA_REG()     *((volatile uint8 *)(APCTL1_REG))
#define APCTL2_REG                0xFFFF8018
#define APCTL2_SET_DATA_REG(DATA) *((volatile uint8 *)(APCTL2_REG)) = (DATA)
#define APCTL2_GET_DATA_REG()     *((volatile uint8 *)(APCTL2_REG))
#define APCTL3_REG                0xFFFF8019
#define APCTL3_SET_DATA_REG(DATA) *((volatile uint8 *)(APCTL3_REG)) = (DATA)
#define APCTL3_GET_DATA_REG()     *((volatile uint8 *)(APCTL3_REG))

/*************************************************
PORT J DATA AND DIRECTION
*************************************************/
#define PTJD_REG                  0xFFFF801A
#define PTJD_SET_DATA_REG(DATA)   *((volatile uint8 *)(PTJD_REG)) = (DATA)
#define PTJD_GET_DATA_REG()       *((volatile uint8 *)(PTJD_REG))
#define PTJDD_REG                 0xFFFF801B
#define PTJDD_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTJDD_REG)) = (DATA)
#define PTJDD_GET_DATA_REG()      *((volatile uint8 *)(PTJDD_REG))

/*************************************************
Interrupt Pin Request Status and Control
*************************************************/
#define IRQSC                     0xFFFF801C
#define IRQSC_SET_DATA_REG(DATA)  *((volatile uint8 *)(IRQSC_REG)) = (DATA)
#define IRQSC_GET_DATA_REG()      *((volatile uint8 *)(IRQSC_REG))


/*************************************************
Keyboard Interrupts 
*************************************************/
#define KBISC_REG                0xFFFF801E
#define KBISC_SET_DATA_REG(DATA) *((volatile uint8 *)(KBISC_REG)) = (DATA)
#define KBISC_GET_DATA_REG()     *((volatile uint8 *)(KBISC_REG))
#define KBIES_REG                0xFFFF801F
#define KBIES_SET_DATA_REG(DATA) *((volatile uint8 *)(KBIES_REG)) = (DATA)
#define KBIES_GET_DATA_REG()     *((volatile uint8 *)(KBIES_REG))

/*************************************************
Serial Communications Interface 1 (SCIV4)
*************************************************/
#define SCI1BDH_REG                  0xFFFF8038
#define SCI1BDH_SET_DATA_REG(DATA)   *((volatile uint8 *)(SCI1BDH_REG)) = (DATA)
#define SCI1BDH_GET_DATA_REG()       *((volatile uint8 *)(SCI1BDH_REG))
#define SCI1BDL_REG                  0xFFFF8039
#define SCI1BDL_SET_DATA_REG(DATA)   *((volatile uint8 *)(SCI1BDL_REG)) = (DATA)
#define SCI1BDL_GET_DATA_REG()       *((volatile uint8 *)(SCI1BDL_REG))
#define SCI1C1_REG                   0xFFFF803A
#define SCI1C1_SET_DATA_REG(DATA)    *((volatile uint8 *)(SCI1C1_REG)) = (DATA)
#define SCI1C1_GET_DATA_REG()        *((volatile uint8 *)(SCI1C1_REG))
#define SCI1C2_REG                   0xFFFF803B
#define SCI1C2_SET_DATA_REG(DATA)    *((volatile uint8 *)(SCI1C2_REG)) = (DATA)
#define SCI1C2_GET_DATA_REG()        *((volatile uint8 *)(SCI1C2_REG))
#define SCI1S1_REG                   0xFFFF803C
#define SCI1S1_SET_DATA_REG(DATA)    *((volatile uint8 *)(SCI1S1_REG)) = (DATA)
#define SCI1S1_GET_DATA_REG()        *((volatile uint8 *)(SCI1S1_REG))
#define SCI1S2_REG                   0xFFFF803D
#define SCI1S2_SET_DATA_REG(DATA)    *((volatile uint8 *)(SCI1S2_REG)) = (DATA)
#define SCI1S2_GET_DATA_REG()        *((volatile uint8 *)(SCI1S2_REG))
#define SCI1C3_REG                   0xFFFF803E
#define SCI1C3_SET_DATA_REG(DATA)    *((volatile uint8 *)(SCI1C3_REG)) = (DATA)
#define SCI1C3_GET_DATA_REG()        *((volatile uint8 *)(SCI1C3_REG))
#define SCI1D_REG                    0xFFFF803F
#define SCI1D_SET_DATA_REG(DATA)     *((volatile uint8 *)(SCI1D_REG)) = (DATA)
#define SCI1D_GET_DATA_REG()         *((volatile uint8 *)(SCI1D_REG))

/*************************************************
Serial Communications Interface 2 (SCIV4)
*************************************************/
#define SCI2BDH_REG                0xFFFF8040
#define SCI2BDH_SET_DATA_REG(DATA) *((volatile uint8 *)(SCI2BDH_REG)) = (DATA)
#define SCI2BDH_GET_DATA_REG()     *((volatile uint8 *)(SCI2BDH_REG))
#define SCI2BDL_REG                0xFFFF8041
#define SCI2BDL_SET_DATA_REG(DATA) *((volatile uint8 *)(SCI2BDL_REG)) = (DATA)
#define SCI2BDL_GET_DATA_REG()     *((volatile uint8 *)(SCI2BDL_REG))
#define SCI2C1_REG                 0xFFFF8042
#define SCI2C1_SET_DATA_REG(DATA)  *((volatile uint8 *)(SCI2C1_REG)) = (DATA)
#define SCI2C1_GET_DATA_REG()      *((volatile uint8 *)(SCI2C1_REG))
#define SCI2C2_REG                 0xFFFF8043
#define SCI2C2_SET_DATA_REG(DATA)  *((volatile uint8 *)(SCI2C2_REG)) = (DATA)
#define SCI2C2_GET_DATA_REG()      *((volatile uint8 *)(SCI2C2_REG))
#define SCI2S1_REG                 0xFFFF8044
#define SCI2S1_SET_DATA_REG(DATA)  *((volatile uint8 *)(SCI2S1_REG)) = (DATA)
#define SCI2S1_GET_DATA_REG()      *((volatile uint8 *)(SCI2S1_REG))
#define SCI2S2_REG                 0xFFFF8045
#define SCI2S2_SET_DATA_REG(DATA)  *((volatile uint8 *)(SCI2S2_REG)) = (DATA)
#define SCI2S2_GET_DATA_REG()      *((volatile uint8 *)(SCI2S2_REG))
#define SCI2C3_REG                 0xFFFF8046
#define SCI2C3_SET_DATA_REG(DATA)  *((volatile uint8 *)(SCI2C3_REG)) = (DATA)
#define SCI2C3_GET_DATA_REG()      *((volatile uint8 *)(SCI2C3_REG))
#define SCI2D_REG                  0xFFFF8047
#define SCI2D_SET_DATA_REG(DATA)   *((volatile uint8 *)(SCI2D_REG)) = (DATA)
#define SCI2D_GET_DATA_REG()       *((volatile uint8 *)(SCI2D_REG))

/*************************************************
Multipurpose Clock Generator (MCGV2)
*************************************************/
#define MCGC1_REG                    0xFFFF8048
#define MCGC1_SET_DATA_REG(DATA)     *((volatile uint8 *)(MCGC1_REG)) = (DATA)
#define MCGC1_GET_DATA_REG()         *((volatile uint8 *)(MCGC1_REG))
#define MCGC2_REG                    0xFFFF8049
#define MCGC2_SET_DATA_REG(DATA)     *((volatile uint8 *)(MCGC2_REG)) = (DATA)
#define MCGC2_GET_DATA_REG()         *((volatile uint8 *)(MCGC2_REG))
#define MCGTRM_REG                   0xFFFF804A
#define MCGTRM_SET_DATA_REG(DATA)    *((volatile uint8 *)(MCGTRM_REG)) = (DATA)
#define MCGTRM_GET_DATA_REG()        *((volatile uint8 *)(MCGTRM_REG))
#define MCGSC_REG                    0xFFFF804B
#define MCGSC_SET_DATA_REG(DATA)     *((volatile uint8 *)(MCGSC_REG)) = (DATA)
#define MCGSC_GET_DATA_REG()         *((volatile uint8 *)(MCGSC_REG))
#define MCGC3_REG                    0xFFFF804C
#define MCGC3_SET_DATA_REG(DATA)     *((volatile uint8 *)(MCGC3_REG)) = (DATA)
#define MCGC3_GET_DATA_REG()         *((volatile uint8 *)(MCGC3_REG))
#define MCGC4_REG                    0xFFFF804D
#define MCGC4_SET_DATA_REG(DATA)     *((volatile uint8 *)(MCGC4_REG)) = (DATA)
#define MCGC4_GET_DATA_REG()         *((volatile uint8 *)(MCGC4_REG))

/*************************************************
Serial Peripheral Interface 1 (SPIV3)
*************************************************/
#define SPI1C1_REG                   0xFFFF8050
#define SPI1C1_SET_DATA_REG(DATA)    *((volatile uint8 *)(SPI1C1_REG)) = (DATA)
#define SPI1C1_GET_DATA_REG()        *((volatile uint8 *)(SPI1C1_REG))
#define SPI1C2_REG                   0xFFFF8051
#define SPI1C2_SET_DATA_REG(DATA)    *((volatile uint8 *)(SPI1C2_REG)) = (DATA)
#define SPI1C2_GET_DATA_REG()        *((volatile uint8 *)(SPI1C2_REG))
#define SPI1BR_REG                   0xFFFF8052
#define SPI1BR_SET_DATA_REG(DATA)    *((volatile uint8 *)(SPI1BR_REG)) = (DATA)
#define SPI1BR_GET_DATA_REG()        *((volatile uint8 *)(SPI1BR_REG))
#define SPI1S_REG                    0xFFFF8053
#define SPI1S_SET_DATA_REG(DATA)     *((volatile uint8 *)(SPI1S_REG)) = (DATA)
#define SPI1S_GET_DATA_REG()         *((volatile uint8 *)(SPI1S_REG))
#define SPI1D_REG                    0xFFFF8055
#define SPI1D_SET_DATA_REG(DATA)     *((volatile uint8 *)(SPI1D_REG)) = (DATA)
#define SPI1D_GET_DATA_REG()         *((volatile uint8 *)(SPI1D_REG))


/*************************************************
Inter-Intergrated Circuit (IICV2)
*************************************************/
#define IICA_REG                     0xFFFF8058
#define IICA_SET_DATA_REG(DATA)      *((volatile uint8 *)(IICA_REG)) = (DATA)
#define IICA_GET_DATA_REG()          *((volatile uint8 *)(IICA_REG))
#define IICF_REG                     0xFFFF8059
#define IICF_SET_DATA_REG(DATA)      *((volatile uint8 *)(IICF_REG)) = (DATA)
#define IICF_GET_DATA_REG()          *((volatile uint8 *)(IICF_REG))
#define IICC1_REG                    0xFFFF805A
#define IICC1_SET_DATA_REG(DATA)     *((volatile uint8 *)(IICC1_REG)) = (DATA)
#define IICC1_GET_DATA_REG()         *((volatile uint8 *)(IICC1_REG))
#define IICS_REG                     0xFFFF805B
#define IICS_SET_DATA_REG(DATA)      *((volatile uint8 *)(IICS_REG)) = (DATA)
#define IICS_GET_DATA_REG()          *((volatile uint8 *)(IICS_REG))
#define IICD_REG                     0xFFFF805C
#define IICD_SET_DATA_REG(DATA)      *((volatile uint8 *)(IICD_REG)) = (DATA)
#define IICD_GET_DATA_REG()          *((volatile uint8 *)(IICD_REG))
#define IICC2_REG                    0xFFFF805D
#define IICC2_SET_DATA_REG(DATA)     *((volatile uint8 *)(IICC2_REG)) = (DATA)
#define IICC2_GET_DATA_REG()         *((volatile uint8 *)(IICC2_REG))


/*************************************************
Analog Comparator 3V (ACMPVLPV1)
*************************************************/
#define ACMP1SC_REG                  0xFFFF805E
#define ACMP1SC_SET_DATA_REG(DATA)   *((volatile uint8 *)(ACMP1SC_REG)) = (DATA)
#define ACMP1SC_GET_DATA_REG()       *((volatile uint8 *)(ACMP1SC_REG))
#define ACMP2SC_REG                  0xFFFF805F
#define ACMP2SC_SET_DATA_REG(DATA)   *((volatile uint8 *)(ACMP2SC_REG)) = (DATA)
#define ACMP2SC_GET_DATA_REG()       *((volatile uint8 *)(ACMP2SC_REG))      


/*************************************************
FlexTimer Module 1 (FTMV1)            
*************************************************/
#define FTM1SC_REG                   0xFFFF8080
#define FTM1SC_SET_DATA_REG(DATA)    *((volatile uint8 *)(FTM1SC_REG)) = (DATA)
#define FTM1SC_GET_DATA_REG()        *((volatile uint8 *)(FTM1SC_REG))
#define FTM1CNTH_REG                 0xFFFF8081
#define FTM1CNTH_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1CNTH_REG)) = (DATA)
#define FTM1CNTH_GET_DATA_REG()      *((volatile uint8 *)(FTM1CNTH_REG))
#define FTM1CNTL_REG                 0xFFFF8082
#define FTM1CNTL_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1CNTL_REG)) = (DATA)
#define FTM1CNTL_GET_DATA_REG()      *((volatile uint8 *)(FTM1CNTL_REG))    
#define FTM1MODH_REG                 0xFFFF8083
#define FTM1MODH_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1MODH_REG)) = (DATA)
#define FTM1MODH_GET_DATA_REG()      *((volatile uint8 *)(FTM1MODH_REG))
#define FTM1MODL_REG                 0xFFFF8084
#define FTM1MODL_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1MODL_REG)) = (DATA)
#define FTM1MODL_GET_DATA_REG()      *((volatile uint8 *)(FTM1MODL_REG))
#define FTM1C0SC_REG                 0xFFFF8085
#define FTM1C0SC_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1C0SC_REG)) = (DATA)
#define FTM1C0SC_GET_DATA_REG()      *((volatile uint8 *)(FTM1C0SC_REG))
#define FTM1C0VH_REG                 0xFFFF8086
#define FTM1C0VH_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1C0VH_REG)) = (DATA)
#define FTM1C0VH_GET_DATA_REG()      *((volatile uint8 *)(FTM1C0VH_REG))
#define FTM1C0VL_REG                 0xFFFF8087
#define FTM1C0VL_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1C0VL_REG)) = (DATA)
#define FTM1C0VL_GET_DATA_REG()      *((volatile uint8 *)(FTM1C0VL_REG))
#define FTM1C1SC_REG                 0xFFFF8088
#define FTM1C1SC_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1C1SC_REG)) = (DATA)
#define FTM1C1SC_GET_DATA_REG()      *((volatile uint8 *)(FTM1C1SC_REG))
#define FTM1C1VH_REG                 0xFFFF8089
#define FTM1C1VH_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1C1VH_REG)) = (DATA)
#define FTM1C1VH_GET_DATA_REG()      *((volatile uint8 *)(FTM1C1VH_REG))
#define FTM1C1VL_REG                 0xFFFF808A
#define FTM1C1VL_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1C1VL_REG)) = (DATA)
#define FTM1C1VL_GET_DATA_REG()      *((volatile uint8 *)(FTM1C1VL_REG))
#define FTM1C2SC_REG                 0xFFFF808B
#define FTM1C2SC_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1C2SC_REG)) = (DATA)
#define FTM1C2SC_GET_DATA_REG()      *((volatile uint8 *)(FTM1C2SC_REG))
#define FTM1C2VH_REG                 0xFFFF808C
#define FTM1C2VH_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1C2VH_REG)) = (DATA)
#define FTM1C2VH_GET_DATA_REG()      *((volatile uint8 *)(FTM1C2VH_REG))
#define FTM1C2VL_REG                 0xFFFF808D
#define FTM1C2VL_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1C2VL_REG)) = (DATA)
#define FTM1C2VL_GET_DATA_REG()      *((volatile uint8 *)(FTM1C2VL_REG))
#define FTM1C3SC_REG                 0xFFFF808E
#define FTM1C3SC_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1C3SC_REG)) = (DATA)
#define FTM1C3SC_GET_DATA_REG()      *((volatile uint8 *)(FTM1C3SC_REG))
#define FTM1C3VH_REG                 0xFFFF808F
#define FTM1C3VH_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1C3VH_REG)) = (DATA)
#define FTM1C3VH_GET_DATA_REG()      *((volatile uint8 *)(FTM1C3VH_REG))
#define FTM1C3VL_REG                 0xFFFF8090
#define FTM1C3VL_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1C3VL_REG)) = (DATA)
#define FTM1C3VL_GET_DATA_REG()      *((volatile uint8 *)(FTM1C3VL_REG))
#define FTM1C4SC_REG                 0xFFFF8091
#define FTM1C4SC_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1C4SC_REG)) = (DATA)
#define FTM1C4SC_GET_DATA_REG()      *((volatile uint8 *)(FTM1C4SC_REG))
#define FTM1C4VH_REG                 0xFFFF8092
#define FTM1C4VH_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1C4VH_REG)) = (DATA)
#define FTM1C4VH_GET_DATA_REG()      *((volatile uint8 *)(FTM1C4VH_REG))
#define FTM1C4VL_REG                 0xFFFF8093
#define FTM1C4VL_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1C4VL_REG)) = (DATA)
#define FTM1C4VL_GET_DATA_REG()      *((volatile uint8 *)(FTM1C4VL_REG))
#define FTM1C5SC_REG                 0xFFFF8094
#define FTM1C5SC_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1C5SC_REG)) = (DATA)
#define FTM1C5SC_GET_DATA_REG()      *((volatile uint8 *)(FTM1C5SC_REG))
#define FTM1C5VH_REG                 0xFFFF8095
#define FTM1C5VH_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1C5VH_REG)) = (DATA)
#define FTM1C5VH_GET_DATA_REG()      *((volatile uint8 *)(FTM1C5VH_REG))
#define FTM1C5VL_REG                 0xFFFF8096
#define FTM1C5VL_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1C5VL_REG)) = (DATA)
#define FTM1C5VL_GET_DATA_REG()      *((volatile uint8 *)(FTM1C5VL_REG))
#define FTM1CNTINH_REG                   0xFFFF809D
#define FTM1CNTINH_SET_DATA_REG(DATA)    *((volatile uint8 *)(FTM1CNTINH_REG)) = (DATA)
#define FTM1CNTINH_GET_DATA_REG()        *((volatile uint8 *)(FTM1CNTINH_REG))
#define FTM1CNTINL_REG                   0xFFFF809E
#define FTM1CNTINL_SET_DATA_REG(DATA)    *((volatile uint8 *)(FTM1CNTINL_REG)) = (DATA)
#define FTM1CNTINL_GET_DATA_REG()        *((volatile uint8 *)(FTM1CNTINL_REG))
#define FTM1STATUS_REG                   0xFFFF809F
#define FTM1STATUS_SET_DATA_REG(DATA)    *((volatile uint8 *)(FTM1STATUS_REG)) = (DATA)
#define FTM1STATUS_GET_DATA_REG()        *((volatile uint8 *)(FTM1STATUS_REG))                                   
#define FTM1MODE_REG                     0xFFFF80A0
#define FTM1MODE_SET_DATA_REG(DATA)      *((volatile uint8 *)(FTM1MODE_REG)) = (DATA)
#define FTM1MODE_GET_DATA_REG()          *((volatile uint8 *)(FTM1MODE_REG))
#define FTM1SYNC_REG                     0xFFFF80A1
#define FTM1SYNC_SET_DATA_REG(DATA)      *((volatile uint8 *)(FTM1SYNC_REG)) = (DATA)
#define FTM1SYNC_GET_DATA_REG()          *((volatile uint8 *)(FTM1SYNC_REG))
#define FTM1OUTINIT_REG                  0xFFFF80A2
#define FTM1OUTINIT_SET_DATA_REG(DATA)   *((volatile uint8 *)(FTM1OUTINIT_REG)) = (DATA)
#define FTM1OUTINIT_GET_DATA_REG()       *((volatile uint8 *)(FTM1OUTINIT_REG))
#define FTM1OUTMASK_REG                  0xFFFF80A3
#define FTM1OUTMASK_SET_DATA_REG(DATA)   *((volatile uint8 *)(FTM1OUTMASK_REG)) = (DATA)
#define FTM1OUTMASK_GET_DATA_REG()       *((volatile uint8 *)(FTM1OUTMASK_REG))
#define FTM1COMBINE0_REG                 0xFFFF80A4
#define FTM1COMBINE0_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1COMBINE0_REG)) = (DATA)
#define FTM1COMBINE0_GET_DATA_REG()      *((volatile uint8 *)(FTM1COMBINE0_REG))
#define FTM1COMBINE1_REG                 0xFFFF80A5
#define FTM1COMBINE1_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1COMBINE1_REG)) = (DATA)
#define FTM1COMBINE1_GET_DATA_REG()      *((volatile uint8 *)(FTM1COMBINE1_REG))
#define FTM1COMBINE2_REG                 0xFFFF80A6
#define FTM1COMBINE2_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1COMBINE2_REG)) = (DATA)
#define FTM1COMBINE2_GET_DATA_REG()      *((volatile uint8 *)(FTM1COMBINE2_REG))
#define FTM1DEADTIME_REG                 0xFFFF80A8
#define FTM1DEADTIME_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM1DEADTIME_REG)) = (DATA)
#define FTM1DEADTIME_GET_DATA_REG()      *((volatile uint8 *)(FTM1DEADTIME_REG))
#define FTM1EXTTRIG_REG                  0xFFFF80A9
#define FTM1EXTTRIG_SET_DATA_REG(DATA)   *((volatile uint8 *)(FTM1EXTTRIG_REG)) = (DATA)
#define FTM1EXTTRIG_GET_DATA_REG()       *((volatile uint8 *)(FTM1EXTTRIG_REG))
#define FTM1POL_REG                      0xFFFF80AA
#define FTM1POL_SET_DATA_REG(DATA)       *((volatile uint8 *)(FTM1POL_REG)) = (DATA)
#define FTM1POL_GET_DATA_REG()           *((volatile uint8 *)(FTM1POL_REG))
#define FTM1FMS_REG                      0xFFFF80AB
#define FTM1FMS_SET_DATA_REG(DATA)       *((volatile uint8 *)(FTM1FMS_REG)) = (DATA)
#define FTM1FMS_GET_DATA_REG()           *((volatile uint8 *)(FTM1FMS_REG))
#define FTM1FILTER0_REG                  0xFFFF80AC
#define FTM1FILTER0_SET_DATA_REG(DATA)   *((volatile uint8 *)(FTM1FILTER0_REG)) = (DATA)
#define FTM1FILTER0_GET_DATA_REG()       *((volatile uint8 *)(FTM1FILTER0_REG))
#define FTM1FILTER1_REG                  0xFFFF80AD
#define FTM1FILTER1_SET_DATA_REG(DATA)   *((volatile uint8 *)(FTM1FILTER1_REG)) = (DATA)
#define FTM1FILTER1_GET_DATA_REG()       *((volatile uint8 *)(FTM1FILTER1_REG))
#define FTM1FLTFILTER_REG                0xFFFF80AE
#define FTM1FLTFILTER_SET_DATA_REG(DATA) *((volatile uint8 *)(FTM1FLTFILTER_REG)) = (DATA)
#define FTM1FLTFILTER_GET_DATA_REG()     *((volatile uint8 *)(FTM1FLTFILTER_REG))
#define FTM1RFU_REG                      0xFFFF80AF
#define FTM1RFU_SET_DATA_REG(DATA)       *((volatile uint8 *)(FTM1RFU_REG)) = (DATA)
#define FTM1RFU_GET_DATA_REG()           *((volatile uint8 *)(FTM1RFU_REG))



/*************************************************
FlexTimer Module 2 (FTMV1)            
*************************************************/
#define FTM2SC_REG                   0xFFFF80C0
#define FTM2SC_SET_DATA_REG(DATA)    *((volatile uint8 *)(FTM2SC_REG)) = (DATA)
#define FTM2SC_GET_DATA_REG()        *((volatile uint8 *)(FTM2SC_REG))
#define FTM2CNTH_REG                 0xFFFF80C1
#define FTM2CNTH_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2CNTH_REG)) = (DATA)
#define FTM2CNTH_GET_DATA_REG()      *((volatile uint8 *)(FTM2CNTH_REG))
#define FTM2CNTL_REG                 0xFFFF80C2
#define FTM2CNTL_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2CNTL_REG)) = (DATA)
#define FTM2CNTL_GET_DATA_REG()      *((volatile uint8 *)(FTM2CNTL_REG))    
#define FTM2MODH_REG                 0xFFFF80C3
#define FTM2MODH_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2MODH_REG)) = (DATA)
#define FTM2MODH_GET_DATA_REG()      *((volatile uint8 *)(FTM2MODH_REG))
#define FTM2MODL_REG                 0xFFFF80C4
#define FTM2MODL_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2MODL_REG)) = (DATA)
#define FTM2MODL_GET_DATA_REG()      *((volatile uint8 *)(FTM2MODL_REG))
#define FTM2C0SC_REG                 0xFFFF80C5
#define FTM2C0SC_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2C0SC_REG)) = (DATA)
#define FTM2C0SC_GET_DATA_REG()      *((volatile uint8 *)(FTM2C0SC_REG))
#define FTM2C0VH_REG                 0xFFFF80C6
#define FTM2C0VH_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2C0VH_REG)) = (DATA)
#define FTM2C0VH_GET_DATA_REG()      *((volatile uint8 *)(FTM2C0VH_REG))
#define FTM2C0VL_REG                 0xFFFF80C7
#define FTM2C0VL_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2C0VL_REG)) = (DATA)
#define FTM2C0VL_GET_DATA_REG()      *((volatile uint8 *)(FTM2C0VL_REG))
#define FTM2C1SC_REG                 0xFFFF80C8
#define FTM2C1SC_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2C1SC_REG)) = (DATA)
#define FTM2C1SC_GET_DATA_REG()      *((volatile uint8 *)(FTM2C1SC_REG))
#define FTM2C1VH_REG                 0xFFFF80C9
#define FTM2C1VH_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2C1VH_REG)) = (DATA)
#define FTM2C1VH_GET_DATA_REG()      *((volatile uint8 *)(FTM2C1VH_REG))
#define FTM2C1VL_REG                 0xFFFF80CA
#define FTM2C1VL_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2C1VL_REG)) = (DATA)
#define FTM2C1VL_GET_DATA_REG()      *((volatile uint8 *)(FTM2C1VL_REG))
#define FTM2C2SC_REG                 0xFFFF80CB
#define FTM2C2SC_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2C2SC_REG)) = (DATA)
#define FTM2C2SC_GET_DATA_REG()      *((volatile uint8 *)(FTM2C2SC_REG))
#define FTM2C2VH_REG                 0xFFFF80CC
#define FTM2C2VH_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2C2VH_REG)) = (DATA)
#define FTM2C2VH_GET_DATA_REG()      *((volatile uint8 *)(FTM2C2VH_REG))
#define FTM2C2VL_REG                 0xFFFF80CD
#define FTM2C2VL_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2C2VL_REG)) = (DATA)
#define FTM2C2VL_GET_DATA_REG()      *((volatile uint8 *)(FTM2C2VL_REG))
#define FTM2C3SC_REG                 0xFFFF80CE
#define FTM2C3SC_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2C3SC_REG)) = (DATA)
#define FTM2C3SC_GET_DATA_REG()      *((volatile uint8 *)(FTM2C3SC_REG))
#define FTM2C3VH_REG                 0xFFFF80CF
#define FTM2C3VH_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2C3VH_REG)) = (DATA)
#define FTM2C3VH_GET_DATA_REG()      *((volatile uint8 *)(FTM2C3VH_REG))
#define FTM2C3VL_REG                 0xFFFF80D0
#define FTM2C3VL_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2C3VL_REG)) = (DATA)
#define FTM2C3VL_GET_DATA_REG()      *((volatile uint8 *)(FTM2C3VL_REG))
#define FTM2C4SC_REG                 0xFFFF80D1
#define FTM2C4SC_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2C4SC_REG)) = (DATA)
#define FTM2C4SC_GET_DATA_REG()      *((volatile uint8 *)(FTM2C4SC_REG))
#define FTM2C4VH_REG                 0xFFFF80D2
#define FTM2C4VH_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2C4VH_REG)) = (DATA)
#define FTM2C4VH_GET_DATA_REG()      *((volatile uint8 *)(FTM2C4VH_REG))
#define FTM2C4VL_REG                 0xFFFF80D3
#define FTM2C4VL_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2C4VL_REG)) = (DATA)
#define FTM2C4VL_GET_DATA_REG()      *((volatile uint8 *)(FTM2C4VL_REG))
#define FTM2C5SC_REG                 0xFFFF80D4
#define FTM2C5SC_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2C5SC_REG)) = (DATA)
#define FTM2C5SC_GET_DATA_REG()      *((volatile uint8 *)(FTM2C5SC_REG))
#define FTM2C5VH_REG                 0xFFFF80D5
#define FTM2C5VH_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2C5VH_REG)) = (DATA)
#define FTM2C5VH_GET_DATA_REG()      *((volatile uint8 *)(FTM2C5VH_REG))
#define FTM2C5VL_REG                 0xFFFF80D6
#define FTM2C5VL_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2C5VL_REG)) = (DATA)
#define FTM2C5VL_GET_DATA_REG()      *((volatile uint8 *)(FTM2C5VL_REG))
#define FTM2CNTINH_REG                   0xFFFF80DD
#define FTM2CNTINH_SET_DATA_REG(DATA)    *((volatile uint8 *)(FTM2CNTINH_REG)) = (DATA)
#define FTM2CNTINH_GET_DATA_REG()        *((volatile uint8 *)(FTM2CNTINH_REG))
#define FTM2CNTINL_REG                   0xFFFF80DE
#define FTM2CNTINL_SET_DATA_REG(DATA)    *((volatile uint8 *)(FTM2CNTINL_REG)) = (DATA)
#define FTM2CNTINL_GET_DATA_REG()        *((volatile uint8 *)(FTM2CNTINL_REG))
#define FTM2STATUS_REG                   0xFFFF80DF
#define FTM2STATUS_SET_DATA_REG(DATA)    *((volatile uint8 *)(FTM2STATUS_REG)) = (DATA)
#define FTM2STATUS_GET_DATA_REG()        *((volatile uint8 *)(FTM2STATUS_REG))                                   
#define FTM2MODE_REG                     0xFFFF80E0
#define FTM2MODE_SET_DATA_REG(DATA)      *((volatile uint8 *)(FTM2MODE_REG)) = (DATA)
#define FTM2MODE_GET_DATA_REG()          *((volatile uint8 *)(FTM2MODE_REG))
#define FTM2SYNC_REG                     0xFFFF80E1
#define FTM2SYNC_SET_DATA_REG(DATA)      *((volatile uint8 *)(FTM2SYNC_REG)) = (DATA)
#define FTM2SYNC_GET_DATA_REG()          *((volatile uint8 *)(FTM2SYNC_REG))
#define FTM2OUTINIT_REG                  0xFFFF80E2
#define FTM2OUTINIT_SET_DATA_REG(DATA)   *((volatile uint8 *)(FTM2OUTINIT_REG)) = (DATA)
#define FTM2OUTINIT_GET_DATA_REG()       *((volatile uint8 *)(FTM2OUTINIT_REG))
#define FTM2OUTMASK_REG                  0xFFFF80E3
#define FTM2OUTMASK_SET_DATA_REG(DATA)   *((volatile uint8 *)(FTM2OUTMASK_REG)) = (DATA)
#define FTM2OUTMASK_GET_DATA_REG()       *((volatile uint8 *)(FTM2OUTMASK_REG))
#define FTM2COMBINE0_REG                 0xFFFF80E4
#define FTM2COMBINE0_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2COMBINE0_REG)) = (DATA)
#define FTM2COMBINE0_GET_DATA_REG()      *((volatile uint8 *)(FTM2COMBINE0_REG))
#define FTM2COMBINE1_REG                 0xFFFF80E5
#define FTM2COMBINE1_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2COMBINE1_REG)) = (DATA)
#define FTM2COMBINE1_GET_DATA_REG()      *((volatile uint8 *)(FTM2COMBINE1_REG))
#define FTM2COMBINE2_REG                 0xFFFF80E6
#define FTM2COMBINE2_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2COMBINE2_REG)) = (DATA)
#define FTM2COMBINE2_GET_DATA_REG()      *((volatile uint8 *)(FTM2COMBINE2_REG))
#define FTM2DEADTIME_REG                 0xFFFF80E8
#define FTM2DEADTIME_SET_DATA_REG(DATA)  *((volatile uint8 *)(FTM2DEADTIME_REG)) = (DATA)
#define FTM2DEADTIME_GET_DATA_REG()      *((volatile uint8 *)(FTM2DEADTIME_REG))
#define FTM2EXTTRIG_REG                  0xFFFF80E9
#define FTM2EXTTRIG_SET_DATA_REG(DATA)   *((volatile uint8 *)(FTM2EXTTRIG_REG)) = (DATA)
#define FTM2EXTTRIG_GET_DATA_REG()       *((volatile uint8 *)(FTM2EXTTRIG_REG))
#define FTM2POL_REG                      0xFFFF80EA
#define FTM2POL_SET_DATA_REG(DATA)       *((volatile uint8 *)(FTM2POL_REG)) = (DATA)
#define FTM2POL_GET_DATA_REG()           *((volatile uint8 *)(FTM2POL_REG))
#define FTM2FMS_REG                      0xFFFF80EB
#define FTM2FMS_SET_DATA_REG(DATA)       *((volatile uint8 *)(FTM2FMS_REG)) = (DATA)
#define FTM2FMS_GET_DATA_REG()           *((volatile uint8 *)(FTM2FMS_REG))
#define FTM2FILTER0_REG                  0xFFFF80EC
#define FTM2FILTER0_SET_DATA_REG(DATA)   *((volatile uint8 *)(FTM2FILTER0_REG)) = (DATA)
#define FTM2FILTER0_GET_DATA_REG()       *((volatile uint8 *)(FTM2FILTER0_REG))
#define FTM2FILTER1_REG                  0xFFFF80ED
#define FTM2FILTER1_SET_DATA_REG(DATA)   *((volatile uint8 *)(FTM2FILTER1_REG)) = (DATA)
#define FTM2FILTER1_GET_DATA_REG()       *((volatile uint8 *)(FTM2FILTER1_REG))
#define FTM2FLTFILTER_REG                0xFFFF80EE
#define FTM2FLTFILTER_SET_DATA_REG(DATA) *((volatile uint8 *)(FTM2FLTFILTER_REG)) = (DATA)
#define FTM2FLTFILTER_GET_DATA_REG()     *((volatile uint8 *)(FTM2FLTFILTER_REG))
#define FTM2RFU_REG                      0xFFFF80EF
#define FTM2RFU_SET_DATA_REG(DATA)       *((volatile uint8 *)(FTM2RFU_REG)) = (DATA)
#define FTM2RFU_GET_DATA_REG()           *((volatile uint8 *)(FTM2RFU_REG))


/*************************************************
Resets, Interrupts, and General System Control
*************************************************/
#define SRS_REG                   0xFFFF9800
#define SRS_SET_DATA_REG(DATA)    *((volatile uint8 *)(SRS_REG)) = (DATA)
#define SRS_GET_DATA_REG()        *((volatile uint8 *)(SRS_REG))
#define SOPT_REG                  0xFFFF9802
#define SOPT_SET_DATA_REG(DATA)   *((volatile uint8 *)(SOPT_REG)) = (DATA)
#define SOPT_GET_DATA_REG()       *((volatile uint8 *)(SOPT_REG))
#define SMCLK_REG                 0xFFFF9803
#define SMCLK_SET_DATA_REG(DATA)  *((volatile uint8 *)(SMCLK_REG)) = (DATA)
#define SMCLK_GET_DATA_REG()      *((volatile uint8 *)(SMCLK_REG))
#define SDIDH_REG                 0xFFFF9806
#define SDIDH_SET_DATA_REG(DATA)  *((volatile uint8 *)(SDIDH_REG)) = (DATA)
#define SDIDH_GET_DATA_REG()      *((volatile uint8 *)(SDIDH_REG))
#define SDIDL_REG                 0xFFFF9807
#define SDIDL_SET_DATA_REG(DATA)  *((volatile uint8 *)(SDIDL_REG)) = (DATA)
#define SDIDL_GET_DATA_REG()      *((volatile uint8 *)(SDIDL_REG))
#define SRTISC_REG                0xFFFF9808
#define SRTISC_SET_DATA_REG(DATA) *((volatile uint8 *)(SRTISC_REG)) = (DATA)
#define SRTISC_GET_DATA_REG()     *((volatile uint8 *)(SRTISC_REG))
#define SPMSC1_REG                0xFFFF9809
#define SPMSC1_SET_DATA_REG(DATA) *((volatile uint8 *)(SPMSC1_REG)) = (DATA)
#define SPMSC1_GET_DATA_REG()     *((volatile uint8 *)(SPMSC1_REG))
#define SPMSC2_REG                0xFFFF980A
#define SPMSC2_SET_DATA_REG(DATA) *((volatile uint8 *)(SPMSC2_REG)) = (DATA)
#define SPMSC2_GET_DATA_REG()     *((volatile uint8 *)(SPMSC2_REG))
#define SOPT2_REG                 0xFFFF980C
#define SOPT2_SET_DATA_REG(DATA)  *((volatile uint8 *)(SOPT2_REG)) = (DATA)
#define SOPT2_GET_DATA_REG()      *((volatile uint8 *)(SOPT2_REG))
#define SCGC1_REG                 0xFFFF980D
#define SCGC1_SET_DATA_REG(DATA)  *((volatile uint8 *)(SCGC1_REG)) = (DATA)
#define SCGC1_GET_DATA_REG()      *((volatile uint8 *)(SCGC1_REG))
#define SCGC2_REG                 0xFFFF980E
#define SCGC2_SET_DATA_REG(DATA)  *((volatile uint8 *)(SCGC2_REG)) = (DATA)
#define SCGC2_GET_DATA_REG()      *((volatile uint8 *)(SCGC2_REG)) 

/*************************************************
Flash Module
*************************************************/
#define FCDIV_REG                 0xFFFF9820
#define FCDIV_SET_DATA_REG(DATA)  *((volatile uint8 *)(FCDIV_REG)) = (DATA)
#define FCDIV_GET_DATA_REG()      *((volatile uint8 *)(FCDIV_REG))
#define FOPT_REG                  0xFFFF9821
#define FOPT_SET_DATA_REG(DATA)   *((volatile uint8 *)(FOPT_REG)) = (DATA)
#define FOPT_GET_DATA_REG()       *((volatile uint8 *)(FOPT_REG))
#define FCNFG_REG                 0xFFFF9823
#define FCNFG_SET_DATA_REG(DATA)  *((volatile uint8 *)(FCNFG_REG)) = (DATA)
#define FCNFG_GET_DATA_REG()      *((volatile uint8 *)(FCNFG_REG))
#define FPROT_REG                 0xFFFF9824
#define FPROT_SET_DATA_REG(DATA)  *((volatile uint8 *)(FPROT_REG)) = (DATA)
#define FPROT_GET_DATA_REG()      *((volatile uint8 *)(FPROT_REG))
#define FSTAT_REG                 0xFFFF9825
#define FSTAT_SET_DATA_REG(DATA)  *((volatile uint8 *)(FSTAT_REG)) = (DATA)
#define FSTAT_GET_DATA_REG()      *((volatile uint8 *)(FSTAT_REG))
#define FCMD_REG                  0xFFFF9826
#define FCMD_SET_DATA_REG(DATA)   *((volatile uint8 *)(FCMD_REG)) = (DATA)
#define FCMD_GET_DATA_REG()       *((volatile uint8 *)(FCMD_REG))


/*************************************************
Timer/Pulse-Width Modulator 3 (TPMV3)
*************************************************/
#define TPM3SC_REG                   0xFFFF8030
#define TPM3SC_SET_DATA_REG(DATA)    *((volatile uint8 *)(TPM3SC_REG)) = (DATA)
#define TPM3SC_GET_DATA_REG()        *((volatile uint8 *)(TPM3SC_REG))
#define TPM3CNTH_REG                 0xFFFF8031
#define TPM3CNTH_SET_DATA_REG(DATA)  *((volatile uint8 *)(TPM3CNTH_REG)) = (DATA)
#define TPM3CNTH_GET_DATA_REG()      *((volatile uint8 *)(TPM3CNTH_REG))
#define TPM3CNTL_REG                 0xFFFF8032
#define TPM3CNTL_SET_DATA_REG(DATA)  *((volatile uint8 *)(TPM3CNTL_REG)) = (DATA)
#define TPM3CNTL_GET_DATA_REG()      *((volatile uint8 *)(TPM3CNTL_REG))
#define TPM3MODH_REG                 0xFFFF8033
#define TPM3MODH_SET_DATA_REG(DATA)  *((volatile uint8 *)(TPM3MODH_REG)) = (DATA)
#define TPM3MODH_GET_DATA_REG()      *((volatile uint8 *)(TPM3MODH_REG))
#define TPM3MODL_REG                 0xFFFF8034
#define TPM3MODL_SET_DATA_REG(DATA)  *((volatile uint8 *)(TPM3MODL_REG)) = (DATA)
#define TPM3MODL_GET_DATA_REG()      *((volatile uint8 *)(TPM3MODL_REG))
#define TPM3C0SC_REG                 0xFFFF8035
#define TPM3C0SC_SET_DATA_REG(DATA)  *((volatile uint8 *)(TPM3C0SC_REG)) = (DATA)
#define TPM3C0SC_GET_DATA_REG()      *((volatile uint8 *)(TPM3C0SC_REG))
#define TPM3C0VH_REG                 0xFFFF8036
#define TPM3C0VH_SET_DATA_REG(DATA)  *((volatile uint8 *)(TPM3C0VH_REG)) = (DATA)
#define TPM3C0VH_GET_DATA_REG()      *((volatile uint8 *)(TPM3C0VH_REG))
#define TPM3C0VL_REG                 0xFFFF8037
#define TPM3C0VL_SET_DATA_REG(DATA)  *((volatile uint8 *)(TPM3SC_REG)) = (DATA)
#define TPM3C0VL_GET_DATA_REG()      *((volatile uint8 *)(TPM3SC_REG))
#define TPM3C1SC_REG                 0xFFFF8038
#define TPM3C1SC_SET_DATA_REG(DATA)  *((volatile uint8 *)(TPM3C1SC_REG)) = (DATA)
#define TPM3C1SC_GET_DATA_REG()      *((volatile uint8 *)(TPM3C1SC_REG))
#define TPM3C1VH_REG                 0xFFFF8039
#define TPM3C1VH_SET_DATA_REG(DATA)  *((volatile uint8 *)(TPM3C1VH_REG)) = (DATA)
#define TPM3C1VH_GET_DATA_REG()      *((volatile uint8 *)(TPM3C1VH_REG))
#define TPM3C1VL_REG                 0xFFFF803A
#define TPM3C1VL_SET_DATA_REG(DATA)  *((volatile uint8 *)(TPM3C1VL_REG)) = (DATA)
#define TPM3C1VL_GET_DATA_REG()      *((volatile uint8 *)(TPM3C1VL_REG))



/*************************************************
Ports A-J Pull-Up, Slew Rate, and Drive Strength
*************************************************/
#define PTAPE_REG                 0xFFFF9840
#define PTAPE_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTAPE_REG)) = (DATA)
#define PTAPE_GET_DATA_REG()      *((volatile uint8 *)(PTAPE_REG))
#define PTASE_REG                 0xFFFF9841
#define PTASE_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTASE_REG)) = (DATA)
#define PTASE_GET_DATA_REG()      *((volatile uint8 *)(PTASE_REG))
#define PTADS_REG                 0xFFFF9842
#define PTADS_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTADS_REG)) = (DATA)
#define PTADS_GET_DATA_REG()      *((volatile uint8 *)(PTADS_REG))
#define PTBPE_REG                 0xFFFF9844
#define PTBPE_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTBPE_REG)) = (DATA)
#define PTBPE_GET_DATA_REG()      *((volatile uint8 *)(PTBPE_REG))
#define PTBSE_REG                 0xFFFF9845
#define PTBSE_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTBSE_REG)) = (DATA)
#define PTBSE_GET_DATA_REG()      *((volatile uint8 *)(PTBSE_REG))
#define PTBDS_REG                 0xFFFF9846
#define PTBDS_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTBDS_REG)) = (DATA)
#define PTBDS_GET_DATA_REG()      *((volatile uint8 *)(PTBDS_REG))
#define PTCPE_REG                 0xFFFF9848
#define PTCPE_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTCPE_REG)) = (DATA)
#define PTCPE_GET_DATA_REG()      *((volatile uint8 *)(PTCPE_REG))
#define PTCSE_REG                 0xFFFF9849
#define PTCSE_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTCSE_REG)) = (DATA)
#define PTCSE_GET_DATA_REG()      *((volatile uint8 *)(PTCSE_REG))
#define PTCDS_REG                 0xFFFF984A
#define PTCDS_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTCDS_REG)) = (DATA)
#define PTCDS_GET_DATA_REG()      *((volatile uint8 *)(PTCDS_REG))
#define PTDPE_REG                 0xFFFF984C
#define PTDPE_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTDPE_REG)) = (DATA)
#define PTDPE_GET_DATA_REG()      *((volatile uint8 *)(PTDPE_REG))
#define PTDSE_REG                 0xFFFF984D
#define PTDSE_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTDSE_REG)) = (DATA)
#define PTDSE_GET_DATA_REG()      *((volatile uint8 *)(PTDSE_REG))
#define PTDDS_REG                 0xFFFF984E
#define PTDDS_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTDDS_REG)) = (DATA)
#define PTDDS_GET_DATA_REG()      *((volatile uint8 *)(PTDDS_REG))
#define PTEPE_REG                 0xFFFF9850
#define PTEPE_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTEPE_REG)) = (DATA)
#define PTEPE_GET_DATA_REG()      *((volatile uint8 *)(PTEPE_REG))
#define PTESE_REG                 0xFFFF9851
#define PTESE_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTESE_REG)) = (DATA)
#define PTESE_GET_DATA_REG()      *((volatile uint8 *)(PTESE_REG))
#define PTEDS_REG                 0xFFFF9852
#define PTEDS_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTEDS_REG)) = (DATA)
#define PTEDS_GET_DATA_REG()      *((volatile uint8 *)(PTEDS_REG))
#define PTFPE_REG                 0xFFFF9854
#define PTFPE_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTFPE_REG)) = (DATA)
#define PTFPE_GET_DATA_REG()      *((volatile uint8 *)(PTFPE_REG))
#define PTFSE_REG                 0xFFFF9855
#define PTFSE_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTFSE_REG)) = (DATA)
#define PTFSE_GET_DATA_REG()      *((volatile uint8 *)(PTFSE_REG))
#define PTFDS_REG                 0xFFFF9856
#define PTFDS_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTFDS_REG)) = (DATA)
#define PTFDS_GET_DATA_REG()      *((volatile uint8 *)(PTFDS_REG))
#define PTGPE_REG                 0xFFFF9858
#define PTGPE_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTGPE_REG)) = (DATA)
#define PTGPE_GET_DATA_REG()      *((volatile uint8 *)(PTGPE_REG))
#define PTGSE_REG                 0xFFFF9859
#define PTGSE_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTGSE_REG)) = (DATA)
#define PTGSE_GET_DATA_REG()      *((volatile uint8 *)(PTGSE_REG))
#define PTGDS_REG                 0xFFFF985A
#define PTGDS_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTGDS_REG)) = (DATA)
#define PTGDS_GET_DATA_REG()      *((volatile uint8 *)(PTGDS_REG))
#define PTHPE_REG                 0xFFFF985C
#define PTHPE_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTHPE_REG)) = (DATA)
#define PTHPE_GET_DATA_REG()      *((volatile uint8 *)(PTHPE_REG))
#define PTHSE_REG                 0xFFFF985D
#define PTHSE_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTHSE_REG)) = (DATA)
#define PTHSE_GET_DATA_REG()      *((volatile uint8 *)(PTHSE_REG))
#define PTHDS_REG                 0xFFFF985E
#define PTHDS_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTHDS_REG)) = (DATA)
#define PTHDS_GET_DATA_REG()      *((volatile uint8 *)(PTHDS_REG))
#define PTJPE_REG                 0xFFFF9860
#define PTJPE_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTJPE_REG)) = (DATA)
#define PTJPE_GET_DATA_REG()      *((volatile uint8 *)(PTJPE_REG))
#define PTJSE_REG                 0xFFFF9861
#define PTJSE_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTJSE_REG)) = (DATA)
#define PTJSE_GET_DATA_REG()      *((volatile uint8 *)(PTJSE_REG))
#define PTJDS_REG                 0xFFFF9862
#define PTJDS_SET_DATA_REG(DATA)  *((volatile uint8 *)(PTJDS_REG)) = (DATA)
#define PTJDS_GET_DATA_REG()      *((volatile uint8 *)(PTJDS_REG))


/*************************************************
Serial Peripheral Interface 2 (SPIV3)
*************************************************/
#define SPI2C1_REG                0xFFFF9868
#define SPI2C1_SET_DATA_REG(DATA) *((volatile uint8 *)(SPI2C1_REG)) = (DATA)
#define SPI2C1_GET_DATA_REG()     *((volatile uint8 *)(SPI2C1_REG))
#define SPI2C2_REG                0xFFFF9869
#define SPI2C2_SET_DATA_REG(DATA) *((volatile uint8 *)(SPI2C2_REG)) = (DATA)
#define SPI2C2_GET_DATA_REG()     *((volatile uint8 *)(SPI2C2_REG))
#define SPI2BR_REG                0xFFFF986A
#define SPI2BR_SET_DATA_REG(DATA) *((volatile uint8 *)(SPI2BR_REG)) = (DATA)
#define SPI2BR_GET_DATA_REG()     *((volatile uint8 *)(SPI2BR_REG))
#define SPI2S_REG                 0xFFFF986B
#define SPI2S_SET_DATA_REG(DATA)  *((volatile uint8 *)(SPI2S_REG)) = (DATA)
#define SPI2S_GET_DATA_REG()      *((volatile uint8 *)(SPI2S_REG))
#define SPI2DH_REG                0xFFFF986C
#define SPI2DH_SET_DATA_REG(DATA) *((volatile uint8 *)(SPI2DH_REG)) = (DATA)
#define SPI2DH_GET_DATA_REG()     *((volatile uint8 *)(SPI2DH_REG))
#define SPI2DL_REG                0xFFFF986D
#define SPI2DL_SET_DATA_REG(DATA) *((volatile uint8 *)(SPI2DL_REG)) = (DATA)
#define SPI2DL_GET_DATA_REG()     *((volatile uint8 *)(SPI2DL_REG))
#define SPI2MH_REG                0xFFFF986E
#define SPI2MH_SET_DATA_REG(DATA) *((volatile uint8 *)(SPI2MH_REG)) = (DATA)
#define SPI2MH_GET_DATA_REG()     *((volatile uint8 *)(SPI2MH_REG))
#define SPI2ML_REG                0xFFFF986F
#define SPI2ML_SET_DATA_REG(DATA) *((volatile uint8 *)(SPI2ML_REG)) = (DATA)
#define SPI2ML_GET_DATA_REG()     *((volatile uint8 *)(SPI2ML_REG))
#define SPI2C3_REG                0xFFFF9870
#define SPI2C3_SET_DATA_REG(DATA) *((volatile uint8 *)(SPI2C3_REG)) = (DATA)
#define SPI2C3_GET_DATA_REG()     *((volatile uint8 *)(SPI2C3_REG))
#define SPICI_REG                 0xFFFF9871
#define SPICI_SET_DATA_REG(DATA)  *((volatile uint8 *)(SPICI_REG)) = (DATA)
#define SPICI_GET_DATA_REG()      *((volatile uint8 *)(SPICI_REG))


/*************************************************
Freescale's Controller Area Network (MSCANV1)
*************************************************/
#define CANCTL0_REG                 0xFFFF9880
#define CANCTL0_SET_DATA_REG(DATA)  *((volatile uint8 *)(CANCTL0_REG)) = (DATA)
#define CANCTL0_GET_DATA_REG()      *((volatile uint8 *)(CANCTL0_REG))
#define CANCTL1_REG                 0xFFFF9881
#define CANCTL1_SET_DATA_REG(DATA)  *((volatile uint8 *)(CANCTL1_REG)) = (DATA)
#define CANCTL1_GET_DATA_REG()      *((volatile uint8 *)(CANCTL1_REG))
#define CANBTR0_REG                 0xFFFF9882
#define CANBTR0_SET_DATA_REG(DATA)  *((volatile uint8 *)(CANBTR0_REG)) = (DATA)
#define CANBTR0_GET_DATA_REG()      *((volatile uint8 *)(CANBTR0_REG))
#define CANBTR1_REG                 0xFFFF9883
#define CANBTR1_SET_DATA_REG(DATA)  *((volatile uint8 *)(CANBTR1_REG)) = (DATA)
#define CANBTR1_GET_DATA_REG()      *((volatile uint8 *)(CANBTR1_REG))
#define CANRFLG_REG                 0xFFFF9884
#define CANRFLG_SET_DATA_REG(DATA)  *((volatile uint8 *)(CANRFLG_REG)) = (DATA)
#define CANRFLG_GET_DATA_REG()      *((volatile uint8 *)(CANRFLG_REG))
#define CANRIER_REG                 0xFFFF9885
#define CANRIER_SET_DATA_REG(DATA)  *((volatile uint8 *)(CANRIER_REG)) = (DATA)
#define CANRIER_GET_DATA_REG()      *((volatile uint8 *)(CANRIER_REG))
#define CANTFLG_REG                 0xFFFF9886
#define CANTFLG_SET_DATA_REG(DATA)  *((volatile uint8 *)(CANTFLG_REG)) = (DATA)
#define CANTFLG_GET_DATA_REG()      *((volatile uint8 *)(CANTFLG_REG))
#define CANTIER_REG                 0xFFFF9887
#define CANTIER_SET_DATA_REG(DATA)  *((volatile uint8 *)(CANTIER_REG)) = (DATA)
#define CANTIER_GET_DATA_REG()      *((volatile uint8 *)(CANTIER_REG))
#define CANTARQ_REG                 0xFFFF9888
#define CANTARQ_SET_DATA_REG(DATA)  *((volatile uint8 *)(CANTARQ_REG)) = (DATA)
#define CANTARQ_GET_DATA_REG()      *((volatile uint8 *)(CANTARQ_REG))
#define CANTAAK_REG                 0xFFFF9889
#define CANTAAK_SET_DATA_REG(DATA)  *((volatile uint8 *)(CANTAAK_REG)) = (DATA)
#define CANTAAK_GET_DATA_REG()      *((volatile uint8 *)(CANTAAK_REG))
#define CANTBSEL_REG                0xFFFF988A
#define CANTBSEL_SET_DATA_REG(DATA) *((volatile uint8 *)(CANTBSEL_REG)) = (DATA)
#define CANTBSEL_GET_DATA_REG()     *((volatile uint8 *)(CANTBSEL_REG))
#define CANIDAC_REG                 0xFFFF988B
#define CANIDAC_SET_DATA_REG(DATA)  *((volatile uint8 *)(CANIDAC_REG)) = (DATA)
#define CANIDAC_GET_DATA_REG()      *((volatile uint8 *)(CANIDAC_REG))
#define CANMISC_REG                 0xFFFF988D
#define CANMISC_SET_DATA_REG(DATA)  *((volatile uint8 *)(CANMISC_REG)) = (DATA)
#define CANMISC_GET_DATA_REG()      *((volatile uint8 *)(CANMISC_REG))
#define CANRXERR_REG                0xFFFF988E
#define CANRXERR_SET_DATA_REG(DATA) *((volatile uint8 *)(CANRXERR_REG)) = (DATA)
#define CANRXERR_GET_DATA_REG()     *((volatile uint8 *)(CANRXERR_REG))
#define CANTXERR_REG                0xFFFF988F
#define CANTXERR_SET_DATA_REG(DATA) *((volatile uint8 *)(CANTXERR_REG)) = (DATA)
#define CANTXERR_GET_DATA_REG()     *((volatile uint8 *)(CANTXERR_REG))
#define CANIDAR0_REG                0xFFFF9890
#define CANIDAR0_SET_DATA_REG(DATA) *((volatile uint8 *)(CANIDAR0_REG)) = (DATA)
#define CANIDAR0_GET_DATA_REG()     *((volatile uint8 *)(CANIDAR0_REG))
#define CANIDAR1_REG                0xFFFF9891
#define CANIDAR1_SET_DATA_REG(DATA) *((volatile uint8 *)(CANIDAR1_REG)) = (DATA)
#define CANIDAR1_GET_DATA_REG()     *((volatile uint8 *)(CANIDAR1_REG))
#define CANIDAR2_REG                0xFFFF9892
#define CANIDAR2_SET_DATA_REG(DATA) *((volatile uint8 *)(CANIDAR2_REG)) = (DATA)
#define CANIDAR2_GET_DATA_REG()     *((volatile uint8 *)(CANIDAR2_REG))
#define CANIDAR3_REG                0xFFFF9893
#define CANIDAR3_SET_DATA_REG(DATA) *((volatile uint8 *)(CANIDAR3_REG)) = (DATA)
#define CANIDAR3_GET_DATA_REG()     *((volatile uint8 *)(CANIDAR3_REG))
#define CANIDMR0_REG                0xFFFF9894
#define CANIDMR0_SET_DATA_REG(DATA) *((volatile uint8 *)(CANIDMR0_REG)) = (DATA)
#define CANIDMR0_GET_DATA_REG()     *((volatile uint8 *)(CANIDMR0_REG))
#define CANIDMR1_REG                0xFFFF9895
#define CANIDMR1_SET_DATA_REG(DATA) *((volatile uint8 *)(CANIDMR1_REG)) = (DATA)
#define CANIDMR1_GET_DATA_REG()     *((volatile uint8 *)(CANIDMR1_REG))
#define CANIDMR2_REG                0xFFFF9896
#define CANIDMR2_SET_DATA_REG(DATA) *((volatile uint8 *)(CANIDMR2_REG)) = (DATA)
#define CANIDMR2_GET_DATA_REG()     *((volatile uint8 *)(CANIDMR2_REG))
#define CANIDMR3_REG                0xFFFF9897
#define CANIDMR3_SET_DATA_REG(DATA) *((volatile uint8 *)(CANIDMR3_REG)) = (DATA)
#define CANIDMR3_GET_DATA_REG()     *((volatile uint8 *)(CANIDMR3_REG))
#define CANIDAR4_REG                0xFFFF9898
#define CANIDAR4_SET_DATA_REG(DATA) *((volatile uint8 *)(CANIDAR4_REG)) = (DATA)
#define CANIDAR4_GET_DATA_REG()     *((volatile uint8 *)(CANIDAR4_REG))
#define CANIDAR5_REG                0xFFFF9899
#define CANIDAR5_SET_DATA_REG(DATA) *((volatile uint8 *)(CANIDAR5_REG)) = (DATA)
#define CANIDAR5_GET_DATA_REG()     *((volatile uint8 *)(CANIDAR5_REG))
#define CANIDAR6_REG                0xFFFF989A
#define CANIDAR6_SET_DATA_REG(DATA) *((volatile uint8 *)(CANIDAR6_REG)) = (DATA)
#define CANIDAR6_GET_DATA_REG()     *((volatile uint8 *)(CANIDAR6_REG))
#define CANIDAR7_REG                0xFFFF989B
#define CANIDAR7_SET_DATA_REG(DATA) *((volatile uint8 *)(CANIDAR7_REG)) = (DATA)
#define CANIDAR7_GET_DATA_REG()     *((volatile uint8 *)(CANIDAR7_REG))
#define CANIDMR4_REG                0xFFFF989C
#define CANIDMR4_SET_DATA_REG(DATA) *((volatile uint8 *)(CANIDMR4_REG)) = (DATA)
#define CANIDMR4_GET_DATA_REG()     *((volatile uint8 *)(CANIDMR4_REG))
#define CANIDMR5_REG                0xFFFF989D
#define CANIDMR5_SET_DATA_REG(DATA) *((volatile uint8 *)(CANIDMR5_REG)) = (DATA)
#define CANIDMR5_GET_DATA_REG()     *((volatile uint8 *)(CANIDMR5_REG))
#define CANIDMR6_REG                0xFFFF989E
#define CANIDMR6_SET_DATA_REG(DATA) *((volatile uint8 *)(CANIDMR6_REG)) = (DATA)
#define CANIDMR6_GET_DATA_REG()     *((volatile uint8 *)(CANIDMR6_REG))
#define CANIDMR7_REG                0xFFFF989F
#define CANIDMR7_SET_DATA_REG(DATA) *((volatile uint8 *)(CANIDMR7_REG)) = (DATA)
#define CANIDMR7_GET_DATA_REG()     *((volatile uint8 *)(CANIDMR7_REG))


/*************************************************
Cyclic Redundancy Check Generator (CRCV1)
*************************************************/
#define CRCH_REG                  0xFFFF98C0
#define CRCH_SET_DATA_REG(DATA)   *((volatile uint8 *)(CRCH_REG)) = (DATA)
#define CRCH_GET_DATA_REG()       *((volatile uint8 *)(CRCH_REG))
#define CRCL_REG                  0xFFFF98C1
#define CRCL_SET_DATA_REG(DATA)   *((volatile uint8 *)(CRCL_REG)) = (DATA)
#define CRCL_GET_DATA_REG()       *((volatile uint8 *)(CRCL_REG))
#define CRCL0_REG                 0xFFFF98C4
#define CRCL0_SET_DATA_REG(DATA)  *((volatile uint8 *)(CRCL0_REG)) = (DATA)
#define CRCL0_GET_DATA_REG()      *((volatile uint8 *)(CRCL0_REG))
#define CRCL1_REG                 0xFFFF98C5
#define CRCL1_SET_DATA_REG(DATA)  *((volatile uint8 *)(CRCL1_REG)) = (DATA)
#define CRCL1_GET_DATA_REG()      *((volatile uint8 *)(CRCL1_REG))
#define CRCL2_REG                 0xFFFF98C6
#define CRCL2_SET_DATA_REG(DATA)  *((volatile uint8 *)(CRCL2_REG)) = (DATA)
#define CRCL2_GET_DATA_REG()      *((volatile uint8 *)(CRCL2_REG))
#define CRCL3_REG                 0xFFFF98C7
#define CRCL3_SET_DATA_REG(DATA)  *((volatile uint8 *)(CRCL3_REG)) = (DATA)
#define CRCL3_GET_DATA_REG()      *((volatile uint8 *)(CRCL3_REG))


#endif

