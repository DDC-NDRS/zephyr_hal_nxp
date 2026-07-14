/*
 * Copyright 2020-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 *   @file
 *
 *   @addtogroup adc_sar_ip Adc Sar IPL
 *   @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Adc_Sar_Ip.h"
#include "Adc_Sar_Ip_Irq.h"
#include "Adc_Sar_Ip_HwAccess.h"
#include "Adc_Sar_Ip_TrustedFunctions.h"
#include "Reg_eSys.h"
#include "SchM_Adc.h"

#include "OsIf.h"
#include "Devassert.h"

/* local definitions on the limits of the clock frequency */
#define ADC_CLOCK_FREQ_MAX_RUNTIME     (80000000U)
#define ADC_CLOCK_FREQ_MAX_CALIBRATION (40000000U)

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ADC_SAR_IP_VENDOR_ID_C                   43
#define ADC_SAR_IP_AR_RELEASE_MAJOR_VERSION_C    4
#define ADC_SAR_IP_AR_RELEASE_MINOR_VERSION_C    7
#define ADC_SAR_IP_AR_RELEASE_REVISION_VERSION_C 0
#define ADC_SAR_IP_SW_MAJOR_VERSION_C            3
#define ADC_SAR_IP_SW_MINOR_VERSION_C            0
#define ADC_SAR_IP_SW_PATCH_VERSION_C            0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Adc_Sar_Ip.c file and Adc_Sar_Ip.h file are of the same vendor */
#if (ADC_SAR_IP_VENDOR_ID_C != ADC_SAR_IP_VENDOR_ID)
#error "Adc_Sar_Ip.c and Adc_Sar_Ip.h have different vendor ids"
#endif

/* Check if Adc_Sar_Ip.c file and Adc_Sar_Ip.h file are of the same Autosar version */
#if ((ADC_SAR_IP_AR_RELEASE_MAJOR_VERSION_C != ADC_SAR_IP_AR_RELEASE_MAJOR_VERSION) || \
     (ADC_SAR_IP_AR_RELEASE_MINOR_VERSION_C != ADC_SAR_IP_AR_RELEASE_MINOR_VERSION) || \
     (ADC_SAR_IP_AR_RELEASE_REVISION_VERSION_C != ADC_SAR_IP_AR_RELEASE_REVISION_VERSION))
#error "AutoSar Version Numbers of Adc_Sar_Ip.c and Adc_Sar_Ip.h are different"
#endif

/* Check if Adc_Sar_Ip.c file and Adc_Sar_Ip.h file are of the same Software version */
#if ((ADC_SAR_IP_SW_MAJOR_VERSION_C != ADC_SAR_IP_SW_MAJOR_VERSION) || \
     (ADC_SAR_IP_SW_MINOR_VERSION_C != ADC_SAR_IP_SW_MINOR_VERSION) || \
     (ADC_SAR_IP_SW_PATCH_VERSION_C != ADC_SAR_IP_SW_PATCH_VERSION))
#error "Software Version Numbers of Adc_Sar_Ip.c and Adc_Sar_Ip.h are different"
#endif

/* Check if Adc_Sar_Ip.c file and Adc_Sar_Ip_Irq.h file are of the same vendor */
#if (ADC_SAR_IP_VENDOR_ID_C != ADC_SAR_IP_VENDOR_ID_IRQ)
#error "Adc_Sar_Ip.c and Adc_Sar_Ip_Irq.h have different vendor ids"
#endif

/* Check if Adc_Sar_Ip.c file and Adc_Sar_Ip_Irq.h file are of the same Autosar version */
#if ((ADC_SAR_IP_AR_RELEASE_MAJOR_VERSION_C != ADC_SAR_IP_AR_RELEASE_MAJOR_VERSION_IRQ) || \
     (ADC_SAR_IP_AR_RELEASE_MINOR_VERSION_C != ADC_SAR_IP_AR_RELEASE_MINOR_VERSION_IRQ) || \
     (ADC_SAR_IP_AR_RELEASE_REVISION_VERSION_C != ADC_SAR_IP_AR_RELEASE_REVISION_VERSION_IRQ))
#error "AutoSar Version Numbers of Adc_Sar_Ip.c and Adc_Sar_Ip_Irq.h are different"
#endif

/* Check if Adc_Sar_Ip.c file and Adc_Sar_Ip_Irq.h file are of the same Software version */
#if ((ADC_SAR_IP_SW_MAJOR_VERSION_C != ADC_SAR_IP_SW_MAJOR_VERSION_IRQ) || \
     (ADC_SAR_IP_SW_MINOR_VERSION_C != ADC_SAR_IP_SW_MINOR_VERSION_IRQ) || \
     (ADC_SAR_IP_SW_PATCH_VERSION_C != ADC_SAR_IP_SW_PATCH_VERSION_IRQ))
#error "Software Version Numbers of Adc_Sar_Ip.c and Adc_Sar_Ip_Irq.h are different"
#endif

/* Check if Adc_Sar_Ip.c file and Adc_Sar_Ip_HwAccess.h file are of the same vendor */
#if (ADC_SAR_IP_VENDOR_ID_C != ADC_SAR_IP_VENDOR_ID_HWACCESS)
#error "Adc_Sar_Ip.c and Adc_Sar_Ip_HwAccess.h have different vendor ids"
#endif

/* Check if Adc_Sar_Ip.c file and Adc_Sar_Ip_HwAccess.h file are of the same Autosar version */
#if ((ADC_SAR_IP_AR_RELEASE_MAJOR_VERSION_C != ADC_SAR_IP_AR_RELEASE_MAJOR_VERSION_HWACCESS) || \
     (ADC_SAR_IP_AR_RELEASE_MINOR_VERSION_C != ADC_SAR_IP_AR_RELEASE_MINOR_VERSION_HWACCESS) || \
     (ADC_SAR_IP_AR_RELEASE_REVISION_VERSION_C != ADC_SAR_IP_AR_RELEASE_REVISION_VERSION_HWACCESS))
#error "AutoSar Version Numbers of Adc_Sar_Ip.c and Adc_Sar_Ip_HwAccess.h are different"
#endif

/* Check if Adc_Sar_Ip.c file and Adc_Sar_Ip_HwAccess.h file are of the same Software version */
#if ((ADC_SAR_IP_SW_MAJOR_VERSION_C != ADC_SAR_IP_SW_MAJOR_VERSION_HWACCESS) || \
     (ADC_SAR_IP_SW_MINOR_VERSION_C != ADC_SAR_IP_SW_MINOR_VERSION_HWACCESS) || \
     (ADC_SAR_IP_SW_PATCH_VERSION_C != ADC_SAR_IP_SW_PATCH_VERSION_HWACCESS))
#error "Software Version Numbers of Adc_Sar_Ip.c and Adc_Sar_Ip_HwAccess.h are different"
#endif

/* Check if Adc_Sar_Ip.c file and Adc_Sar_Ip_TrustedFunctions.h file are of the same vendor */
#if (ADC_SAR_IP_VENDOR_ID_C != ADC_SAR_IP_VENDOR_ID_TRUSTEDFUNCTIONS)
#error "Adc_Sar_Ip.c and Adc_Sar_Ip_TrustedFunctions.h have different vendor ids"
#endif

/* Check if Adc_Sar_Ip.c file and Adc_Sar_Ip_TrustedFunctions.h file are of the same Autosar version */
#if ((ADC_SAR_IP_AR_RELEASE_MAJOR_VERSION_C != ADC_SAR_IP_AR_RELEASE_MAJOR_VERSION_TRUSTEDFUNCTIONS) || \
     (ADC_SAR_IP_AR_RELEASE_MINOR_VERSION_C != ADC_SAR_IP_AR_RELEASE_MINOR_VERSION_TRUSTEDFUNCTIONS) || \
     (ADC_SAR_IP_AR_RELEASE_REVISION_VERSION_C != ADC_SAR_IP_AR_RELEASE_REVISION_VERSION_TRUSTEDFUNCTIONS))
#error "AutoSar Version Numbers of Adc_Sar_Ip.c and Adc_Sar_Ip_TrustedFunctions.h are different"
#endif

/* Check if Adc_Sar_Ip.c file and Adc_Sar_Ip_TrustedFunctions.h file are of the same Software version */
#if ((ADC_SAR_IP_SW_MAJOR_VERSION_C != ADC_SAR_IP_SW_MAJOR_VERSION_TRUSTEDFUNCTIONS) || \
     (ADC_SAR_IP_SW_MINOR_VERSION_C != ADC_SAR_IP_SW_MINOR_VERSION_TRUSTEDFUNCTIONS) || \
     (ADC_SAR_IP_SW_PATCH_VERSION_C != ADC_SAR_IP_SW_PATCH_VERSION_TRUSTEDFUNCTIONS))
#error "Software Version Numbers of Adc_Sar_Ip.c and Adc_Sar_Ip_TrustedFunctions.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if Adc_Sar_Ip.c file and Reg_eSys.h file are of the same Autosar version */
#if ((ADC_SAR_IP_AR_RELEASE_MAJOR_VERSION_C != REG_ESYS_AR_RELEASE_MAJOR_VERSION) || \
     (ADC_SAR_IP_AR_RELEASE_MINOR_VERSION_C != REG_ESYS_AR_RELEASE_MINOR_VERSION))
#error "AutoSar Version Numbers of Adc_Sar_Ip.c and Reg_eSys.h are different"
#endif

#if defined(ADC_SAR_IP_DEV_ERROR_DETECT)
/* Check if Adc_Sar_Ip.c file and OsIf.h file are of the same Autosar version */
#if ((ADC_SAR_IP_AR_RELEASE_MAJOR_VERSION_C != OSIF_AR_RELEASE_MAJOR_VERSION) || \
     (ADC_SAR_IP_AR_RELEASE_MINOR_VERSION_C != OSIF_AR_RELEASE_MINOR_VERSION))
#error "AutoSar Version Numbers of Adc_Sar_Ip.c and OsIf.h are different"
#endif
#endif /* defined(ADC_SAR_IP_DEV_ERROR_DETECT) */

#if (STD_ON == ADC_SAR_IP_ENABLE_USER_MODE_SUPPORT)
/* Checks against RegLockMacros.h */
#if ((ADC_SAR_IP_AR_RELEASE_MAJOR_VERSION_C != REGLOCKMACROS_AR_RELEASE_MAJOR_VERSION) || \
     (ADC_SAR_IP_AR_RELEASE_MINOR_VERSION_C != REGLOCKMACROS_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR Version Numbers of Adc_Sar_Ip.c and RegLockMacros.h are different"
#endif
#endif /* (STD_ON == ADC_SAR_IP_ENABLE_USER_MODE_SUPPORT) */

/* Check if Adc_Sar_Ip.c file and SchM_Adc.h file are of the same version */
#if ((ADC_SAR_IP_AR_RELEASE_MAJOR_VERSION_C != SCHM_ADC_AR_RELEASE_MAJOR_VERSION) || \
     (ADC_SAR_IP_AR_RELEASE_MINOR_VERSION_C != SCHM_ADC_AR_RELEASE_MINOR_VERSION))
#error "AutoSar Version Numbers of Adc_Sar_Ip.c and SchM_Adc.h are different"
#endif
#endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
/* ADC_SAR_IP_INST_HAS_REG_<bitwidth> macros. Checks the availability of a
    register index based on the availability of the ADC channels
    for the particular u32Instance on the platform.
    <bitwidth> represents the width of the bitfield associated with each
    ADC channel in the register series.
*/
#define ADC_SAR_IP_INST_HAS_REG_4(inst, regIdx) \
    ((Adc_Sar_Ip_au32AdcChanBitmap[inst][(regIdx) / 4U] & (0xFFUL << (((regIdx) % 4U) * 8U))) != 0U)

#define ADC_SAR_IP_INST_HAS_REG_32(inst, regIdx) \
    ((Adc_Sar_Ip_au32AdcChanBitmap[inst][(regIdx) / 32U] & (0x01UL << ((regIdx) % 32U))) != 0U)

/* <bitwidth> = 4. Four bits in the register correspond to one ADC channel */
#define ADC_SAR_IP_INST_HAS_CWSELRn(inst, x) (ADC_SAR_IP_INST_HAS_REG_4(inst, x))

/* <bitwidth> = 32. The entire 4 byte register is associated with one ADC channel */
#define ADC_SAR_IP_INST_HAS_CDRn(inst, n)  (ADC_SAR_IP_INST_HAS_REG_32(inst, n))
#define ADC_SAR_IP_INST_HAS_CHANn(inst, n) (ADC_SAR_IP_INST_HAS_REG_32(inst, n))

#define ADC_SAR_IP_INST_HAS_DSDR(inst) ((Adc_Sar_Ip_au32AdcFeatureBitmap[inst] & (1UL << 0U)) != 0U)
#define ADC_SAR_IP_INST_HAS_PSCR(inst)             ((Adc_Sar_Ip_au32AdcFeatureBitmap[inst] & (1UL << 1U)) != 0U)
#define ADC_SAR_IP_INST_HAS_CTU(inst)              ((Adc_Sar_Ip_au32AdcFeatureBitmap[inst] & (1UL << 2U)) != 0U)
#define ADC_SAR_IP_INST_HAS_CTU_TRIGGER_MODE(inst) ((Adc_Sar_Ip_au32AdcFeatureBitmap[inst] & (1UL << 3U)) != 0U)

/* Macros for watchdog registers to help decode and compose bit mask for the functionality */
#define ADC_SAR_IP_WDG_REG_MASK_HIGH(registerIdx) ((uint32)((uint32)1UL << (((registerIdx) * 2U) + 1U)))
#define ADC_SAR_IP_WDG_REG_MASK_LOW(registerIdx)  ((uint32)((uint32)1UL << ((registerIdx ) * 2U)))

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/
#define ADC_START_SEC_CONST_UNSPECIFIED
#include "Adc_MemMap.h"

/* Table of pBase addresses for ADC instances. */
ADC_Type* const Adc_Sar_Ip_apxAdcBase[ADC_INSTANCE_COUNT] = IP_ADC_BASE_PTRS;
static TEMPSENSE_Type* const Adc_Sar_Ip_apxTempsenseBase[TEMPSENSE_INSTANCE_COUNT] = IP_TEMPSENSE_BASE_PTRS;

/* Not generated by config tooling since no tempsense channel is configured on this project;
   the tempsense API stays compiled in but unused, so a placeholder is enough. */
static const uint16 AdcVoltageRefs[ADC_INSTANCE_COUNT] = {0};

#define ADC_STOP_SEC_CONST_UNSPECIFIED
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Adc_MemMap.h"
/* Global state structure */
static Adc_Sar_Ip_StateStructType Adc_Sar_Ip_axAdcSarState[ADC_SAR_IP_INSTANCE_COUNT];

#define ADC_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Adc_MemMap.h"

#define ADC_START_SEC_CONST_32
#include "Adc_MemMap.h"

static const uint8 Adc_Sar_Ip_au8AdcGroupCount[ADC_SAR_IP_INSTANCE_COUNT] = FEATURE_ADC_MAX_GROUP_COUNT;

static const uint32 Adc_Sar_Ip_au32AdcChanBitmap[ADC_SAR_IP_INSTANCE_COUNT][ADC_SAR_IP_NUM_GROUP_CHAN] =
    FEATURE_ADC_CHN_AVAIL_BITMAP;

static const uint32 Adc_Sar_Ip_au32AdcFeatureBitmap[ADC_SAR_IP_INSTANCE_COUNT] = FEATURE_ADC_FEAT_AVAIL_BITMAP;

static uint16 const AdcChanCount[ADC_SAR_IP_INSTANCE_COUNT]
                                [ADC_SAR_IP_NUM_GROUP_CHAN] = FEATURE_ADC_MAX_CHN_COUNT;

#define ADC_STOP_SEC_CONST_32
#include "Adc_MemMap.h"

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   GLOBAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"

static inline uint8 Adc_Sar_GetResolution(const uint32 Instance);

static inline uint16 Adc_Sar_GetMaskedResult(const uint32 Instance, const uint32 Cdr);
static inline uint32 Adc_Sar_GetMsrFlags(uint32 const Instance);
static inline uint32 Adc_Sar_GetIsrFlags(uint32 const Instance);
static inline uint32 Adc_Sar_GetADCLKSELValue(Adc_Sar_Ip_ClockSelType ClockSel);
static inline uint32 Adc_Sar_CollectMcrMasks(const uint32 Instance, const Adc_Sar_Ip_ConfigType* const Config,
                                             uint32 InitialMcr);
static inline void   Adc_Sar_ConfigChannels(uint32 const Instance, Adc_Sar_Ip_ChanConfigType const* ChannelConfigsPtr,
                                            uint8 NumChannels);
static inline Adc_Sar_Ip_StatusType Adc_Sar_CheckSelfTestProgress(const uint32 Instance);
static inline void Adc_Sar_ConfigSelftestThreshold(uint32 const Instance,
                                                   Adc_Sar_Ip_SelfTestThresholdType const* SelfTestThresholdConfig);
static inline void Adc_Sar_EnableSelftestThreshold(uint32 const Instance);
static inline void Adc_Sar_DisableSelftestThreshold(uint32 const Instance);
static uint32 Adc_Sar_GetConvResults(const uint32 Instance, const Adc_Sar_Ip_ConvChainType ChainType,
                                     uint16* const ResultsRaw, Adc_Sar_Ip_ChanResultType* const ResultsStruct,
                                     const uint32 Length);

static void Adc_Sar_ResetWdog(uint32 const Instance);

static inline void Adc_Sar_EnableClkDiv(const uint32 Instance, const boolean ClkDivEnable);

static inline void Adc_Sar_CheckAndCallNotification(void (*Callback)(void));

static inline void Adc_Sar_CheckAndCallEocNotification(uint32 Instance, uint16 ChanIdx, uint16 VectAdr, uint32 EocFlag,
                                                       boolean* CeocfrFlag);

static inline uint32 Adc_Sar_CheckAndCallWorrNotification(uint32 Instance, uint16 ChanIdx, uint16 VectAdr);

static inline void Adc_CheckAndCallAllChannelNotification(const uint32 Instance);

static inline void Adc_Sar_ConfigExternalTrigger(const uint32 Instance, const Adc_Sar_Ip_ExtTriggerEdgeType TriggerEdge,
                                                 const uint32 TrgEdgeSetMask, const uint32 TrgEdgeClrMask,
                                                 const uint32 TrigSrcMask);

static inline uint32 Adc_Sar_TempsenseConvFp2Int(const uint32 FloatingPoint);
static inline uint16 Adc_Sar_TempsenseConvInt2Fp(sint32 const SignedInteger);

static inline void Adc_Sar_SetNormalChain(const uint32 Instance, const uint32* const Mask);
static inline void Adc_Sar_SetInjectedChain(uint32 const Instance, uint32 const* const Mask);

/* The function is used to reduce complexity for parent function */
static inline uint32 Adc_Sar_GetValueFromBool(boolean const bVal, uint32 const TrueVal, uint32 const FalseVal);

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
/*FUNCTION*********************************************************************
 *
 * Function Name : Adc_Sar_GetResolution
 * Description   : Returns Adc Sar resolution for conversion data
 *
 *END*************************************************************************/
static inline uint8 Adc_Sar_GetResolution(uint32 const Instance) {
    uint8 Resolution;
    static uint8 const ResolutionArray[] = {14U, 12U, 10U, 8U}; /* maps each register bit value to resolution bit number */
    ADC_Type const* const AdcBasePtr = Adc_Sar_Ip_apxAdcBase[Instance];
    uint32 Calbistreg = AdcBasePtr->CALBISTREG;
    /* ResolutionArray can be used only for 2 bits resolutions. On S32K3 platforms only 2 bits are used so "& 3U"
     * operation is needed */
    uint8 ResolutionBits = (uint8)(((Calbistreg & ADC_CALBISTREG_RESN_MASK) >> ADC_CALBISTREG_RESN_SHIFT) & 3U);

    Resolution = ResolutionArray[ResolutionBits];

    return Resolution;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : Adc_Sar_ConfigSelftestThreshold
 * Description   : Configure self-test threshold value
 *
 *END*************************************************************************/
static inline void Adc_Sar_ConfigSelftestThreshold(uint32 const Instance,
                                                   Adc_Sar_Ip_SelfTestThresholdType const* SelfTestThresholdConfig) {
    ADC_Type* AdcBasePtr;
    volatile uint32* STAW0RAddr;
    volatile uint32* STAW1RAddr;
    volatile uint32* STAW2RAddr;
    volatile uint32* STAW4RAddr;
    volatile uint32* STAW5RAddr;

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[Instance];
    STAW0RAddr = &AdcBasePtr->STAW0R;
    STAW1RAddr = &AdcBasePtr->STAW1R;
    STAW2RAddr = &AdcBasePtr->STAW2R;
    STAW4RAddr = &AdcBasePtr->STAW4R;
    STAW5RAddr = &AdcBasePtr->STAW5R;

    /* Configure the self-test watchdog threshold for S0 algorithm */
    *STAW0RAddr &= ~(ADC_STAW0R_THRH_MASK | ADC_STAW0R_THRL_MASK);
    *STAW0RAddr |= ADC_STAW0R_THRH(SelfTestThresholdConfig->AdcSTAW0RHighVal) |
                   ADC_STAW0R_THRL(SelfTestThresholdConfig->AdcSTAW0RLowVal);

    /* Configure the self-test watchdog threshold for S1 algorithm */
    *STAW1RAddr &= ~(ADC_STAW1R_THRL_MASK);
    *STAW1RAddr |= ADC_STAW1R_THRL(SelfTestThresholdConfig->AdcSTAW1RLowVal);

    /* Configure the self-test watchdog threshold for S2 algorithm */
    *STAW2RAddr &= ~(ADC_STAW2R_THRL_MASK);
    *STAW2RAddr |= ADC_STAW2R_THRL(SelfTestThresholdConfig->AdcSTAW2RLowVal);

    /* Configure the self-test watchdog threshold for C algorithm */
    *STAW4RAddr &= ~(ADC_STAW4R_THRH_MASK | ADC_STAW4R_THRL_MASK);
    *STAW4RAddr |= ADC_STAW4R_THRH(SelfTestThresholdConfig->AdcSTAW4RHighVal) |
                   ADC_STAW4R_THRL(SelfTestThresholdConfig->AdcSTAW4RLowVal);
    *STAW5RAddr &= ~(ADC_STAW5R_THRH_MASK | ADC_STAW5R_THRL_MASK);
    *STAW5RAddr |= ADC_STAW5R_THRH(SelfTestThresholdConfig->AdcSTAW5RHighVal) |
                   ADC_STAW5R_THRL(SelfTestThresholdConfig->AdcSTAW5RLowVal);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : Adc_Sar_EnableSelftestThreshold
 * Description   : Enable self-test threshold
 *
 *END*************************************************************************/
static inline void Adc_Sar_EnableSelftestThreshold(uint32 const Instance) {
    ADC_Type* AdcBasePtr;
    volatile uint32* STAW0RAddr;
    volatile uint32* STAW1RAddr;
    volatile uint32* STAW2RAddr;
    volatile uint32* STAW4RAddr;

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[Instance];
    STAW0RAddr = &AdcBasePtr->STAW0R;
    STAW1RAddr = &AdcBasePtr->STAW1R;
    STAW2RAddr = &AdcBasePtr->STAW2R;
    STAW4RAddr = &AdcBasePtr->STAW4R;

    /* Enable the self-test watchdog threshold for S0 algorithm */
    *STAW0RAddr |= ADC_STAW0R_AWDE(0x1UL);

    /* Enable the self-test watchdog threshold for S1 algorithm */
    *STAW1RAddr |= ADC_STAW1R_AWDE(0x1UL);

    /* Enable the self-test watchdog threshold for S2 algorithm */
    *STAW2RAddr |= ADC_STAW2R_AWDE(0x1UL);

    /* Enable the self-test watchdog threshold for C algorithm */
    *STAW4RAddr |= ADC_STAW4R_AWDE(0x1UL);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : Adc_Sar_DisableSelftestThreshold
 * Description   : Disable self-test threshold
 *
 *END*************************************************************************/
static inline void Adc_Sar_DisableSelftestThreshold(uint32 const Instance) {
    ADC_Type* AdcBasePtr;
    volatile uint32* STAW0RAddr;
    volatile uint32* STAW1RAddr;
    volatile uint32* STAW2RAddr;
    volatile uint32* STAW4RAddr;

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[Instance];
    STAW0RAddr = &AdcBasePtr->STAW0R;
    STAW1RAddr = &AdcBasePtr->STAW1R;
    STAW2RAddr = &AdcBasePtr->STAW2R;
    STAW4RAddr = &AdcBasePtr->STAW4R;

    /* Disable the self-test watchdog threshold for S0 algorithm */
    *STAW0RAddr &= ~(ADC_STAW0R_AWDE_MASK);

    /* Disable the self-test watchdog threshold for S1 algorithm */
    *STAW1RAddr &= ~(ADC_STAW1R_AWDE_MASK);

    /* Disable the self-test watchdog threshold for S2 algorithm */
    *STAW2RAddr &= ~(ADC_STAW2R_AWDE_MASK);

    /* Disable the self-test watchdog threshold for C algorithm */
    *STAW4RAddr &= ~(ADC_STAW4R_AWDE_MASK);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : Adc_Sar_GetMaskedResult
 * Description   : Returns result masked accordingly with alignment
 *
 *END*************************************************************************/
static inline uint16 Adc_Sar_GetMaskedResult(uint32 const Instance, uint32 const Cdr) {
    uint32 CdrMask;
    uint16 Result;
    uint8 Resolution;

    if (FALSE == Adc_Sar_Ip_axAdcSarState[Instance].BypassResolution) {
        Resolution = Adc_Sar_GetResolution(Instance);
    }
    else {
        Resolution = ADC_SAR_IP_RESULT_RESOLUTION;
    }

    /* If the result is left aligned, adjust register mask accordingly */
    if (Adc_Sar_Ip_axAdcSarState[Instance].DataAlign == ADC_SAR_IP_DATA_ALIGNED_LEFT) {
        /* Assumption: the width of the register is less than 16 */
        CdrMask = (uint32)ADC_CDR_CDATA_MASK << (16u - Resolution);
        Result = ((uint16)(Cdr & CdrMask)) >> ADC_CDR_CDATA_SHIFT;
    }
    else {
        CdrMask = ((uint32)ADC_CDR_CDATA_MASK >> 1U) &
                  ((uint32)ADC_CDR_CDATA_MASK << (ADC_SAR_IP_RESULT_RESOLUTION - Resolution));
        Result = ((uint16)(Cdr & CdrMask)) >> (ADC_SAR_IP_RESULT_RESOLUTION - Resolution + ADC_CDR_CDATA_SHIFT);
    }

    return Result;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : Adc_Sar_GetMsrFlags
 * Description   : Returns the flag status from MSR register
 *
 *END*************************************************************************/
static inline uint32 Adc_Sar_GetMsrFlags(uint32 const Instance) {
    uint32 Msr;
    uint32 Flags;
    ADC_Type const* AdcBasePtr;

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[Instance];
    Msr = AdcBasePtr->MSR;

    Flags  = ((Msr & ADC_MSR_CALIBRTD_MASK) != 0U) ? ADC_SAR_IP_STATUS_FLAG_CALIBRATED : 0U;
    Flags |= ((Msr & ADC_MSR_NSTART_MASK  ) != 0U) ? ADC_SAR_IP_STATUS_FLAG_NORMAL_STARTED : 0U;
    Flags |= ((Msr & ADC_MSR_JABORT_MASK  ) != 0U) ? ADC_SAR_IP_STATUS_FLAG_INJECTED_ABORTED : 0U;
    Flags |= ((Msr & ADC_MSR_JSTART_MASK  ) != 0U) ? ADC_SAR_IP_STATUS_FLAG_INJECTED_STARTED : 0U;
    if (ADC_SAR_IP_INST_HAS_CTU(Instance)) {
        Flags |= ((Msr & ADC_MSR_CTUSTART_MASK) != 0U) ? ADC_SAR_IP_STATUS_FLAG_CTU_STARTED : 0U;
    }
    Flags |= ((Msr & ADC_MSR_ACKO_MASK) != 0U) ? ADC_SAR_IP_STATUS_FLAG_AUTOCLOCKOFF : 0U;

    return Flags;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : Adc_Sar_GetIsrFlags
 * Description   : Returns the flag status from ISR register
 *
 *END*************************************************************************/
static inline uint32 Adc_Sar_GetIsrFlags(uint32 const Instance) {
    uint32 Flags;
    uint32 Isr;
    ADC_Type const* AdcBasePtr;

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[Instance];
    Isr = AdcBasePtr->ISR;

    Flags  = ((Isr & ADC_ISR_EOC_MASK ) != 0U) ? ADC_SAR_IP_NOTIF_FLAG_NORMAL_EOC : 0U;
    Flags |= ((Isr & ADC_ISR_ECH_MASK ) != 0U) ? ADC_SAR_IP_NOTIF_FLAG_NORMAL_ENDCHAIN : 0U;
    Flags |= ((Isr & ADC_ISR_JEOC_MASK) != 0U) ? ADC_SAR_IP_NOTIF_FLAG_INJECTED_EOC : 0U;
    Flags |= ((Isr & ADC_ISR_JECH_MASK) != 0U) ? ADC_SAR_IP_NOTIF_FLAG_INJECTED_ENDCHAIN : 0U;
    if (ADC_SAR_IP_INST_HAS_CTU(Instance)) {
        Flags |= ((Isr & ADC_ISR_EOCTU_MASK) != 0U) ? ADC_SAR_IP_NOTIF_FLAG_CTU_EOC : 0U;
    }

    return Flags;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : Adc_Sar_GetADCLKSELValue
 * Description   : This function returns the value that ADCLKSEL field should
 * have based on the input parameter.
 *
 *END*************************************************************************/
static inline uint32 Adc_Sar_GetADCLKSELValue(Adc_Sar_Ip_ClockSelType ClockSel) {
    return ADC_MCR_ADCLKSEL(ClockSel);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : Adc_Sar_CollectMcrMasks
 * Description   : The function collects the mask for MCR register from provided
 * structure. The funcion is used to reduce the complexity of Adc_Sar_Ip_Init()
 *
 *END*************************************************************************/
static inline uint32 Adc_Sar_CollectMcrMasks(uint32 const Instance, Adc_Sar_Ip_ConfigType const* const Config,
                                             uint32 InitialMcr) {
    uint32 Mcr = InitialMcr;

    Mcr &= ~(ADC_MCR_MODE_MASK);
    Mcr |= ADC_MCR_MODE(Config->ConvMode);
    Mcr &= ~(ADC_MCR_ADCLKSEL_MASK);
    Mcr |= Adc_Sar_GetADCLKSELValue(Config->ClkSelect);
    Mcr &= ~(ADC_MCR_ACKO_MASK);
    Mcr |= Adc_Sar_GetValueFromBool(Config->AutoClockOff, ADC_MCR_ACKO_MASK, 0U);
    Mcr &= ~(ADC_MCR_OWREN_MASK);
    Mcr |= Adc_Sar_GetValueFromBool(Config->OverwriteEnable, ADC_MCR_OWREN_MASK, 0U);
    Mcr &= ~(ADC_MCR_WLSIDE_MASK);
    Mcr |= ADC_MCR_WLSIDE(Config->DataAlign);

    if (ADC_SAR_IP_INST_HAS_CTU(Instance)) {
        Mcr &= ~(ADC_MCR_CTUEN_MASK | ADC_MCR_CTU_MODE_MASK); /* Clear CTU_MODE bit of MCR*/

        switch (Config->CtuMode) {
            case ADC_SAR_IP_CTU_MODE_CONTROL :
                Mcr |= ADC_MCR_CTUEN(1U); /* Enable CTU */
                break;

            case ADC_SAR_IP_CTU_MODE_TRIGGER :
                Mcr |= ADC_MCR_CTU_MODE(1U); /* Set CTU to Trigger Mode CTU_MODE = 1 */
                Mcr |= ADC_MCR_CTUEN(1U);    /* Enable CTU */
                break;

            case ADC_SAR_IP_CTU_MODE_DISABLED :
                /* CTU is disabled (CTUEN = 0 and CTU_MODE = 0) */
                /* Pass through */
            default : /* no-op */
                break;
        }
    }

    switch (Config->InjectedEdge) {
        case ADC_SAR_IP_EXT_TRIG_EDGE_FALLING :
            /* Already on falling edge JEDGE = 0 */
            Mcr &= ~(ADC_MCR_JTRGEN_MASK);
            Mcr |= ADC_MCR_JTRGEN_MASK; /* enable Injected trigger */
            break;

        case ADC_SAR_IP_EXT_TRIG_EDGE_RISING :
            /* Enable Injected trigger and set to rising edge JEDGE = 1 */
            Mcr &= ~(ADC_MCR_JEDGE_MASK | ADC_MCR_JTRGEN_MASK);
            Mcr |= (ADC_MCR_JEDGE_MASK | ADC_MCR_JTRGEN_MASK);
            break;

        case ADC_SAR_IP_EXT_TRIG_EDGE_DISABLED :
            /* Already set to injected trigger disabled (JTRGEN = 0 and JEDGE = 0) */
        default : /* no-op */
            break;
    }

    /* Get normal trigger masks */
    Mcr &= ~(ADC_MCR_EDGE_MASK);
    Mcr |= (Config->ExtTrigger == ADC_SAR_IP_EXT_TRIG_EDGE_RISING) ? (ADC_MCR_EDGE(1U)) : 0U;
    if (Config->ExtTrigger != ADC_SAR_IP_EXT_TRIG_EDGE_DISABLED) {
        Mcr &= ~(ADC_MCR_TRGEN_MASK);
        Mcr |= Adc_Sar_GetValueFromBool(Config->NormalExtTrgEn, ADC_MCR_TRGEN_MASK, 0U);
        Mcr &= ~(ADC_MCR_XSTRTEN_MASK);
        Mcr |= Adc_Sar_GetValueFromBool(Config->NormalAuxExtTrgEn, ADC_MCR_XSTRTEN_MASK, 0U);
    }

    Mcr &= ~(ADC_MCR_AVGEN_MASK);
    Mcr |= Adc_Sar_GetValueFromBool(Config->AvgEn, ADC_MCR_AVGEN_MASK, 0U);
    Mcr &= ~(ADC_MCR_AVGS_MASK);
    Mcr |= ADC_MCR_AVGS(Config->AvgSel);


    return Mcr;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : Adc_Sar_ConfigChannels
 * Description   : Configure a list of channels by enabling channel notifications
 * and setting presampling.
 *END*************************************************************************/
static inline void Adc_Sar_ConfigChannels(uint32 const Instance, Adc_Sar_Ip_ChanConfigType const* ChannelConfigsPtr,
                                          uint8 NumChannels) {
    uint32 VectAdr;
    uint32 VectBit;
    uint32 CimrMask[ADC_SAR_IP_NUM_GROUP_CHAN]  = ADC_SAR_IP_NUM_GROUP_CHAN_INIT_VAL;
    uint32 CwenrMask[ADC_SAR_IP_NUM_GROUP_CHAN] = ADC_SAR_IP_NUM_GROUP_CHAN_INIT_VAL;
    uint32 DmarMask[ADC_SAR_IP_NUM_GROUP_CHAN]  = ADC_SAR_IP_NUM_GROUP_CHAN_INIT_VAL;
    uint32 PsrMask[ADC_SAR_IP_NUM_GROUP_CHAN]   = ADC_SAR_IP_NUM_GROUP_CHAN_INIT_VAL;
    const Adc_Sar_Ip_ChanConfigType* ChnConfig;
    ADC_Type* AdcBasePtr;

    for (size_t Index = 0U; Index < NumChannels; Index++) {
        ChnConfig = &ChannelConfigsPtr[Index];

        /* Each CWSELR register contains 8 watchdog selections according to 8 channels
           Each watchdog selection possibly needs maximum 4 bits for setting
           This is to calculate the CWSELR register index and position of channel on that register */
        VectAdr = (uint32)ChnConfig->ChanIndex / 8U;
        VectBit = (uint32)ChnConfig->ChanIndex % 8U;
        if (ADC_SAR_IP_INST_HAS_CWSELRn(Instance, VectAdr)) {
            Adc_Sar_WriteChannelMapping(Instance, VectAdr, VectBit, ChnConfig->WdgThreshRegIndex);
            /* Store threshold register index for configured channel */
            Adc_Sar_Ip_axAdcSarState[Instance].ChanWdgThresholdIndex[ChnConfig->ChanIndex] =
                ChnConfig->WdgThreshRegIndex;
        }

        VectAdr = ADC_SAR_IP_CHAN_2_VECT((uint32)ChnConfig->ChanIndex);
        VectBit = ADC_SAR_IP_CHAN_2_BIT((uint32)ChnConfig->ChanIndex);
        /* Collect bit-mask for WDG, EOC, DMA and Presample */
        CimrMask[VectAdr]  |= Adc_Sar_GetValueFromBool(ChnConfig->EndOfConvNotification, (1UL << VectBit), 0UL);
        CwenrMask[VectAdr] |= Adc_Sar_GetValueFromBool(ChnConfig->WdgNotificationEn, (1UL << VectBit), 0UL);
        DmarMask[VectAdr]  |= Adc_Sar_GetValueFromBool(ChnConfig->EndOfConvDmaEnable, (1UL << VectBit), 0UL);
        PsrMask[VectAdr]   |= Adc_Sar_GetValueFromBool(ChnConfig->PresamplingEnable, (1UL << VectBit), 0UL);
    }

    /* Enable WDG, EOC, DMA and Presample */
    for (size_t Index = 0U; Index < Adc_Sar_Ip_au8AdcGroupCount[Instance]; Index++) {
        AdcBasePtr = Adc_Sar_Ip_apxAdcBase[Instance];

        CIMR(AdcBasePtr, Index)  = CimrMask[Index];
        CWENR(AdcBasePtr, Index) = CwenrMask[Index];
        DMAR(AdcBasePtr, Index)  = DmarMask[Index];
        PSR(AdcBasePtr, Index)   = PsrMask[Index];
    }
}

/*FUNCTION*********************************************************************
 *
 * Function Name : Adc_Sar_CheckSelfTestProgress
 * Description   : Configures watchdog threshold with provided array of configuration
 *
 *END*************************************************************************/
static inline Adc_Sar_Ip_StatusType Adc_Sar_CheckSelfTestProgress(uint32 const Instance) {
    Adc_Sar_Ip_StatusType Status = ADC_SAR_IP_STATUS_SUCCESS;
    uint32 Reg;
    uint32 TimeoutTicks = OsIf_MicrosToTicks(ADC_SAR_IP_TIMEOUT_VAL, ADC_SAR_IP_TIMEOUT_TYPE);
    uint32 CurrentTicks = OsIf_GetCounter(ADC_SAR_IP_TIMEOUT_TYPE);
    uint32 ElapsedTicks;
    volatile uint32 const* MSRAddr;
    volatile uint32 const* STSR1Addr;
    ADC_Type const* AdcBasePtr;

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[Instance];
    MSRAddr    = &AdcBasePtr->MSR;
    STSR1Addr  = &AdcBasePtr->STSR1;

    /*  Each for loop checks the conversion of all steps in self-test S algorithm
     *   ForLoop(0): while (AlgS-start-1) ->S0 -> S1 -> S2 -> while (Alg-end-1) -> C0 to C11 ->
     *   ForLoop(1): while (AlgS-start-2) ->S0 -> S1 -> S2 -> while (Alg-end-2)
     */
    for (size_t Index = 0U; Index < 2U; Index++) {
        /* Wait until Alg S has started*/
        ElapsedTicks = 0U;

        while ((((*MSRAddr) & ADC_MSR_SELF_TEST_S_MASK) != ADC_MSR_SELF_TEST_S_MASK) &&
               (ElapsedTicks < TimeoutTicks)) {
            ElapsedTicks += OsIf_GetElapsed(&CurrentTicks, ADC_SAR_IP_TIMEOUT_TYPE);
        }

        if (ElapsedTicks >= TimeoutTicks) {
            Status = ADC_SAR_IP_STATUS_TIMEOUT;
        }

        if (Status == ADC_SAR_IP_STATUS_SUCCESS) {
            /* Wait until Alg S has finished*/
            ElapsedTicks = 0U;
            while ((((*MSRAddr) & ADC_MSR_SELF_TEST_S_MASK) == ADC_MSR_SELF_TEST_S_MASK) &&
                   (ElapsedTicks < TimeoutTicks)) {
                ElapsedTicks += OsIf_GetElapsed(&CurrentTicks, ADC_SAR_IP_TIMEOUT_TYPE);
            }

            if (ElapsedTicks >= TimeoutTicks) {
                Status = ADC_SAR_IP_STATUS_TIMEOUT;
            }
        }

        if (Status == ADC_SAR_IP_STATUS_TIMEOUT) {
            /* Break the loop if timeout occured in order to increase performance */
            break;
        }
    }

    if (Status != ADC_SAR_IP_STATUS_TIMEOUT) {
        Reg  = ADC_STSR1_ERR_S0_MASK;
        Reg |= ADC_STSR1_ERR_S1_MASK | ADC_STSR1_ERR_S2_MASK | ADC_STSR1_ERR_C_MASK;
        if (((*STSR1Addr) & Reg) != 0UL) {
            Status = ADC_SAR_IP_STATUS_ERROR;
        }
    }

    return Status;
}
/*FUNCTION*********************************************************************
 *
 * Function Name : Adc_Sar_GetConvResults
 * Description   : Reads the conversion results to output arrays
 * Params:
 *  - Instance : the ADC Instance to read
 *  - ChainType : the conversion chain (Normal, Injected or CTU)
 *  - ResultsRaw : an uint16 array to write only conversion data
 *  - ResultsStruct : an Adc_Sar_Ip_ChanResultType array to write detailed information
                      about each conversion result
 *  - length : the maximum size of ResultsRaw and ResultsStruct
 *
 * ResultsRaw or ResultsStruct can be NULL, but not both, as the function will
 * have nowhere to write the results.
 *
 *END*************************************************************************/
static uint32 Adc_Sar_GetConvResults(uint32 const Instance, Adc_Sar_Ip_ConvChainType const ChainType,
                                     uint16* const ResultsRaw, Adc_Sar_Ip_ChanResultType* const ResultsStruct,
                                     uint32 const Length) {
    uint32 Index = 0U;
    boolean LengthExceeded = FALSE;
    ADC_Type* AdcBasePtr;
    uint32 VectAdr;
    uint32 VectBit;
    uint8  ChnIdx;
    uint32 Cdr;
    volatile uint32* CEOCFRAddr;
    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[Instance];

    /* ResultsRaw and ResultsStruct cannot be both NULL */
    DevAssert((ResultsRaw != NULL_PTR) || (ResultsStruct != NULL_PTR));

    /* Go through each channel group */
    for (VectAdr = 0U; VectAdr < Adc_Sar_Ip_au8AdcGroupCount[Instance]; VectAdr++) {
        CEOCFRAddr = &CEOCFR(AdcBasePtr, VectAdr);

        /* go through each bit in the group, check if there is a completed conversion */
        for (VectBit = 0U; VectBit < AdcChanCount[Instance][VectAdr]; VectBit++) {
            ChnIdx = (uint8)((VectAdr * 32U) + VectBit);
            if (!(ADC_SAR_IP_INST_HAS_CDRn(Instance, ChnIdx))) {
                continue; /* skip if the CDR register is not available */
            }

            Cdr = CDR(AdcBasePtr, ChnIdx);
            if ((ADC_CDR_RESULT((uint32)ChainType) | ADC_CDR_VALID_MASK) ==
                (Cdr & (ADC_CDR_RESULT_MASK | ADC_CDR_VALID_MASK))) {
                /* if the result type matches the one request by ChainType
                   and the data is valid, write to the output array(s)
                */
                if (ResultsRaw != NULL_PTR) {
                    ResultsRaw[Index] = Adc_Sar_GetMaskedResult(Instance, Cdr);
                }
                if (ResultsStruct != NULL_PTR) {
                    ResultsStruct[Index].ConvData        = Adc_Sar_GetMaskedResult(Instance, Cdr);
                    ResultsStruct[Index].AdcChnIdx       = ChnIdx;
                    ResultsStruct[Index].ValidFlag       = ((Cdr & ADC_CDR_VALID_MASK) != 0U) ? TRUE : FALSE;
                    ResultsStruct[Index].OverWrittenFlag = ((Cdr & ADC_CDR_OVERW_MASK) != 0U) ? TRUE : FALSE;
                }
                /* Increment the current Index and reset the CEOCFR flag */
                *CEOCFRAddr = ((uint32)1UL << VectBit); /* w1c bit */
                Index++;
                if (Index >= Length) {
                    /* We have filled the output buffer, exit the loop.
                     * Data may still exist in the result registers, which won't be reached.
                     */
                    LengthExceeded = TRUE;
                    break;
                }
            }
        }

        if (LengthExceeded) {
            break;
        }
    }

    return Index;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : Adc_Sar_ResetWdog
 * Description   : Reset and disable the Analog Watchdog feature
 *
 *END*************************************************************************/
static void Adc_Sar_ResetWdog(uint32 const Instance) {
    uint8 MaxThresholdRegs;
    ADC_Type* AdcBasePtr;

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[Instance];
    MaxThresholdRegs = ADC_SAR_IP_THRHLR_COUNT;

    for (size_t Index = 0U; Index < Adc_Sar_Ip_au8AdcGroupCount[Instance]; Index++) {
        CWENR(AdcBasePtr, Index) = 0U;
        AWORR(AdcBasePtr, Index) = 0xFFFFFFFFU; /* w1c bits */
    }

    for (size_t Index = 0U; Index < MaxThresholdRegs; Index++) {
        Adc_Sar_WriteThresholds(Instance, (uint8)Index, 0xFFFFu, 0U);
    }

    for (size_t Index = 0U; Index < ADC_SAR_IP_CWSELR_COUNT; Index++) {
        if (!(ADC_SAR_IP_INST_HAS_CWSELRn(Instance, Index))) {
            continue; /* skip register if it's not available */
        }
        Adc_Sar_ResetWdogCWSELR(Instance, (uint8)Index);
    }
}

/*FUNCTION*********************************************************************
 *
 * Function Name : Adc_Sar_EnableClkDiv
 * Description   : Configure clock divider
 *
 *END*************************************************************************/
static inline void Adc_Sar_EnableClkDiv(uint32 const Instance, boolean const ClkDivEnable) {
    /* S32K358 has no clock divider register; nothing to configure. */
    (void) Instance;
    (void) ClkDivEnable;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : Adc_Sar_CheckAndCallNotification
 * Description   : Checks if the given callback is not NULL then calls it
 *
 *END*************************************************************************/
static inline void Adc_Sar_CheckAndCallNotification(void (*Callback)(void)) {
    if (Callback != NULL_PTR) {
        Callback();
    }
}

/*FUNCTION*********************************************************************
 *
 * Function Name : Adc_Sar_CheckAndCallEocNotification
 * Description   : Checks if the given channel interrupt was triggered, clears
 *                 the interrupt, check if it is not spurious, checks that the
 *                 callback is not null.
 *
 *END*************************************************************************/
static inline void Adc_Sar_CheckAndCallEocNotification(uint32 Instance, uint16 ChanIdx, uint16 VectAdr, uint32 EocFlag,
                                                       boolean* CeocfrFlag) {
    ADC_Type* AdcBasePtr;
    const uint32 Mask = (uint32)1UL << ADC_SAR_IP_CHAN_2_BIT(ChanIdx);
    uint32 Ceocfr = 0U;
    uint32 Cimr;
    volatile uint32* CEOCFRAddr;

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[Instance];
    CEOCFRAddr = &CEOCFR(AdcBasePtr, VectAdr);
    Cimr       = (CIMR(AdcBasePtr, VectAdr) & Mask);

    Ceocfr = ((*CEOCFRAddr) & Mask);
    /* Check if the interrupt was not spurious */
    if ((Ceocfr != 0U) && (Cimr != 0U) && (EocFlag != 0U)) {
        /* Clears flag by w1c */
        *CEOCFRAddr = Mask;
        *CeocfrFlag = TRUE;

        /* Check if the callback is not null */
        if (Adc_Sar_Ip_axAdcSarState[Instance].EndOfConvNotification != NULL_PTR) {
            Adc_Sar_Ip_axAdcSarState[Instance].EndOfConvNotification(ChanIdx);
        }
    }
}

/*FUNCTION*********************************************************************
 *
 * Function Name : Adc_Sar_CheckAndCallWorrNotification
 * Description   : Checks if the given channel interrupt was triggered, clears
 *                 the interrupt, check if it is not spurious, checks that the
 *                 callback is not null and return WTISR flag
 *                 in order to be cleared outside of this function when loop of all channels is completed.
 *
 *END*************************************************************************/
static inline uint32 Adc_Sar_CheckAndCallWorrNotification(uint32 Instance, uint16 ChanIdx, uint16 VectAdr) {
    ADC_Type* AdcBasePtr;
    const uint32 Mask = (uint32)1UL << ADC_SAR_IP_CHAN_2_BIT(ChanIdx);
    uint32 Aworr;
    uint32 Cwenr;
    uint32 Wtisr;
    uint32 Wtimr;
    uint32 WdgFlags = 0U;
    uint32 ThresholdIndex;
    volatile uint32* AWORRAddr;

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[Instance];
    AWORRAddr  = &AWORR(AdcBasePtr, VectAdr);
    Cwenr      = (CWENR(AdcBasePtr, VectAdr) & Mask);
    Wtisr      = AdcBasePtr->WTISR;
    Wtimr      = AdcBasePtr->WTIMR;

    Aworr = ((*AWORRAddr) & Mask);
    /* Check if wdg channel enabled associated to the wdg out of range flag */
    if ((Aworr != 0U) && (Cwenr != 0U)) {
        /* Get the mapping threshold register index corresponding to the configured channel */
        ThresholdIndex = Adc_Sar_Ip_axAdcSarState[Instance].ChanWdgThresholdIndex[ChanIdx];

        /* Check if the high/low flags were not set spuriously. */
        if ((Wtimr & (ADC_SAR_IP_WDG_REG_MASK_LOW(ThresholdIndex))) != 0U) {
            WdgFlags |= ((Wtisr & ADC_SAR_IP_WDG_REG_MASK_LOW(ThresholdIndex)) != 0U) ? ADC_SAR_IP_WDG_LOW_FLAG : 0U;
        }

        if ((Wtimr & (ADC_SAR_IP_WDG_REG_MASK_HIGH(ThresholdIndex))) != 0U) {
            WdgFlags |= ((Wtisr & ADC_SAR_IP_WDG_REG_MASK_HIGH(ThresholdIndex)) != 0U) ? ADC_SAR_IP_WDG_HIGH_FLAG : 0U;
        }

        if (WdgFlags != 0U) {
            /* Only clear relevant flags if interrupt is not spurious (i.e: satisfy combination of AWORR-CWENR and
             * WTISR-WTIMR) */
            *AWORRAddr = Mask;
            /* Multiple ADC channels can use same THRHLRx so return the associated WTISR flag value of that threshold
                which will be used for clearing all WTISR flags outside of this function, when completing the loop for
               ADC channels */
            WdgFlags = WdgFlags << (ThresholdIndex << 1);
            /* Check if the callback is not null */
            if (Adc_Sar_Ip_axAdcSarState[Instance].WdgOutOfRangeNotification != NULL_PTR) {
                Adc_Sar_Ip_axAdcSarState[Instance].WdgOutOfRangeNotification(ChanIdx, (uint8)WdgFlags);
            }
        }
    }

    return WdgFlags;
}

/*LOCAL FUNCTION*********************************************************************
 *
 * Function Name : Adc_CheckAndCallAllChannelNotification
 * Description   : Check for all watchdog interrupts and for all individual channel interrupts
 * if it was detected. And then call the appropriate notification
 *
 *END*********************************************************************************/
static inline void Adc_CheckAndCallAllChannelNotification(uint32 const Instance) {
    ADC_Type* AdcBasePtr;
    uint16 VectAdr;
    uint16 PhyChan;
    uint16 ChanCnt;
    uint32 WtisrMask = 0U;
    volatile uint32* WTISRAddr;
    volatile const uint32* IMRAddr;
    volatile uint32* ISRAddr;
    uint32 EocFlag;
    boolean CeocfrFlag = FALSE;

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[Instance];
    IMRAddr    = &AdcBasePtr->IMR;
    ISRAddr    = &AdcBasePtr->ISR;
    WTISRAddr  = &AdcBasePtr->WTISR;

    /* EocFlag = 0 if all EOC flags are spurious interrupts */
    /* Avoid Compiler Warning about accessing two volatile variables simultaneously */
    EocFlag  = *IMRAddr;
    EocFlag &= *ISRAddr;
    EocFlag &= (ADC_ISR_EOC_MASK | ADC_ISR_JEOC_MASK);

    /* Clear EOC Flag */
    if (EocFlag != 0) {
        *ISRAddr = EocFlag;
    }

    for (VectAdr = 0U; VectAdr < Adc_Sar_Ip_au8AdcGroupCount[Instance]; VectAdr++) {
        for (ChanCnt = 0U; ChanCnt < AdcChanCount[Instance][VectAdr]; ChanCnt++) {
            PhyChan = (ChanCnt + (uint16)(ADC_SAR_IP_HW_REG_SIZE * VectAdr));

            /* Check end of conversion interrupt */
            Adc_Sar_CheckAndCallEocNotification(Instance, PhyChan, VectAdr, EocFlag, &CeocfrFlag);

            /* Check watchdog out of range interrupt */
            WtisrMask |= Adc_Sar_CheckAndCallWorrNotification(Instance, PhyChan, VectAdr);
        }
    }

    if (WtisrMask != 0U) {
        *WTISRAddr = WtisrMask;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_ConfigExternalTrigger
 * Description   : This function configures the external trigger.
 *
 * END**************************************************************************/
static inline void Adc_Sar_ConfigExternalTrigger(uint32 const Instance, Adc_Sar_Ip_ExtTriggerEdgeType const TriggerEdge,
                                                 uint32 const TrgEdgeSetMask, uint32 const TrgEdgeClrMask,
                                                 uint32 const TrigSrcMask) {
    ADC_Type* AdcBasePtr;
    volatile uint32* MCRAddr;

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[Instance];
    MCRAddr    = &AdcBasePtr->MCR;
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_21();

    switch (TriggerEdge) {
        case ADC_SAR_IP_EXT_TRIG_EDGE_FALLING :
            *MCRAddr &= ~TrgEdgeSetMask; /* set to falling edge 0 */
            *MCRAddr |= TrigSrcMask;     /* enable external trigger */
            break;

        case ADC_SAR_IP_EXT_TRIG_EDGE_RISING :
            /* enable external trigger and set to rising edge EDGE = 1 */
            *MCRAddr |= (TrgEdgeSetMask | TrigSrcMask);
            break;

        case ADC_SAR_IP_EXT_TRIG_EDGE_DISABLED :
            /* disable external trigger and reset edge field */
            *MCRAddr &= ~(TrgEdgeClrMask | TrigSrcMask);
            break;

        default : /* no-op */
            break;
    }

    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_21();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_TempsenseConvFp2Int
 * Description   : The function converts the number in signed fixed point format
 * (1,11,4) to the integer number multipled with ADC_SAR_IP_TEMPSENSE_MULTIPLIER to avoid
 * rounding the decimal part.
 *
 *END**************************************************************************/
static inline uint32 Adc_Sar_TempsenseConvFp2Int(uint32 const FloatingPoint) {
    uint32 RetVal;

    /* The integer and decimal part multiple with ADC_SAR_IP_TEMPSENSE_MULTIPLIER to avoid rounding the decimal part */
    RetVal = ((FloatingPoint & ADC_SAR_IP_TEMPSENSE_INTEGER_MASK) >> ADC_SAR_IP_TEMPSENSE_INTEGER_SHIFT) *
             ADC_SAR_IP_TEMPSENSE_MULTIPLIER;
    RetVal += ((FloatingPoint & ADC_SAR_IP_TEMPSENSE_DECIMAL_MASK) * ADC_SAR_IP_TEMPSENSE_MULTIPLIER) /
              (ADC_SAR_IP_TEMPSENSE_DECIMAL_MASK + 1U);

    return RetVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_TempsenseConvInt2Fp
 * Description   : The function converts the number in integer number to signed fixed
 * point format (1,11,4). The integer number parameter is multipled with ADC_SAR_IP_TEMPSENSE_MULTIPLIER
 *
 *END**************************************************************************/
static inline uint16 Adc_Sar_TempsenseConvInt2Fp(sint32 const SignedInteger) {
    uint16 RetVal;
    uint32 Temp;

    if (SignedInteger < 0) {
        RetVal = ADC_SAR_IP_TEMPSENSE_SIGN_MASK;
        Temp   = (uint32)(-SignedInteger);
    }
    else {
        RetVal = 0U;
        Temp   = (uint32)SignedInteger;
    }

    /* Calculates the integer part */
    RetVal |= (uint16)(((Temp / ADC_SAR_IP_TEMPSENSE_MULTIPLIER) << ADC_SAR_IP_TEMPSENSE_INTEGER_SHIFT) &
                       ADC_SAR_IP_TEMPSENSE_INTEGER_MASK);
    /* Calculates the decimal part */
    RetVal |= (uint16)(((Temp % ADC_SAR_IP_TEMPSENSE_MULTIPLIER) * (ADC_SAR_IP_TEMPSENSE_DECIMAL_MASK + 1U)) /
                       ADC_SAR_IP_TEMPSENSE_MULTIPLIER);

    return RetVal;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : Adc_Sar_Ip_IRQHandler
 * Description   : Handles Adc Sar interrupts
 *
 * @implements     Adc_Sar_Ip_IRQHandler_Activity
 *END*************************************************************************/
void Adc_Sar_Ip_IRQHandler(uint32 const Instance) {
    ADC_Type* AdcBasePtr;
    volatile uint32* ISRAddr;
    volatile uint32* WTISRAddr;
    uint32 Isr;
    uint32 Wtisr;
    uint32 Imr;

    DevAssert(Instance < ADC_SAR_IP_INSTANCE_COUNT);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[Instance];
    ISRAddr    = &AdcBasePtr->ISR;
    WTISRAddr  = &AdcBasePtr->WTISR;
    Imr        = AdcBasePtr->IMR;

    /* CPR_RTD_00011 */
    if (Adc_Sar_Ip_axAdcSarState[Instance].InitStatus) {
        /* Check which interrupt was triggered and not spurious, clear it and call the associated callback */
        if ((((*ISRAddr) & ADC_ISR_EOCTU_MASK) != 0U) && ((Imr & ADC_IMR_MSKEOCTU_MASK) != 0U)) {
            /* CPR_RTD_00644 */
            *ISRAddr = ADC_ISR_EOCTU_MASK;
            Adc_Sar_CheckAndCallNotification(Adc_Sar_Ip_axAdcSarState[Instance].EndOfCtuConversionNotification);
        }

        if ((((*ISRAddr) & ADC_ISR_ECH_MASK) != 0U) && ((Imr & ADC_IMR_MSKECH_MASK) != 0U)) {
            /* CPR_RTD_00644 */
            *ISRAddr = ADC_ISR_ECH_MASK;
            Adc_Sar_CheckAndCallNotification(Adc_Sar_Ip_axAdcSarState[Instance].EndOfNormalChainNotification);
        }

        if ((((*ISRAddr) & ADC_ISR_JECH_MASK) != 0U) && ((Imr & ADC_IMR_MSKJECH_MASK) != 0U)) {
            /* CPR_RTD_00644 */
            *ISRAddr = ADC_ISR_JECH_MASK;
            Adc_Sar_CheckAndCallNotification(Adc_Sar_Ip_axAdcSarState[Instance].EndOfInjectedChainNotification);
        }

        Adc_CheckAndCallAllChannelNotification(Instance);
    }
    else {
        /* CPR_RTD_00011 */
        Isr      = *ISRAddr;
        *ISRAddr = Isr;

        Wtisr      = *WTISRAddr;
        *WTISRAddr = Wtisr;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_SetNormalChain
 * Description   : This function configures the ADC Normal Chain.
 *
 *END**************************************************************************/
static inline void Adc_Sar_SetNormalChain(uint32 const Instance, uint32 const* const Mask) {
    ADC_Type* AdcBasePtr;

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[Instance];
    for (size_t Index = 0U; Index < Adc_Sar_Ip_au8AdcGroupCount[Instance]; Index++) {
        NCMR(AdcBasePtr, Index) = Mask[Index];
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_SetInjectedChain
 * Description   : This function configures the ADC Injected Chain.
 *
 *END**************************************************************************/
static inline void Adc_Sar_SetInjectedChain(uint32 const Instance, uint32 const* const Mask) {
    ADC_Type* AdcBasePtr;

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[Instance];
    for (size_t Index = 0U; Index < Adc_Sar_Ip_au8AdcGroupCount[Instance]; Index++) {
        JCMR(AdcBasePtr, Index) = Mask[Index];
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_GetValueFromBool
 * Description   : The function is used to reduce complexity for parent function
 *
 *END**************************************************************************/
static inline uint32 Adc_Sar_GetValueFromBool(boolean const bVal, uint32 const TrueVal, uint32 const FalseVal) {
    return ((TRUE == bVal) ? TrueVal : FalseVal);
}

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_Init
 * Description   : This function initializes the ADC_SAR module by configuring all
 * available features.
 *
 * @implements      Adc_Sar_Ip_Init_Activity
 * END**************************************************************************/
Adc_Sar_Ip_StatusType Adc_Sar_Ip_Init(uint32 const u32Instance, Adc_Sar_Ip_ConfigType const* const pConfig) {
    Adc_Sar_Ip_StatusType Status = ADC_SAR_IP_STATUS_SUCCESS;
    volatile uint32* MCRAddr;
    volatile uint32* PDEDRAddr;
    volatile uint32* DMAEAddr;
    volatile uint32* DSDRAddr;
    volatile uint32* PSCRAddr;
    ADC_Type* AdcBasePtr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);
    DevAssert(pConfig != NULL_PTR);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    MCRAddr    = &AdcBasePtr->MCR;
    PDEDRAddr  = &AdcBasePtr->PDEDR;
    DMAEAddr   = &AdcBasePtr->DMAE;
    DSDRAddr   = &AdcBasePtr->DSDR;
    PSCRAddr   = &AdcBasePtr->PSCR;

    /* Stop any conversions, if any */
    (void) Adc_Sar_Ip_AbortChain(u32Instance, TRUE, FALSE);

    /* Clear CTUEN to allow Powerdown operation to succeed. */
    *MCRAddr &= ~ADC_MCR_CTUEN_MASK;

    Status = Adc_Sar_Ip_Powerdown(u32Instance);
    if (ADC_SAR_IP_STATUS_SUCCESS == Status) {
        /* Collects the mask and writes MCR mask */
        *MCRAddr = Adc_Sar_CollectMcrMasks(u32Instance, pConfig, *MCRAddr);

        Adc_Sar_Ip_axAdcSarState[u32Instance].DataAlign = pConfig->DataAlign;

        Status = Adc_Sar_Ip_Powerup(u32Instance);
        if (ADC_SAR_IP_STATUS_SUCCESS == Status) {
            if (ADC_SAR_IP_CTU_MODE_TRIGGER == pConfig->CtuMode) {
                /* Workaround to enable CTU_MODE because it cannot be written in power-down mode in SAF85 */
                *MCRAddr |= ADC_MCR_CTU_MODE(1U);
            }
            /* Enables high speed conversion or calibration */
            Adc_Sar_EnableHighSpeed(AdcBasePtr, pConfig->HighSpeedConvEn);

            /* Set the sample times for each channnel group */
            Adc_Sar_Ip_SetSampleTimes(u32Instance, pConfig->SampleTimeArr);

            *PDEDRAddr = ADC_PDEDR_PDED(pConfig->PowerDownDelay);

            /* Configure clock divider */
            Adc_Sar_EnableClkDiv(u32Instance, pConfig->ClkDivEnable);

            if (ADC_SAR_IP_INST_HAS_DSDR(u32Instance)) {
                *DSDRAddr = ADC_DSDR_DSD(pConfig->DecodeDelay);
            }

            /* Configure chain conversions */
            Adc_Sar_SetNormalChain(u32Instance, pConfig->ChanMaskNormal);
            Adc_Sar_SetInjectedChain(u32Instance, pConfig->ChanMaskInjected);

            /* Configure resolution */
            Adc_Sar_Ip_SetResolution(u32Instance, pConfig->AdcResolution);

            /* Configure WDG */
            if ((pConfig->WdgThresholds != NULL_PTR) && (pConfig->NumWdgThresholds > 0U)) {
                for (size_t Index = 0U; Index < pConfig->NumWdgThresholds; Index++) {
                    Adc_Sar_Ip_SetWdgThreshold(u32Instance, pConfig->WdgThresholds[Index].WdgIndex,
                                               &pConfig->WdgThresholds[Index]);
                }
            }

            if (pConfig->SelfTestThresholdConfig != NULL_PTR) {
                /* Configure self-test threshold value */
                Adc_Sar_ConfigSelftestThreshold(u32Instance, pConfig->SelfTestThresholdConfig);
            }

            /* Configure DMA for channels */
            *DMAEAddr &= ~(ADC_DMAE_DMAEN_MASK | ADC_DMAE_DCLR_MASK);
            if (pConfig->DmaEnable) {
                *DMAEAddr |= (ADC_DMAE_DMAEN(1U) | ADC_DMAE_DCLR((uint32)pConfig->DmaClearSource));
            }

            /* Configure per channel notifications and presampling */
            if ((pConfig->ChannelConfigsPtr != NULL_PTR) && (pConfig->NumChannels > 0U)) {
                Adc_Sar_ConfigChannels(u32Instance, pConfig->ChannelConfigsPtr, pConfig->NumChannels);
            }

            /* Configure presampling sources */
            *PSCRAddr &= ~(ADC_PSCR_PRECONV_MASK);
            *PSCRAddr |= ADC_PSCR_PRECONV(pConfig->BypassSampling ? 1u : 0U);

            Adc_Sar_Ip_SetPresamplingSource(u32Instance, ADC_SAR_IP_CHAN_GROUP_0, pConfig->PresamplingSourceArr[0U]);
            Adc_Sar_Ip_SetPresamplingSource(u32Instance, ADC_SAR_IP_CHAN_GROUP_1, pConfig->PresamplingSourceArr[1U]);
            Adc_Sar_Ip_SetPresamplingSource(u32Instance, ADC_SAR_IP_CHAN_GROUP_2, pConfig->PresamplingSourceArr[2U]);

            /* Add notification callbacks to the state structure */
            Adc_Sar_Ip_StateStructType* Adc_Sar_Ip_State = &Adc_Sar_Ip_axAdcSarState[u32Instance];

            Adc_Sar_Ip_State->EndOfNormalChainNotification   = pConfig->EndOfNormalChainNotification;
            Adc_Sar_Ip_State->EndOfInjectedChainNotification = pConfig->EndOfInjectedChainNotification;
            Adc_Sar_Ip_State->EndOfCtuConversionNotification = pConfig->EndOfCtuConversionNotification;
            Adc_Sar_Ip_State->EndOfConvNotification          = pConfig->EndOfConvNotification;
            Adc_Sar_Ip_State->WdgOutOfRangeNotification      = pConfig->WdgOutOfRangeNotification;
            Adc_Sar_Ip_State->BypassResolution               = pConfig->BypassResolution;
            Adc_Sar_Ip_State->CalibrationClkSelect           = pConfig->CalibrationClkSelect;

            /* Configure user gain and offset */
            AdcBasePtr->ADC_USER_OFFSET_GAIN_REG =
                ADC_USER_OFFSET(pConfig->UsrOffset) | ADC_USER_GAIN(pConfig->UsrGain);

            /* Mark that the driver was initialized */
            Adc_Sar_Ip_State->InitStatus = TRUE;
        }
    }

    return Status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_Deinit
 * Description   : This function writes all the internal ADC registers with
 *  their Reference Manual reset values.
 *
 * @implements      Adc_Sar_Ip_DeInit_Activity
 * END**************************************************************************/
Adc_Sar_Ip_StatusType Adc_Sar_Ip_Deinit(uint32 const u32Instance) {
    ADC_Type* AdcBasePtr;
    uint32 Index;
    Adc_Sar_Ip_ConfigType DefaultConfig;
    Adc_Sar_Ip_StatusType Status;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);

    DefaultConfig.ConvMode             = ADC_SAR_IP_CONV_MODE_ONESHOT;
    DefaultConfig.ClkSelect            = ADC_SAR_IP_CLK_FULL_BUS;
    DefaultConfig.CalibrationClkSelect = ADC_SAR_IP_CLK_HALF_BUS;
    DefaultConfig.HighSpeedConvEn      = FALSE;
    DefaultConfig.CtuMode              = ADC_SAR_IP_CTU_MODE_DISABLED;
    DefaultConfig.InjectedEdge         = ADC_SAR_IP_EXT_TRIG_EDGE_DISABLED;
    DefaultConfig.ExtTrigger           = ADC_SAR_IP_EXT_TRIG_EDGE_DISABLED;
    DefaultConfig.NormalExtTrgEn       = FALSE;
    DefaultConfig.NormalAuxExtTrgEn    = FALSE;
    for (Index = 0U; Index < Adc_Sar_Ip_au8AdcGroupCount[u32Instance]; Index++) {
        DefaultConfig.SampleTimeArr[Index] = ADC_SAR_IP_DEF_SAMPLE_TIME;
        DefaultConfig.PresamplingSourceArr[Index] = ADC_SAR_IP_PRESAMPLE_VREFL;
    }
    DefaultConfig.BypassSampling  = FALSE;
    DefaultConfig.AutoClockOff    = FALSE;
    DefaultConfig.OverwriteEnable = FALSE;
    DefaultConfig.DataAlign       = ADC_SAR_IP_DATA_ALIGNED_RIGHT;
    DefaultConfig.DecodeDelay     = 0U;
    DefaultConfig.PowerDownDelay  = 0U;
    DefaultConfig.SelfTestThresholdConfig = NULL_PTR;
    DefaultConfig.ClkDivEnable      = FALSE;
    DefaultConfig.AvgEn             = FALSE;
    DefaultConfig.AvgSel            = ADC_SAR_IP_AVG_4_CONV;
    DefaultConfig.UsrOffset         = 0U;
    DefaultConfig.UsrGain           = 0U;
    DefaultConfig.DmaEnable         = FALSE;
    DefaultConfig.DmaClearSource    = ADC_SAR_IP_DMA_REQ_CLEAR_ON_ACK;
    DefaultConfig.NumChannels       = 0U;
    DefaultConfig.ChannelConfigsPtr = NULL_PTR;
    DefaultConfig.EndOfNormalChainNotification   = NULL_PTR;
    DefaultConfig.EndOfInjectedChainNotification = NULL_PTR;
    DefaultConfig.EndOfCtuConversionNotification = NULL_PTR;

    DefaultConfig.EndOfConvNotification     = NULL_PTR;
    DefaultConfig.NumWdgThresholds          = 0U;
    DefaultConfig.WdgThresholds             = NULL_PTR;
    DefaultConfig.WdgOutOfRangeNotification = NULL_PTR;

    Status = Adc_Sar_Ip_Init(u32Instance, &DefaultConfig);
    if (ADC_SAR_IP_STATUS_SUCCESS == Status) {
        AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
        for (Index = 0U; Index < Adc_Sar_Ip_au8AdcGroupCount[u32Instance]; Index++) {
            CIMR(AdcBasePtr, Index)   = 0U;
            CEOCFR(AdcBasePtr, Index) = 0xFFFFFFFFU; /* w1c bits */
            DMAR(AdcBasePtr, Index)   = 0U;
            PSR(AdcBasePtr, Index)    = 0U;
        }

        /* Deinit watchdog interrupts */
        Adc_Sar_ResetWdog(u32Instance);
        AdcBasePtr->WTIMR = 0U;
        /* Deinit channel configuration */

        Adc_Sar_Ip_ClearStatusFlags(u32Instance, ADC_SAR_IP_NOTIF_FLAG_ALL);
        /* Set default resolution */
        Adc_Sar_Ip_SetResolution(u32Instance, ADC_SAR_IP_RESOLUTION_12);

        /* Mark that the driver was deinitialized */
        Adc_Sar_Ip_axAdcSarState[u32Instance].InitStatus = FALSE;

        Status = Adc_Sar_Ip_Powerdown(u32Instance);
    }

    return Status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_ChainConfig
 * Description   : This function configures the ADC Normal and Injected Chains
 *  with the options provided in the structure.
 *
 * @implements      Adc_Sar_Ip_ChainConfig_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_ChainConfig(uint32 const u32Instance, Adc_Sar_Ip_ChansIdxMaskType const* const pChansIdxMask,
                            Adc_Sar_Ip_ConvChainType const pChainType) {
    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);
    DevAssert(pChansIdxMask != NULL_PTR);

    /* Enabling unavailable channels is forbidden */
    for (size_t i = 0U; i < ADC_SAR_IP_NUM_GROUP_CHAN; i++) {
        DevAssert((pChansIdxMask->ChanMaskArr[i] & (~Adc_Sar_Ip_au32AdcChanBitmap[u32Instance][i])) == 0U);
    }

    switch (pChainType) {
        case ADC_SAR_IP_CONV_CHAIN_NORMAL :
            Adc_Sar_SetNormalChain(u32Instance, pChansIdxMask->ChanMaskArr);
            break;

        case ADC_SAR_IP_CONV_CHAIN_INJECTED :
            Adc_Sar_SetInjectedChain(u32Instance, pChansIdxMask->ChanMaskArr);
            break;

        default : /* no-op */
            DevAssert(FALSE);
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_EnableChannel
 * Description   : This function enables a channel in a conversion chain (
 *  ADC_SAR_IP_CONV_CHAIN_NORMAL or ADC_SAR_IP_CONV_CHAIN_INJECTED).
 *
 * @implements      Adc_Sar_Ip_EnableChannel_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_EnableChannel(uint32 const u32Instance, Adc_Sar_Ip_ConvChainType const pChainType,
                              uint32 const u32ChnIdx) {
    uint32 VectAdr;
    uint32 VectBit;
    ADC_Type* AdcBasePtr;
    volatile uint32* NCMRAddr;
    volatile uint32* JCMRAddr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);
    DevAssert(u32ChnIdx < ADC_SAR_IP_CDR_COUNT);
    DevAssert(ADC_SAR_IP_INST_HAS_CHANn(u32Instance, u32ChnIdx));

    VectAdr = ADC_SAR_IP_CHAN_2_VECT(u32ChnIdx);
    VectBit = ADC_SAR_IP_CHAN_2_BIT(u32ChnIdx);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    NCMRAddr   = &NCMR(AdcBasePtr, VectAdr);
    JCMRAddr   = &JCMR(AdcBasePtr, VectAdr);

    switch (pChainType) {
        case ADC_SAR_IP_CONV_CHAIN_NORMAL :
            SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_23();
            *NCMRAddr |= (1UL << VectBit);
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_23();
            break;

        case ADC_SAR_IP_CONV_CHAIN_INJECTED :
            SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_26();
            *JCMRAddr |= (1UL << VectBit);
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_26();
            break;

        default : /* no-op */
            DevAssert(FALSE);
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_DisableChannel
 * Description   : This function disables a channel from a conversion chain (ADC_SAR_IP_CONV_CHAIN_NORMAL
 *  or ADC_SAR_IP_CONV_CHAIN_INJECTED).
 *
 * @implements      Adc_Sar_Ip_DisableChannel_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_DisableChannel(uint32 const u32Instance, Adc_Sar_Ip_ConvChainType const pChainType,
                               uint32 const u32ChnIdx) {
    uint32 VectAdr;
    uint32 VectBit;
    ADC_Type* AdcBasePtr;
    volatile uint32* NCMRAddr;
    volatile uint32* JCMRAddr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);
    DevAssert(u32ChnIdx < ADC_SAR_IP_CDR_COUNT);
    DevAssert(ADC_SAR_IP_INST_HAS_CHANn(u32Instance, u32ChnIdx));

    VectAdr = ADC_SAR_IP_CHAN_2_VECT(u32ChnIdx);
    VectBit = ADC_SAR_IP_CHAN_2_BIT(u32ChnIdx);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    NCMRAddr   = &NCMR(AdcBasePtr, VectAdr);
    JCMRAddr   = &JCMR(AdcBasePtr, VectAdr);

    switch (pChainType) {
        case ADC_SAR_IP_CONV_CHAIN_NORMAL :
            SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_24();
            *NCMRAddr &= ~(1UL << VectBit);
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_24();
            break;

        case ADC_SAR_IP_CONV_CHAIN_INJECTED :
            SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_27();
            *JCMRAddr &= ~(1UL << VectBit);
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_27();
            break;

        default : /* no-op */
            DevAssert(FALSE);
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_SetResolution
 * Description   : This function sets the conversion resolution (number of bits per conversion data)
 *
 * @implements      Adc_Sar_Ip_SetResolution_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_SetResolution(uint32 const u32Instance, Adc_Sar_Ip_Resolution const eResolution) {
    uint32 Calbistreg;
    ADC_Type* AdcBasePtr;
    uint32 Msr;
    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);
    volatile uint32* CALBISTREGAddr;

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    Msr = AdcBasePtr->MSR;
    CALBISTREGAddr = &AdcBasePtr->CALBISTREG;

    /* The selected ADC should be in IDLE state */
    DevAssert((Msr & ADC_MSR_ADCSTATUS_MASK) == ADC_MSR_ADCSTATUS(ADC_SAR_IP_MSR_ADCSTATUS_IDLE));
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_37();
    Calbistreg = *CALBISTREGAddr;

    /* Clear the bits and set resolution value */
    Calbistreg &= ~(ADC_CALBISTREG_RESN_MASK);
    Calbistreg |= ADC_CALBISTREG_RESN(eResolution);
    *CALBISTREGAddr = Calbistreg;
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_37();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_StartConversion
 * Description   : This function starts a conversion chain (ADC_SAR_IP_CONV_CHAIN_NORMAL
 *  or ADC_SAR_IP_CONV_CHAIN_INJECTED).
 *
 * @implements      Adc_Sar_Ip_StartConversion_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_StartConversion(uint32 const u32Instance, Adc_Sar_Ip_ConvChainType const pChainType) {
    ADC_Type* AdcBasePtr;
    volatile uint32* MCRAddr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    MCRAddr    = &AdcBasePtr->MCR;

    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_10();
    switch (pChainType) {
        case ADC_SAR_IP_CONV_CHAIN_NORMAL :
            *MCRAddr |= ADC_MCR_NSTART(1U);
            break;

        case ADC_SAR_IP_CONV_CHAIN_INJECTED :
            *MCRAddr |= ADC_MCR_JSTART(1U);
            break;

        default : /* no-op */
            DevAssert(FALSE);
            break;
    }

    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_10();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_GetStatusFlags
 * Description   : This function returns the status flags of the ADC.
 *
 * @implements      Adc_Sar_Ip_GetStatusFlags_Activity
 * END**************************************************************************/
uint32 Adc_Sar_Ip_GetStatusFlags(uint32 const u32Instance) {
    uint32 Flags;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);

    /* Returns the flag status from MSR register */
    Flags  = Adc_Sar_GetMsrFlags(u32Instance);

    /* Returns the flag status from ISR register */
    Flags |= Adc_Sar_GetIsrFlags(u32Instance);

    return Flags;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_ClearStatusFlags
 * Description   : This function clears the status flags that are set to '1' in
 *  the mask.
 *
 * @implements      Adc_Sar_Ip_ClearStatusFlags_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_ClearStatusFlags(uint32 const u32Instance, uint32 const u32Mask) {
    uint32 IsrFlags;
    volatile uint32* ISRAddr;
    ADC_Type* AdcBasePtr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);
    DevAssert((u32Mask & (~ADC_SAR_IP_NOTIF_FLAG_ALL)) == 0UL);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    ISRAddr    = &AdcBasePtr->ISR;

    IsrFlags  = ((u32Mask & ADC_SAR_IP_NOTIF_FLAG_NORMAL_EOC)        != 0U) ? ADC_ISR_EOC(1U) : 0U;
    IsrFlags |= ((u32Mask & ADC_SAR_IP_NOTIF_FLAG_NORMAL_ENDCHAIN)   != 0U) ? ADC_ISR_ECH(1U) : 0U;
    IsrFlags |= ((u32Mask & ADC_SAR_IP_NOTIF_FLAG_INJECTED_EOC)      != 0U) ? ADC_ISR_JEOC(1U) : 0U;
    IsrFlags |= ((u32Mask & ADC_SAR_IP_NOTIF_FLAG_INJECTED_ENDCHAIN) != 0U) ? ADC_ISR_JECH(1U) : 0U;
    if (ADC_SAR_IP_INST_HAS_CTU(u32Instance)) {
        IsrFlags |= ((u32Mask & ADC_SAR_IP_NOTIF_FLAG_CTU_EOC) != 0U) ? ADC_ISR_EOCTU(1U) : 0U;
    }

    /* Write-1-to-clear bits in ISR register */
    *ISRAddr = IsrFlags;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_SelfTest
 * Description   : This function executes a self test on the ADC instance.
 *
 * @implements      Adc_Sar_Ip_SelfTest_Activity
 * END**************************************************************************/
Adc_Sar_Ip_StatusType Adc_Sar_Ip_SelfTest(uint32 const u32Instance) {
    ADC_Type* AdcBasePtr;
    Adc_Sar_Ip_StatusType Status = ADC_SAR_IP_STATUS_SUCCESS;
    uint32 Reg;
    uint32 MsrStatus;
    uint32 TimeoutTicks = OsIf_MicrosToTicks(ADC_SAR_IP_TIMEOUT_VAL, ADC_SAR_IP_TIMEOUT_TYPE);
    uint32 CurrentTicks = OsIf_GetCounter(ADC_SAR_IP_TIMEOUT_TYPE);
    uint32 ElapsedTicks = 0U;
    volatile uint32* MCRAddr;
    volatile uint32 const* MSRAddr;
    volatile uint32* NCMR0Addr;
    volatile uint32* STCR1Addr;
    volatile uint32* STCR2Addr;
    volatile uint32* STCR3Addr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    MCRAddr    = &AdcBasePtr->MCR;
    MSRAddr    = &AdcBasePtr->MSR;
    NCMR0Addr  = &NCMR(AdcBasePtr, 0U);
    STCR1Addr  = &AdcBasePtr->STCR1;
    STCR2Addr  = &AdcBasePtr->STCR2;
    STCR3Addr  = &AdcBasePtr->STCR3;

    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_25();
    /* 1. Program NCMR0 to select channels to be converted for normal conversion.*/
    *NCMR0Addr |= ADC_NCMR_CH0(0x1UL);
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_25();

    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_11();
    /* Self-test will only run with CPU mode so clear CTU enable */
    *MCRAddr &= ~(ADC_MCR_CTUEN_MASK);

    /* 2. Program MCR[MODE] = 1 to select Scan mode. ADC_ONE_SHOT_MODE_U32 ADCDIG_CONTINUOUS_MODE_U32*/
    *MCRAddr |= ADC_MCR_MODE(0x1UL);
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_11();

    /* 3. Program sampling duration values in STCR1[INPSAMPx].*/
    Reg = 0U;
    Reg |= ADC_STCR1_INPSAMP_S(0x10UL) | ADC_STCR1_INPSAMP_C(0x10UL);
    *STCR1Addr = Reg;

    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_35();
    /* 4. Select the self-testing algorithm in STCR3[ALG]. */
    *STCR3Addr |= ADC_STCR3_ALG(0x3UL);
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_35();

    Adc_Sar_EnableSelftestThreshold(u32Instance);

    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_35();
    /* 5. Enable the self-testing channel by setting STCR2[EN]. */
    *STCR2Addr |= ADC_STCR2_EN(0x1UL);
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_35();

    /* 6. Start the normal conversion by setting MCR[NSTART]. */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_11();
    *MCRAddr |= ADC_MCR_NSTART(0x1UL);
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_11();

    /*  Check that all algorithms have executed at least once. */
    Status = Adc_Sar_CheckSelfTestProgress(u32Instance);

    /* Stop the conversion */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_11();
    *MCRAddr &= ~(ADC_MCR_NSTART(0x1UL));
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_11();

    if (ADC_SAR_IP_STATUS_SUCCESS == Status) {
        /* Read ADC status */
        MsrStatus = ((*MSRAddr) & ADC_MSR_ADCSTATUS_MASK) >> ADC_MSR_ADCSTATUS_SHIFT;
        /* Wait for ADC changes to the expected Idle mode, The bitfield MSR[ADCSTATUS] should be checked to Idle
            * state when MCR[NSTART] is written to 0 */
        TimeoutTicks = OsIf_MicrosToTicks(ADC_SAR_IP_TIMEOUT_VAL, ADC_SAR_IP_TIMEOUT_TYPE);
        ElapsedTicks = 0U;
        while ((MsrStatus != ADC_MSR_ADCSTATUS(ADC_SAR_IP_MSR_ADCSTATUS_IDLE)) &&
               (ElapsedTicks < TimeoutTicks)) {
            MsrStatus = ((*MSRAddr) & ADC_MSR_ADCSTATUS_MASK) >> ADC_MSR_ADCSTATUS_SHIFT;
            ElapsedTicks += OsIf_GetElapsed(&CurrentTicks, ADC_SAR_IP_TIMEOUT_TYPE);
        }
    }

    Adc_Sar_DisableSelftestThreshold(u32Instance);

    /* Disable Self-test */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_35();
    *STCR2Addr &= ~(ADC_STCR2_EN(0x1UL));
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_35();

    if (ElapsedTicks >= TimeoutTicks) {
        Status = ADC_SAR_IP_STATUS_TIMEOUT;
    }

    return Status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_GetConvDataToArray
 * Description   : This function reads the conversion result values for a conversion chain
 *  (ADC_SAR_IP_CONV_CHAIN_NORMAL, ADC_SAR_IP_CONV_CHAIN_INJECTED or ADC_SAR_IP_CONV_CHAIN_CTU).
 *
 * @implements      Adc_Sar_Ip_GetConvDataToArray_Activity
 * END**************************************************************************/
uint32 Adc_Sar_Ip_GetConvDataToArray(uint32 const u32Instance, Adc_Sar_Ip_ConvChainType const pChainType,
                                     uint32 const u32Length, uint16* const pResults) {
    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);
    return Adc_Sar_GetConvResults(u32Instance, pChainType, pResults, NULL_PTR, u32Length);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_GetConvResultsToArray
 * Description   : This function gets the conversion results for the selected
 *  Conversion Chain. It follows the same algorithm as Adc_Sar_Ip_GetConvDataToArray,
 *  but will copy some extra information to the output.
 *
 * @implements      Adc_Sar_Ip_GetConvResultsToArray_Activity
 * END**************************************************************************/
uint32 Adc_Sar_Ip_GetConvResultsToArray(uint32 const u32Instance, Adc_Sar_Ip_ConvChainType const pChainType,
                                        uint32 const u32Length, Adc_Sar_Ip_ChanResultType* const pResults) {
    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);
    return Adc_Sar_GetConvResults(u32Instance, pChainType, NULL_PTR, pResults, u32Length);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_GetConvData
 * Description   : This function returns the result of the conversion for
 * a single channel
 *
 * @implements      Adc_Sar_Ip_GetConvData_Activity
 * END**************************************************************************/
uint16 Adc_Sar_Ip_GetConvData(uint32 const u32Instance, uint32 const u32ChnIdx) {
    uint16 Result = 0U;
    uint32 VectAdr;
    uint32 VectBit;
    uint32 Cdr;
    ADC_Type* AdcBasePtr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);
    DevAssert(u32ChnIdx < ADC_SAR_IP_CDR_COUNT);
    DevAssert(ADC_SAR_IP_INST_HAS_CHANn(u32Instance, u32ChnIdx));

    VectAdr = ADC_SAR_IP_CHAN_2_VECT(u32ChnIdx);
    VectBit = ADC_SAR_IP_CHAN_2_BIT(u32ChnIdx);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    Cdr = CDR(AdcBasePtr, u32ChnIdx);
    /* check if the conversion data is valid */
    if (((Cdr & ADC_CDR_VALID_MASK) != 0U)) {
        /* the data is correct, store the result in and clear the flag */
        Result = Adc_Sar_GetMaskedResult(u32Instance, Cdr);
        CEOCFR(AdcBasePtr, VectAdr) = ((uint32)1UL << VectBit); /* w1c bit */
    }

    return Result;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_GetConvResult
 * Description   : This function returns the result and the status of
 * the conversion for a single channel
 *
 * @implements      Adc_Sar_Ip_GetConvResult_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_GetConvResult(uint32 const u32Instance, uint32 const u32ChnIdx,
                              Adc_Sar_Ip_ConvChainType const pChainType, Adc_Sar_Ip_ChanResultType* const pResult) {
    uint32 VectAdr;
    uint32 VectBit;
    uint32 Cdr;
    volatile uint32* CEOCFRAddr;
    ADC_Type* AdcBasePtr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);
    DevAssert(u32ChnIdx < ADC_SAR_IP_CDR_COUNT);
    DevAssert(pResult != NULL_PTR);
    DevAssert(ADC_SAR_IP_INST_HAS_CHANn(u32Instance, u32ChnIdx));

    VectAdr = ADC_SAR_IP_CHAN_2_VECT(u32ChnIdx);
    VectBit = ADC_SAR_IP_CHAN_2_BIT(u32ChnIdx);

    pResult->ConvData        = 0U;
    pResult->AdcChnIdx       = (uint8)u32ChnIdx;
    pResult->ValidFlag       = FALSE;
    pResult->OverWrittenFlag = FALSE;

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    Cdr        = CDR(AdcBasePtr, u32ChnIdx);
    CEOCFRAddr = &CEOCFR(AdcBasePtr, VectAdr);

    /* Check if the result type matches the one request by pChainType */
    if (ADC_CDR_RESULT((uint32)pChainType) == (Cdr & ADC_CDR_RESULT_MASK)) {
        pResult->ValidFlag       = ((Cdr & ADC_CDR_VALID_MASK) != 0U) ? TRUE : FALSE;
        pResult->OverWrittenFlag = (1U == ((Cdr & ADC_CDR_OVERW_MASK) >> ADC_CDR_OVERW_SHIFT));
        pResult->ConvData        = Adc_Sar_GetMaskedResult(u32Instance, Cdr);
    }

    *CEOCFRAddr = ((uint32)1UL << VectBit); /* w1c bit */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_DoCalibration
 * Description   : This functions executes a calibration sequence. It is recommended
 *  to run this sequence before using the ADC converter. The maximum clock frequency
 *  for the calibration is 40 MHz, this function sets the ADCLKSEL bit resulting in
 *  a maximum input clock frequency of 80 MHz.
 *
 * @implements      Adc_Sar_Ip_DoCalibration_Activity
 * END**************************************************************************/
Adc_Sar_Ip_StatusType Adc_Sar_Ip_DoCalibration(uint32 const u32Instance) {
    ADC_Type* AdcBasePtr;
    Adc_Sar_Ip_StatusType Status    = ADC_SAR_IP_STATUS_SUCCESS;
    Adc_Sar_Ip_StatusType CalStatus = ADC_SAR_IP_STATUS_SUCCESS;
    uint32 AdcClkSel;
    uint32 Mcr;
    volatile uint32* MCRAddr;
    volatile uint32* CALBISTREGAddr;
    volatile uint32* CAL2Addr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);

    AdcBasePtr     = Adc_Sar_Ip_apxAdcBase[u32Instance];
    MCRAddr        = &AdcBasePtr->MCR;
    CALBISTREGAddr = &AdcBasePtr->CALBISTREG;
    CAL2Addr       = &AdcBasePtr->CAL2;

    /* Set CLKSEL to CalibrationClkSelect value */
    Status = Adc_Sar_Ip_Powerdown(u32Instance);
    if (ADC_SAR_IP_STATUS_SUCCESS == Status) {
        /* Save the current state of ADCLKSEL in order to restore it */
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_12();
        Mcr = *MCRAddr;
        AdcClkSel = (Mcr & ADC_MCR_ADCLKSEL_MASK);
        Mcr &= ~(ADC_MCR_ADCLKSEL_MASK);
        Mcr |= Adc_Sar_GetADCLKSELValue(Adc_Sar_Ip_axAdcSarState[u32Instance].CalibrationClkSelect);
        *MCRAddr = Mcr;
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_12();

        Status = Adc_Sar_Ip_Powerup(u32Instance);
        if (ADC_SAR_IP_STATUS_SUCCESS == Status) {
            /* S32K358 calibration is CALBISTREG/CAL2-based (not MCR-based); nothing further
                to do here beyond the pointer setup above. */

            /* Restore the state of ADCLKSEL */
            Status = Adc_Sar_Ip_Powerdown(u32Instance);
        }

        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_12();
        Mcr = *MCRAddr;
        Mcr &= ~(ADC_MCR_ADCLKSEL_MASK);
        Mcr |= AdcClkSel;
        *MCRAddr = Mcr;
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_12();

        if (ADC_SAR_IP_STATUS_SUCCESS == Status) {
            Status = Adc_Sar_Ip_Powerup(u32Instance);

            if (ADC_SAR_IP_STATUS_SUCCESS != CalStatus) {
                Status = CalStatus;
            }
        }
    }

    return Status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_Powerup
 * Description   : This function enables the ADC module (by clearing the Powerdown
 *  bit).
 *
 * @implements      Adc_Sar_Ip_Powerup_Activity
 * END**************************************************************************/
Adc_Sar_Ip_StatusType Adc_Sar_Ip_Powerup(uint32 const u32Instance) {
    Adc_Sar_Ip_StatusType ReturnStatus = ADC_SAR_IP_STATUS_SUCCESS;

    ADC_Type const* AdcBasePtr;
    uint32 ExpectedStatus = ADC_MSR_ADCSTATUS(ADC_SAR_IP_MSR_ADCSTATUS_IDLE); /* expected status is IDLE */
    uint32 MsrStatus;
    volatile uint32 const* MSRAddr;
    uint32 TimeoutTicks = OsIf_MicrosToTicks(ADC_SAR_IP_TIMEOUT_VAL, ADC_SAR_IP_TIMEOUT_TYPE);
    uint32 CurrentTicks = OsIf_GetCounter(ADC_SAR_IP_TIMEOUT_TYPE);
    uint32 ElapsedTicks = 0U;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    MSRAddr    = &AdcBasePtr->MSR;

    MsrStatus = (*MSRAddr) & ADC_MSR_ADCSTATUS_MASK;

    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_13();
    Adc_Sar_Powerup(u32Instance);
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_13();

    /* Wait for the device to power up */
    while ((MsrStatus != ExpectedStatus) && (ElapsedTicks < TimeoutTicks)) {
        MsrStatus = (*MSRAddr) & ADC_MSR_ADCSTATUS_MASK;
        ElapsedTicks += OsIf_GetElapsed(&CurrentTicks, ADC_SAR_IP_TIMEOUT_TYPE);
    }

    if (ElapsedTicks >= TimeoutTicks) {
        ReturnStatus = ADC_SAR_IP_STATUS_TIMEOUT;
    }

    return ReturnStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_Powerdown
 * Description   : This function disables the ADC module (by setting the Powerdown
 *  bit).
 *
 * @implements      Adc_Sar_Ip_Powerdown_Activity
 * END**************************************************************************/
Adc_Sar_Ip_StatusType Adc_Sar_Ip_Powerdown(uint32 const u32Instance) {
    ADC_Type const* AdcBasePtr;
    Adc_Sar_Ip_StatusType ReturnStatus = ADC_SAR_IP_STATUS_SUCCESS;
    uint32 ExpectedStatus =
        ADC_MSR_ADCSTATUS(ADC_SAR_IP_MSR_ADCSTATUS_POWER_DOWN); /* expected status is powered down */
    uint32 MsrStatus;
    volatile uint32 const* MSRAddr;
    uint32 TimeoutTicks = OsIf_MicrosToTicks(ADC_SAR_IP_TIMEOUT_VAL, ADC_SAR_IP_TIMEOUT_TYPE);
    uint32 CurrentTicks = OsIf_GetCounter(ADC_SAR_IP_TIMEOUT_TYPE);
    uint32 ElapsedTicks = 0U;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    MSRAddr    = &AdcBasePtr->MSR;

    MsrStatus = (*MSRAddr) & ADC_MSR_ADCSTATUS_MASK;

    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_14();
    Adc_Sar_Powerdown(u32Instance);
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_14();

    /* Wait for the device to power down */
    while ((MsrStatus != ExpectedStatus) && (ElapsedTicks < TimeoutTicks)) {
        MsrStatus = (*MSRAddr) & ADC_MSR_ADCSTATUS_MASK;
        ElapsedTicks += OsIf_GetElapsed(&CurrentTicks, ADC_SAR_IP_TIMEOUT_TYPE);

        #if (__GTEST == 1)
        /* For unit testing, force the status to be the expected value to avoid timeout */
        MsrStatus = ExpectedStatus;
        #endif
    }

    if (ElapsedTicks >= TimeoutTicks) {
        ReturnStatus = ADC_SAR_IP_STATUS_TIMEOUT;
    }

    return ReturnStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_EnableNotifications
 * Description   : This function enables the ADC notifications set to '1' in the
 *  mask parameter.
 *
 * @implements      Adc_Sar_Ip_EnableNotifications_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_EnableNotifications(uint32 const u32Instance, uint32 const u32NotificationMask) {
    ADC_Type* AdcBasePtr;
    uint32 ImrFlags;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);
    DevAssert((u32NotificationMask & (~ADC_SAR_IP_NOTIF_FLAG_ALL)) == 0UL);

    ImrFlags  = ((u32NotificationMask & ADC_SAR_IP_NOTIF_FLAG_NORMAL_EOC)        != 0U) ? ADC_IMR_MSKEOC(1U) : 0U;
    ImrFlags |= ((u32NotificationMask & ADC_SAR_IP_NOTIF_FLAG_INJECTED_EOC)      != 0U) ? ADC_IMR_MSKJEOC(1U) : 0U;
    ImrFlags |= ((u32NotificationMask & ADC_SAR_IP_NOTIF_FLAG_NORMAL_ENDCHAIN)   != 0U) ? ADC_IMR_MSKECH(1U) : 0U;
    ImrFlags |= ((u32NotificationMask & ADC_SAR_IP_NOTIF_FLAG_INJECTED_ENDCHAIN) != 0U) ? ADC_IMR_MSKJECH(1U) : 0U;
    if (ADC_SAR_IP_INST_HAS_CTU(u32Instance)) {
        ImrFlags |= ((u32NotificationMask & ADC_SAR_IP_NOTIF_FLAG_CTU_EOC) != 0U) ? ADC_IMR_MSKEOCTU(1U) : 0U;
    }

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_33();
    AdcBasePtr->IMR |= ImrFlags;
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_33();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_DisableNotifications
 * Description   : This function disables the ADC notifications set to '1' in the
 *  mask parameter.
 *
 * @implements      Adc_Sar_Ip_DisableNotifications_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_DisableNotifications(uint32 const u32Instance, uint32 const u32NotificationMask) {
    ADC_Type* AdcBasePtr;
    uint32 ImrFlags;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);
    DevAssert((u32NotificationMask & (~ADC_SAR_IP_NOTIF_FLAG_ALL)) == 0UL);

    ImrFlags  = ((u32NotificationMask & ADC_SAR_IP_NOTIF_FLAG_NORMAL_EOC)        != 0U) ? ADC_IMR_MSKEOC(1U) : 0U;
    ImrFlags |= ((u32NotificationMask & ADC_SAR_IP_NOTIF_FLAG_INJECTED_EOC)      != 0U) ? ADC_IMR_MSKJEOC(1U) : 0U;
    ImrFlags |= ((u32NotificationMask & ADC_SAR_IP_NOTIF_FLAG_NORMAL_ENDCHAIN)   != 0U) ? ADC_IMR_MSKECH(1U) : 0U;
    ImrFlags |= ((u32NotificationMask & ADC_SAR_IP_NOTIF_FLAG_INJECTED_ENDCHAIN) != 0U) ? ADC_IMR_MSKJECH(1U) : 0U;
    if (ADC_SAR_IP_INST_HAS_CTU(u32Instance)) {
        ImrFlags |= ((u32NotificationMask & ADC_SAR_IP_NOTIF_FLAG_CTU_EOC) != 0U) ? ADC_IMR_MSKEOCTU(1U) : 0U;
    }

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_34();
    AdcBasePtr->IMR &= ~(ImrFlags);
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_34();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_EnableChannelNotifications
 * Description   : This function enables End-of-Conversion and watchdog
 * interrupts generation for a single channel.
 *
 * @implements      Adc_Sar_Ip_EnableChannelNotifications_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_EnableChannelNotifications(uint32 const u32Instance, uint32 const u32ChnIdx, uint32 const u32Mask) {
    ADC_Type* AdcBasePtr;
    volatile uint32* CIMRAddr;
    volatile uint32* CWENRAddr;
    uint32 VectAdr;
    uint32 VectBit;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);
    DevAssert(u32ChnIdx < ADC_SAR_IP_CDR_COUNT);
    DevAssert((u32Mask & ~(ADC_SAR_IP_CHAN_NOTIF_FLAG_ALL)) == 0UL);
    DevAssert(ADC_SAR_IP_INST_HAS_CHANn(u32Instance, u32ChnIdx));

    VectAdr = ADC_SAR_IP_CHAN_2_VECT(u32ChnIdx);
    VectBit = ADC_SAR_IP_CHAN_2_BIT(u32ChnIdx);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    CIMRAddr   = &CIMR(AdcBasePtr, VectAdr);
    CWENRAddr  = &CWENR(AdcBasePtr, VectAdr);

    if ((u32Mask & ADC_SAR_IP_CHAN_NOTIF_EOC) != 0U) {
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_30();
        *CIMRAddr |= 1UL << VectBit;
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_30();
    }

    if ((u32Mask & ADC_SAR_IP_CHAN_NOTIF_WDG) != 0U) {
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_28();
        *CWENRAddr |= 1UL << VectBit;
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_28();
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_DisableChannelNotifications
 * Description   : This function disables End-of-Conversion and watchdog
 * interrupts generation for a single channel.
 *
 * @implements      Adc_Sar_Ip_DisableChannelNotifications_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_DisableChannelNotifications(uint32 const u32Instance, uint32 const u32ChnIdx, uint32 const u32Mask) {
    ADC_Type* AdcBasePtr;
    volatile uint32* CIMRAddr;
    volatile uint32* CWENRAddr;
    uint32 VectAdr;
    uint32 VectBit;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);
    DevAssert(u32ChnIdx < ADC_SAR_IP_CDR_COUNT);
    DevAssert((u32Mask & ~(ADC_SAR_IP_CHAN_NOTIF_FLAG_ALL)) == 0UL);
    DevAssert(ADC_SAR_IP_INST_HAS_CHANn(u32Instance, u32ChnIdx));

    VectAdr = ADC_SAR_IP_CHAN_2_VECT(u32ChnIdx);
    VectBit = ADC_SAR_IP_CHAN_2_BIT(u32ChnIdx);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    CIMRAddr   = &CIMR(AdcBasePtr, VectAdr);
    CWENRAddr  = &CWENR(AdcBasePtr, VectAdr);

    if ((u32Mask & ADC_SAR_IP_CHAN_NOTIF_EOC) != 0U) {
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_31();
        *CIMRAddr &= ~(1UL << VectBit);
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_31();
    }

    if ((u32Mask & ADC_SAR_IP_CHAN_NOTIF_WDG) != 0U) {
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_29();
        *CWENRAddr &= ~(1UL << VectBit);
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_29();
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_SetClockMode
 * Description   : This function initializes the ADC clock configuration.
 *
 * @implements      Adc_Sar_Ip_SetClockMode_Activity
 * END**************************************************************************/
Adc_Sar_Ip_StatusType Adc_Sar_Ip_SetClockMode(uint32 const                            u32Instance,
                                              Adc_Sar_Ip_ClockConfigType const* const pConfig) {
    Adc_Sar_Ip_StatusType Status = ADC_SAR_IP_STATUS_SUCCESS;
    uint32 Mcr;
    volatile uint32* MCRAddr;
    volatile uint32* PDEDRAddr;
    ADC_Type* AdcBasePtr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);
    DevAssert(pConfig != NULL_PTR);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    MCRAddr    = &AdcBasePtr->MCR;
    PDEDRAddr  = &AdcBasePtr->PDEDR;

    /* Read MCR value and clear values that will be replaced */
    Mcr = Adc_Sar_GetADCLKSELValue(pConfig->ClkSelect);
    Status = Adc_Sar_Ip_Powerdown(u32Instance);
    if (ADC_SAR_IP_STATUS_SUCCESS == Status) {
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_15();
        *MCRAddr = (*MCRAddr & ~(ADC_MCR_ADCLKSEL_MASK)) | Mcr;
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_15();

        Status = Adc_Sar_Ip_Powerup(u32Instance);
        if (ADC_SAR_IP_STATUS_SUCCESS == Status) {
            SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_51();
            /* Enables high speed conversion or calibration */
            Adc_Sar_EnableHighSpeed(AdcBasePtr, pConfig->HighSpeedConvEn);
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_51();

            Adc_Sar_Ip_SetAveraging(u32Instance, pConfig->AvgEn, pConfig->AvgSel);

            /* Set powerdown delay */
            *PDEDRAddr = ADC_PDEDR_PDED(pConfig->PowerDownDelay);

            /* Set sample times */
            Adc_Sar_Ip_SetSampleTimes(u32Instance, pConfig->SampleTimeArr);
        }
    }

    return Status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_SetSampleTimes
 * Description   : This function sets the sample times for each channnel group.
 *
 * @implements      Adc_Sar_Ip_SetSampleTimes_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_SetSampleTimes(uint32 const u32Instance, uint8 const* const aSampleTimes) {
    ADC_Type* AdcBasePtr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    for (size_t Index = 0U; Index < Adc_Sar_Ip_au8AdcGroupCount[u32Instance]; Index++) {
        /* Set sample times */
        CTR(AdcBasePtr, Index) = ADC_CTR_INPSAMP(aSampleTimes[Index]);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_SetAveraging
 * Description   : This function sets the sample times for each channnel group.
 *
 * @implements      Adc_Sar_Ip_SetAveraging_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_SetAveraging(uint32 const u32Instance, boolean const bAvgEn, Adc_Sar_Ip_AvgSelectType const eAvgSel) {
    ADC_Type* AdcBasePtr;
    volatile uint32* MCRAddr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    MCRAddr    = &AdcBasePtr->MCR;

    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_16();
    /* Clear old values */
    *MCRAddr &= ~(ADC_MCR_AVGEN_MASK | ADC_MCR_AVGS_MASK);

    /* Write new values */
    *MCRAddr |= ADC_MCR_AVGEN(bAvgEn ? 1U : 0U) | ADC_MCR_AVGS(eAvgSel);
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_16();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_AbortConversion
 * Description   : This function aborts an ongoing conversion.
 *
 * @implements      Adc_Sar_Ip_AbortConversion_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_AbortConversion(uint32 const u32Instance) {
    ADC_Type* AdcBasePtr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_17();
    AdcBasePtr->MCR |= ADC_MCR_ABORT(1U);
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_17();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_AbortChain
 * Description   : This function aborts an ongoing chain of conversions.
 *
 * @implements      Adc_Sar_Ip_AbortChain_Activity
 * END**************************************************************************/
Adc_Sar_Ip_StatusType Adc_Sar_Ip_AbortChain(uint32 const u32Instance, boolean const bBlocking,
                                            boolean const bAllowRestart) {
    ADC_Type* AdcBasePtr;
    volatile uint32* MCRAddr;
    volatile uint32 const* MSRAddr;
    uint32 MsrStatus;
    uint32 TimeoutTicks = OsIf_MicrosToTicks(ADC_SAR_IP_TIMEOUT_VAL, ADC_SAR_IP_TIMEOUT_TYPE);
    uint32 CurrentTicks = OsIf_GetCounter(ADC_SAR_IP_TIMEOUT_TYPE);
    uint32 ElapsedTicks = 0U;
    Adc_Sar_Ip_StatusType ReturnStatus = ADC_SAR_IP_STATUS_SUCCESS;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    MCRAddr    = &AdcBasePtr->MCR;
    MSRAddr    = &AdcBasePtr->MSR;

    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_18();
    /* The behavior of the ADC depends on MCR[MODE] (One-Shot/Scan Operation modes).
    If Scan Operation mode is disabled, MSR[NSTART] is automatically reset together with MCR[ABORTCHAIN].
    Otherwise, in Scan Operation mode, a new chain is started. Therefore MCR[NSTART] should be cleared
    before abort the current chain of conversions. */
    if (!bAllowRestart) {
        *MCRAddr &= ~(ADC_MCR_NSTART(1U));
    }
    *MCRAddr |= ADC_MCR_ABORTCHAIN(1U);
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_18();

    if (bBlocking) {
        /* Wait for the ongoing conversion to stop */
        MsrStatus = *MSRAddr & ADC_MSR_NSTART_MASK;
        while ((MsrStatus == ADC_MSR_NSTART_MASK) && (ElapsedTicks < TimeoutTicks)) {
            MsrStatus = *MSRAddr & ADC_MSR_NSTART_MASK;
            ElapsedTicks += OsIf_GetElapsed(&CurrentTicks, ADC_SAR_IP_TIMEOUT_TYPE);
        }

        if (ElapsedTicks >= TimeoutTicks) {
            ReturnStatus = ADC_SAR_IP_STATUS_TIMEOUT;
        }
    }

    return ReturnStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_SetPresamplingSource
 * Description   : This function configures the Presampling Source for a channel group (0-31, 32-63, 64 -95)
 *
 * @implements      Adc_Sar_Ip_SetPresamplingSource_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_SetPresamplingSource(uint32 const u32Instance, Adc_Sar_Ip_ChanGroupType const pChanGroup,
                                     Adc_Sar_Ip_PresamplingSourceType const pPresampleSource) {
    uint32 Pscr;
    ADC_Type* AdcBasePtr;
    volatile uint32* PSCRAddr;

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    PSCRAddr   = &AdcBasePtr->PSCR;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);

    if (ADC_SAR_IP_INST_HAS_PSCR(u32Instance)) {
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_38();

        Pscr = *PSCRAddr;

        switch (pChanGroup) {
            case ADC_SAR_IP_CHAN_GROUP_0 :
                Pscr &= ~(ADC_PSCR_PREVAL0_MASK);
                Pscr |= ADC_PSCR_PREVAL0((uint32)pPresampleSource);
                break;

            case ADC_SAR_IP_CHAN_GROUP_1 :
                Pscr &= ~(ADC_PSCR_PREVAL1_MASK);
                Pscr |= ADC_PSCR_PREVAL1((uint32)pPresampleSource);
                break;

            case ADC_SAR_IP_CHAN_GROUP_2 :
                Pscr &= ~(ADC_PSCR_PREVAL2_MASK);
                Pscr |= ADC_PSCR_PREVAL2((uint32)pPresampleSource);
                break;

            default : /* no-op */
                /* Not supported */
                DevAssert(FALSE);
                break;
        }

        *PSCRAddr = Pscr;

        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_38();
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_EnableChannelPresampling
 * Description   : This function enables the Presampling on one channel of the ADC.
 *
 * @implements      Adc_Sar_Ip_EnableChannelPresampling_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_EnableChannelPresampling(uint32 const u32Instance, uint32 const u32ChnIdx) {
    uint32 VectAdr;
    uint32 VectBit;
    ADC_Type* AdcBasePtr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);
    DevAssert(u32ChnIdx < ADC_SAR_IP_CDR_COUNT);
    DevAssert(ADC_SAR_IP_INST_HAS_CHANn(u32Instance, u32ChnIdx));

    if (ADC_SAR_IP_INST_HAS_PSCR(u32Instance)) {
        VectAdr = ADC_SAR_IP_CHAN_2_VECT(u32ChnIdx);
        VectBit = ADC_SAR_IP_CHAN_2_BIT(u32ChnIdx);

        AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_41();
        PSR(AdcBasePtr, VectAdr) |= 1UL << VectBit;
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_41();
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_DisableChannelPresampling
 * Description   : This function disables the Presampling on one channel of the ADC.
 *
 * @implements      Adc_Sar_Ip_DisableChannelPresampling_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_DisableChannelPresampling(uint32 const u32Instance, uint32 const u32ChnIdx) {
    uint32 VectAdr;
    uint32 VectBit;
    ADC_Type* AdcBasePtr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);
    DevAssert(u32ChnIdx < ADC_SAR_IP_CDR_COUNT);
    DevAssert(ADC_SAR_IP_INST_HAS_CHANn(u32Instance, u32ChnIdx));

    if (ADC_SAR_IP_INST_HAS_PSCR(u32Instance)) {
        VectAdr = ADC_SAR_IP_CHAN_2_VECT(u32ChnIdx);
        VectBit = ADC_SAR_IP_CHAN_2_BIT(u32ChnIdx);

        AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_42();
        PSR(AdcBasePtr, VectAdr) &= ~(1UL << VectBit);
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_42();
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_EnablePresampleConversion
 * Description   : This function enables bypass of the Sampling Phase, resulting in a conversion
 * of the presampled data. This is available only for channels that have presampling
 * enabled.
 *
 * @implements      Adc_Sar_Ip_EnablePresampleConversion_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_EnablePresampleConversion(uint32 const u32Instance) {
    ADC_Type* AdcBasePtr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);

    if (ADC_SAR_IP_INST_HAS_PSCR(u32Instance)) {
        AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_39();
        AdcBasePtr->PSCR |= ADC_PSCR_PRECONV(1U);
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_39();
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_DisablePresampleConversion
 * Description   : This function disables Sampling Phase bypass.
 *
 * @implements      Adc_Sar_Ip_DisablePresampleConversion_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_DisablePresampleConversion(uint32 const u32Instance) {
    ADC_Type* AdcBasePtr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);

    if (ADC_SAR_IP_INST_HAS_PSCR(u32Instance)) {
        AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_40();
        AdcBasePtr->PSCR &= ~(ADC_PSCR_PRECONV(1U));
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_40();
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_EnableDma
 * Description   : This function enables requests to DMA from ADC
 *
 * @implements      Adc_Sar_Ip_EnableDma_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_EnableDma(uint32 const u32Instance) {
    ADC_Type* AdcBasePtr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_43();
    AdcBasePtr->DMAE |= ADC_DMAE_DMAEN(1U);
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_43();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_DisableDma
 * Description   : This function disables requests to DMA from ADC
 *
 * @implements      Adc_Sar_Ip_DisableDma_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_DisableDma(uint32 const u32Instance) {
    ADC_Type* AdcBasePtr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_44();
    AdcBasePtr->DMAE &= ~(ADC_DMAE_DMAEN(1U));
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_44();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_EnableChannelDma
 * Description   : This function enables DMA requests triggered by End of Conversion event from
 *  a selected channel.
 *
 * @implements      Adc_Sar_Ip_EnableChannelDma_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_EnableChannelDma(uint32 const u32Instance, uint32 const u32ChnIdx) {
    ADC_Type* AdcBasePtr;
    uint32 VectAdr;
    uint32 VectBit;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);
    DevAssert(u32ChnIdx < ADC_SAR_IP_CDR_COUNT);
    DevAssert(ADC_SAR_IP_INST_HAS_CHANn(u32Instance, u32ChnIdx));

    VectAdr = ADC_SAR_IP_CHAN_2_VECT(u32ChnIdx);
    VectBit = ADC_SAR_IP_CHAN_2_BIT(u32ChnIdx);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_46();
    DMAR(AdcBasePtr, VectAdr) |= 1UL << VectBit;
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_46();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_DisableChannelDma
 * Description   : This function disables DMA requests triggered by End of Conversion event from
 *  a selected channel.
 *
 * @implements      Adc_Sar_Ip_DisableChannelDma_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_DisableChannelDma(uint32 const u32Instance, uint32 const u32ChnIdx) {
    ADC_Type* AdcBasePtr;
    uint32 VectAdr;
    uint32 VectBit;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);
    DevAssert(u32ChnIdx < ADC_SAR_IP_CDR_COUNT);
    DevAssert(ADC_SAR_IP_INST_HAS_CHANn(u32Instance, u32ChnIdx));

    VectAdr = ADC_SAR_IP_CHAN_2_VECT(u32ChnIdx);
    VectBit = ADC_SAR_IP_CHAN_2_BIT(u32ChnIdx);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_47();
    DMAR(AdcBasePtr, VectAdr) &= ~(1UL << VectBit);
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_47();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_DisableChannelDmaAll
 * Description   : This function disables DMA requests triggered by End of Conversion event from
 *  all channels.
 *
 * @implements      Adc_Sar_Ip_DisableChannelDmaAll_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_DisableChannelDmaAll(uint32 const u32Instance) {
    ADC_Type* AdcBasePtr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    for (size_t Index = 0U; Index < Adc_Sar_Ip_au8AdcGroupCount[u32Instance]; Index++) {
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_48();
        DMAR(AdcBasePtr, Index) &= ~(Adc_Sar_Ip_au32AdcChanBitmap[u32Instance][Index]);
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_48();
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_SetDmaClearSource
 * Description   : This function selects the DMA Request Flag Clear Source.
 *
 * @implements      Adc_Sar_Ip_SetDmaClearSource_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_SetDmaClearSource(uint32 const u32Instance, Adc_Sar_Ip_ClearSourceType const pDmaClear) {
    ADC_Type* AdcBasePtr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_45();
    AdcBasePtr->DMAE &= ~(ADC_DMAE_DCLR_MASK);
    AdcBasePtr->DMAE |= ADC_DMAE_DCLR((uint32)pDmaClear);
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_45();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_SetWdgThreshold
 * Description   : This function sets the watchdog thresholds for a certain register.
 *
 * @implements      Adc_Sar_Ip_SetWdgThreshold_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_SetWdgThreshold(uint32 const u32Instance, uint8 const u8RegisterIdx,
                                Adc_Sar_Ip_WdgThresholdType const* const pThresholdValues) {
    ADC_Type* AdcBasePtr;
    volatile uint32* WTIMRAddr;
    uint8  Shift;
    uint16 HighThreshold;
    uint16 LowThreshold;
    uint32 Wtimr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);
    DevAssert(pThresholdValues != NULL_PTR);
    DevAssert(u8RegisterIdx < ADC_SAR_IP_THRHLR_COUNT);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    WTIMRAddr  = &AdcBasePtr->WTIMR;

    if (FALSE == Adc_Sar_Ip_axAdcSarState[u32Instance].BypassResolution) {
        /* Calculate the shift of the threshold value to get the number of bits
         * needed by the hardware unit. */
        Shift = ADC_SAR_IP_RESULT_RESOLUTION - Adc_Sar_GetResolution(u32Instance);

        /* Shift the threshold to obtain the value to be written in the threshold register. */
        HighThreshold = (pThresholdValues->HighThreshold) << Shift;
        LowThreshold  = (pThresholdValues->LowThreshold) << Shift;

        /* If the bits of the high threshold value that are ignored due to
         * resolution remain 0, this will trigger interrupts when the conversion
         * value is equal to the high threshold value because the ignored bits
         * of the conversion result will be more than 0, so the high threshold
         * value will need to have the ignored bits set to 1. */
        HighThreshold |= (((uint16)1U << Shift) - 1U);

        Adc_Sar_WriteThresholds(u32Instance, u8RegisterIdx, HighThreshold, LowThreshold);
    }
    else {
        Adc_Sar_WriteThresholds(u32Instance, u8RegisterIdx, pThresholdValues->HighThreshold,
                                pThresholdValues->LowThreshold);
    }

    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_32();

    Wtimr = *WTIMRAddr;

    if (pThresholdValues->HighThresholdIntEn) {
        Wtimr |= (ADC_SAR_IP_WDG_REG_MASK_HIGH(u8RegisterIdx));
    }
    else {
        Wtimr &= (~ADC_SAR_IP_WDG_REG_MASK_HIGH(u8RegisterIdx));
    }

    if (pThresholdValues->LowThresholdIntEn) {
        Wtimr |= (ADC_SAR_IP_WDG_REG_MASK_LOW(u8RegisterIdx));
    }
    else {
        Wtimr &= (~ADC_SAR_IP_WDG_REG_MASK_LOW(u8RegisterIdx));
    }

    *WTIMRAddr = Wtimr;

    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_32();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_SetConversionMode
 * Description   : This function configures the used conversion mode.
 * Note: The ADC instance must be in IDLE state in order to change this.
 *
 * @implements      Adc_Sar_Ip_SetConversionMode_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_SetConversionMode(uint32 const u32Instance, Adc_Sar_Ip_ConvModeType const eConvMode) {
    ADC_Type* AdcBasePtr;
    volatile const uint32* MSRAddr;
    volatile uint32* MCRAddr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    MSRAddr    = &AdcBasePtr->MSR;
    MCRAddr    = &AdcBasePtr->MCR;

    /* The selected ADC should be in IDLE state */
    DevAssert(((*MSRAddr) & ADC_MSR_ADCSTATUS_MASK) == ADC_MSR_ADCSTATUS(ADC_SAR_IP_MSR_ADCSTATUS_IDLE));

    /* Edit MODE */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_19();
    switch (eConvMode) {
        case ADC_SAR_IP_CONV_MODE_ONESHOT :
            *MCRAddr &= ~(ADC_MCR_MODE(1U)); /* MODE = 0 */
            break;

        case ADC_SAR_IP_CONV_MODE_SCAN :
            *MCRAddr |= ADC_MCR_MODE(1U); /* MODE = 1 */
            break;

        default : /* no-op */
            break;
    }
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_19();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_SetCtuMode
 * Description   : This function configures the CTU mode and enable.
 *
 * @implements      Adc_Sar_Ip_SetCtuMode_Activity
 * END**************************************************************************/
Adc_Sar_Ip_StatusType Adc_Sar_Ip_SetCtuMode(uint32 const u32Instance, Adc_Sar_Ip_CtuModeType const eCtuMode) {
    ADC_Type* AdcBasePtr;
    Adc_Sar_Ip_StatusType Status = ADC_SAR_IP_STATUS_SUCCESS;
    volatile uint32* MCRAddr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);
    DevAssert(!((FALSE == ADC_SAR_IP_INST_HAS_CTU_TRIGGER_MODE(u32Instance)) &&
                (ADC_SAR_IP_CTU_MODE_TRIGGER == eCtuMode)));

    AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32Instance];
    MCRAddr    = &AdcBasePtr->MCR;

    /* Clear CTUEN to allow Powerdown operation to succeed. */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_20();
    *MCRAddr &= ~ADC_MCR_CTUEN_MASK;
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_20();

    /* Power down */
    Status = Adc_Sar_Ip_Powerdown(u32Instance);
    if (ADC_SAR_IP_STATUS_SUCCESS == Status) {
        /* Configure CTU */
        if (ADC_SAR_IP_INST_HAS_CTU(u32Instance)) {
            SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_20();
            switch (eCtuMode) {
                case ADC_SAR_IP_CTU_MODE_CONTROL :
                    *MCRAddr &= ~(ADC_MCR_CTU_MODE(1U)); /* CTU_MODE = 0 */
                    *MCRAddr |= ADC_MCR_CTUEN(1U);       /* CTUEN = 1 */
                    break;

                case ADC_SAR_IP_CTU_MODE_TRIGGER :
                    /* Set CTU_MODE = 1 and CTUEN = 1 */
                    *MCRAddr |= (ADC_MCR_CTU_MODE(1U) | ADC_MCR_CTUEN(1U));
                    break;

                    /* Set CTU_MODE = 0 and CTUEN = 0 */
                case ADC_SAR_IP_CTU_MODE_DISABLED :
                    *MCRAddr &= ~(ADC_MCR_CTU_MODE(1U) | ADC_MCR_CTUEN(1U));
                    break;

                default : /* no-op */
                    break;
            }
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_20();
        }

        /* Power up */
        Status = Adc_Sar_Ip_Powerup(u32Instance);
    }

    return Status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_SetExternalTrigger
 * Description   : This function configures the external trigger.
 *
 * @implements      Adc_Sar_Ip_SetExternalTrigger_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_SetExternalTrigger(uint32 const u32Instance, Adc_Sar_Ip_ExtTriggerEdgeType const eTriggerEdge,
                                   Adc_Sar_Ip_ExtTriggerSourceType const eTrggerSrc) {
    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);

    /* Switch between injected and normal external trigger */
    switch (eTrggerSrc) {
        case ADC_SAR_IP_NORMAL_EXT_TRIG :
            Adc_Sar_ConfigExternalTrigger(u32Instance, eTriggerEdge, ADC_MCR_EDGE_MASK, 0U, ADC_MCR_TRGEN_MASK);
            break;

        case ADC_SAR_IP_AUX_NORMAL_EXT_TRIG :
            Adc_Sar_ConfigExternalTrigger(u32Instance, eTriggerEdge, ADC_MCR_EDGE_MASK, 0U, ADC_MCR_XSTRTEN_MASK);
            break;

        case ADC_SAR_IP_ALL_NORMAL_EXT_TRIG :
            Adc_Sar_ConfigExternalTrigger(u32Instance, eTriggerEdge, ADC_MCR_EDGE_MASK, ADC_MCR_EDGE_MASK,
                                          (ADC_MCR_TRGEN_MASK | ADC_MCR_XSTRTEN_MASK));
            break;

        case ADC_SAR_IP_INJECTED_EXT_TRIG :
            Adc_Sar_ConfigExternalTrigger(u32Instance, eTriggerEdge, ADC_MCR_JEDGE_MASK, ADC_MCR_JEDGE_MASK,
                                          ADC_MCR_JTRGEN_MASK);
            break;

        default : /* no-op */
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_TempSenseCalculateTemp
 * Description   : This function calculates the temperature on chip from the provided
 * parameter.
 *
 * @implements      Adc_Sar_Ip_TempSenseCalculateTemp_Activity
 * END**************************************************************************/
uint16 Adc_Sar_Ip_TempSenseCalculateTemp(uint32 const u32AdcInstance, uint32 const u32TempInstance,
                                         uint16 const u16TempSenseAdcConvData) {
    uint32 Vets;
    uint32 Vref;
    uint32 TempValue;
    sint32 Tets;
    uint16 Result;
    uint8 Resolution;

    if (FALSE == Adc_Sar_Ip_axAdcSarState[u32AdcInstance].BypassResolution) {
        Resolution = Adc_Sar_GetResolution(u32AdcInstance);
    }
    else {
        Resolution = ADC_SAR_IP_RESULT_RESOLUTION;
    }

    Result = (Resolution > ADC_SAR_IP_TEMPSENSE_RESOLUTION)
                 ? (u16TempSenseAdcConvData >> (Resolution - ADC_SAR_IP_TEMPSENSE_RESOLUTION))
                 : (u16TempSenseAdcConvData << (ADC_SAR_IP_TEMPSENSE_RESOLUTION - Resolution));

    DevAssert(u32TempInstance < TEMPSENSE_INSTANCE_COUNT);
    DevAssert(AdcVoltageRefs[u32AdcInstance] <= 0x58U); /* Vref should be less than 5.5V */

    const TEMPSENSE_Type* const TempSenseBasePtr = Adc_Sar_Ip_apxTempsenseBase[u32TempInstance];
    uint32 Tca0 = TempSenseBasePtr->TCA0;
    uint32 Tca1 = TempSenseBasePtr->TCA1;
    uint32 Tca2 = TempSenseBasePtr->TCA2;

    if (AdcVoltageRefs[u32AdcInstance] > ADC_SAR_IP_TEMPSENSE_VOLTAGE_SUPPLY) {
        Vref = Adc_Sar_TempsenseConvFp2Int(ADC_SAR_IP_TEMPSENSE_VOLTAGE_SUPPLY);
    }
    else {
        Vref = Adc_Sar_TempsenseConvFp2Int(AdcVoltageRefs[u32AdcInstance]);
    }

    if ((Tca0 & ADC_SAR_IP_TEMPSENSE_SIGN_MASK) != 0U) {
        Tets = -(sint32)(Adc_Sar_TempsenseConvFp2Int(Tca0));
    }
    else {
        Tets = (sint32)(Adc_Sar_TempsenseConvFp2Int(Tca0));
    }

    Vets      = (uint32)((Vref * Result) / ADC_SAR_IP_TEMPSENSE_RESOLUTION_12B);
    TempValue = (Adc_Sar_TempsenseConvFp2Int(Tca1) * Vets) / ADC_SAR_IP_TEMPSENSE_MULTIPLIER;

    if ((Tca1 & ADC_SAR_IP_TEMPSENSE_SIGN_MASK) != 0U) {
        Tets -= (sint32)(TempValue);
    }
    else {
        Tets += (sint32)(TempValue);
    }

    Vets      = (Vets * Vets) / ADC_SAR_IP_TEMPSENSE_MULTIPLIER;
    TempValue = (Adc_Sar_TempsenseConvFp2Int(Tca2) * Vets) / ADC_SAR_IP_TEMPSENSE_MULTIPLIER;

    if ((Tca2 & ADC_SAR_IP_TEMPSENSE_SIGN_MASK) != 0U) {
        Tets -= (sint32)(TempValue);
    }
    else {
        Tets += (sint32)(TempValue);
    }

    return Adc_Sar_TempsenseConvInt2Fp(Tets);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_TempSenseGetTemp
 * Description   : This function starts a normal software conversion on tempsense
 * channel and calculates the temperature on chip from the data conversion
 * parameter. Tempsense calculations are done using 12bits operators, so it is
 * recommended for Adc to run on minimum resolution of 12-bit.
 *
 * @implements      Adc_Sar_Ip_TempSenseGetTemp_Activity
 * END**************************************************************************/
Adc_Sar_Ip_StatusType Adc_Sar_Ip_TempSenseGetTemp(uint32 const u32AdcInstance, uint32 const u32TempInstance,
                                                  uint16* const pTempSenseVal) {
    Adc_Sar_Ip_StatusType ReturnStatus = ADC_SAR_IP_STATUS_SUCCESS;
    uint32 TimeoutTicks = OsIf_MicrosToTicks(ADC_SAR_IP_TIMEOUT_VAL, ADC_SAR_IP_TIMEOUT_TYPE);
    uint32 CurrentTicks = OsIf_GetCounter(ADC_SAR_IP_TIMEOUT_TYPE);
    uint32 ElapsedTicks = 0U;
    uint32 ExpectedStatus;
    uint32 ConvFlagStatus;
    uint32 Cdr;
    uint16 Result;
    uint8 Resolution;
    uint32 VectAdr;
    uint32 VectBit;
    ADC_Type* const AdcBasePtr = Adc_Sar_Ip_apxAdcBase[u32AdcInstance];
    uint32 Cimr[ADC_SAR_IP_NUM_GROUP_CHAN];
    uint32 Cwenr[ADC_SAR_IP_NUM_GROUP_CHAN];
    const uint32 Imr   = AdcBasePtr->IMR;
    uint32 const Wtimr = AdcBasePtr->WTIMR;

    DevAssert(u32AdcInstance < ADC_SAR_IP_INSTANCE_COUNT);
    DevAssert(u32TempInstance < TEMPSENSE_INSTANCE_COUNT);
    DevAssert(AdcVoltageRefs[u32AdcInstance] <= 0x58U); /* Vref should be less than 5.5V */

    /* Store the state of control interrupt registers and disable them,
     * Since this function cannt work when any ISR enabled */
    AdcBasePtr->IMR   = 0UL;
    AdcBasePtr->WTIMR = 0UL;
    for (VectAdr = 0U; VectAdr < Adc_Sar_Ip_au8AdcGroupCount[u32AdcInstance]; VectAdr++) {
        Cimr[VectAdr]             = CIMR(AdcBasePtr, VectAdr);
        CIMR(AdcBasePtr, VectAdr) = 0UL;

        Cwenr[VectAdr]             = CWENR(AdcBasePtr, VectAdr);
        CWENR(AdcBasePtr, VectAdr) = 0UL;
    }

    VectAdr = ADC_SAR_IP_CHAN_2_VECT(ADC_SAR_IP_TEMPSENSE_CHANNEL);
    VectBit = ADC_SAR_IP_CHAN_2_BIT(ADC_SAR_IP_TEMPSENSE_CHANNEL);
    /* Enable tempsense channel */
    NCMR(AdcBasePtr, VectAdr) |= (1UL << VectBit);

    /* One-shot mode */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_22();
    AdcBasePtr->MCR &= ~(ADC_MCR_MODE(1U));
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_22();

    /* Start normal software conversion */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_22();
    AdcBasePtr->MCR |= ADC_MCR_NSTART(1U);
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_22();

    /* Wait for the conversion to be finished */
    ExpectedStatus = (1UL << VectBit);
    ConvFlagStatus = CEOCFR(AdcBasePtr, VectAdr) & (1UL << VectBit);
    while ((ConvFlagStatus != ExpectedStatus) && (ElapsedTicks < TimeoutTicks)) {
        ConvFlagStatus = CEOCFR(AdcBasePtr, VectAdr) & (1UL << VectBit);
        ElapsedTicks += OsIf_GetElapsed(&CurrentTicks, ADC_SAR_IP_TIMEOUT_TYPE);
    }
    if (ElapsedTicks >= TimeoutTicks) {
        ReturnStatus = ADC_SAR_IP_STATUS_TIMEOUT;
    }

    if (ReturnStatus == ADC_SAR_IP_STATUS_SUCCESS) {
        Cdr = CDR(AdcBasePtr, (uint32)ADC_SAR_IP_TEMPSENSE_CHANNEL);
        if (((Cdr & ADC_CDR_VALID_MASK) != 0U)) {
            if (FALSE == Adc_Sar_Ip_axAdcSarState[u32AdcInstance].BypassResolution) {
                Resolution = Adc_Sar_GetResolution(u32AdcInstance);
            }
            else {
                Resolution = ADC_SAR_IP_RESULT_RESOLUTION;
            }

            Result = Adc_Sar_GetMaskedResult(u32AdcInstance, Cdr);
            /* the data is correct, store the result in 12bit resolution and clear the flag */
            if (Adc_Sar_Ip_axAdcSarState[u32AdcInstance].DataAlign == ADC_SAR_IP_DATA_ALIGNED_LEFT) {
                /* Assumption: the width of the register is less than 16 */
                Result = Result >> (16u - Resolution);
            }

            CEOCFR(AdcBasePtr, VectAdr) = ((uint32)1UL << VectBit); /* w1c bit */
            *pTempSenseVal = Adc_Sar_Ip_TempSenseCalculateTemp(u32AdcInstance, u32TempInstance, Result);
        }
    }

    /* Disable tempsense channel */
    NCMR(AdcBasePtr, VectAdr) &= ~(1UL << VectBit);

    /* Re-store control interrupt registers */
    AdcBasePtr->IMR   = Imr;
    AdcBasePtr->WTIMR = Wtimr;
    for (VectAdr = 0U; VectAdr < Adc_Sar_Ip_au8AdcGroupCount[u32AdcInstance]; VectAdr++) {
        CIMR(AdcBasePtr, VectAdr) = Cimr[VectAdr];

        CWENR(AdcBasePtr, VectAdr) = Cwenr[VectAdr];
    }

    return ReturnStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_TempSenseEnable
 * Description   : This function enables the temperature sensor.
 *
 * @implements      Adc_Sar_Ip_TempSenseEnable_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_TempSenseEnable(uint32 const u32Instance) {
    DevAssert(u32Instance < TEMPSENSE_INSTANCE_COUNT);
    TEMPSENSE_Type* const TempSenseBasePtr = Adc_Sar_Ip_apxTempsenseBase[u32Instance];

    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_49();
    TempSenseBasePtr->ETSCTL |= TEMPSENSE_ETSCTL_ETS_EN_MASK;
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_49();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Adc_Sar_Ip_TempSenseDisable
 * Description   : This function disables the temperature sensor.
 *
 * @implements      Adc_Sar_Ip_TempSenseDisable_Activity
 * END**************************************************************************/
void Adc_Sar_Ip_TempSenseDisable(uint32 const u32Instance) {
    DevAssert(u32Instance < TEMPSENSE_INSTANCE_COUNT);
    TEMPSENSE_Type* const TempSenseBasePtr = Adc_Sar_Ip_apxTempsenseBase[u32Instance];

    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_50();
    TempSenseBasePtr->ETSCTL &= (~TEMPSENSE_ETSCTL_ETS_EN_MASK);
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_50();
}

/*FUNCTION*********************************************************************
 *
 * Function Name : Adc_Sar_Ip_GetDataAddress
 * Description   : Returns the address of the specified CDR register
 * @implements      Adc_Sar_Ip_GetDataAddress_Activity
 *END*************************************************************************/
uint32 Adc_Sar_Ip_GetDataAddress(uint32 u32Instance, uint32 u32ChannelIndex) {
    uint32 returnAddr;

    DevAssert(u32Instance < ADC_SAR_IP_INSTANCE_COUNT);
    DevAssert(u32ChannelIndex < ADC_SAR_IP_CDR_COUNT);
    DevAssert(ADC_SAR_IP_INST_HAS_CHANn(u32Instance, u32ChannelIndex));

    returnAddr = (uint32)&CDR(Adc_Sar_Ip_apxAdcBase[u32Instance], u32ChannelIndex);

    return returnAddr;
}

#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
