/*
 * Copyright 2020, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_reset.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.reset"
#endif

#define PCC_CLKCFG_SWRST_MASK (0x10000000U)

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Assert reset to peripheral.
 *
 * Asserts reset signal to specified peripheral module.
 *
 * param peripheral Assert reset to this peripheral.
 */
void RESET_SetPeripheralReset(reset_ip_name_t peripheral)
{
    volatile uint32_t *pccReg = (volatile uint32_t *)(uint32_t)peripheral;

    if (pccReg != NULL)
    {
        *pccReg &= ~PCC_CLKCFG_SWRST_MASK;
    }
}

/*!
 * brief Clear reset to peripheral.
 *
 * Clears reset signal to specified peripheral module, allows it to operate.
 *
 * param peripheral Clear reset to this peripheral.
 */
void RESET_ClearPeripheralReset(reset_ip_name_t peripheral)
{
    volatile uint32_t *pccReg = (volatile uint32_t *)(uint32_t)peripheral;

    if (pccReg != NULL)
    {
        *pccReg |= PCC_CLKCFG_SWRST_MASK;
    }
}

/*!
 * brief Reset peripheral module.
 *
 * Reset peripheral module.
 *
 * param peripheral Peripheral to reset.
 */
void RESET_PeripheralReset(reset_ip_name_t peripheral)
{
    RESET_SetPeripheralReset(peripheral);
    RESET_ClearPeripheralReset(peripheral);
}
