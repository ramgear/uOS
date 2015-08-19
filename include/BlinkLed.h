//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#ifndef BLINKLED_H_
#define BLINKLED_H_

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

#include "os_types.h"

// ----- LED definitions ------------------------------------------------------

// Adjust these definitions for your own board.

#define BLINK_GPIOx(_N)                 ((GPIO_TypeDef *)(GPIOA_BASE + (GPIOB_BASE-GPIOA_BASE)*(_N)))
#define BLINK_PIN_MASK(_N)              (1 << (_N))
#define BLINK_RCC_MASKx(_N)             (RCC_AHB1ENR_GPIOAEN << (_N))

static const u32 LED_PORTn[] 	= { 3, 3, 3, 3 };
static const u32 LED_PINn[] 	= { 13, 12, 14, 15 };

typedef enum
{
	LED3,
	LED4,
	LED5,
	LED6,
} LEDs;
// ----------------------------------------------------------------------------

class BlinkLed
{
private:
	LEDs	mLed;
public:
  BlinkLed(LEDs led) : mLed(led) {

  }

  void
  powerUp();

  inline void
  __attribute__((always_inline))
  turnOn()
  {
	  HAL_GPIO_WritePin(BLINK_GPIOx(LED_PORTn[mLed]),
      BLINK_PIN_MASK(LED_PINn[mLed]), GPIO_PIN_SET);
  }

  inline void
  __attribute__((always_inline))
  turnOff()
  {
	  HAL_GPIO_WritePin(BLINK_GPIOx(LED_PORTn[mLed]),
      BLINK_PIN_MASK(LED_PINn[mLed]), GPIO_PIN_RESET);
  }
};

// ----------------------------------------------------------------------------

#endif // BLINKLED_H_
