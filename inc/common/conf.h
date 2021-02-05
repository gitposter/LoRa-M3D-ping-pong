/*
 ******************************************************************************
 * @file    inc/conf.h
 * @module  cross module
 * @author  Mohamed Hnezli
 * @version V0.2
 * @date    12-04-2019
 * @brief   project wide configuration file.
 ******************************************************************************
 * @attention
 *
 * - The present software had been tested only on STM32F3CCTx and may be non
 * functional on other targets.
 *
 * <h2><center>&copy COPYRIGHT 2019 Mohamed Hnezli </center></h2>
 ******************************************************************************
 */

#ifndef CONF_H_
#define CONF_H_

/* include ------------------------------------------------------------------ */
#include <stdbool.h>                   // boolean values
#include <stdint.h>                    // custom integer types


/* define ------------------------------------------------------------------- */
/*
 * @brief peripheral allocation
 */
#define CONF_I2C_SSD1306               I2C1
#define CONF_SPI_SX1276                SPI1

/*
 * @brief GPIO connections
 */
#define CONF_GPIO_SX1276_RST           GPIOA
#define CONF_PIN_SX1276_RST            GPIO_PIN_2
#define CONF_GPIO_SX1276_DIO0          GPIOA
#define CONF_PIN_SX1276_DIO0           GPIO_PIN_3
#define CONF_GPIO_SX1276_SPI           GPIOA
#define CONF_PIN_SX1276_NSS            GPIO_PIN_4
#define CONF_PIN_SX1276_SCK            GPIO_PIN_5
#define CONF_PIN_SX1276_MISO           GPIO_PIN_6
#define CONF_PIN_SX1276_MOSI           GPIO_PIN_7
#define CONF_GPIO_SSD1306_RST          GPIOB
#define CONF_PIN_SSD1306_RST           GPIO_PIN_5
#define CONF_GPIO_SSD1306_I2C          GPIOB
#define CONF_PIN_SSD1306_SCL           GPIO_PIN_6
#define CONF_PIN_SSD1306_SDA           GPIO_PIN_7
#define CONF_GPIO_LED                  GPIOC
#define CONF_PIN_LED                   GPIO_PIN_13


/* typedef ------------------------------------------------------------------ */
/* variable ----------------------------------------------------------------- */
/* class -------------------------------------------------------------------- */
/* method ------------------------------------------------------------------- */
/* function ----------------------------------------------------------------- */


#endif /* CONF_H_ */
