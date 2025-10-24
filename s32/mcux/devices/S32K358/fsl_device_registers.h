/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __FSL_DEVICE_REGISTERS_H__
#define __FSL_DEVICE_REGISTERS_H__

/*
 * Include the cpu specific register header files.
 *
 * The CPU macro should be declared in the project or makefile.
 */

#if defined(CPU_S32K358)

#define S32K358_SERIES

/* CMSIS-style register definitions */
#include "S32K358.h"
/* CPU specific feature definitions */
#include "S32K358_features.h"

/*
 * In order to reuse RTD CMSIS-based headers for the MCUX drivers, is needed
 * to redefine the peripheral macros from IP_PERIPHERAL_n to PERIPHERALn.
 */
#include "S32K358_glue_mcux.h"

/*
 * RTD header S32K358_COMMON.h already defined the code configuration for CMSIS,
 * so include the CMSIS core header here since it's needed for some common
 * functions of MCUX.
 */
#include "core_cm7.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */
