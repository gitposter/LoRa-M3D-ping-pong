/*
 ******************************************************************************
 * @file    common/error.h
 * @module  cross module
 * @author  Mohamed Hnezli
 * @version V0.2
 * @date    12-04-2019
 * @brief   defines error handling utilities.
 ******************************************************************************
 * @attention
 *
 * - The present software had been tested only on STM32F3CCTx and may be non
 * functional on other targets.
 *
 * <h2><center>&copy COPYRIGHT 2019 Mohamed Hnezli </center></h2>
 ******************************************************************************
 */

#ifndef ERROR_H_
#define ERROR_H_

/* include ------------------------------------------------------------------ */
/* define ------------------------------------------------------------------- */
/*
 * @brief return error codes
 * @note  all error value must be 32-bit negative integers
 */
#define EUNKNOWN             (int32_t(-1))       // unknown error has occurred
#define ENOERR               (int32_t(0))        // no known error has occurred


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
error_critical (const char* file, int line);


#endif /* ERROR_H_ */
