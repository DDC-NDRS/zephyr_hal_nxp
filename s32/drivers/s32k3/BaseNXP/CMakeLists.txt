# Copyright 2023 NXP
# SPDX-License-Identifier: BSD-3-Clause

zephyr_include_directories_ifdef(CONFIG_SOC_S32K344 header/s32k344)
zephyr_include_directories_ifdef(CONFIG_SOC_S32K358 header/s32k358)
zephyr_include_directories(include)
zephyr_library_sources(src/OsIf_Interrupts.c)
zephyr_library_sources(src/OsIf_Timer.c)
zephyr_library_sources(src/OsIf_Timer_System.c)
zephyr_library_sources(src/OsIf_Timer_System_Internal_Systick.c)
