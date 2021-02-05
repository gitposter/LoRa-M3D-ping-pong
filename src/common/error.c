/*
 ******************************************************************************
 * @file    common/error.cpp
 * @module  cross module
 * @author  Mohamed Hnezli
 * @version V0.2
 * @date    12-04-2019
 * @brief   implements error handling utilities.
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
#include "common/error.h"              // header file


/* define ------------------------------------------------------------------- */
/* typedef ------------------------------------------------------------------ */
/* variable ----------------------------------------------------------------- */
/* class -------------------------------------------------------------------- */
/* method ------------------------------------------------------------------- */
/* function ----------------------------------------------------------------- */
/*
 * @name:   error_critical.
 * @brief:  halts program on system failure.
 * @param:  file: file name macro.
 *          line: line macro.
 * @retval: none.
 */
void
error_critical (const char * file, int line)
{
  while (1)
    {
      ;  // halt program
    }
}
