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

#ifdef __cplusplus
extern "C" {
#endif



extern uint32_t GetTickCount( void );

uint32_t millis( void )
{
// todo: ensure no interrupts
	return GetTickCount() ;
}

uint32_t micros( void )
{
#if 0 // original function:
    uint32_t ticks;
    int32_t count;

		SysTick->CTRL;
    do {
        ticks = SysTick->VAL;
        count = GetTickCount();
    } while (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk);

    return count * 1000 + (SysTick->LOAD + 1 - ticks) / (SystemCoreClock/1000000) ;
#else
    uint32_t ticks, ticks2;
    uint32_t pend, pend2;
    uint32_t count, count2;

    ticks2  = SysTick->VAL;
    pend2   = !!(SCB->ICSR & SCB_ICSR_PENDSTSET_Msk)  ;
    count2  = GetTickCount();

    do {
        ticks=ticks2;
        pend=pend2;
        count=count2;
        ticks2  = SysTick->VAL;
        pend2   = !!(SCB->ICSR & SCB_ICSR_PENDSTSET_Msk)  ;
        count2  = GetTickCount();
    } while ((pend != pend2) || (count != count2) || (ticks < ticks2));

    return ((count+pend) * 1000) + (((SysTick->LOAD  - ticks)*(1048576/(F_CPU/1000000)))>>20) ; 
    // this is an optimization to turn a runtime division into two compile-time divisions and 
    // a runtime multiplication and shift, saving a few cycles 
#endif
}

void delay( uint32_t ms )
{
	if (ms == 0) return;
    uint32_t end = GetTickCount() + ms;
    while (GetTickCount() < end);
}

#ifdef __cplusplus
}
#endif
