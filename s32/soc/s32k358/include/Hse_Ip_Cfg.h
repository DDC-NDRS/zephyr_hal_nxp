/*
 * Copyright 2025 NXP
*
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef HSE_IP_CFG_H
#define HSE_IP_CFG_H

/**
*   @file
*
*   @addtogroup CRYPTO
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "S32K358_MU.h"
#include "OsIf.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define HSE_IP_CFG_VENDOR_ID_H                       43
#define HSE_IP_CFG_MODULE_ID_H                       114
#define HSE_IP_CFG_AR_RELEASE_MAJOR_VERSION_H        4
#define HSE_IP_CFG_AR_RELEASE_MINOR_VERSION_H        7
#define HSE_IP_CFG_AR_RELEASE_REVISION_VERSION_H     0
#define HSE_IP_CFG_SW_MAJOR_VERSION_H                3
#define HSE_IP_CFG_SW_MINOR_VERSION_H                0
#define HSE_IP_CFG_SW_PATCH_VERSION_H                0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/* Pre-processor switch to enable/disable development error detection for Hse Ip API */
#define HSE_IP_DEV_ERROR_DETECT                  (STD_OFF)

/* OsIf counter type used in timeout detection for HSE IP service request */
#define HSE_IP_TIMEOUT_OSIF_COUNTER_TYPE         (OSIF_COUNTER_DUMMY)

/* S32K358 only routes MU_0 and MU_1 to the HSE firmware core (a third instance, MU_2, is
 * core-to-core only and is not used for HSE communication).
 */
#define MU_HOST_BASE_PTRS                        { IP_MU_0__MUB, IP_MU_1__MUB }

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* HSE_IP_CFG_H */
