# Copyright 2024 NXP
# SPDX-License-Identifier: BSD-3-Clause

if(CONFIG_CRYPTO_NXP_S32_HSE OR CONFIG_ENTROPY_NXP_S32_HSE_TRNG)
    zephyr_include_directories(
        interface
        interface/inc_common
        interface/config
        interface/inc_custom
        interface/inc_services
    )
endif()

