//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"


#define OS_TASK_USER_NUM		6

#include "os.h"
#include "Timer.h"
#include "BlinkLed.h"
#include "os_isr.h"

// ----------------------------------------------------------------------------
//
// Standalone STM32F4 led blink sample (trace via DEBUG).
//
// In debug configurations, demonstrate how to print a greeting message
// on the trace device. In release configurations the message is
// simply discarded.
//
// Then demonstrates how to blink a led with 1Hz, using a
// continuous loop and SysTick delays.
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// Definitions visible only within this translation unit.
namespace
{
  // ----- Timing definitions -------------------------------------------------

  // Keep the LED on for 2/3 of a second.
  constexpr Timer::ticks_t BLINK_ON_TICKS = Timer::FREQUENCY_HZ * 2 / 3;
  constexpr Timer::ticks_t BLINK_OFF_TICKS = Timer::FREQUENCY_HZ
      - BLINK_ON_TICKS;
}

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

/* define tasks priority */
#define	TASK1_TASK_PRIORITY	1
#define	TASK2_TASK_PRIORITY	2
#define	TASK3_TASK_PRIORITY	2
#define	TASK4_TASK_PRIORITY	3
#define	TASK5_TASK_PRIORITY	3
#define	TASK6_TASK_PRIORITY	3

/* define tasks priority */
#define	TASKx_TASK_STACK_SIZE	128

/* define tasks */
static void Task1(void *arg);
static void Task2(void *arg);
static void Task3(void *arg);
static void Task4(void *arg);
static void Task5(void *arg);
static void Task6(void *arg);

static stack_t Task1Stk[TASKx_TASK_STACK_SIZE];
static stack_t Task2Stk[TASKx_TASK_STACK_SIZE];
static stack_t Task3Stk[TASKx_TASK_STACK_SIZE];
static stack_t Task4Stk[TASKx_TASK_STACK_SIZE];
static stack_t Task5Stk[TASKx_TASK_STACK_SIZE];
static stack_t Task6Stk[TASKx_TASK_STACK_SIZE];

int
main(int argc, char* argv[])
{
  // Send a greeting to the trace device (skipped on Release).
  trace_puts("Hello ARM World!");

  // At this stage the system clock should have already been configured
  // at high speed.
  trace_printf("System clock: %uHz\n", SystemCoreClock);

	BlinkLed blinkLed(LED3);

	  // Perform all necessary initialisations for the LED.
	  blinkLed.powerUp();

  Timer timer;
  timer.start();

  /* Initial OS */
  OS_Init();

  uint32_t seconds = 0;

  /* Create tasks */
  OS_Task_Create(
		  Task1
		  , Task1Stk
		  , TASKx_TASK_STACK_SIZE
		  , TASK1_TASK_PRIORITY
		  , "Task 1"
		  , OS_TASK_OPT_DEFAULT
		  );

  OS_Task_Create(
		  Task2
		  , Task2Stk
		  , TASKx_TASK_STACK_SIZE
		  , TASK2_TASK_PRIORITY
		  , "Task 2"
		  , OS_TASK_OPT_DEFAULT
		  );

  OS_Task_Create(
		  Task3
		  , Task3Stk
		  , TASKx_TASK_STACK_SIZE
		  , TASK3_TASK_PRIORITY
		  , "Task 3"
		  , OS_TASK_OPT_DEFAULT
		  );

  OS_Task_Create(
		  Task4
		  , Task4Stk
		  , TASKx_TASK_STACK_SIZE
		  , TASK4_TASK_PRIORITY
		  , "Task 4"
		  , OS_TASK_OPT_DEFAULT
		  );

  OS_Task_Create(
		  Task5
		  , Task5Stk
		  , TASKx_TASK_STACK_SIZE
		  , TASK5_TASK_PRIORITY
		  , "Task 5"
		  , OS_TASK_OPT_DEFAULT
		  );

  OS_Task_Create(
		  Task6
		  , Task6Stk
		  , TASKx_TASK_STACK_SIZE
		  , TASK6_TASK_PRIORITY
		  , "Task 6"
		  , OS_TASK_OPT_DEFAULT
		  );

  /* Start OS */
  OS_Start();

  // Infinite loop
  while (1)
    {

	  blinkLed.turnOn();
	  timer.sleep(1000);
	  blinkLed.turnOff();
      ++seconds;

      // Count seconds on the trace device.
      trace_printf("Second %u\n", seconds);
    }
  // Infinite loop, never return.
}

static volatile u32 sTicks = 0;

OS_ISR_HANDLER(SysTick_Handler)
{
	++sTicks;
	Timer::tick();
}

static void Task1(void *arg)
{
	(void)arg;

	BlinkLed led(LED4);
	led.powerUp();

	while(OS_TRUE)
	{
		led.turnOn();
		OS_Time_Delay(OS_TIME_TICKS_PER_SEC);
		led.turnOff();
		OS_Time_Delay(OS_TIME_TICKS_PER_SEC);
	}
}

static void Task2(void *arg)
{
	(void)arg;

	BlinkLed led(LED5);
	led.powerUp();

	while(OS_TRUE)
	{
		led.turnOn();
		OS_Time_Delay(OS_TIME_TICKS_PER_SEC);
		led.turnOff();
		OS_Time_Delay(OS_TIME_TICKS_PER_SEC);
	}
}

static void Task3(void *arg)
{
	(void)arg;

	u32 ulCtr = 0;

	while(OS_TRUE)
	{
		ulCtr++;
		OS_Time_Delay(OS_TIME_TICKS_PER_SEC);
	}
}

static void Task4(void *arg)
{
	(void)arg;

	BlinkLed led(LED6);
	led.powerUp();

	while(OS_TRUE)
	{
		led.turnOn();
		OS_Time_Delay(OS_TIME_TICKS_PER_SEC);
		led.turnOff();
		OS_Time_Delay(OS_TIME_TICKS_PER_SEC);
	}
}

static void Task5(void *arg)
{
	(void)arg;

	u32 ulCtr = 0;

	while(OS_TRUE)
	{
		ulCtr++;
		OS_Time_Delay(OS_TIME_TICKS_PER_SEC);
	}
}

static void Task6(void *arg)
{
	(void)arg;

	u32 ulCtr = 0;

	while(OS_TRUE)
	{
		ulCtr++;
		OS_Time_Delay(OS_TIME_TICKS_PER_SEC);
	}
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
