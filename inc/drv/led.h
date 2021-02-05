/*
 ******************************************************************************
 * @file    drv/led.h
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

#ifndef LED_H_
#define LED_H_

/* include ------------------------------------------------------------------ */
#include "stm32f3xx.h"                 // GPIO driver
#include <stdint.h>                    // custom integer types


/* define ------------------------------------------------------------------- */
/* typedef ------------------------------------------------------------------ */
/* variable ----------------------------------------------------------------- */
/* class -------------------------------------------------------------------- */
class led
{
public:
  /*
   * @name:   led.
   * @brief:  constructor that initializes GPIO pin.
   * @param:  gpio: port.
   *          pin: pin number.
   * @retval: none.
   */
  led (GPIO_TypeDef* gpio, uint32_t pin);

  /*
   * @name:   ~led.
   * @brief:  destructor that liberates GPIO pin.
   * @param:  none.
   * @retval: none.
   */
  ~led ();

  /*
   * @name:   on.
   * @brief:  turns on the LED.
   * @param:  none.
   * @retval: none.
   */
  void
  on (void);

  /*
   * @name:   off.
   * @brief:  turns off the LED.
   * @param:  none.
   * @retval: none.
   */
  void
  off (void);

  /*
   * @name:   toggle.
   * @brief:  inverts LED's status.
   * @param:  none.
   * @retval: none.
   */
  void
  toggle (void);

private:
  GPIO_TypeDef* gpio_;
  uint32_t pin_;
};


/* method ------------------------------------------------------------------- */
/* function ----------------------------------------------------------------- */



#endif /* LED_H_ */
