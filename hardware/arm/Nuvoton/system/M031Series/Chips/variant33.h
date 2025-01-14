/*
  variant33.h
  
  Copyright (c) 2018 huaweiwx@sina.com 2018.11.1

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
#pragma GCC diagnostic ignored "-Wconversion-null"

#define MFP_NULL {NULL, NULL, {NULL, NULL, NULL}}
#define MFP_PN(a,b,c) {P##a,BIT##b,{(uint32_t)&SYS->GP##a##_MFP##c, \
                                     SYS_GP##a##_MFP##c##_P##a##b##MFP_Msk, \
					                 SYS_GP##a##_MFP##c##_P##a##b##MFP_GPIO}}

#ifndef GPIO_DESC_USERDEF
const GPIOPinDescription GPIO_Desc[] =
{
  MFP_NULL,         //0
  MFP_PN(B, 5, L),  //1   ADC0_CH5/I2C0_SCL/PWM0_CH0/UART2_TXD/TM0/INT0
  MFP_PN(B, 4, L),  //2   ADC0_CH4/I2C0_SDA/PWM0_CH1/UART2_RXD/TM1/INT1
  MFP_PN(B, 3, L),  //3   ADC0_CH3/I2C1_SCL/UART1_TXD/PWM0_CH2/PWM0_BRAKE0/INT2
  MFP_PN(B, 2, L),  //4   ADC0_CH2/I2C1_SDA/UART1_RXD/PWM0_CH3/INT3
  MFP_PN(B, 1, L),  //5   ADC0_CH1/UART2_TXD/I2C1_SCL/PWM0_CH4/PWM0_BRAKE0
  MFP_PN(B, 0, L),  //6   ADC0_CH0/UART2_RXD/SPI0_I2SMCLK/I2C1_SDA/PWM0_CH5/PWM0_BRAKE1
  MFP_PN(F, 5, L),  //7   UART2_RXD/UART2_nCTS/PWM0_CH0/ADC0_ST
  MFP_PN(F, 4, L),  //8   UART2_TXD/UART2_nRTS/PWM0_CH1
  MFP_PN(F, 3, L),  //9   UART0_TXD/I2C0_SCL/XT1_IN
  MFP_PN(F, 2, L),  //10  UART0_RXD/I2C0_SDA/XT1_OUT
  MFP_PN(A, 3, L),  //11  SPI0_SS/UART1_TXD/I2C1_SCL/PWM0_CH2/CLKO
  MFP_PN(A, 2, L),  //12  SPI0_CLK/UART1_RXD/I2C1_SDA/PWM0_CH3
  MFP_PN(A, 1, L),  //13  SPI0_MISO/UART0_TXD/UART1_nCTS/PWM0_CH4
  MFP_PN(A, 0, L),  //14  SPI0_MOSI/UART0_RXD/UART1_nRTS/PWM0_CH5
  MFP_PN(F, 15,H),  //15  PWM0_BRAKE0/PWM0_CH1/CLKO/INT4
  MFP_NULL       ,  //16  nRESET
#if USE_ICE == 0
  MFP_PN(F, 0, L),  //17  UART1_TXD/I2C1_SCL/UART0_TXD/ICE_DAT
  MFP_PN(F, 1, L),  //18  UART1_RXD/I2C1_SDA/UART0_RXD/ICE_CLK
#else
  MFP_NULL,         //17  UART1_TXD/I2C1_SCL/UART0_TXD/ICE_DAT
  MFP_NULL,         //18  UART1_RXD/I2C1_SDA/UART0_RXD/ICE_CLK
#endif
  MFP_PN(C, 1, L),  //19  UART2_TXD/I2C0_SCL
  MFP_PN(C, 0, L),  //20  UART2_RXD/I2C0_SDA
  MFP_PN(A, 12,H),  //21  I2C1_SCL
  MFP_PN(A, 13,H),  //22  I2C1_SDA
  MFP_PN(A, 14,H),  //23  UART0_TXD
  MFP_PN(A, 15,H),  //24  UART0_RXD
  MFP_NULL       ,  //25  VSS
  MFP_NULL       ,  //26  LDO_CAP
  MFP_NULL       ,  //27  VDD
  MFP_PN(B, 15,H),  //28  ADC0_CH15/SPI0_SS/UART0_nCTS/TM0_EXT/PWM0_BRAKE1
  MFP_PN(B, 14,H),  //29  ADC0_CH14/SPI0_CLK/UART0_nRTS/TM1_EXT/CLKO
  MFP_PN(B, 13,H),  //30  ADC0_CH13/SPI0_MISO/UART0_TXD
  MFP_PN(B, 12,H),  //31  ADC0_CH12/SPI0_MOSI/UART0_RXD
  MFP_NULL       ,  //32  AVDD
};
#endif

#ifndef PWM_DESC_USERDEF
const PWMPinDescription PWM_Desc[]={
    {PWM0,PWM0_MODULE,PWM0_IRQn,1, 500,{PA_0, SYS_GPA_MFPL_PA0MFP_PWM0_CH5 }}, 
    {PWM0,PWM0_MODULE,PWM0_IRQn,2, 500,{PA_1, SYS_GPA_MFPL_PA1MFP_PWM0_CH4 }}, 
    {PWM0,PWM0_MODULE,PWM0_IRQn,3, 500,{PA_2, SYS_GPA_MFPL_PA2MFP_PWM0_CH3 }}, 
    {PWM0,PWM0_MODULE,PWM0_IRQn,4, 500,{PA_3, SYS_GPA_MFPL_PA3MFP_PWM0_CH2 }}, 
//    {PWM0,PWM0_MODULE,PWM0_IRQn,5, 500,{PA_4, SYS_GPA_MFPL_PA4MFP_PWM0_CH1 }}, 
//    {PWM0,PWM0_MODULE,PWM0_IRQn,6, 500,{PA_5, SYS_GPA_MFPL_PA5MFP_PWM0_CH0 }}, 
    {PWM0,PWM0_MODULE,PWM0_IRQn,7, 500,{PB_0, SYS_GPB_MFPL_PB0MFP_PWM0_CH5 }}, 
    {PWM0,PWM0_MODULE,PWM0_IRQn,8, 500,{PB_1, SYS_GPB_MFPL_PB1MFP_PWM0_CH4 }},
    {PWM0,PWM0_MODULE,PWM0_IRQn,9, 500,{PB_2, SYS_GPB_MFPL_PB2MFP_PWM0_CH3 }}, 
    {PWM0,PWM0_MODULE,PWM0_IRQn,11,500,{PB_3, SYS_GPB_MFPL_PB3MFP_PWM0_CH2 }},
    {PWM0,PWM0_MODULE,PWM0_IRQn,12,500,{PB_4, SYS_GPB_MFPL_PB4MFP_PWM0_CH1 }}, 
    {PWM0,PWM0_MODULE,PWM0_IRQn,13,500,{PB_5, SYS_GPB_MFPL_PB5MFP_PWM0_CH0 }},
//    {PWM0,PWM0_MODULE,PWM0_IRQn,14,500,{PD_15,SYS_GPD_MFPH_PD15MFP_PWM0_CH5}},  
    {PWM0,PWM0_MODULE,PWM0_IRQn,15,500,{PF_4, SYS_GPF_MFPL_PF4MFP_PWM0_CH1 }}, 
    {PWM0,PWM0_MODULE,PWM0_IRQn,16,500,{PF_5, SYS_GPF_MFPL_PF5MFP_PWM0_CH0 }},
//    {PWM0,PWM0_MODULE,PWM0_IRQn,17,500,{PF_14,SYS_GPF_MFPH_PF14MFP_PWM0_CH4}}, 
    {PWM0,PWM0_MODULE,PWM0_IRQn,18,500,{PF_15,SYS_GPF_MFPH_PF15MFP_PWM0_CH1}}, 
//    {PWM1,PWM1_MODULE,PWM1_IRQn,19,500,{PA_6 ,SYS_GPA_MFPL_PA6MFP_PWM1_CH5 }},
//	{PWM1,PWM1_MODULE,PWM1_IRQn,19,500,{PA_7 ,SYS_GPA_MFPL_PA7MFP_PWM1_CH4 }},
	{PWM1,PWM1_MODULE,PWM1_IRQn,19,500,{PB_0 ,SYS_GPB_MFPL_PB0MFP_PWM1_CH5 }},
	{PWM1,PWM1_MODULE,PWM1_IRQn,19,500,{PB_1 ,SYS_GPB_MFPL_PB1MFP_PWM1_CH4 }},
//	{PWM1,PWM1_MODULE,PWM1_IRQn,19,500,{PB_6 ,SYS_GPB_MFPL_PB6MFP_PWM1_CH5 }},
//	{PWM1,PWM1_MODULE,PWM1_IRQn,19,500,{PB_7 ,SYS_GPB_MFPL_PB7MFP_PWM1_CH4 }},
	{PWM1,PWM1_MODULE,PWM1_IRQn,19,500,{PB_12,SYS_GPB_MFPH_PB12MFP_PWM1_CH3}},
	{PWM1,PWM1_MODULE,PWM1_IRQn,19,500,{PB_13,SYS_GPB_MFPH_PB13MFP_PWM1_CH2}},
	{PWM1,PWM1_MODULE,PWM1_IRQn,19,500,{PB_14,SYS_GPB_MFPH_PB14MFP_PWM1_CH1}},
	{PWM1,PWM1_MODULE,PWM1_IRQn,19,500,{PB_15,SYS_GPB_MFPH_PB15MFP_PWM1_CH0}},
	{PWM1,PWM1_MODULE,PWM1_IRQn,19,500,{PC_0 ,SYS_GPC_MFPL_PC0MFP_PWM1_CH5 }},
	{PWM1,PWM1_MODULE,PWM1_IRQn,19,500,{PC_1 ,SYS_GPC_MFPL_PC1MFP_PWM1_CH4 }},
//	{PWM1,PWM1_MODULE,PWM1_IRQn,19,500,{PC_2 ,SYS_GPC_MFPL_PC2MFP_PWM1_CH3 }},
//	{PWM1,PWM1_MODULE,PWM1_IRQn,19,500,{PC_3 ,SYS_GPC_MFPL_PC3MFP_PWM1_CH2 }},
//	{PWM1,PWM1_MODULE,PWM1_IRQn,19,500,{PC_4 ,SYS_GPC_MFPL_PC4MFP_PWM1_CH1 }},
//	{PWM1,PWM1_MODULE,PWM1_IRQn,19,500,{PC_5 ,SYS_GPC_MFPL_PC5MFP_PWM1_CH0 }},
//	{PWM0,PWM1_MODULE,PWM1_IRQn,19,500,{PC_6 ,SYS_GPC_MFPL_PC6MFP_PWM1_CH3 }},
//	{PWM0,PWM1_MODULE,PWM1_IRQn,19,500,{PC_7 ,SYS_GPC_MFPL_PC7MFP_PWM1_CH2 }},
};
#endif

#ifndef ADC_DESC_USERDEF
const ADCPinDescription ADC_Desc[]={
	{ADC,ADC_MODULE,0 ,{PB_0   ,SYS_GPB_MFPL_PB0MFP_ADC_CH0   }},
	{ADC,ADC_MODULE,1 ,{PB_1   ,SYS_GPB_MFPL_PB1MFP_ADC_CH1   }},
	{ADC,ADC_MODULE,2 ,{PB_2   ,SYS_GPB_MFPL_PB2MFP_ADC_CH2   }},
	{ADC,ADC_MODULE,3 ,{PB_3   ,SYS_GPB_MFPL_PB3MFP_ADC_CH3   }},
	{ADC,ADC_MODULE,4 ,{PB_4   ,SYS_GPB_MFPL_PB4MFP_ADC_CH4   }},
	{ADC,ADC_MODULE,5 ,{PB_5   ,SYS_GPB_MFPL_PB5MFP_ADC_CH5   }},
//	{ADC,ADC_MODULE,6 ,{PB_6   ,SYS_GPB_MFPL_PB6MFP_ADC_CH6   }},
//	{ADC,ADC_MODULE,7 ,{PB_7   ,SYS_GPB_MFPL_PB7MFP_ADC_CH7   }},
//	{ADC,ADC_MODULE,8 ,{PB_8   ,SYS_GPB_MFPH_PB8MFP_ADC_CH8   }},
//	{ADC,ADC_MODULE,9 ,{PB_9   ,SYS_GPB_MFPH_PB9MFP_ADC_CH9   }},
//	{ADC,ADC_MODULE,10,{PB_10  ,SYS_GPB_MFPH_PB10MFP_ADC_CH10 }},
//	{ADC,ADC_MODULE,11,{PB_11  ,SYS_GPB_MFPH_PB11MFP_ADC_CH11 }},
	{ADC,ADC_MODULE,12,{PB_12  ,SYS_GPB_MFPH_PB12MFP_ADC_CH12 }},
	{ADC,ADC_MODULE,13,{PB_13  ,SYS_GPB_MFPH_PB13MFP_ADC_CH13 }},
	{ADC,ADC_MODULE,14,{PB_14  ,SYS_GPB_MFPH_PB14MFP_ADC_CH14 }},
	{ADC,ADC_MODULE,15,{PB_15  ,SYS_GPB_MFPH_PB15MFP_ADC_CH15 }},
};
#endif

#ifndef UART_DESC_USERDEF
const UARTPinAlt_TypeDef UART0PinAlt[] = {
  {{PA_0 ,SYS_GPA_MFPL_PA0MFP_UART0_RXD },{PA_1 ,SYS_GPA_MFPL_PA1MFP_UART0_TXD }},	
  {{PA_15,SYS_GPA_MFPH_PA15MFP_UART0_RXD},{PA_14,SYS_GPA_MFPH_PA14MFP_UART0_TXD}},	
  {{PB_12,SYS_GPB_MFPH_PB12MFP_UART0_RXD},{PB_13,SYS_GPB_MFPH_PB13MFP_UART0_TXD}},	
  {{PF_2 ,SYS_GPF_MFPL_PF2MFP_UART0_RXD },{PF_3 ,SYS_GPF_MFPL_PF3MFP_UART0_TXD }},	
//  {{PA_4 ,SYS_GPA_MFPL_PA4MFP_UART0_RXD },{PA_5 ,SYS_GPA_MFPL_PA5MFP_UART0_TXD }},	
//  {{PA_6 ,SYS_GPA_MFPL_PA6MFP_UART0_RXD },{PA_7 ,SYS_GPA_MFPL_PA7MFP_UART0_TXD }},	
//  {{PB_8 ,SYS_GPB_MFPH_PB8MFP_UART0_RXD },{PB_9 ,SYS_GPB_MFPH_PB9MFP_UART0_TXD }},	
//  {{PD_2 ,SYS_GPD_MFPL_PD2MFP_UART0_RXD },{PD_3 ,SYS_GPD_MFPL_PD3MFP_UART0_TXD }},	
//  {{PF_1 ,SYS_GPF_MFPL_PF1MFP_UART0_RXD },{PF_0 ,SYS_GPF_MFPL_PF0MFP_UART0_TXD }},	
};

const UARTPinAlt_TypeDef UART1PinAlt[] = {
  {{PA_2,SYS_GPA_MFPL_PA2MFP_UART1_RXD},{PA_3,SYS_GPA_MFPL_PA3MFP_UART1_TXD}},
  {{PB_2,SYS_GPB_MFPL_PB2MFP_UART1_RXD},{PB_3,SYS_GPB_MFPL_PB3MFP_UART1_TXD}},
//  {{PA_8,SYS_GPA_MFPH_PA8MFP_UART1_RXD},{PA_9,SYS_GPA_MFPH_PA9MFP_UART1_TXD}},
//  {{PB_6,SYS_GPB_MFPL_PB6MFP_UART1_RXD},{PB_7,SYS_GPB_MFPL_PB7MFP_UART1_TXD}},
//{{PF_1,SYS_GPF_MFPL_PF1MFP_UART1_RXD},{PF_0,SYS_GPF_MFPL_PF0MFP_UART1_TXD}},
};

const UARTPinAlt_TypeDef UART2PinAlt[] = {
  {{PB_0,SYS_GPB_MFPL_PB0MFP_UART2_RXD},{PB_1,SYS_GPB_MFPL_PB1MFP_UART2_TXD}}, 
  {{PB_4,SYS_GPB_MFPL_PB4MFP_UART2_RXD},{PB_5,SYS_GPB_MFPL_PB5MFP_UART2_TXD}}, 
  {{PC_0,SYS_GPC_MFPL_PC0MFP_UART2_RXD},{PC_1,SYS_GPC_MFPL_PC1MFP_UART2_TXD}},
  {{PF_5,SYS_GPF_MFPL_PF5MFP_UART2_RXD},{PF_4,SYS_GPF_MFPL_PF4MFP_UART2_TXD}},
//  {{PC_4,SYS_GPC_MFPL_PC4MFP_UART2_RXD},{PC_5,SYS_GPC_MFPL_PC5MFP_UART2_TXD}}, 
};

const UARTPinDescription UART_Desc[]={
   {UART0,UART0_MODULE,UART02_IRQn,UART0PinAlt},
   {UART1,UART1_MODULE,UART1_IRQn,UART1PinAlt},
   {UART2,UART2_MODULE,UART02_IRQn,UART2PinAlt},
};
#endif

#ifndef SPI_DESC_USERDEF
const SPIPinAlt_TypeDef SPI0PinAlt[] = { 
	{{PA_2 ,SYS_GPA_MFPL_PA2MFP_SPI0_CLK },{PA_1 ,SYS_GPA_MFPL_PA1MFP_SPI0_MISO },{PA_0 ,SYS_GPA_MFPL_PA0MFP_SPI0_MOSI },{PA_3 ,SYS_GPA_MFPL_PA3MFP_SPI0_SS }},
    {{PB_14,SYS_GPB_MFPH_PB14MFP_SPI0_CLK},{PB_13,SYS_GPB_MFPH_PB13MFP_SPI0_MISO},{PB_12,SYS_GPB_MFPH_PB12MFP_SPI0_MOSI},{PB_15,SYS_GPB_MFPH_PB15MFP_SPI0_SS}}, 
//	{{PD_2 ,SYS_GPD_MFPL_PD2MFP_SPI0_CLK },{PD_1 ,SYS_GPD_MFPL_PD1MFP_SPI0_MISO },{PD_0 ,SYS_GPD_MFPL_PD0MFP_SPI0_MOSI },{PD_3 ,SYS_GPD_MFPL_PD3MFP_SPI0_SS }},
};
const SPIPinDescription SPI_Desc[]={
  {SPI0,SPI0_MODULE,SPI0_IRQn,CLK_CLKSEL2_SPI0SEL_PCLK1, SPI0PinAlt},
};
#endif

#ifndef I2C_DESC_USERDEF
const I2CPinAlt_TypeDef I2C0PinAlt[] = {
  {{PB_4 ,SYS_GPB_MFPL_PB4MFP_I2C0_SDA },{PB_5 ,SYS_GPB_MFPL_PB5MFP_I2C0_SCL}},
  {{PC_0 ,SYS_GPC_MFPL_PC0MFP_I2C0_SDA },{PC_1 ,SYS_GPC_MFPL_PC1MFP_I2C0_SCL}},
  {{PF_2 ,SYS_GPF_MFPL_PF2MFP_I2C0_SDA },{PF_3 ,SYS_GPF_MFPL_PF3MFP_I2C0_SCL}},
//  {{PA_4 ,SYS_GPA_MFPL_PA4MFP_I2C0_SDA },{PA_5 ,SYS_GPA_MFPL_PA5MFP_I2C0_SCL}},
};
const I2CPinAlt_TypeDef I2C1PinAlt[] = {
 {{PA_2 ,SYS_GPA_MFPL_PA2MFP_I2C1_SDA },{PA_3 ,SYS_GPA_MFPL_PA3MFP_I2C1_SCL }},
 {{PA_13,SYS_GPA_MFPH_PA13MFP_I2C1_SDA},{PA_12,SYS_GPA_MFPH_PA12MFP_I2C1_SCL}},
 {{PB_0 ,SYS_GPB_MFPL_PB0MFP_I2C1_SDA },{PB_1 ,SYS_GPB_MFPL_PB1MFP_I2C1_SCL }},
 {{PB_2 ,SYS_GPB_MFPL_PB2MFP_I2C1_SDA },{PB_3 ,SYS_GPB_MFPL_PB3MFP_I2C1_SCL }},
// {{PA_6 ,SYS_GPA_MFPL_PA6MFP_I2C1_SDA },{PA_7 ,SYS_GPA_MFPL_PA7MFP_I2C1_SCL }},
// {{PB_10,SYS_GPB_MFPH_PB10MFP_I2C1_SDA},{PB_11,SYS_GPB_MFPH_PB11MFP_I2C1_SCL}},
// {{PC_4 ,SYS_GPC_MFPL_PC4MFP_I2C1_SDA },{PC_5 ,SYS_GPC_MFPL_PC5MFP_I2C1_SCL }},
};
const I2CPinDescription I2C_Desc[]={	
 {I2C0,I2C0_MODULE,I2C0_IRQn,I2C0PinAlt},
 {I2C1,I2C1_MODULE,I2C1_IRQn,I2C1PinAlt},
};
#endif
