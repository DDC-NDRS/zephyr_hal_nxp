/*
 * Copyright 2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef HSE_IP_CFG_H
#define HSE_IP_CFG_H

/*==================================================================================================
*                                          INCLUDE FILES
==================================================================================================*/
#include "S32K358_MU.h"
#include "OsIf.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define HSE_IP_CFG_VENDOR_ID_H                      43
#define HSE_IP_CFG_SW_MAJOR_VERSION_H               3
#define HSE_IP_CFG_SW_MINOR_VERSION_H               0
#define HSE_IP_CFG_SW_PATCH_VERSION_H               0

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/* S32K358 only routes MU_0 and MU_1 to the HSE firmware core (MU_2 is core-to-core only). */
#define HSE_IP_MU_0                          ((uint8)0U)
#define HSE_IP_MU_1                          ((uint8)1U)

/* Max number of MU instances usable for HSE host<->firmware communication */
#define HSE_IP_NUM_OF_MU_INSTANCES               (2)

/* Max number of channels per MU interface (compile-time array bound; actual per-channel
 * availability is polled from hardware at runtime via Hse_Ip_GetFreeChannel()). */
#define HSE_IP_NUM_OF_CHANNELS_PER_MU            (16)

/* Pre-processor switch to enable/disable development error detection for Hse Ip API */
#define HSE_IP_DEV_ERROR_DETECT                  (STD_OFF)

/* OsIf counter type used in timeout detection for HSE IP service request */
#define HSE_IP_TIMEOUT_OSIF_COUNTER_TYPE         (OSIF_COUNTER_DUMMY)

/* Support for Hse operations using TCM addresses */
#define HSE_IP_ENABLE_TCM_SUPPORT                       (STD_OFF)

/* Initializer for the MU Host base addresses (S32K358 device header names these with an
 * underscore - IP_MU_0__MUB/IP_MU_1__MUB - unlike the S32Z/E naming this Hse_Ip/Mu_Ip pair was
 * originally written against). */
#define MU_HOST_BASE_PTRS                        { IP_MU_0__MUB, IP_MU_1__MUB }

/* crypto_nxp_s32_hse.c (drivers/crypto/crypto_nxp_s32_hse.c) resolves a devicetree instance's MU
 * number by token-pasting IP_MU##indx##__MUB_BASE, matching the S32Z/E device header naming
 * (IP_MU0__MUB_BASE). Alias the S32K358 names (IP_MU_0__MUB_BASE) so that driver works unmodified
 * on S32K3 too. */
#define IP_MU0__MUB_BASE                         IP_MU_0__MUB_BASE
#define IP_MU1__MUB_BASE                         IP_MU_1__MUB_BASE

#endif /* HSE_IP_CFG_H */
