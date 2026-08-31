# Copyright 2024 NXP
# SPDX-License-Identifier: BSD-3-Clause

# CONFIG_NXP_S32_HSE_IP lets the HSE ABI headers be pulled in without the Zephyr
# crypto/entropy drivers, for direct Hse_Ip use during HSE bring-up. #CUSTOM@NDRS
if(CONFIG_CRYPTO_NXP_S32_HSE OR CONFIG_ENTROPY_NXP_S32_HSE_TRNG OR CONFIG_NXP_S32_HSE_IP)
    zephyr_include_directories(
        interface
        interface/inc_common
        interface/config
        interface/inc_custom
        interface/inc_services
    )
endif()

