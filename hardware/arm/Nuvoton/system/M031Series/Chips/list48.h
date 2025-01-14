/****************************************************************************
 * MCU: M031LE3AE(LQFP48)
 * @file     M031LE3AE.csv
 * @version  V1.13
 * @Date     2019/04/02-10:47:33 
 * @brief    NuMicro pin descriptions file
 * Copyright (C) 2013-2019 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#ifndef _CHIP48_PINLIST_H_
#define _CHIP48_PINLIST_H_

#if USE_ICE >0
  #define CHIP_PIN_LIST \
     PIN(B,5 ,1 ),  /*  ADC0_CH5/ACMP1_N/I2C0_SCL/PWM0_CH0/UART2_TXD/TM0/INT0                                */\
     PIN(B,4 ,2 ),  /*  ADC0_CH4/ACMP1_P1/I2C0_SDA/PWM0_CH1/UART2_RXD/TM1/INT1                               */\
     PIN(B,3 ,3 ),  /*  ADC0_CH3/ACMP0_N/I2C1_SCL/UART1_TXD/PWM0_CH2/PWM0_BRAKE0/TM2/INT2                    */\
     PIN(B,2 ,4 ),  /*  ADC0_CH2/ACMP0_P1/I2C1_SDA/UART1_RXD/PWM0_CH3/TM3/INT3                               */\
     PIN(B,1 ,5 ),  /*  ADC0_CH1/UART2_TXD/I2C1_SCL/PWM0_CH4/PWM1_CH4/PWM0_BRAKE0                            */\
     PIN(B,0 ,6 ),  /*  ADC0_CH0/UART2_RXD/SPI0_I2SMCLK/I2C1_SDA/PWM0_CH5/PWM1_CH5/PWM0_BRAKE1               */\
     PIN(A,11,7 ),  /*  ACMP0_P0/EBI_nRD/USCI0_CLK/TM0_EXT                                                   */\
     PIN(A,10,8 ),  /*  ACMP1_P0/EBI_nWR/USCI0_DAT0/TM1_EXT                                                  */\
     PIN(A,9 ,9 ),  /*  EBI_MCLK/USCI0_DAT1/UART1_TXD/TM2_EXT                                                */\
     PIN(A,8 ,10),  /*  EBI_ALE/USCI0_CTL1/UART1_RXD/TM3_EXT/INT4                                            */\
     PIN(F,5 ,11),  /*  UART2_RXD/UART2_nCTS/PWM0_CH0/X32_IN/ADC0_ST                                         */\
     PIN(F,4 ,12),  /*  UART2_TXD/UART2_nRTS/PWM0_CH1/X32_OUT                                                */\
     PIN(F,3 ,13),  /*  EBI_nCS0/UART0_TXD/I2C0_SCL/XT1_IN                                                   */\
     PIN(F,2 ,14),  /*  EBI_nCS1/UART0_RXD/I2C0_SDA/XT1_OUT                                                  */\
     PIN(A,7 ,15),  /*  EBI_AD7/UART0_TXD/I2C1_SCL/PWM1_CH4/ACMP0_WLAT/TM2/INT1                              */\
     PIN(A,6 ,16),  /*  EBI_AD6/UART0_RXD/I2C1_SDA/PWM1_CH5/ACMP1_WLAT/TM3/INT0                              */\
     PIN(A,5 ,17),  /*  UART0_nCTS/UART0_TXD/I2C0_SCL/PWM0_CH0                                               */\
     PIN(A,4 ,18),  /*  SPI0_I2SMCLK/UART0_nRTS/UART0_RXD/I2C0_SDA/PWM0_CH1                                  */\
     PIN(A,3 ,19),  /*  SPI0_SS/UART1_TXD/I2C1_SCL/PWM0_CH2/CLKO/PWM1_BRAKE1                                 */\
     PIN(A,2 ,20),  /*  SPI0_CLK/UART1_RXD/I2C1_SDA/PWM0_CH3                                                 */\
     PIN(A,1 ,21),  /*  SPI0_MISO/UART0_TXD/UART1_nCTS/PWM0_CH4                                              */\
     PIN(A,0 ,22),  /*  SPI0_MOSI/UART0_RXD/UART1_nRTS/PWM0_CH5                                              */\
     PIN(F,15,23),  /*  PWM0_BRAKE0/PWM0_CH1/TM2/CLKO/INT4                                                   */\
     /*       24)       nRESET                                                                               */\
     /*PIN(F,0 ,25),    UART1_TXD/I2C1_SCL/UART0_TXD/ICE_DAT                                                 */\
     /*PIN(F,1 ,26),    UART1_RXD/I2C1_SDA/UART0_RXD/ICE_CLK                                                 */\
     PIN(C,5 ,27),  /*  EBI_AD5/UART2_TXD/I2C1_SCL/PWM1_CH0                                                  */\
     PIN(C,4 ,28),  /*  EBI_AD4/UART2_RXD/I2C1_SDA/PWM1_CH1                                                  */\
     PIN(C,3 ,29),  /*  EBI_AD3/UART2_nRTS/PWM1_CH2                                                          */\
     PIN(C,2 ,30),  /*  EBI_AD2/UART2_nCTS/PWM1_CH3                                                          */\
     PIN(C,1 ,31),  /*  EBI_AD1/UART2_TXD/I2C0_SCL/PWM1_CH4/ACMP0_O                                          */\
     PIN(C,0 ,32),  /*  EBI_AD0/UART2_RXD/I2C0_SDA/PWM1_CH5/ACMP1_O                                          */\
     PIN(A,12,33),  /*  I2C1_SCL                                                                             */\
     PIN(A,13,34),  /*  I2C1_SDA                                                                             */\
     PIN(A,14,35),  /*  UART0_TXD                                                                            */\
     PIN(A,15,36),  /*  UART0_RXD                                                                            */\
     /*       37        VSS                                                                                  */\
     /*       38        LDO_CAP                                                                              */\
     /*       39        VDD                                                                                  */\
     PIN(C,14,40),  /*  EBI_AD11/SPI0_I2SMCLK/USCI0_CTL0/TM1                                                 */\
     PIN(B,15,41),  /*  ADC0_CH15/EBI_AD12/SPI0_SS/USCI0_CTL1/UART0_nCTS/PWM1_CH0/TM0_EXT/PWM0_BRAKE1        */\
     PIN(B,14,42),  /*  ADC0_CH14/EBI_AD13/SPI0_CLK/USCI0_DAT1/UART0_nRTS/PWM1_CH1/TM1_EXT/CLKO              */\
     PIN(B,13,43),  /*  ADC0_CH13/ACMP0_P3/ACMP1_P3/EBI_AD14/SPI0_MISO/USCI0_DAT0/UART0_TXD/PWM1_CH2/TM2_EXT */\
     PIN(B,12,44),  /*  ADC0_CH12/ACMP0_P2/ACMP1_P2/EBI_AD15/SPI0_MOSI/USCI0_CLK/UART0_RXD/PWM1_CH3/TM3_EXT  */\
     /*       45        AVDD                                                                                 */\
     /*       46        AVSS                                                                                 */\
     PIN(B,7 ,47),  /*  ADC0_CH7/EBI_nWRL/UART1_TXD/EBI_nCS0/PWM1_BRAKE0/PWM1_CH4/INT5/ACMP0_O               */\
     PIN(B,6 ,48)   /*  ADC0_CH6/EBI_nWRH/UART1_RXD/EBI_nCS1/PWM1_BRAKE1/PWM1_CH5/INT4/ACMP1_O               */ 

#else /*used ICE*/
  #define CHIP_PIN_LIST \
     PIN(B,5 ,1 ),  /*  ADC0_CH5/ACMP1_N/I2C0_SCL/PWM0_CH0/UART2_TXD/TM0/INT0                                */\
     PIN(B,4 ,2 ),  /*  ADC0_CH4/ACMP1_P1/I2C0_SDA/PWM0_CH1/UART2_RXD/TM1/INT1                               */\
     PIN(B,3 ,3 ),  /*  ADC0_CH3/ACMP0_N/I2C1_SCL/UART1_TXD/PWM0_CH2/PWM0_BRAKE0/TM2/INT2                    */\
     PIN(B,2 ,4 ),  /*  ADC0_CH2/ACMP0_P1/I2C1_SDA/UART1_RXD/PWM0_CH3/TM3/INT3                               */\
     PIN(B,1 ,5 ),  /*  ADC0_CH1/UART2_TXD/I2C1_SCL/PWM0_CH4/PWM1_CH4/PWM0_BRAKE0                            */\
     PIN(B,0 ,6 ),  /*  ADC0_CH0/UART2_RXD/SPI0_I2SMCLK/I2C1_SDA/PWM0_CH5/PWM1_CH5/PWM0_BRAKE1               */\
     PIN(A,11,7 ),  /*  ACMP0_P0/EBI_nRD/USCI0_CLK/TM0_EXT                                                   */\
     PIN(A,10,8 ),  /*  ACMP1_P0/EBI_nWR/USCI0_DAT0/TM1_EXT                                                  */\
     PIN(A,9 ,9 ),  /*  EBI_MCLK/USCI0_DAT1/UART1_TXD/TM2_EXT                                                */\
     PIN(A,8 ,10),  /*  EBI_ALE/USCI0_CTL1/UART1_RXD/TM3_EXT/INT4                                            */\
     PIN(F,5 ,11),  /*  UART2_RXD/UART2_nCTS/PWM0_CH0/X32_IN/ADC0_ST                                         */\
     PIN(F,4 ,12),  /*  UART2_TXD/UART2_nRTS/PWM0_CH1/X32_OUT                                                */\
     PIN(F,3 ,13),  /*  EBI_nCS0/UART0_TXD/I2C0_SCL/XT1_IN                                                   */\
     PIN(F,2 ,14),  /*  EBI_nCS1/UART0_RXD/I2C0_SDA/XT1_OUT                                                  */\
     PIN(A,7 ,15),  /*  EBI_AD7/UART0_TXD/I2C1_SCL/PWM1_CH4/ACMP0_WLAT/TM2/INT1                              */\
     PIN(A,6 ,16),  /*  EBI_AD6/UART0_RXD/I2C1_SDA/PWM1_CH5/ACMP1_WLAT/TM3/INT0                              */\
     PIN(A,5 ,17),  /*  UART0_nCTS/UART0_TXD/I2C0_SCL/PWM0_CH0                                               */\
     PIN(A,4 ,18),  /*  SPI0_I2SMCLK/UART0_nRTS/UART0_RXD/I2C0_SDA/PWM0_CH1                                  */\
     PIN(A,3 ,19),  /*  SPI0_SS/UART1_TXD/I2C1_SCL/PWM0_CH2/CLKO/PWM1_BRAKE1                                 */\
     PIN(A,2 ,20),  /*  SPI0_CLK/UART1_RXD/I2C1_SDA/PWM0_CH3                                                 */\
     PIN(A,1 ,21),  /*  SPI0_MISO/UART0_TXD/UART1_nCTS/PWM0_CH4                                              */\
     PIN(A,0 ,22),  /*  SPI0_MOSI/UART0_RXD/UART1_nRTS/PWM0_CH5                                              */\
     PIN(F,15,23),  /*  PWM0_BRAKE0/PWM0_CH1/TM2/CLKO/INT4                                                   */\
     /*       24)       nRESET                                                                               */\
     PIN(F,0 ,25),  /*  UART1_TXD/I2C1_SCL/UART0_TXD/ICE_DAT                                                 */\
     PIN(F,1 ,26),  /*  UART1_RXD/I2C1_SDA/UART0_RXD/ICE_CLK                                                 */\
     PIN(C,5 ,27),  /*  EBI_AD5/UART2_TXD/I2C1_SCL/PWM1_CH0                                                  */\
     PIN(C,4 ,28),  /*  EBI_AD4/UART2_RXD/I2C1_SDA/PWM1_CH1                                                  */\
     PIN(C,3 ,29),  /*  EBI_AD3/UART2_nRTS/PWM1_CH2                                                          */\
     PIN(C,2 ,30),  /*  EBI_AD2/UART2_nCTS/PWM1_CH3                                                          */\
     PIN(C,1 ,31),  /*  EBI_AD1/UART2_TXD/I2C0_SCL/PWM1_CH4/ACMP0_O                                          */\
     PIN(C,0 ,32),  /*  EBI_AD0/UART2_RXD/I2C0_SDA/PWM1_CH5/ACMP1_O                                          */\
     PIN(A,12,33),  /*  I2C1_SCL                                                                             */\
     PIN(A,13,34),  /*  I2C1_SDA                                                                             */\
     PIN(A,14,35),  /*  UART0_TXD                                                                            */\
     PIN(A,15,36),  /*  UART0_RXD                                                                            */\
     /*       37        VSS                                                                                  */\
     /*       38        LDO_CAP                                                                              */\
     /*       39        VDD                                                                                  */\
     PIN(C,14,40),  /*  EBI_AD11/SPI0_I2SMCLK/USCI0_CTL0/TM1                                                 */\
     PIN(B,15,41),  /*  ADC0_CH15/EBI_AD12/SPI0_SS/USCI0_CTL1/UART0_nCTS/PWM1_CH0/TM0_EXT/PWM0_BRAKE1        */\
     PIN(B,14,42),  /*  ADC0_CH14/EBI_AD13/SPI0_CLK/USCI0_DAT1/UART0_nRTS/PWM1_CH1/TM1_EXT/CLKO              */\
     PIN(B,13,43),  /*  ADC0_CH13/ACMP0_P3/ACMP1_P3/EBI_AD14/SPI0_MISO/USCI0_DAT0/UART0_TXD/PWM1_CH2/TM2_EXT */\
     PIN(B,12,44),  /*  ADC0_CH12/ACMP0_P2/ACMP1_P2/EBI_AD15/SPI0_MOSI/USCI0_CLK/UART0_RXD/PWM1_CH3/TM3_EXT  */\
     /*       45        AVDD                                                                                 */\
     /*       46        AVSS                                                                                 */\
     PIN(B,7 ,47),  /*  ADC0_CH7/EBI_nWRL/UART1_TXD/EBI_nCS0/PWM1_BRAKE0/PWM1_CH4/INT5/ACMP0_O               */\
     PIN(B,6 ,48)   /*  ADC0_CH6/EBI_nWRH/UART1_RXD/EBI_nCS1/PWM1_BRAKE1/PWM1_CH5/INT4/ACMP1_O               */ 
#endif

#define MISO_PIN PB_5
#define MOSI_PIN PB_4
#define  SCK_PIN PB_3
#define   SS_PIN PB_2

#define  SDA_PIN PC_0
#define  SCL_PIN PC_1

#define A0  0
#define A1  1
#define A2  2
#define A3  3
#define A4  4
#define A5  5

#endif

