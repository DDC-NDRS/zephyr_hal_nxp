# Copyright 2023 NXP
# SPDX-License-Identifier: BSD-3-Clause

add_subdirectory(BaseNXP)
add_subdirectory(Mcu)
add_subdirectory(Rte)
add_subdirectory(Icu)

# CONFIG_NXP_S32_HSE_IP builds the MU transport + HSE ABI without the Zephyr
# crypto/entropy drivers, for direct Hse_Ip use during HSE bring-up. #CUSTOM@NDRS
if(CONFIG_CRYPTO_NXP_S32_HSE OR CONFIG_ENTROPY_NXP_S32_HSE_TRNG OR CONFIG_NXP_S32_HSE_IP)
  add_subdirectory(Crypto)
  add_subdirectory(HSE)
endif()

add_subdirectory_ifdef(CONFIG_ADC_NXP_S32_ADC_SAR Adc)
add_subdirectory_ifdef(CONFIG_MEMC_NXP_S32_QSPI Fls)

if(CONFIG_ETH_NXP_S32_GMAC OR CONFIG_MDIO_NXP_S32_GMAC)
  add_subdirectory(Eth_GMAC)
endif()

add_subdirectory_ifdef(CONFIG_NXP_S32_EMIOS Mcl)
add_subdirectory_ifdef(CONFIG_PWM_NXP_S32_EMIOS Pwm)
