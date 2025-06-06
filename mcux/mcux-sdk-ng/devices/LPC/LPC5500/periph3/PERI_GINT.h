/*
** ###################################################################
**     Processors:          LPC5502JBD64
**                          LPC5502JHI48
**                          LPC5502JHI48CPXXXX
**                          LPC5504JBD64
**                          LPC5504JHI48
**                          LPC5504JHI48CPXXXX
**                          LPC5506JBD64
**                          LPC5506JHI48
**                          LPC5506JHI48CPXXXX
**                          LPC55S04JBD64
**                          LPC55S04JHI48
**                          LPC55S06JBD64
**                          LPC55S06JHI48
**
**     Version:             rev. 1.0, 2020-04-09
**     Build:               b240704
**
**     Abstract:
**         CMSIS Peripheral Access Layer for GINT
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2024 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2020-04-09)
**         Initial version based on Niobe4mini
**
** ###################################################################
*/

/*!
 * @file GINT.h
 * @version 1.0
 * @date 2020-04-09
 * @brief CMSIS Peripheral Access Layer for GINT
 *
 * CMSIS Peripheral Access Layer for GINT
 */

#if !defined(GINT_H_)
#define GINT_H_                                  /**< Symbol preventing repeated inclusion */

#if (defined(CPU_LPC5502JBD64) || defined(CPU_LPC5502JHI48))
#include "LPC5502_COMMON.h"
#elif (defined(CPU_LPC5502JHI48CPXXXX))
#include "LPC5502CPXXXX_COMMON.h"
#elif (defined(CPU_LPC5504JBD64) || defined(CPU_LPC5504JHI48))
#include "LPC5504_COMMON.h"
#elif (defined(CPU_LPC5504JHI48CPXXXX))
#include "LPC5504CPXXXX_COMMON.h"
#elif (defined(CPU_LPC5506JBD64) || defined(CPU_LPC5506JHI48))
#include "LPC5506_COMMON.h"
#elif (defined(CPU_LPC5506JHI48CPXXXX))
#include "LPC5506CPXXXX_COMMON.h"
#elif (defined(CPU_LPC55S04JBD64) || defined(CPU_LPC55S04JHI48))
#include "LPC55S04_COMMON.h"
#elif (defined(CPU_LPC55S06JBD64) || defined(CPU_LPC55S06JHI48))
#include "LPC55S06_COMMON.h"
#else
  #error "No valid CPU defined!"
#endif

/* ----------------------------------------------------------------------------
   -- Device Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_access_layer Device Peripheral Access Layer
 * @{
 */


/*
** Start of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic push
  #else
    #pragma push
    #pragma anon_unions
  #endif
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

/* ----------------------------------------------------------------------------
   -- GINT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GINT_Peripheral_Access_Layer GINT Peripheral Access Layer
 * @{
 */

/** GINT - Size of Registers Arrays */
#define GINT_PORT_POL_COUNT                       2u
#define GINT_PORT_ENA_COUNT                       2u

/** GINT - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< GPIO grouped interrupt control register, offset: 0x0 */
       uint8_t RESERVED_0[28];
  __IO uint32_t PORT_POL[GINT_PORT_POL_COUNT];     /**< GPIO grouped interrupt port 0 polarity register, array offset: 0x20, array step: 0x4 */
       uint8_t RESERVED_1[24];
  __IO uint32_t PORT_ENA[GINT_PORT_ENA_COUNT];     /**< GPIO grouped interrupt port 0 enable register, array offset: 0x40, array step: 0x4 */
} GINT_Type;

/* ----------------------------------------------------------------------------
   -- GINT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GINT_Register_Masks GINT Register Masks
 * @{
 */

/*! @name CTRL - GPIO grouped interrupt control register */
/*! @{ */

#define GINT_CTRL_INT_MASK                       (0x1U)
#define GINT_CTRL_INT_SHIFT                      (0U)
/*! INT - Group interrupt status. This bit is cleared by writing a one to it. Writing zero has no effect.
 *  0b0..No request. No interrupt request is pending.
 *  0b1..Request active. Interrupt request is active.
 */
#define GINT_CTRL_INT(x)                         (((uint32_t)(((uint32_t)(x)) << GINT_CTRL_INT_SHIFT)) & GINT_CTRL_INT_MASK)

#define GINT_CTRL_COMB_MASK                      (0x2U)
#define GINT_CTRL_COMB_SHIFT                     (1U)
/*! COMB - Combine enabled inputs for group interrupt
 *  0b0..Or. OR functionality: A grouped interrupt is generated when any one of the enabled inputs is active (based on its programmed polarity).
 *  0b1..And. AND functionality: An interrupt is generated when all enabled bits are active (based on their programmed polarity).
 */
#define GINT_CTRL_COMB(x)                        (((uint32_t)(((uint32_t)(x)) << GINT_CTRL_COMB_SHIFT)) & GINT_CTRL_COMB_MASK)

#define GINT_CTRL_TRIG_MASK                      (0x4U)
#define GINT_CTRL_TRIG_SHIFT                     (2U)
/*! TRIG - Group interrupt trigger
 *  0b0..Edge-triggered.
 *  0b1..Level-triggered.
 */
#define GINT_CTRL_TRIG(x)                        (((uint32_t)(((uint32_t)(x)) << GINT_CTRL_TRIG_SHIFT)) & GINT_CTRL_TRIG_MASK)
/*! @} */

/*! @name PORT_POL - GPIO grouped interrupt port 0 polarity register */
/*! @{ */

#define GINT_PORT_POL_POL_MASK                   (0xFFFFFFFFU)
#define GINT_PORT_POL_POL_SHIFT                  (0U)
/*! POL - Configure pin polarity of port m pins for group interrupt. Bit n corresponds to pin PIOm_n
 *    of port m. 0 = the pin is active LOW. If the level on this pin is LOW, the pin contributes to
 *    the group interrupt. 1 = the pin is active HIGH. If the level on this pin is HIGH, the pin
 *    contributes to the group interrupt.
 */
#define GINT_PORT_POL_POL(x)                     (((uint32_t)(((uint32_t)(x)) << GINT_PORT_POL_POL_SHIFT)) & GINT_PORT_POL_POL_MASK)
/*! @} */

/*! @name PORT_ENA - GPIO grouped interrupt port 0 enable register */
/*! @{ */

#define GINT_PORT_ENA_ENA_MASK                   (0xFFFFFFFFU)
#define GINT_PORT_ENA_ENA_SHIFT                  (0U)
/*! ENA - Enable port 0 pin for group interrupt. Bit n corresponds to pin Pm_n of port m. 0 = the
 *    port 0 pin is disabled and does not contribute to the grouped interrupt. 1 = the port 0 pin is
 *    enabled and contributes to the grouped interrupt.
 */
#define GINT_PORT_ENA_ENA(x)                     (((uint32_t)(((uint32_t)(x)) << GINT_PORT_ENA_ENA_SHIFT)) & GINT_PORT_ENA_ENA_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group GINT_Register_Masks */


/*!
 * @}
 */ /* end of group GINT_Peripheral_Access_Layer */


/*
** End of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic pop
  #else
    #pragma pop
  #endif
#elif defined(__GNUC__)
  /* leave anonymous unions enabled */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=default
#else
  #error Not supported compiler type
#endif

/*!
 * @}
 */ /* end of group Peripheral_access_layer */


#endif  /* GINT_H_ */

