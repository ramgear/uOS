//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#include "Timer.h"
#include "diag/Trace.h"
#include "os.h"

// ----------------------------------------------------------------------------

volatile Timer::ticks_t Timer::ms_delayCount;
bool Timer::mStart = false;

// ----------------------------------------------------------------------------
void
SysTickHook(void);

void
Timer::sleep(ticks_t ticks)
{
  ms_delayCount = ticks;

  mStart = true;
  // Busy wait until the SysTick decrements the counter to zero.
  while (ms_delayCount != 0u)
    ;
  mStart = false;
}

// ----- SysTick_Handler() ---------------------------------------------------

// ----------------------------------------------------------------------------
