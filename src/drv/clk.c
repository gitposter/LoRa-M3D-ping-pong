/*
 ******************************************************************************
 * @file    drv/clk_conf.cpp
 * @module  clk_conf
 * @author  Mohamed Hnezli
 * @version V0.2
 * @date    12-04-2019
 * @brief   implements system clocks configuration utilities.
 ******************************************************************************
 * @attention
 *
 * - The present software had been tested only on STM32F3CCTx and may be non
 * functional on other targets.
 *
 * <h2><center>&copy COPYRIGHT 2019 Mohamed Hnezli </center></h2>
 ******************************************************************************
 */

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/* include ------------------------------------------------------------------ */
#include "drv/clk.h"                   // header file
#include "stm32f3xx.h"                 // MCU HAL
#include "common/error.h"              // error_critical


/* define ------------------------------------------------------------------- */
/* typedef ------------------------------------------------------------------ */
/* variable ----------------------------------------------------------------- */
/* class -------------------------------------------------------------------- */
/* method ------------------------------------------------------------------- */
/* function ----------------------------------------------------------------- */
/*
 * @name:   clk_sysconf.
 * @brief:  configures system clock and enable Systick IRQ.
 * @param:  none.
 * @retval: none.
 */
void
clk_sysconf (void)
{
  RCC_OscInitTypeDef rcc_osc = {0};
  RCC_ClkInitTypeDef rcc_clk = {0};

  /* SysClk = (PLL_N * (HSI_VALUE / PLL_M)) / PLL_P   is subject to:
   * Freq(AHB)  < 168MHz
   * Freq(APB)  < 42MHz
   * Freq(APB2) < 84MHz */
  rcc_osc.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSE;
  rcc_osc.HSEState = RCC_HSE_ON;
  rcc_osc.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  rcc_osc.HSIState = RCC_HSI_ON;
  rcc_osc.HSICalibrationValue = 16;
  rcc_osc.PLL.PLLState = RCC_PLL_ON;
  rcc_osc.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  rcc_osc.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&rcc_osc) != HAL_OK)
    {
	  error_critical((const char*)__FILE__, __LINE__);
    }

  /* initialize the SysClk and AHB and APB busses clocks */
  rcc_clk.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                      |RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  rcc_clk.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  rcc_clk.AHBCLKDivider = RCC_SYSCLK_DIV1;
  rcc_clk.APB1CLKDivider = RCC_HCLK_DIV2;
  rcc_clk.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&rcc_clk, FLASH_LATENCY_2) != HAL_OK)
    {
      error_critical(__FILE__, __LINE__);
    }


  /* configure the Systick interrupt time */
  HAL_SYSTICK_Config (HAL_RCC_GetHCLKFreq () / 1000);

  /* Configure the Systick */
  HAL_SYSTICK_CLKSourceConfig (SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority (SysTick_IRQn, 0, 0);     // highest IRQs

  return;
}

/*
 * @name:   clk_conf_ssd1306.
 * @brief:  configures clocks for SSD1306 module.
 * @param:  none.
 * @retval: none.
 */
void
clk_conf_ssd1306 (void)
{
  RCC_PeriphCLKInitTypeDef pclk = {0};

  pclk.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  pclk.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&pclk) != HAL_OK)
    {
      error_critical(__FILE__, __LINE__);
    }

  /* enable needed clocks */
  if (__HAL_RCC_GPIOB_IS_CLK_DISABLED())
    {
      __HAL_RCC_GPIOB_CLK_ENABLE();
    }

  /* enable interface clock */
  if (__HAL_RCC_I2C1_IS_CLK_DISABLED())
    {
      __HAL_RCC_I2C1_CLK_ENABLE();
    }

  return;
}

/*
 * @name:   clk_conf_sx1276.
 * @brief:  configures clocks for SX1276 module.
 * @param:  none.
 * @retval: none.
 */
void
clk_conf_sx1276 (void)
{
  /* enable needed clocks */
  if (__HAL_RCC_GPIOA_IS_CLK_DISABLED())
    {
      __HAL_RCC_GPIOA_CLK_ENABLE();
    }

  /* enable interface clock */
  if (__HAL_RCC_SPI1_IS_CLK_DISABLED())
    {
      __HAL_RCC_SPI1_CLK_ENABLE();
    }

  return;
}

/*
 * @name:   clk_sysconf.
 * @brief:  configures clocks for SSD1306 module.
 * @param:  none.
 * @retval: none.
 */
void
clk_conf_led (void)
{
  /* enable needed clocks */
  if (__HAL_RCC_GPIOC_IS_CLK_DISABLED())
    {
      __HAL_RCC_GPIOC_CLK_ENABLE();
    }

  return;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

