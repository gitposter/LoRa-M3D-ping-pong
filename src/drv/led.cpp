/*
 ******************************************************************************
 * @file    drv/led.cpp
 * @module  led
 * @author  Mohamed Hnezli
 * @version V0.2
 * @date    12-04-2019
 * @brief   implements LED control API.
 ******************************************************************************
 * @attention
 *
 * - The present software had been tested only on STM32F3CCTx and may be non
 * functional on other targets.
 *
 * <h2><center>&copy COPYRIGHT 2019 Mohamed Hnezli </center></h2>
 ******************************************************************************
 */

/* include ------------------------------------------------------------------ */
#include "drv/led.h"                   // header file
#include "stm32f3xx.h"                 // GPIO driver


/* define ------------------------------------------------------------------- */
/* typedef ------------------------------------------------------------------ */
/* variable ----------------------------------------------------------------- */
/* class -------------------------------------------------------------------- */
/* method ------------------------------------------------------------------- */
/* function ----------------------------------------------------------------- */
/*
 * @name:   led.
 * @brief:  constructor that initializes GPIO pin.
 * @param:  gpio: port.
 *          pin: pin number.
 * @retval: none.
 */
led::led (GPIO_TypeDef* gpio, uint32_t pin)
: gpio_(gpio), pin_(pin)
{
  /*Configure GPIO pin : PC13 */
  GPIO_InitTypeDef gpio_init;
  gpio_init.Pin = pin_;
  gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
  gpio_init.Pull = GPIO_NOPULL;
  gpio_init.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(gpio_, &gpio_init);
}

/*
 * @name:   ~led.
 * @brief:  destructor that liberates GPIO pin.
 * @param:  none.
 * @retval: none.
 */
led::~led ()
{
  HAL_GPIO_DeInit (gpio_, pin_);
}

/*
 * @name:   on.
 * @brief:  turns on the LED.
 * @param:  none.
 * @retval: none.
 */
void
led::on ()
{
  HAL_GPIO_WritePin (gpio_, pin_, GPIO_PIN_SET);

  return;
}

/*
 * @name:   off.
 * @brief:  turns off the LED.
 * @param:  none.
 * @retval: none.
 */
void
led::off (void)
{
  HAL_GPIO_WritePin (gpio_, pin_, GPIO_PIN_RESET);

  return;
}

/*
 * @name:   toggle.
 * @brief:  inverts LED's status.
 * @param:  none.
 * @retval: none.
 */
void
led::toggle (void)
{
  HAL_GPIO_TogglePin (gpio_, pin_);

  return;
}
