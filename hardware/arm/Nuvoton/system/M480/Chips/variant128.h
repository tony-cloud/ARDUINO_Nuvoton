/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "Arduino.h"

#pragma GCC diagnostic ignored "-Wconversion-null"

#ifndef GPIO_DESC_USERDEF
const GPIOPinDescription GPIO_Desc[] =
{
  {NULL, NULL, {NULL, NULL, NULL}}, //0
  {PB, BIT5,  {(uint32_t)&SYS->GPB_MFPL, SYS_GPB_MFPL_PB5MFP_Msk, SYS_GPB_MFPL_PB5MFP_GPIO }},   //1 
  {PB, BIT4,  {(uint32_t)&SYS->GPB_MFPL, SYS_GPB_MFPL_PB4MFP_Msk, SYS_GPB_MFPL_PB4MFP_GPIO }},   //2 
  {PB, BIT3,  {(uint32_t)&SYS->GPB_MFPL, SYS_GPB_MFPL_PB3MFP_Msk, SYS_GPB_MFPL_PB3MFP_GPIO }},   //3 
  {PB, BIT2,  {(uint32_t)&SYS->GPB_MFPL, SYS_GPB_MFPL_PB2MFP_Msk, SYS_GPB_MFPL_PB2MFP_GPIO }},   //4 
  {PC, BIT12, {(uint32_t)&SYS->GPC_MFPH, SYS_GPC_MFPH_PC12MFP_Msk, SYS_GPC_MFPH_PC12MFP_GPIO}},  //5
  {PC, BIT11, {(uint32_t)&SYS->GPC_MFPH, SYS_GPC_MFPH_PC11MFP_Msk, SYS_GPC_MFPH_PC11MFP_GPIO}},  //6
  {PC, BIT10, {(uint32_t)&SYS->GPC_MFPH, SYS_GPC_MFPH_PC10MFP_Msk, SYS_GPC_MFPH_PC10MFP_GPIO}},  //7
  {PC, BIT9,  {(uint32_t)&SYS->GPC_MFPH, SYS_GPC_MFPH_PC9MFP_Msk, SYS_GPC_MFPH_PC9MFP_GPIO }},   //8
  {PB, BIT1,  {(uint32_t)&SYS->GPB_MFPL, SYS_GPB_MFPL_PB1MFP_Msk, SYS_GPB_MFPL_PB1MFP_GPIO }},   //9
  {PB, BIT0,  {(uint32_t)&SYS->GPB_MFPL, SYS_GPB_MFPL_PB0MFP_Msk, SYS_GPB_MFPL_PB0MFP_GPIO }},   //10
  {NULL, NULL, {NULL, NULL, NULL}}, //11
  {NULL, NULL, {NULL, NULL, NULL}}, //12
  {PA, BIT11, {(uint32_t)&SYS->GPA_MFPH, SYS_GPA_MFPH_PA11MFP_Msk, SYS_GPA_MFPH_PA11MFP_GPIO}},  //13
  {PA, BIT10, {(uint32_t)&SYS->GPA_MFPH, SYS_GPA_MFPH_PA10MFP_Msk, SYS_GPA_MFPH_PA10MFP_GPIO}},  //14
  {PA, BIT9,  {(uint32_t)&SYS->GPA_MFPH, SYS_GPA_MFPH_PA9MFP_Msk,  SYS_GPA_MFPH_PA9MFP_GPIO }},  //15
  {PA, BIT8,  {(uint32_t)&SYS->GPA_MFPH, SYS_GPA_MFPH_PA8MFP_Msk,  SYS_GPA_MFPH_PA8MFP_GPIO }},  //16
  {PC, BIT13, {(uint32_t)&SYS->GPC_MFPH, SYS_GPC_MFPH_PC13MFP_Msk, SYS_GPC_MFPH_PC13MFP_GPIO}},  //17
  {PD, BIT12, {(uint32_t)&SYS->GPD_MFPH, SYS_GPD_MFPH_PD12MFP_Msk, SYS_GPD_MFPH_PD12MFP_GPIO}},  //18
  {PD, BIT11, {(uint32_t)&SYS->GPD_MFPH, SYS_GPD_MFPH_PD11MFP_Msk, SYS_GPD_MFPH_PD11MFP_GPIO}},  //19
  {PD, BIT10, {(uint32_t)&SYS->GPD_MFPH, SYS_GPD_MFPH_PD10MFP_Msk, SYS_GPD_MFPH_PD10MFP_GPIO}},  //20
  {PG, BIT2,  {(uint32_t)&SYS->GPG_MFPL, SYS_GPG_MFPL_PG2MFP_Msk,  SYS_GPG_MFPL_PG2MFP_GPIO }},  //21
  {PG, BIT3,  {(uint32_t)&SYS->GPG_MFPL, SYS_GPG_MFPL_PG3MFP_Msk,  SYS_GPG_MFPL_PG3MFP_GPIO }},  //22
  {PG, BIT4,  {(uint32_t)&SYS->GPG_MFPL, SYS_GPG_MFPL_PG4MFP_Msk,  SYS_GPG_MFPL_PG4MFP_GPIO }},  //23
  {PF, BIT11, {(uint32_t)&SYS->GPF_MFPH, SYS_GPF_MFPH_PF11MFP_Msk, SYS_GPF_MFPH_PF11MFP_GPIO}},  //24
  {PF, BIT10, {(uint32_t)&SYS->GPF_MFPH, SYS_GPF_MFPH_PF10MFP_Msk, SYS_GPF_MFPH_PF10MFP_GPIO}},  //25
  {PF, BIT9,  {(uint32_t)&SYS->GPF_MFPH, SYS_GPF_MFPH_PF9MFP_Msk,  SYS_GPF_MFPH_PF9MFP_GPIO }},  //26
  {PF, BIT8,  {(uint32_t)&SYS->GPF_MFPH, SYS_GPF_MFPH_PF8MFP_Msk,  SYS_GPF_MFPH_PF8MFP_GPIO }},  //27
  {PF, BIT7,  {(uint32_t)&SYS->GPF_MFPL, SYS_GPF_MFPL_PF7MFP_Msk,  SYS_GPF_MFPL_PF7MFP_GPIO }},  //28
  {PF, BIT6,  {(uint32_t)&SYS->GPF_MFPL, SYS_GPF_MFPL_PF6MFP_Msk,  SYS_GPF_MFPL_PF6MFP_GPIO }},  //29
  {NULL, NULL, {NULL, NULL, NULL}},                                                              //30
  {PF, BIT5, {(uint32_t)&SYS->GPF_MFPL, SYS_GPF_MFPL_PF5MFP_Msk, SYS_GPF_MFPL_PF5MFP_GPIO }},    //31
  {PF, BIT4, {(uint32_t)&SYS->GPF_MFPL, SYS_GPF_MFPL_PF4MFP_Msk, SYS_GPF_MFPL_PF4MFP_GPIO }},    //32
  {PH, BIT4, {(uint32_t)&SYS->GPH_MFPL, SYS_GPH_MFPL_PH4MFP_Msk, SYS_GPH_MFPL_PH4MFP_GPIO }},    //33
  {PH, BIT5, {(uint32_t)&SYS->GPH_MFPL, SYS_GPH_MFPL_PH5MFP_Msk, SYS_GPH_MFPL_PH5MFP_GPIO }},    //34
  {PH, BIT6, {(uint32_t)&SYS->GPH_MFPL, SYS_GPH_MFPL_PH6MFP_Msk, SYS_GPH_MFPL_PH6MFP_GPIO }},    //35
  {PH, BIT7, {(uint32_t)&SYS->GPH_MFPL, SYS_GPH_MFPL_PH7MFP_Msk, SYS_GPH_MFPL_PH7MFP_GPIO }},    //36
  {PF, BIT3, {(uint32_t)&SYS->GPF_MFPL, SYS_GPF_MFPL_PF3MFP_Msk, SYS_GPF_MFPL_PF3MFP_GPIO }},    //37
  {PF, BIT2, {(uint32_t)&SYS->GPF_MFPL, SYS_GPF_MFPL_PF2MFP_Msk, SYS_GPF_MFPL_PF2MFP_GPIO }},    //38
  {NULL, NULL, {NULL, NULL, NULL}}, //39
  {NULL, NULL, {NULL, NULL, NULL}}, //40
  {PE, BIT8, {(uint32_t)&SYS->GPE_MFPH, SYS_GPE_MFPH_PE8MFP_Msk, SYS_GPE_MFPH_PE8MFP_GPIO }}, //41
  {PE, BIT9, {(uint32_t)&SYS->GPE_MFPH, SYS_GPE_MFPH_PE9MFP_Msk, SYS_GPE_MFPH_PE9MFP_GPIO }}, //42
  {PE, BIT10, {(uint32_t)&SYS->GPE_MFPH, SYS_GPE_MFPH_PE10MFP_Msk, SYS_GPE_MFPH_PE10MFP_GPIO}}, //43
  {PE, BIT11, {(uint32_t)&SYS->GPE_MFPH, SYS_GPE_MFPH_PE11MFP_Msk, SYS_GPE_MFPH_PE11MFP_GPIO}}, //44
  {PE, BIT12, {(uint32_t)&SYS->GPE_MFPH, SYS_GPE_MFPH_PE12MFP_Msk, SYS_GPE_MFPH_PE12MFP_GPIO}}, //45
  {PE, BIT13, {(uint32_t)&SYS->GPE_MFPH, SYS_GPE_MFPH_PE13MFP_Msk, SYS_GPE_MFPH_PE13MFP_GPIO}}, //46
  {PC, BIT8, {(uint32_t)&SYS->GPC_MFPH, SYS_GPC_MFPH_PC8MFP_Msk, SYS_GPC_MFPH_PC8MFP_GPIO }}, //47
  {PC, BIT7, {(uint32_t)&SYS->GPC_MFPL, SYS_GPC_MFPL_PC7MFP_Msk, SYS_GPC_MFPL_PC7MFP_GPIO }}, //48
  {PC, BIT6, {(uint32_t)&SYS->GPC_MFPL, SYS_GPC_MFPL_PC6MFP_Msk, SYS_GPC_MFPL_PC6MFP_GPIO }}, //49
  {PA, BIT7, {(uint32_t)&SYS->GPA_MFPL, SYS_GPA_MFPL_PA7MFP_Msk, SYS_GPA_MFPL_PA7MFP_GPIO }}, //50
  {PA, BIT6, {(uint32_t)&SYS->GPA_MFPL, SYS_GPA_MFPL_PA6MFP_Msk, SYS_GPA_MFPL_PA6MFP_GPIO }}, //51
  {NULL, NULL, {NULL, NULL, NULL}},                                                           //52
  {NULL, NULL, {NULL, NULL, NULL}},                                                           //53
  {NULL, NULL, {NULL, NULL, NULL}}, 											     	 	  //54
  {PA, BIT5, {(uint32_t)&SYS->GPA_MFPL, SYS_GPA_MFPL_PA5MFP_Msk, SYS_GPA_MFPL_PA5MFP_GPIO }}, //55
  {PA, BIT4, {(uint32_t)&SYS->GPA_MFPL, SYS_GPA_MFPL_PA4MFP_Msk, SYS_GPA_MFPL_PA4MFP_GPIO }}, //56
  {PA, BIT3, {(uint32_t)&SYS->GPA_MFPL, SYS_GPA_MFPL_PA3MFP_Msk, SYS_GPA_MFPL_PA3MFP_GPIO }}, //57
  {PA, BIT2, {(uint32_t)&SYS->GPA_MFPL, SYS_GPA_MFPL_PA2MFP_Msk, SYS_GPA_MFPL_PA2MFP_GPIO }}, //58
  {PA, BIT1, {(uint32_t)&SYS->GPA_MFPL, SYS_GPA_MFPL_PA1MFP_Msk, SYS_GPA_MFPL_PA1MFP_GPIO }}, //59
  {PA, BIT0, {(uint32_t)&SYS->GPA_MFPL, SYS_GPA_MFPL_PA0MFP_Msk, SYS_GPA_MFPL_PA0MFP_GPIO }}, //60
  {NULL, NULL, {NULL, NULL, NULL}}, //61
  {PE, BIT14, {(uint32_t)&SYS->GPE_MFPH, SYS_GPE_MFPH_PE14MFP_Msk, SYS_GPE_MFPH_PE14MFP_GPIO}}, //62
  {PE, BIT15, {(uint32_t)&SYS->GPE_MFPH, SYS_GPE_MFPH_PE15MFP_Msk, SYS_GPE_MFPH_PE15MFP_GPIO}}, //63
  {NULL, NULL, {NULL, NULL, NULL}}, //64
#if USE_ICE == 0
  {PF, BIT0, {(uint32_t)&SYS->GPF_MFPL, SYS_GPF_MFPL_PF0MFP_Msk, SYS_GPF_MFPL_PF0MFP_GPIO }}, //65
  {PF, BIT1, {(uint32_t)&SYS->GPF_MFPL, SYS_GPF_MFPL_PF1MFP_Msk, SYS_GPF_MFPL_PF1MFP_GPIO }}, //66
#else
  {NULL, NULL, {NULL, NULL, NULL}}, //65
  {NULL, NULL, {NULL, NULL, NULL}}, //66
#endif
  {PD, BIT9, {(uint32_t)&SYS->GPD_MFPH, SYS_GPD_MFPH_PD9MFP_Msk, SYS_GPD_MFPH_PD9MFP_GPIO }}, //67
  {PD, BIT8, {(uint32_t)&SYS->GPD_MFPH, SYS_GPD_MFPH_PD8MFP_Msk, SYS_GPD_MFPH_PD8MFP_GPIO }}, //68
  {PC, BIT5, {(uint32_t)&SYS->GPC_MFPL, SYS_GPC_MFPL_PC5MFP_Msk, SYS_GPC_MFPL_PC5MFP_GPIO }}, //69
  {PC, BIT4, {(uint32_t)&SYS->GPC_MFPL, SYS_GPC_MFPL_PC4MFP_Msk, SYS_GPC_MFPL_PC4MFP_GPIO }}, //70
  {PC, BIT3, {(uint32_t)&SYS->GPC_MFPL, SYS_GPC_MFPL_PC3MFP_Msk, SYS_GPC_MFPL_PC3MFP_GPIO }}, //71
  {PC, BIT2, {(uint32_t)&SYS->GPC_MFPL, SYS_GPC_MFPL_PC2MFP_Msk, SYS_GPC_MFPL_PC2MFP_GPIO }}, //72
  {PC, BIT1, {(uint32_t)&SYS->GPC_MFPL, SYS_GPC_MFPL_PC1MFP_Msk, SYS_GPC_MFPL_PC1MFP_GPIO }}, //73
  {PC, BIT0, {(uint32_t)&SYS->GPC_MFPL, SYS_GPC_MFPL_PC0MFP_Msk, SYS_GPC_MFPL_PC0MFP_GPIO }}, //74
  {NULL, NULL, {NULL, NULL, NULL}}, //75
  {NULL, NULL, {NULL, NULL, NULL}}, //76
  {PG, BIT9,  {(uint32_t)&SYS->GPG_MFPH, SYS_GPG_MFPH_PG9MFP_Msk,  SYS_GPG_MFPH_PG9MFP_GPIO }}, //77
  {PG, BIT10, {(uint32_t)&SYS->GPG_MFPH, SYS_GPG_MFPH_PG10MFP_Msk, SYS_GPG_MFPH_PG10MFP_GPIO}}, //78
  {PG, BIT11, {(uint32_t)&SYS->GPG_MFPH, SYS_GPG_MFPH_PG11MFP_Msk, SYS_GPG_MFPH_PG11MFP_GPIO}}, //79
  {PG, BIT12, {(uint32_t)&SYS->GPG_MFPH, SYS_GPG_MFPH_PG12MFP_Msk, SYS_GPG_MFPH_PG12MFP_GPIO}}, //80
  {PG, BIT13, {(uint32_t)&SYS->GPG_MFPH, SYS_GPG_MFPH_PG13MFP_Msk, SYS_GPG_MFPH_PG13MFP_GPIO}}, //81
  {PG, BIT14, {(uint32_t)&SYS->GPG_MFPH, SYS_GPG_MFPH_PG14MFP_Msk, SYS_GPG_MFPH_PG14MFP_GPIO}}, //82
  {PG, BIT15, {(uint32_t)&SYS->GPG_MFPH, SYS_GPG_MFPH_PG15MFP_Msk, SYS_GPG_MFPH_PG15MFP_GPIO}}, //83
  {PD, BIT13, {(uint32_t)&SYS->GPD_MFPH, SYS_GPD_MFPH_PD13MFP_Msk, SYS_GPD_MFPH_PD13MFP_GPIO}}, //84
  {PA, BIT12, {(uint32_t)&SYS->GPA_MFPH, SYS_GPA_MFPH_PA12MFP_Msk, SYS_GPA_MFPH_PA12MFP_GPIO}}, //85
  {PA, BIT13, {(uint32_t)&SYS->GPA_MFPH, SYS_GPA_MFPH_PA13MFP_Msk, SYS_GPA_MFPH_PA13MFP_GPIO}}, //86
  {PA, BIT14, {(uint32_t)&SYS->GPA_MFPH, SYS_GPA_MFPH_PA14MFP_Msk, SYS_GPA_MFPH_PA14MFP_GPIO}}, //87
  {PA, BIT15, {(uint32_t)&SYS->GPA_MFPH, SYS_GPA_MFPH_PA15MFP_Msk, SYS_GPA_MFPH_PA15MFP_GPIO}}, //88
  {NULL, NULL, {NULL, NULL, NULL}}, 															//89
  {NULL, NULL, {NULL, NULL, NULL}}, 															//90
  {NULL, NULL, {NULL, NULL, NULL}},                                                             //91
  {NULL, NULL, {NULL, NULL, NULL}}, //92
  {NULL, NULL, {NULL, NULL, NULL}}, //93
  {NULL, NULL, {NULL, NULL, NULL}}, //94
  {NULL, NULL, {NULL, NULL, NULL}}, //95
  {NULL, NULL, {NULL, NULL, NULL}}, //96
  {PE, BIT7, {(uint32_t)&SYS->GPE_MFPL, SYS_GPE_MFPL_PE7MFP_Msk, SYS_GPE_MFPL_PE7MFP_GPIO }}, //97
  {PE, BIT6, {(uint32_t)&SYS->GPE_MFPL, SYS_GPE_MFPL_PE6MFP_Msk, SYS_GPE_MFPL_PE6MFP_GPIO }}, //98
  {PE, BIT5, {(uint32_t)&SYS->GPE_MFPL, SYS_GPE_MFPL_PE5MFP_Msk, SYS_GPE_MFPL_PE5MFP_GPIO }}, //99
  {PE, BIT4, {(uint32_t)&SYS->GPE_MFPL, SYS_GPE_MFPL_PE4MFP_Msk, SYS_GPE_MFPL_PE4MFP_GPIO }}, //100
  {PE, BIT3, {(uint32_t)&SYS->GPE_MFPL, SYS_GPE_MFPL_PE3MFP_Msk, SYS_GPE_MFPL_PE3MFP_GPIO }}, //101
  {PE, BIT2, {(uint32_t)&SYS->GPE_MFPL, SYS_GPE_MFPL_PE2MFP_Msk, SYS_GPE_MFPL_PE2MFP_GPIO }}, //102
  {NULL, NULL, {NULL, NULL, NULL}}, //103
  {NULL, NULL, {NULL, NULL, NULL}}, //104
  {PE, BIT1, {(uint32_t)&SYS->GPE_MFPL, SYS_GPE_MFPL_PE1MFP_Msk, SYS_GPE_MFPL_PE1MFP_GPIO }}, //105
  {PE, BIT0, {(uint32_t)&SYS->GPE_MFPL, SYS_GPE_MFPL_PE0MFP_Msk, SYS_GPE_MFPL_PE0MFP_GPIO }}, //106
  {PH, BIT8, {(uint32_t)&SYS->GPH_MFPH, SYS_GPH_MFPH_PH8MFP_Msk, SYS_GPH_MFPH_PH8MFP_GPIO }}, //107
  {PH, BIT9, {(uint32_t)&SYS->GPH_MFPH, SYS_GPH_MFPH_PH9MFP_Msk, SYS_GPH_MFPH_PH9MFP_GPIO }}, //108
  {PH, BIT10,{(uint32_t)&SYS->GPH_MFPH, SYS_GPH_MFPH_PH10MFP_Msk,SYS_GPH_MFPH_PH10MFP_GPIO}}, //109
  {PH, BIT11,{(uint32_t)&SYS->GPH_MFPH, SYS_GPH_MFPH_PH11MFP_Msk,SYS_GPH_MFPH_PH11MFP_GPIO}}, //110
  {PD, BIT14,{(uint32_t)&SYS->GPD_MFPH, SYS_GPD_MFPH_PD14MFP_Msk,SYS_GPD_MFPH_PD14MFP_GPIO}}, //111
  {NULL, NULL, {NULL, NULL, NULL}}, 														  //112
  {NULL, NULL, {NULL, NULL, NULL}}, 														  //113
  {NULL, NULL, {NULL, NULL, NULL}}, 														  //114
  {PC, BIT14, {(uint32_t)&SYS->GPC_MFPH, SYS_GPC_MFPH_PC14MFP_Msk, SYS_GPC_MFPH_PC14MFP_GPIO}}, //115
  {PB, BIT15, {(uint32_t)&SYS->GPB_MFPH, SYS_GPB_MFPH_PB15MFP_Msk, SYS_GPB_MFPH_PB15MFP_GPIO}}, //116
  {PB, BIT14, {(uint32_t)&SYS->GPB_MFPH, SYS_GPB_MFPH_PB14MFP_Msk, SYS_GPB_MFPH_PB14MFP_GPIO}}, //117
  {PB, BIT13, {(uint32_t)&SYS->GPB_MFPH, SYS_GPB_MFPH_PB13MFP_Msk, SYS_GPB_MFPH_PB13MFP_GPIO}}, //118
  {PB, BIT12, {(uint32_t)&SYS->GPB_MFPH, SYS_GPB_MFPH_PB12MFP_Msk, SYS_GPB_MFPH_PB12MFP_GPIO}}, //119
  {NULL, NULL, {NULL, NULL, NULL}}, 															//120
  {NULL, NULL, {NULL, NULL, NULL}}, 															//121
  {NULL, NULL, {NULL, NULL, NULL}}, 															//122
  {PB, BIT11, {(uint32_t)&SYS->GPB_MFPH, SYS_GPB_MFPH_PB11MFP_Msk, SYS_GPB_MFPH_PB11MFP_GPIO}}, //123
  {PB, BIT10, {(uint32_t)&SYS->GPB_MFPH, SYS_GPB_MFPH_PB10MFP_Msk, SYS_GPB_MFPH_PB10MFP_GPIO}}, //124
  {PB, BIT9, {(uint32_t)&SYS->GPB_MFPH, SYS_GPB_MFPH_PB9MFP_Msk, SYS_GPB_MFPH_PB9MFP_GPIO }},   //125
  {PB, BIT8, {(uint32_t)&SYS->GPB_MFPH, SYS_GPB_MFPH_PB8MFP_Msk, SYS_GPB_MFPH_PB8MFP_GPIO }},   //126
  {PB, BIT7, {(uint32_t)&SYS->GPB_MFPL, SYS_GPB_MFPL_PB7MFP_Msk, SYS_GPB_MFPL_PB7MFP_GPIO }},   //127
  {PB, BIT6, {(uint32_t)&SYS->GPB_MFPL, SYS_GPB_MFPL_PB6MFP_Msk, SYS_GPB_MFPL_PB6MFP_GPIO }},   //128
};
#endif

#ifndef PWM_DESC_USERDEF
const PWMPinDescription PWM_Desc[] = { //SYS_GPA_MFPL_PA5MFP_PWM0_CH0
  {EPWM0, EPWM0_MODULE, EPWM0P1_IRQn, 0, 500, {PB_5, SYS_GPB_MFPL_PB5MFP_EPWM0_CH0 }}, //6  PE3
  {EPWM0, EPWM0_MODULE, EPWM0P1_IRQn, 1, 500, {PB_4, SYS_GPB_MFPL_PB4MFP_EPWM0_CH1 }}, //6  PE3
  {EPWM0, EPWM0_MODULE, EPWM0P1_IRQn, 2, 500, {PB_3, SYS_GPB_MFPL_PB3MFP_EPWM0_CH2 }}, //6  PE3
  {EPWM0, EPWM0_MODULE, EPWM0P1_IRQn, 3, 500, {PB_2, SYS_GPB_MFPL_PB2MFP_EPWM0_CH3 }}, //6  PE3
  {EPWM0, EPWM0_MODULE, EPWM0P1_IRQn, 4, 500, {PB_1, SYS_GPB_MFPL_PB1MFP_EPWM0_CH4 }}, //6  PE3
  {EPWM0, EPWM0_MODULE, EPWM0P1_IRQn, 5, 500, {PB_0, SYS_GPB_MFPL_PB0MFP_EPWM0_CH5 }}, //6  PE3
  {EPWM0, EPWM0_MODULE, EPWM0P0_IRQn, 2, 500, {PA_3, SYS_GPA_MFPL_PA3MFP_EPWM0_CH2 }}, //6  PE3
  {EPWM0, EPWM0_MODULE, EPWM0P0_IRQn, 3, 500, {PA_2, SYS_GPA_MFPL_PA2MFP_EPWM0_CH3 }}, //6  PE3
  {EPWM0, EPWM0_MODULE, EPWM0P0_IRQn, 4, 500, {PA_1, SYS_GPA_MFPL_PA1MFP_EPWM0_CH4 }}, //6  PE3
  {EPWM0, EPWM0_MODULE, EPWM0P0_IRQn, 5, 500, {PA_0, SYS_GPA_MFPL_PA0MFP_EPWM0_CH5 }}, //6  PE3

  {EPWM1, EPWM1_MODULE, EPWM1P2_IRQn, 4, 500, {PC_1, SYS_GPC_MFPL_PC1MFP_EPWM1_CH4 }},     //5  PC0
  {EPWM1, EPWM1_MODULE, EPWM1P2_IRQn, 5, 500, {PC_0, SYS_GPC_MFPL_PC0MFP_EPWM1_CH5 }},     //5  PC0
  {EPWM1, EPWM0_MODULE, EPWM1P1_IRQn, 0, 500, {PB_15,SYS_GPB_MFPH_PB15MFP_EPWM1_CH0}}, //6  PE3
  {EPWM1, EPWM0_MODULE, EPWM1P1_IRQn, 1, 500, {PB_14,SYS_GPB_MFPH_PB14MFP_EPWM1_CH1}}, //6  PE3
  {EPWM1, EPWM0_MODULE, EPWM1P1_IRQn, 2, 500, {PB_13,SYS_GPB_MFPH_PB13MFP_EPWM1_CH2}}, //6  PE3
  {EPWM1, EPWM0_MODULE, EPWM1P1_IRQn, 3, 500, {PB_12,SYS_GPB_MFPH_PB12MFP_EPWM1_CH3}}, //6  PE3

//  {BPWM0, BPWM0_MODULE,   BPWM0_IRQn, 5, 500, {PF_5, SYS_GPF_MFPL_PF5MFP_BPWM0_CH4 }}, //0  PC12
//  {BPWM0, BPWM0_MODULE,   BPWM0_IRQn, 4, 500, {PF_4, SYS_GPF_MFPL_PF4MFP_BPWM0_CH5 }}, //1  PC11
//  {BPWM1, BPWM1_MODULE,   BPWM1_IRQn, 4, 500, {PF_3, SYS_GPF_MFPL_PF3MFP_BPWM1_CH0 }}, //1  PC11
//  {BPWM1, BPWM0_MODULE,   BPWM1_IRQn, 4, 500, {PF_2, SYS_GPF_MFPL_PF2MFP_BPWM1_CH1 }}, //1  PC11
 // {EPWM1, EPWM1_MODULE, EPWM1P2_IRQn, 0, 500, {PC_12,SYS_GPC_MFPH_PC12MFP_EPWM1_CH0 }}, //0  PC12
 // {EPWM1, EPWM1_MODULE, EPWM1P2_IRQn, 1, 500, {PC_11,SYS_GPC_MFPH_PC11MFP_EPWM1_CH1 }}, //1  PC11
 // {EPWM1, EPWM1_MODULE, EPWM1P2_IRQn, 2, 500, {PC_10,SYS_GPC_MFPH_PC10MFP_EPWM1_CH2 }}, //1  PC10
 // {EPWM1, EPWM1_MODULE, EPWM1P2_IRQn, 3, 500, {PC_9, SYS_GPC_MFPH_PC9MFP_EPWM1_CH3  }}, //0  PC9
//  {EPWM1, EPWM1_MODULE, EPWM1P2_IRQn, 4, 500, {PC_13,SYS_GPC_MFPH_PC13MFP_EPWM1_CH4 }}, //4  PC13
//  {EPWM0, EPWM0_MODULE, EPWM1P3_IRQn, 5, 500, {PD_7, SYS_GPD_MFPL_PD7MFP_EPWM0_CH5  }}, //7  PD7
};
#endif

#ifndef ADC_DESC_USERDEF
const ADCPinDescription ADC_Desc[] = {
  {EADC, EADC_MODULE, 0,  {PB_0, SYS_GPB_MFPL_PB0MFP_EADC0_CH0  }},  //0
  {EADC, EADC_MODULE, 1,  {PB_1, SYS_GPB_MFPL_PB1MFP_EADC0_CH1  }},  //1
  {EADC, EADC_MODULE, 2,  {PB_2, SYS_GPB_MFPL_PB2MFP_EADC0_CH2 }},   //2
  {EADC, EADC_MODULE, 3,  {PB_3, SYS_GPB_MFPL_PB3MFP_EADC0_CH3 }},   //3
  {EADC, EADC_MODULE, 4,  {PB_4, SYS_GPB_MFPL_PB4MFP_EADC0_CH4 }},   //4
  {EADC, EADC_MODULE, 5,  {PB_5, SYS_GPB_MFPL_PB5MFP_EADC0_CH5 }},   //5
  {EADC, EADC_MODULE, 6,  {PB_6, SYS_GPB_MFPL_PB6MFP_EADC0_CH6 }},   //6
  {EADC, EADC_MODULE, 7,  {PB_7, SYS_GPB_MFPL_PB7MFP_EADC0_CH7 }},   //7
  {EADC, EADC_MODULE, 8,  {PB_8, SYS_GPB_MFPH_PB8MFP_EADC0_CH8  }},  //8
  {EADC, EADC_MODULE, 9,  {PB_9, SYS_GPB_MFPH_PB9MFP_EADC0_CH9  }},  //9
  {EADC, EADC_MODULE, 10, {PB_10,SYS_GPB_MFPH_PB10MFP_EADC0_CH10 }}, //10
  {EADC, EADC_MODULE, 11, {PB_11,SYS_GPB_MFPH_PB11MFP_EADC0_CH11 }}, //11
  {EADC, EADC_MODULE, 12, {PB_12,SYS_GPB_MFPH_PB12MFP_EADC0_CH12 }}, //12
  {EADC, EADC_MODULE, 13, {PB_13,SYS_GPB_MFPH_PB13MFP_EADC0_CH13}},  //13
  {EADC, EADC_MODULE, 14, {PB_14,SYS_GPB_MFPH_PB14MFP_EADC0_CH14}},  //14
  {EADC, EADC_MODULE, 15, {PB_15,SYS_GPB_MFPH_PB15MFP_EADC0_CH15}},  //15
};
#endif

#ifndef SPI_DESC_USERDEF
const SPIPinDescription SPI_Desc[] = {
  {SPI0,SPI0_MODULE,SPI0_IRQn,CLK_CLKSEL2_SPI0SEL_PCLK1,
	{{PA_2,SYS_GPA_MFPL_PA2MFP_SPI0_CLK} ,{PA_0,SYS_GPA_MFPL_PA0MFP_SPI0_MOSI},
	 {PA_1,SYS_GPA_MFPL_PA1MFP_SPI0_MISO},{PA_3,SYS_GPA_MFPL_PA3MFP_SPI0_SS}}},

  {SPI1,SPI1_MODULE,SPI1_IRQn,CLK_CLKSEL2_SPI2SEL_PCLK1,
    {{PB_3,SYS_GPB_MFPL_PB3MFP_SPI1_CLK} ,{PB_4,SYS_GPB_MFPL_PB4MFP_SPI1_MOSI },
	 {PB_5,SYS_GPB_MFPL_PB5MFP_SPI1_MISO},{PB_2,SYS_GPB_MFPL_PB2MFP_SPI1_SS}}},

  {SPI2,SPI2_MODULE,SPI2_IRQn,CLK_CLKSEL2_SPI2SEL_PCLK1,
	{{PA_13,SYS_GPA_MFPH_PA13MFP_SPI2_CLK} ,{PA_15,SYS_GPA_MFPH_PA15MFP_SPI2_MOSI},
	 {PA_14,SYS_GPA_MFPH_PA14MFP_SPI2_MISO},{PA_12,SYS_GPA_MFPH_PA12MFP_SPI2_SS}}},
//  { SPI2, SPI2_MODULE, SPI2_IRQn, CLK_CLKSEL2_SPI2SEL_PCLK1,
//    { {31, SYS_GPD_MFPH_PD15MFP_SPI2_CLK }, {29, SYS_GPD_MFPH_PD13MFP_SPI2_MOSI},
//      {30, SYS_GPD_MFPH_PD14MFP_SPI2_MISO}, {28, SYS_GPD_MFPH_PD12MFP_SPI2_SS  }
//    }
//  },
};
#endif

#ifndef UART_DESC_USERDEF
const UARTPinDescription UART_Desc[] = {
  {UART0, UART0_MODULE, UART0_IRQn, {{PA_0, SYS_GPA_MFPL_PA0MFP_UART0_RXD }, {PA_1, SYS_GPA_MFPL_PA1MFP_UART0_TXD }}},//  {UART0, UART1_MODULE, UART1_IRQn, {{93, SYS_GPB_MFPL_PB2MFP_UART1_RXD }, { 94, SYS_GPB_MFPL_PB3MFP_UART1_TXD }}},
  {UART1, UART1_MODULE, UART1_IRQn, {{PB_2, SYS_GPB_MFPL_PB2MFP_UART1_RXD }, {PB_3, SYS_GPB_MFPL_PB3MFP_UART1_TXD }}},
#if USE_ICE == 0
  {UART1, UART1_MODULE, UART1_IRQn, {{PF_1, SYS_GPF_MFPL_PF1MFP_UART1_RXD }, {PF_0, SYS_GPF_MFPL_PF0MFP_UART1_TXD }}},
#endif
  {UART2, UART2_MODULE, UART2_IRQn, {{PB_0, SYS_GPB_MFPL_PB0MFP_UART2_RXD }, {PB_1, SYS_GPB_MFPL_PB1MFP_UART2_TXD }}},
  {UART2, UART2_MODULE, UART2_IRQn, {{PC_0, SYS_GPC_MFPL_PC0MFP_UART2_RXD }, {PC_1, SYS_GPC_MFPL_PC1MFP_UART2_TXD }}},
  {UART2, UART2_MODULE, UART2_IRQn, {{PF_5, SYS_GPF_MFPL_PF5MFP_UART2_RXD }, {PF_4, SYS_GPF_MFPL_PF4MFP_UART2_TXD }}},
  {UART3, UART3_MODULE, UART3_IRQn, {{PB_14,SYS_GPB_MFPH_PB14MFP_UART3_RXD}, {PB_15,SYS_GPB_MFPH_PB15MFP_UART3_TXD}}},
  {UART4, UART4_MODULE, UART4_IRQn, {{PA_2, SYS_GPA_MFPL_PA2MFP_UART4_RXD }, {PA_3, SYS_GPA_MFPL_PA3MFP_UART4_TXD }}},
  {UART5, UART5_MODULE, UART5_IRQn, {{PB_4, SYS_GPB_MFPL_PB4MFP_UART5_RXD }, {PB_5, SYS_GPB_MFPL_PB5MFP_UART5_TXD }}},
};
#endif

#ifndef I2C_DESC_USERDEF
const I2CPinDescription I2C_Desc[] = {
  {I2C0, I2C0_MODULE, {{PB_5, SYS_GPB_MFPL_PB5MFP_I2C0_SCL}, {PB_4, SYS_GPB_MFPL_PB4MFP_I2C0_SDA }}},
  {I2C0, I2C0_MODULE, {{PC_1, SYS_GPC_MFPL_PC1MFP_I2C0_SCL}, {PC_0, SYS_GPC_MFPL_PC0MFP_I2C0_SDA }}},
  {I2C1, I2C1_MODULE, {{PB_1, SYS_GPB_MFPL_PB1MFP_I2C1_SCL}, {PB_0, SYS_GPB_MFPL_PB0MFP_I2C1_SDA }}},
  {I2C1, I2C1_MODULE, {{PA_3, SYS_GPA_MFPL_PA3MFP_I2C1_SCL}, {PA_2, SYS_GPA_MFPL_PA2MFP_I2C1_SDA }}},
#if USE_ICE == 0
  {I2C1, I2C1_MODULE, {{PF_1, SYS_GPF_MFPL_PF0MFP_I2C1_SCL}, {PF_1, SYS_GPF_MFPL_PF1MFP_I2C1_SDA }}},
#endif
  {I2C2, I2C2_MODULE, {{PA_1, SYS_GPA_MFPL_PA1MFP_I2C2_SCL}, {PA_0, SYS_GPA_MFPL_PA0MFP_I2C2_SDA }}},
  {I2C2, I2C2_MODULE, {{PB_13,SYS_GPB_MFPH_PB13MFP_I2C2_SCL},{PB_12,SYS_GPB_MFPH_PB12MFP_I2C2_SDA}}},
};

#endif

#ifndef CAN_DESC_USERDEF
const CANPinDescription CAN_Desc[] = {
//  {CAN0, CAN0_MODULE, CAN0_IRQn, {{84, SYS_GPA_MFPH_PA13MFP_CAN0_RXD}, {83, SYS_GPA_MFPH_PA12MFP_CAN0_TXD}}},
};
#endif


