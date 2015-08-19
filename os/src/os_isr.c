/**
 ******************************************************************************
 * @file	os_isr.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	19-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "os_isr.h"
#include "os_cpu.h"
#include "os_sched.h"
#include "os.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static u32	sISRNestingCtr	= 0u;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
 * @brief	Enter interrupt service routine calling.
 * @param	None.
 * @return	None.
 */
inline void
OS_ISR_Enter(void)
{
	/* Check OS running */
	if(!OS_IsRunning())
		return;

	++sISRNestingCtr;
}

/**
 * @brief	Exit interrupt service routine calling.
 * @param	None.
 * @return	None.
 */
inline void
OS_ISR_Exit(void)
{
	OS_CPU_SR_ALLOC();

	/* Check OS running */
	if(!OS_IsRunning())
		return;

	OS_CPU_ENTER_CRITICAL();

	if(sISRNestingCtr == 0)	/* Prevent ISR nesting wrapping */
	{
		--sISRNestingCtr;	/* Reduce nesting counter */

		if(sISRNestingCtr == 0)			/* No nesting ? */
		{
			if(!OS_Sched_IsLocking())	/* Not scheduler lock */
			{
				if(OS_Sched_PrepareHighReady())	/* Higher priority ready ? */
				{
					/* Perform context switch */
					OS_CPU_CtxSw();
				}
			}
		}
	}

	OS_CPU_EXIT_CRITICAL();
}

/**
 * @brief	Check for is in interrupt service routine calling.
 * @param	None.
 * @return	TRUE if call from ISR. Otherwise, FALSE.
 */
inline bool
OS_ISR_IsNesting(void)
{
	return (sISRNestingCtr != 0);
}

/*****************************END OF FILE**************************************/
