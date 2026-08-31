# Copyright 2023 NXP
# SPDX-License-Identifier: BSD-3-Clause

zephyr_include_directories(include)
zephyr_library_sources_ifdef(CONFIG_ADC_NXP_S32_ADC_SAR src/SchM_Adc.c)
zephyr_library_sources_ifdef(CONFIG_MEMC_NXP_S32_QSPI src/SchM_Fls.c)
zephyr_library_sources(src/SchM_Icu.c)
zephyr_library_sources_ifdef(CONFIG_NXP_S32_EMIOS src/SchM_Mcl.c)
zephyr_library_sources_ifdef(CONFIG_CLOCK_CONTROL_NXP_S32 src/SchM_Mcu.c)
zephyr_library_sources_ifdef(CONFIG_PWM_NXP_S32_EMIOS src/SchM_Pwm.c)

# Must match the Crypto subdirectory's own gate in ../CMakeLists.txt - Hse_Ip.c calls
# SchM_Enter/Exit_Crypto_*, so it is also needed by ENTROPY_NXP_S32_HSE_TRNG-only builds
# and by NXP_S32_HSE_IP (direct Hse_Ip use during HSE bring-up). #CUSTOM@NDRS
if(CONFIG_CRYPTO_NXP_S32_HSE OR CONFIG_ENTROPY_NXP_S32_HSE_TRNG OR CONFIG_NXP_S32_HSE_IP)
  zephyr_library_sources(src/SchM_Crypto.c)
endif()
