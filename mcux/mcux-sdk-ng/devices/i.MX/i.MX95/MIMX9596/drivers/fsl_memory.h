/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_MEMORY_H_
#define _FSL_MEMORY_H_

#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*@{*/
/*! @brief MEMORY driver version 1.0.0. */
#define FSL_MEMORY_DRIVER_VERSION (MAKE_VERSION(1, 0, 0))
/*@}*/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.memory"
#endif

#if (__CORTEX_M == 33U)
/* The CM33 subsystem local TCM start address, refer to Reference Manual for detailed information */
#define FSL_MEM_M33_TCM_BEGIN 0x20000000U
/* The CM33 subsystem local TCM end address, refer to Reference Manual for detailed information */
#define FSL_MEM_M33_TCM_END 0x2003FFFFU

#define FSL_MEM_M33_TCM_OFFSET 0x200000U
#elif (__CORTEX_M == 7U)
/* The CM7 subsystem local TCM start address, refer to Reference Manual for detailed information */
#define FSL_MEM_M7_TCM_BEGIN 0x20000000U
/* The CM7 subsystem local TCM end address, refer to Reference Manual for detailed information */
#define FSL_MEM_M7_TCM_END 0x2007FFFFU

#define FSL_MEM_M7_TCM_OFFSET 0x400000U
#else
#error "Device is not supported by this driver!"
#endif

typedef enum _mem_direction
{
    kMEMORY_Local2DMA = 0,
    kMEMORY_DMA2Local,
} mem_direction_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif
/*!
 * @brief Convert the memory map address.
 *
 * This function convert the address between system mapped address and native mapped address.
 * There maybe offset between subsystem native address and system address for some memory,
 * this funciton convert the address to different memory map.
 * @param addr address need to be converted.
 * @param direction convert direction.
 * @return the converted address
 */
static inline uint32_t MEMORY_ConvertMemoryMapAddress(uint32_t addr, mem_direction_t direction)
{
    uint32_t dest;

    switch (direction)
    {
        case kMEMORY_Local2DMA:
        {
#if (__CORTEX_M == 33U)
            if ((addr >= FSL_MEM_M33_TCM_BEGIN) && (addr <= FSL_MEM_M33_TCM_END))
            {
                dest = addr + FSL_MEM_M33_TCM_OFFSET;
            }
#elif (__CORTEX_M == 7U)
            if ((addr >= FSL_MEM_M7_TCM_BEGIN) && (addr <= FSL_MEM_M7_TCM_END))
            {
                dest = addr + FSL_MEM_M7_TCM_OFFSET;
            }
#endif
            else
            {
                dest = addr;
            }
            break;
        }
        case kMEMORY_DMA2Local:
        {
#if (__CORTEX_M == 33U)
            if ((addr >= (FSL_MEM_M33_TCM_BEGIN + FSL_MEM_M33_TCM_OFFSET)) &&
                (addr <= (FSL_MEM_M33_TCM_END + FSL_MEM_M33_TCM_OFFSET)))
            {
                dest = addr - FSL_MEM_M33_TCM_OFFSET;
            }
#elif (__CORTEX_M == 7U)
            if ((addr >= (FSL_MEM_M7_TCM_BEGIN + FSL_MEM_M7_TCM_OFFSET)) &&
                (addr <= (FSL_MEM_M7_TCM_END + FSL_MEM_M7_TCM_OFFSET)))
            {
                dest = addr - FSL_MEM_M7_TCM_OFFSET;
            }
#endif
            else
            {
                dest = addr;
            }
            break;
        }
        default:
            dest = addr;
            break;
    }

    return dest;
}
#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* _FSL_MEMORY_H_ */
