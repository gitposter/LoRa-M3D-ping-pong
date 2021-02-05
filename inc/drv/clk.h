/*
 ******************************************************************************
 * @file    drv/clk_conf.h
 * @module  clk_conf
 * @author  Mohamed Hnezli
 * @version V0.2
 * @date    12-04-2019
 * @brief   system clocks configuration utilities.
 ******************************************************************************
 * @attention
 *
 * - The present software had been tested only on STM32F3CCTx and may be non
 * functional on other targets.
 *
 * <h2><center>&copy COPYRIGHT 2019 Mohamed Hnezli </center></h2>
 ******************************************************************************
 */

#ifndef CLK_H_
#define CLK_H_

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/* include ------------------------------------------------------------------ */
/* define ------------------------------------------------------------------- */
/*
 * @brief ENABLE/DISABLE PLL USE
 */
#define CLK_USE_PLL          1


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
clk_sysconf (void);

/*
 * @name:   clk_conf_ssd1306.
 * @brief:  configures clocks for SSD1306 module.
 * @param:  none.
 * @retval: none.
 */
void
clk_conf_ssd1306 (void);

/*
 * @name:   clk_conf_sx1276.
 * @brief:  configures clocks for SX1276 module.
 * @param:  none.
 * @retval: none.
 */
void
clk_conf_sx1276 (void);

/*
 * @name:   clk_sysconf.
 * @brief:  configures clocks for SSD1306 module.
 * @param:  none.
 * @retval: none.
 */
void
clk_conf_led (void);

/*
 * @name:   clk_delay.
 * @brief:  active delay function to be used in driver layer mainly.
 * @param:  ms: number of milliseconds to stop.
 * @retval: none.
 */
#define clk_delay(ms)        HAL_Delay(ms);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CLK_H_ */
