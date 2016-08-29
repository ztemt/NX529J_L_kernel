#ifndef __ET310_DEF__
#define __ET310_DEF__

//
// ET310 Sensor Register Definition 
//
#define  FDATA_ET310_ADDR            0x00       // Frame Buffer Data
#define  FSTATUS_ET310_ADDR          0x01       // Finger Status
#define  INT_EN_ET310_ADDR           0x02       // Interrupt Enable
#define  POWER_CONTL_ET310_ADDR		 0x03		//Power Control
#define  FPS_CTL_ET310_ADDR          0x04       // FPS &CDS Control; dcoffset
#define  ADC_CTL_ET310_ADDR          0x04       // ADC Control
#define  OT_CTL_ET310_ADDR           0x05       // Over Temperture Control
#define  V2LC0_ET310_ADDR            0x06       // V2l Control 0
#define  V2LC1_ET310_ADDR            0x07       // V2l Control 1
#define  DETC_ET310_ADDR             0x08       // Detect Control;interrupt threshold
#define  PGA_CONTL_ET310_ADDR        0x09       // PGA control ; gain
#define  ATC_ET310_ADDR              0x0A       // Analog Test Control
#define  SUSC_ET310_ADDR             0x0B       // Suspend Control
#define  SUSPDC_ET310_ADDR           0x0C       // Suspend Pulse Duty Cycle
#define  TGENC_ET310_ADDR            0x02       // Timing Generation On
#define  SRBA_ET310_ADDR             0x10       // Sensor Row Begin Address
#define  SREA_ET310_ADDR             0x11       // Sensor Row End Address
#define  SCBA_ET310_ADDR             0x12       // Sensor Column Begin Address
#define  SCEA_ET310_ADDR             0x13       // Sensor Column End Address

#define  ET310_DCOFFSET_CTRL         0x7F
#define  ET310_SUSPEND_CYCLE         0xFF
#define  ET310_300KHZ_ENABLE         0x8
#define  ET310_300KHZ_DISABLE        0x0
#define  ET310_DETECT_DOWN           0x80
#define  ET310_POWER_DOWN            0xFB

//
//	ET310 gain range
//
#define  ET310_GAIN_MIN		0x0
#define  ET310_GAIN_MAX		0xF

//
// FSTATUS (Fingerprint Status) 0x01
//
#define  OVERTEMP_ET310              BIT2
#define  DETECT_ET310                BIT1
#define  FRM_RDY_ET310               BIT0

//
// INT_EN (Interrupt Enable) 0x02
//
#define  OTEIE_ET310                 BIT2       // Over Temperature Event Interrupt Enable
#define  FOEIE_ET310                 BIT1       // Finger On Event Interrupt Enable
#define  FRIE_ET310                  BIT0       // Frame Ready Interrupt Enable

//
//FPS_CTL (FPS&CDS Control) 0x03
//
#define  FSCPC_POWER_DOWN_ET310      BIT0       // Finger Sensor Cell Power Control - Power Down(FSCPC)

//
//ADC_CTL (ADC Control) 0x04
//
#define  ADC_PWRDWN_ET310            BIT0       // ADC Power Down

//
// OTP_CTL (Over Temperture Control) 0x05
//

//
//TGENC (time general control) 0x0D
//
#define  TGEN_GEN_ET310_ON           0x10
#define  TGEN_GEN_ET310_OFF          0

#endif
