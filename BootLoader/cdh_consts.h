#ifndef _CDH_CONSTS_H
#define _CDH_CONSTS_H

typedef unsigned short uint16;
typedef unsigned long  uint32;
typedef unsigned long long uint64;
typedef short int16;
typedef long  int32;
typedef char  int8;

typedef volatile struct
{
  uint8 CONTROL1;            //0x00
  uint8 STATUS1;             //0x01
  uint8 STATUS2;             //0x02
  uint8 PWRCTL;              //0x03
  uint8 MRAM_CTL;            //0x04
  uint8 MRAM_CTL_REG;        //0x05
  uint8 MRAM_RD_INIT;        //0x06
  uint8 STATUS3;             //0x07
  uint8 LI1_TX;              //0x08
  uint8 LI1_RX;              //0x09
  uint8 STATUS4;             //0x0A
  uint8 IMU2_TX;             //0x0B
  uint8 IMU2_RX;             //0x0C
  uint8 DAC12_H;             //0x0D
  uint8 CDH_FPGA_VER;        //0x0E
  uint8 TEST_TLM;            //0x0F
  uint8 TEST_CMD;            //0x10
  uint8 DAC12_L;             //0x11
  uint8 CDH_ADC_START;       //0x12
  uint8 CDH_ADC_STOP;        //0x13
  uint8 CDH_ADC_WRITE;       //0x14
  uint8 CDH_ADC_RD_INIT;     //0x15
  uint8 CONTROL2;            //0x16
  uint8 FIP_TX;              //0x17 
  uint8 FIP_RX;              //0x18 
  uint8 IMU1_START;          //0x19 
  uint8 IMU1_STOP;           //0x1A   
  uint8 IMU1_WRITE;          //0x1B 
  uint8 IMU1_RD_INIT;        //0x1C
  uint8 PWM_CTL_REG;         //0x1D
  uint8 PWM_PER_L;           //0x1E
  uint8 PWM_PER_H;           //0x1F
  uint8 PWM_PULSE_XL;        //0x20
  uint8 PWM_PULSE_XH;        //0x21
  uint8 PWM_PULSE_YL;        //0x22
  uint8 PWM_PULSE_YH;        //0x23
  uint8 PWM_PULSE_ZL;        //0x24
  uint8 PWM_PULSE_ZH;        //0x25
  uint8 INT_CTL;             //0x26
  uint8 INT_MASK;            //0x27
  uint8 TIMER1_CTL;          //0x28
  uint8 TIMER1_DAT0;         //0x29
  uint8 TIMER1_DAT1;         //0x2A
  uint8 TIMER1_DAT2;         //0x2B
  uint8 TIMER1_DAT3;         //0x2C 
  uint8 PWRCTL2;             //0x2D
  uint8 SP1_BURN;            //0x2E
  uint8 SP2_BURN;            //0x2F
  uint8 SP3_BURN;            //0x30
  uint8 BD4_BURN;            //0x31
  uint8 EPS_BURN_PWR;        //0x32
  uint8 BURN_PWR_STATUS;     //0x33
  uint8 EPS_ADC_START;       //0x34
  uint8 EPS_ADC_STOP;        //0x35
  uint8 EPS_ADC_WRITE;       //0x36
  uint8 EPS_ADC_RD_INIT;     //0x37
  uint8 SP1_ADC_START;       //0x38
  uint8 SP1_ADC_STOP;        //0x39
  uint8 SP1_ADC_WRITE;       //0x3A
  uint8 SP1_ADC_RD_INIT;     //0x3B
  uint8 SP2_ADC_START;       //0x3C
  uint8 SP2_ADC_STOP;        //0x3D
  uint8 SP2_ADC_WRITE;       //0x3E
  uint8 SP2_ADC_RD_INIT;     //0x3F
  uint8 SP3_ADC_START;       //0x40
  uint8 SP3_ADC_STOP;        //0x41
  uint8 SP3_ADC_WRITE;       //0x42
  uint8 SP3_ADC_RD_INIT;     //0x43
  uint8 BD4_ADC_START;       //0x44
  uint8 BD4_ADC_STOP;        //0x45
  uint8 BD4_ADC_WRITE;       //0x46
  uint8 BD4_ADC_RD_INIT;     //0x47 
  uint8 SP1_MAG_START;       //0x48
  uint8 SP1_MAG_STOP;        //0x49
  uint8 SP1_MAG_WRITE;       //0x4A
  uint8 SP1_MAG_RD_INIT;     //0x4B
  uint8 SP2_MAG_START;       //0x4C
  uint8 SP2_MAG_STOP;        //0x4D
  uint8 SP2_MAG_WRITE;       //0x4E
  uint8 SP2_MAG_RD_INIT;     //0x4F 
  uint8 SP3_MAG_START;       //0x50
  uint8 SP3_MAG_STOP;        //0x51
  uint8 SP3_MAG_WRITE;       //0x52
  uint8 SP3_MAG_RD_INIT;     //0x53
  uint8 BD4_MAG_START;       //0x54
  uint8 BD4_MAG_STOP;        //0x55
  uint8 BD4_MAG_WRITE;       //0x56
  uint8 BD4_MAG_RD_INIT;     //0x57 
  uint8 TIMER2_CTL;          //0x58
  uint8 TIMER2_DAT0;         //0x59
  uint8 TIMER2_DAT1;         //0x5A
  uint8 TIMER2_DAT2;         //0x5B
  uint8 TIMER2_DAT3;         //0X5C  
  uint8 MBARC_MAG_TX;        //0x5D  **RPM Mod for MBARC
  uint8 MBARC_MAG_RX;        //0x5E  **RPM Mod for MBARC
} CDH_IO_t;

#define CDH_IO_ADDR 0xFF8000

#define STS1_UNUSED2                      0x80   // **RPM Mod for MBARC
#define STS1_CDH_IMU1_READY               0x40
#define STS1_MBARC_MAG_RX_EMPTY           0x20   // **RPM Mod for MBARC
#define STS1_EPSON_RX_EMPTY               0x10
#define STS1_LI1_RX_EMPTY                 0x08
#define STS1_CDH_ADC_READY                0x04
#define STS1_CDH_MRAM_READY               0x02
#define STS1_CDH_CPU_FIFO_EF              0x01

#define STS2_UNUSED2                      0x80   // **RPM Mod for MBARC
#define STS2_UNUSED1                      0x40   // **RPM Mod for MBARC
#define STS2_CDH_ADC_READY                0x20
#define STS2_BD4_ADC_READY                0x10
#define STS2_SP3_ADC_READY                0x08
#define STS2_SP2_ADC_READY                0x04
#define STS2_SP1_ADC_READY                0x02
#define STS2_EPS_ADC_READY                0x01

#define STS3_IMU1_INT1                    0x80
#define STS3_IMU1_INT2                    0x40
#define STS3_IMU2_Rx_FIFO_FF              0x20
#define STS3_BD4_MAG_READY                0x10
#define STS3_SP3_MAG_READY                0x08
#define STS3_SP2_MAG_READY                0x04
#define STS3_SP1_MAG_READY                0x02
#define STS3_UNUSED1                      0x01   // **RPM Mod for MBARC

#define STS4_CPUFIFO_FF                   0x80
#define STS4_IMU2_TX_FIFO_FF              0x40
#define STS4_MBARC_MAG_RX_FIFO_FF         0x20   // **RPM Mod for MBARC
#define STS4_MBARC_MAG_TX_FIFO_FF         0x10   // **RPM Mod for MBARC
#define STS4_LI1_RX_FIFO_FF               0x08   
#define STS4_LI1_TX_FIFO_FF               0x04
#define STS4_TEST_RX_FIFO_FF              0x02
#define STS4_TEST_TX_FIFO_FF              0x01

#define CTL1_CDH_OFFBD_WD_KICK_DISABLE    0x80
#define CTL1_CDH_OFFBD_WD_KICK            0x40
#define CTL1_CDH_OB_WD_KICK_DISABLE       0x20
#define CTL1_CDH_ONBD_WD_KICK             0x10
#define CTL1_CDH_LED3                     0x08
#define CTL1_CDH_LED2                     0x04
#define CTL1_CDH_LED1                     0x02
#define CTL1_CDH_LED0                     0x01

#define CTL2_CDH_IMU2_NRESET              0x02
#define CTL2_CDH_LI1_NRESET               0x01

#define PWR_MBARC_MAG                     0x80   // **RPM Mod for MBARC
#define PWR_EPS_ADC                       0x40
#define PWR_UNUSED1                       0x20
#define PWR_RADIO                         0x10
#define PWR_CDH_ADC                       0x08
#define PWR_PPTDAC                        0x04
#define PWR_IMU2                          0x02
#define PWR_IMU1                          0x01

#define PWR2_BD4MAG                       0x80
#define PWR2_BD4AMPADC                    0x40
#define PWR2_SP3MAG                       0x20
#define PWR2_SP3AMPADC                    0x10
#define PWR2_SP2MAG                       0x08
#define PWR2_SP2AMPADC                    0x04
#define PWR2_SP1MAG                       0x02
#define PWR2_SP1AMPADC                    0x01

#define MRAM_CTL_REG_D1_CS                0x20
#define MRAM_CTL_REG_D0_CS                0x10
#define MRAM_CTL_REG_C1_CS                0x08
#define MRAM_CTL_REG_C0_CS                0x04
#define MRAM_CTL_REG_DATA_NWP             0x02
#define MRAM_CTL_REG_CODE_NWP             0x01

#define TIMER_CTL_ENABLE                  0x01

/* INT_CTL bit masks */ 
#define INT5_RADIO_EXT_EVT                0x20
#define INT4_TIMER2                       0x10
#define INT3_SP1_MAG_READY                0x08
#define INT2_EPS_ADC_READY                0x04
#define INT1_ADC_READY                    0x02
#define INT0_TIMER1                       0x01

#define PWM_X_ENABLE                      0x20
#define PWM_X_PLUS                        0x10
#define PWM_Y_ENABLE                      0x08
#define PWM_Y_PLUS                        0x04
#define PWM_Z_ENABLE                      0x02
#define PWM_Z_PLUS                        0x01

#define TIMER1                            0x01
#define TIMER2                            0x02
#endif
