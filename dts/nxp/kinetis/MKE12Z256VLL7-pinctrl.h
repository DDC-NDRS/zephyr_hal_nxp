/*
 * NOTE: Autogenerated file by gen_soc_headers.py
 * for MKE12Z256VLL7/signal_configuration.xml
 *
 * Copyright 2024, NXP
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _ZEPHYR_DTS_BINDING_MKE12Z256VLL7_
#define _ZEPHYR_DTS_BINDING_MKE12Z256VLL7_

#define KINETIS_MUX(port, pin, mux)		\
	(((((port) - 'A') & 0xF) << 28) |	\
	(((pin) & 0x3F) << 22) |		\
	(((mux) & 0x7) << 8))

#define ACMP0_IN0_PTA0 KINETIS_MUX('A',0,0) /* PTA_0 */
#define PTA0 KINETIS_MUX('A',0,1) /* PTA_0 */
#define FTM2_CH1_PTA0 KINETIS_MUX('A',0,2) /* PTA_0 */
#define LPI2C0_SCLS_PTA0 KINETIS_MUX('A',0,3) /* PTA_0 */
#define FXIO_D2_PTA0 KINETIS_MUX('A',0,4) /* PTA_0 */
#define LPUART0_CTS_PTA0 KINETIS_MUX('A',0,6) /* PTA_0 */
#define TRGMUX_OUT3_PTA0_PTA0_PTA0_PTA0_PTA0_PTA0_PTA0_PTA0 KINETIS_MUX('A',0,7) /* PTA_0 */
#define TRGMUX_OUT3_PTA0 KINETIS_MUX('A',0,7) /* PTA_0 */
#define ACMP0_IN1_PTA1 KINETIS_MUX('A',1,0) /* PTA_1 */
#define PTA1 KINETIS_MUX('A',1,1) /* PTA_1 */
#define FTM1_CH1_PTA1 KINETIS_MUX('A',1,2) /* PTA_1 */
#define LPI2C0_SDAS_PTA1 KINETIS_MUX('A',1,3) /* PTA_1 */
#define FXIO_D3_PTA1 KINETIS_MUX('A',1,4) /* PTA_1 */
#define LPUART0_RTS_PTA1 KINETIS_MUX('A',1,6) /* PTA_1 */
#define TRGMUX_OUT0_PTA1_PTA1_PTA1_PTA1_PTA1_PTA1_PTA1_PTA1 KINETIS_MUX('A',1,7) /* PTA_1 */
#define TRGMUX_OUT0_PTA1 KINETIS_MUX('A',1,7) /* PTA_1 */
#define PTA2 KINETIS_MUX('A',2,1) /* PTA_2 */
#define LPI2C0_SDA_PTA2 KINETIS_MUX('A',2,3) /* PTA_2 */
#define EWM_OUT_b_PTA2 KINETIS_MUX('A',2,4) /* PTA_2 */
#define LPUART0_RX_PTA2 KINETIS_MUX('A',2,6) /* PTA_2 */
#define PTA3 KINETIS_MUX('A',3,1) /* PTA_3 */
#define LPI2C0_SCL_PTA3 KINETIS_MUX('A',3,3) /* PTA_3 */
#define EWM_IN_PTA3 KINETIS_MUX('A',3,4) /* PTA_3 */
#define LPUART0_TX_PTA3 KINETIS_MUX('A',3,6) /* PTA_3 */
#define PTA4 KINETIS_MUX('A',4,1) /* PTA_4 */
#define LPUART1_TX_PTA4 KINETIS_MUX('A',4,3) /* PTA_4 */
#define ACMP0_OUT_PTA4 KINETIS_MUX('A',4,4) /* PTA_4 */
#define EWM_OUT_b_PTA4 KINETIS_MUX('A',4,5) /* PTA_4 */
#define SWD_DIO_PTA4 KINETIS_MUX('A',4,7) /* PTA_4 */
#define PTA5 KINETIS_MUX('A',5,1) /* PTA_5 */
#define TCLK1_PTA5 KINETIS_MUX('A',5,3) /* PTA_5 */
#define RESET_b_PTA5 KINETIS_MUX('A',5,7) /* PTA_5 */
#define PTA6 KINETIS_MUX('A',6,1) /* PTA_6 */
#define FTM0_FLT1_PTA6 KINETIS_MUX('A',6,2) /* PTA_6 */
#define LPUART1_CTS_PTA6 KINETIS_MUX('A',6,6) /* PTA_6 */
#define PTA7 KINETIS_MUX('A',7,1) /* PTA_7 */
#define FTM0_FLT2_PTA7 KINETIS_MUX('A',7,2) /* PTA_7 */
#define LPSPI0_PCS3_PTA7 KINETIS_MUX('A',7,3) /* PTA_7 */
#define LPUART1_RTS_PTA7 KINETIS_MUX('A',7,6) /* PTA_7 */
#define PTA8 KINETIS_MUX('A',8,1) /* PTA_8 */
#define FXIO_D6_PTA8 KINETIS_MUX('A',8,4) /* PTA_8 */
#define TRGMUX_OUT0_PTA8 KINETIS_MUX('A',8,7) /* PTA_8 */
#define TRGMUX_OUT0_PTA8_PTA8_PTA8_PTA8_PTA8_PTA8_PTA8_PTA8 KINETIS_MUX('A',8,7) /* PTA_8 */
#define PTA9 KINETIS_MUX('A',9,1) /* PTA_9 */
#define FXIO_D7_PTA9 KINETIS_MUX('A',9,4) /* PTA_9 */
#define TRGMUX_OUT1_PTA9 KINETIS_MUX('A',9,7) /* PTA_9 */
#define TRGMUX_OUT1_PTA9_PTA9_PTA9_PTA9_PTA9_PTA9_PTA9_PTA9 KINETIS_MUX('A',9,7) /* PTA_9 */
#define PTA10 KINETIS_MUX('A',10,1) /* PTA_10 */
#define LPUART0_TX_PTA10 KINETIS_MUX('A',10,3) /* PTA_10 */
#define FXIO_D0_PTA10 KINETIS_MUX('A',10,4) /* PTA_10 */
#define PTA11 KINETIS_MUX('A',11,1) /* PTA_11 */
#define LPUART0_RX_PTA11 KINETIS_MUX('A',11,3) /* PTA_11 */
#define FXIO_D1_PTA11 KINETIS_MUX('A',11,4) /* PTA_11 */
#define PTA12 KINETIS_MUX('A',12,1) /* PTA_12 */
#define LPUART0_TX_PTA12 KINETIS_MUX('A',12,5) /* PTA_12 */
#define PTA13 KINETIS_MUX('A',13,1) /* PTA_13 */
#define LPUART0_RX_PTA13 KINETIS_MUX('A',13,5) /* PTA_13 */
#define PTA14 KINETIS_MUX('A',14,1) /* PTA_14 */
#define FTM0_FLT0_PTA14 KINETIS_MUX('A',14,2) /* PTA_14 */
#define EWM_IN_PTA14 KINETIS_MUX('A',14,4) /* PTA_14 */
#define BUSOUT_PTA14 KINETIS_MUX('A',14,7) /* PTA_14 */
#define PTA15 KINETIS_MUX('A',15,1) /* PTA_15 */
#define FTM1_CH2_PTA15 KINETIS_MUX('A',15,2) /* PTA_15 */
#define LPSPI0_PCS3_PTA15 KINETIS_MUX('A',15,3) /* PTA_15 */
#define PTA16 KINETIS_MUX('A',16,1) /* PTA_16 */
#define FTM1_CH3_PTA16 KINETIS_MUX('A',16,2) /* PTA_16 */
#define LPI2C0_SDA_PTA16 KINETIS_MUX('A',16,4) /* PTA_16 */
#define PTA17 KINETIS_MUX('A',17,1) /* PTA_17 */
#define FTM0_CH6_PTA17 KINETIS_MUX('A',17,2) /* PTA_17 */
#define EWM_OUT_b_PTA17 KINETIS_MUX('A',17,4) /* PTA_17 */
#define PTB0 KINETIS_MUX('B',0,1) /* PTB_0 */
#define LPUART0_RX_PTB0 KINETIS_MUX('B',0,2) /* PTB_0 */
#define LPSPI0_PCS0_PTB0 KINETIS_MUX('B',0,3) /* PTB_0 */
#define LPTMR0_ALT3_PTB0 KINETIS_MUX('B',0,4) /* PTB_0 */
#define PWT_IN3_PTB0 KINETIS_MUX('B',0,5) /* PTB_0 */
#define PTB1 KINETIS_MUX('B',1,1) /* PTB_1 */
#define LPUART0_TX_PTB1 KINETIS_MUX('B',1,2) /* PTB_1 */
#define LPSPI0_SOUT_PTB1 KINETIS_MUX('B',1,3) /* PTB_1 */
#define TCLK0_PTB1 KINETIS_MUX('B',1,4) /* PTB_1 */
#define PTB2 KINETIS_MUX('B',2,1) /* PTB_2 */
#define FTM1_CH0_PTB2 KINETIS_MUX('B',2,2) /* PTB_2 */
#define LPSPI0_SCK_PTB2 KINETIS_MUX('B',2,3) /* PTB_2 */
#define TRGMUX_IN3_PTB2 KINETIS_MUX('B',2,6) /* PTB_2 */
#define PTB3 KINETIS_MUX('B',3,1) /* PTB_3 */
#define FTM1_CH1_PTB3 KINETIS_MUX('B',3,2) /* PTB_3 */
#define LPSPI0_SIN_PTB3 KINETIS_MUX('B',3,3) /* PTB_3 */
#define TRGMUX_IN2_PTB3 KINETIS_MUX('B',3,6) /* PTB_3 */
#define ADC0_SE5_PTB4 KINETIS_MUX('B',4,0) /* PTB_4 */
#define PTB4 KINETIS_MUX('B',4,1) /* PTB_4 */
#define FTM0_CH4_PTB4 KINETIS_MUX('B',4,2) /* PTB_4 */
#define LPSPI0_SOUT_PTB4 KINETIS_MUX('B',4,3) /* PTB_4 */
#define TRGMUX_IN1_PTB4 KINETIS_MUX('B',4,6) /* PTB_4 */
#define ADC0_SE3_PTB5 KINETIS_MUX('B',5,0) /* PTB_5 */
#define PTB5 KINETIS_MUX('B',5,1) /* PTB_5 */
#define FTM0_CH5_PTB5 KINETIS_MUX('B',5,2) /* PTB_5 */
#define LPSPI0_PCS1_PTB5 KINETIS_MUX('B',5,3) /* PTB_5 */
#define TRGMUX_IN0_PTB5 KINETIS_MUX('B',5,6) /* PTB_5 */
#define XTAL_PTB6 KINETIS_MUX('B',6,0) /* PTB_6 */
#define PTB6 KINETIS_MUX('B',6,1) /* PTB_6 */
#define LPI2C0_SDA_PTB6 KINETIS_MUX('B',6,2) /* PTB_6 */
#define LPUART0_RX_PTB6 KINETIS_MUX('B',6,3) /* PTB_6 */
#define EXTAL_PTB7 KINETIS_MUX('B',7,0) /* PTB_7 */
#define PTB7 KINETIS_MUX('B',7,1) /* PTB_7 */
#define LPI2C0_SCL_PTB7 KINETIS_MUX('B',7,2) /* PTB_7 */
#define LPUART0_TX_PTB7 KINETIS_MUX('B',7,3) /* PTB_7 */
#define PTB8 KINETIS_MUX('B',8,1) /* PTB_8 */
#define LPI2C0_SCL_PTB8 KINETIS_MUX('B',8,4) /* PTB_8 */
#define FXIO_D4_PTB8 KINETIS_MUX('B',8,6) /* PTB_8 */
#define PTB9 KINETIS_MUX('B',9,1) /* PTB_9 */
#define LPI2C0_SCLS_PTB9 KINETIS_MUX('B',9,3) /* PTB_9 */
#define FXIO_D5_PTB9 KINETIS_MUX('B',9,6) /* PTB_9 */
#define PTB10 KINETIS_MUX('B',10,1) /* PTB_10 */
#define FTM0_CH0_PTB10 KINETIS_MUX('B',10,2) /* PTB_10 */
#define LPI2C0_SDAS_PTB10 KINETIS_MUX('B',10,3) /* PTB_10 */
#define FXIO_D0_PTB10 KINETIS_MUX('B',10,6) /* PTB_10 */
#define PTB11 KINETIS_MUX('B',11,1) /* PTB_11 */
#define FTM0_CH1_PTB11 KINETIS_MUX('B',11,2) /* PTB_11 */
#define LPI2C0_HREQ_PTB11 KINETIS_MUX('B',11,3) /* PTB_11 */
#define FXIO_D1_PTB11 KINETIS_MUX('B',11,6) /* PTB_11 */
#define PTB12 KINETIS_MUX('B',12,1) /* PTB_12 */
#define FTM0_CH0_PTB12 KINETIS_MUX('B',12,2) /* PTB_12 */
#define PTB13 KINETIS_MUX('B',13,1) /* PTB_13 */
#define FTM0_CH1_PTB13 KINETIS_MUX('B',13,2) /* PTB_13 */
#define PTB14 KINETIS_MUX('B',14,1) /* PTB_14 */
#define FTM0_CH2_PTB14 KINETIS_MUX('B',14,2) /* PTB_14 */
#define PTB15 KINETIS_MUX('B',15,1) /* PTB_15 */
#define FTM0_CH3_PTB15 KINETIS_MUX('B',15,2) /* PTB_15 */
#define PTB16 KINETIS_MUX('B',16,1) /* PTB_16 */
#define FTM0_CH4_PTB16 KINETIS_MUX('B',16,2) /* PTB_16 */
#define PTB17 KINETIS_MUX('B',17,1) /* PTB_17 */
#define FTM0_CH5_PTB17 KINETIS_MUX('B',17,2) /* PTB_17 */
#define ADC0_SE10_PTC0 KINETIS_MUX('C',0,0) /* PTC_0 */
#define PTC0 KINETIS_MUX('C',0,1) /* PTC_0 */
#define FTM0_CH0_PTC0 KINETIS_MUX('C',0,2) /* PTC_0 */
#define ADC0_SE8_PTC1 KINETIS_MUX('C',1,0) /* PTC_1 */
#define PTC1 KINETIS_MUX('C',1,1) /* PTC_1 */
#define FTM0_CH1_PTC1 KINETIS_MUX('C',1,2) /* PTC_1 */
#define ADC0_SE15_PTC2 KINETIS_MUX('C',2,0) /* PTC_2 */
#define ACMP0_IN5_PTC2 KINETIS_MUX('C',2,0) /* PTC_2 */
#define PTC2 KINETIS_MUX('C',2,1) /* PTC_2 */
#define FTM0_CH2_PTC2 KINETIS_MUX('C',2,2) /* PTC_2 */
#define FXIO_D6_PTC2 KINETIS_MUX('C',2,6) /* PTC_2 */
#define ADC0_SE7_PTC3 KINETIS_MUX('C',3,0) /* PTC_3 */
#define ACMP0_IN4_PTC3 KINETIS_MUX('C',3,0) /* PTC_3 */
#define PTC3 KINETIS_MUX('C',3,1) /* PTC_3 */
#define FTM0_CH3_PTC3 KINETIS_MUX('C',3,2) /* PTC_3 */
#define FXIO_D7_PTC3 KINETIS_MUX('C',3,6) /* PTC_3 */
#define ACMP0_IN2_PTC4 KINETIS_MUX('C',4,0) /* PTC_4 */
#define PTC4 KINETIS_MUX('C',4,1) /* PTC_4 */
#define FTM1_CH0_PTC4 KINETIS_MUX('C',4,2) /* PTC_4 */
#define LPUART1_RX_PTC4 KINETIS_MUX('C',4,3) /* PTC_4 */
#define EWM_IN_PTC4 KINETIS_MUX('C',4,5) /* PTC_4 */
#define SWD_CLK_PTC4 KINETIS_MUX('C',4,7) /* PTC_4 */
#define PTC5 KINETIS_MUX('C',5,1) /* PTC_5 */
#define FTM2_CH0_PTC5 KINETIS_MUX('C',5,2) /* PTC_5 */
#define PTC6 KINETIS_MUX('C',6,1) /* PTC_6 */
#define LPUART1_RX_PTC6 KINETIS_MUX('C',6,2) /* PTC_6 */
#define PTC7 KINETIS_MUX('C',7,1) /* PTC_7 */
#define LPUART1_TX_PTC7 KINETIS_MUX('C',7,2) /* PTC_7 */
#define PTC8 KINETIS_MUX('C',8,1) /* PTC_8 */
#define LPUART1_RX_PTC8 KINETIS_MUX('C',8,2) /* PTC_8 */
#define LPUART0_CTS_PTC8 KINETIS_MUX('C',8,6) /* PTC_8 */
#define PTC9 KINETIS_MUX('C',9,1) /* PTC_9 */
#define LPUART1_TX_PTC9 KINETIS_MUX('C',9,2) /* PTC_9 */
#define LPUART0_RTS_PTC9 KINETIS_MUX('C',9,6) /* PTC_9 */
#define PTC10 KINETIS_MUX('C',10,1) /* PTC_10 */
#define LPSPI0_SCK_PTC10 KINETIS_MUX('C',10,5) /* PTC_10 */
#define PTC11 KINETIS_MUX('C',11,1) /* PTC_11 */
#define LPSPI0_SIN_PTC11 KINETIS_MUX('C',11,5) /* PTC_11 */
#define PTC12 KINETIS_MUX('C',12,1) /* PTC_12 */
#define LPSPI0_SOUT_PTC12 KINETIS_MUX('C',12,5) /* PTC_12 */
#define PTC13 KINETIS_MUX('C',13,1) /* PTC_13 */
#define LPSPI0_PCS0_PTC13 KINETIS_MUX('C',13,5) /* PTC_13 */
#define PTC14 KINETIS_MUX('C',14,1) /* PTC_14 */
#define FTM1_CH2_PTC14 KINETIS_MUX('C',14,2) /* PTC_14 */
#define PTC15 KINETIS_MUX('C',15,1) /* PTC_15 */
#define FTM1_CH3_PTC15 KINETIS_MUX('C',15,2) /* PTC_15 */
#define ADC0_SE14_PTC16 KINETIS_MUX('C',16,0) /* PTC_16 */
#define PTC16 KINETIS_MUX('C',16,1) /* PTC_16 */
#define ADC0_SE12_PTC17 KINETIS_MUX('C',17,0) /* PTC_17 */
#define PTC17 KINETIS_MUX('C',17,1) /* PTC_17 */
#define PTD0 KINETIS_MUX('D',0,1) /* PTD_0 */
#define FTM0_CH2_PTD0 KINETIS_MUX('D',0,2) /* PTD_0 */
#define FTM2_CH0_PTD0 KINETIS_MUX('D',0,4) /* PTD_0 */
#define FXIO_D0_PTD0 KINETIS_MUX('D',0,6) /* PTD_0 */
#define TRGMUX_OUT1_PTD0 KINETIS_MUX('D',0,7) /* PTD_0 */
#define TRGMUX_OUT1_PTD0_PTD0_PTD0_PTD0_PTD0_PTD0_PTD0_PTD0 KINETIS_MUX('D',0,7) /* PTD_0 */
#define PTD1 KINETIS_MUX('D',1,1) /* PTD_1 */
#define FTM0_CH3_PTD1 KINETIS_MUX('D',1,2) /* PTD_1 */
#define FTM2_CH1_PTD1 KINETIS_MUX('D',1,4) /* PTD_1 */
#define FXIO_D1_PTD1 KINETIS_MUX('D',1,6) /* PTD_1 */
#define TRGMUX_OUT2_PTD1 KINETIS_MUX('D',1,7) /* PTD_1 */
#define TRGMUX_OUT2_PTD1_PTD1_PTD1_PTD1_PTD1_PTD1_PTD1_PTD1 KINETIS_MUX('D',1,7) /* PTD_1 */
#define PTD2 KINETIS_MUX('D',2,1) /* PTD_2 */
#define FXIO_D4_PTD2 KINETIS_MUX('D',2,4) /* PTD_2 */
#define LPI2C0_SDA_PTD2 KINETIS_MUX('D',2,5) /* PTD_2 */
#define TRGMUX_IN5_PTD2_PTD2_PTD2_PTD2_PTD2_PTD2_PTD2_PTD2 KINETIS_MUX('D',2,6) /* PTD_2 */
#define TRGMUX_IN5_PTD2 KINETIS_MUX('D',2,6) /* PTD_2 */
#define PTD3 KINETIS_MUX('D',3,1) /* PTD_3 */
#define FXIO_D5_PTD3 KINETIS_MUX('D',3,4) /* PTD_3 */
#define LPI2C0_SCL_PTD3 KINETIS_MUX('D',3,5) /* PTD_3 */
#define TRGMUX_IN4_PTD3_PTD3_PTD3_PTD3_PTD3_PTD3_PTD3_PTD3 KINETIS_MUX('D',3,6) /* PTD_3 */
#define TRGMUX_IN4_PTD3 KINETIS_MUX('D',3,6) /* PTD_3 */
#define NMI_b_PTD3 KINETIS_MUX('D',3,7) /* PTD_3 */
#define PTD4 KINETIS_MUX('D',4,1) /* PTD_4 */
#define FTM0_FLT3_PTD4 KINETIS_MUX('D',4,2) /* PTD_4 */
#define ADC0_SE9_PTD5 KINETIS_MUX('D',5,0) /* PTD_5 */
#define PTD5 KINETIS_MUX('D',5,1) /* PTD_5 */
#define FTM2_CH3_PTD5 KINETIS_MUX('D',5,2) /* PTD_5 */
#define LPTMR0_ALT2_PTD5 KINETIS_MUX('D',5,3) /* PTD_5 */
#define FXIO_D3_PTD5 KINETIS_MUX('D',5,4) /* PTD_5 */
#define PWT_IN2_PTD5 KINETIS_MUX('D',5,5) /* PTD_5 */
#define TRGMUX_IN7_PTD5_PTD5_PTD5_PTD5_PTD5_PTD5_PTD5_PTD5 KINETIS_MUX('D',5,6) /* PTD_5 */
#define TRGMUX_IN7_PTD5 KINETIS_MUX('D',5,6) /* PTD_5 */
#define LPUART2_CTS_PTD5 KINETIS_MUX('D',5,7) /* PTD_5 */
#define ADC0_SE11_PTD6 KINETIS_MUX('D',6,0) /* PTD_6 */
#define PTD6 KINETIS_MUX('D',6,1) /* PTD_6 */
#define LPUART2_RX_PTD6 KINETIS_MUX('D',6,2) /* PTD_6 */
#define ADC0_SE13_PTD7 KINETIS_MUX('D',7,0) /* PTD_7 */
#define PTD7 KINETIS_MUX('D',7,1) /* PTD_7 */
#define LPUART2_TX_PTD7 KINETIS_MUX('D',7,2) /* PTD_7 */
#define PTD8 KINETIS_MUX('D',8,1) /* PTD_8 */
#define FTM0_CH7_PTD8 KINETIS_MUX('D',8,2) /* PTD_8 */
#define LPSPI0_PCS1_PTD8 KINETIS_MUX('D',8,5) /* PTD_8 */
#define PTD9 KINETIS_MUX('D',9,1) /* PTD_9 */
#define FXIO_D2_PTD9 KINETIS_MUX('D',9,6) /* PTD_9 */
#define PTD10 KINETIS_MUX('D',10,1) /* PTD_10 */
#define FTM2_CH0_PTD10 KINETIS_MUX('D',10,2) /* PTD_10 */
#define PTD11 KINETIS_MUX('D',11,1) /* PTD_11 */
#define FTM2_CH1_PTD11 KINETIS_MUX('D',11,2) /* PTD_11 */
#define LPUART2_CTS_PTD11 KINETIS_MUX('D',11,6) /* PTD_11 */
#define PTD12 KINETIS_MUX('D',12,1) /* PTD_12 */
#define FTM2_CH2_PTD12 KINETIS_MUX('D',12,2) /* PTD_12 */
#define LPUART2_RTS_PTD12 KINETIS_MUX('D',12,6) /* PTD_12 */
#define PTD13 KINETIS_MUX('D',13,1) /* PTD_13 */
#define LPUART1_RX_PTD13 KINETIS_MUX('D',13,3) /* PTD_13 */
#define PTD14 KINETIS_MUX('D',14,1) /* PTD_14 */
#define LPUART1_TX_PTD14 KINETIS_MUX('D',14,3) /* PTD_14 */
#define CLKOUT_PTD14 KINETIS_MUX('D',14,7) /* PTD_14 */
#define ADC0_SE2_PTD15 KINETIS_MUX('D',15,0) /* PTD_15 */
#define PTD15 KINETIS_MUX('D',15,1) /* PTD_15 */
#define FTM0_CH0_PTD15 KINETIS_MUX('D',15,2) /* PTD_15 */
#define ADC0_SE4_PTD16 KINETIS_MUX('D',16,0) /* PTD_16 */
#define PTD16 KINETIS_MUX('D',16,1) /* PTD_16 */
#define FTM0_CH1_PTD16 KINETIS_MUX('D',16,2) /* PTD_16 */
#define PTD17 KINETIS_MUX('D',17,1) /* PTD_17 */
#define FTM0_FLT2_PTD17 KINETIS_MUX('D',17,2) /* PTD_17 */
#define LPUART2_RX_PTD17 KINETIS_MUX('D',17,3) /* PTD_17 */
#define TRGMUX_OUT2_PTD17_PTD17_PTD17_PTD17_PTD17_PTD17_PTD17_PTD17 KINETIS_MUX('D',17,7) /* PTD_17 */
#define TRGMUX_OUT2_PTD17 KINETIS_MUX('D',17,7) /* PTD_17 */
#define PTE0 KINETIS_MUX('E',0,1) /* PTE_0 */
#define LPSPI0_SCK_PTE0 KINETIS_MUX('E',0,2) /* PTE_0 */
#define TCLK1_PTE0 KINETIS_MUX('E',0,3) /* PTE_0 */
#define PTE1 KINETIS_MUX('E',1,1) /* PTE_1 */
#define LPSPI0_SIN_PTE1 KINETIS_MUX('E',1,2) /* PTE_1 */
#define LPI2C0_HREQ_PTE1 KINETIS_MUX('E',1,3) /* PTE_1 */
#define PTE2 KINETIS_MUX('E',2,1) /* PTE_2 */
#define LPSPI0_SOUT_PTE2 KINETIS_MUX('E',2,2) /* PTE_2 */
#define LPTMR0_ALT3_PTE2 KINETIS_MUX('E',2,3) /* PTE_2 */
#define PWT_IN3_PTE2 KINETIS_MUX('E',2,5) /* PTE_2 */
#define LPUART1_CTS_PTE2 KINETIS_MUX('E',2,6) /* PTE_2 */
#define ADC0_SE6_PTE3 KINETIS_MUX('E',3,0) /* PTE_3 */
#define PTE3 KINETIS_MUX('E',3,1) /* PTE_3 */
#define FTM0_FLT0/TRGMUX_IN6_PTE3_PTE3_PTE3_PTE3_PTE3_PTE3_PTE3_PTE3_PTE3 KINETIS_MUX('E',3,2) /* PTE_3 */
#define FTM0_FLT0_PTE3 KINETIS_MUX('E',3,2) /* PTE_3 */
#define LPUART2_RTS_PTE3 KINETIS_MUX('E',3,3) /* PTE_3 */
#define TRGMUX_IN6_PTE3 KINETIS_MUX('E',3,6) /* PTE_3 */
#define TRGMUX_IN6_PTE3_PTE3_PTE3_PTE3_PTE3_PTE3_PTE3_PTE3 KINETIS_MUX('E',3,6) /* PTE_3 */
#define PTE4 KINETIS_MUX('E',4,1) /* PTE_4 */
#define BUSOUT_PTE4 KINETIS_MUX('E',4,2) /* PTE_4 */
#define FTM2_CH2_PTE4 KINETIS_MUX('E',4,4) /* PTE_4 */
#define FXIO_D6_PTE4 KINETIS_MUX('E',4,6) /* PTE_4 */
#define EWM_OUT_b_PTE4 KINETIS_MUX('E',4,7) /* PTE_4 */
#define PTE5 KINETIS_MUX('E',5,1) /* PTE_5 */
#define TCLK2_PTE5 KINETIS_MUX('E',5,2) /* PTE_5 */
#define FTM2_CH3_PTE5 KINETIS_MUX('E',5,4) /* PTE_5 */
#define FXIO_D7_PTE5 KINETIS_MUX('E',5,6) /* PTE_5 */
#define EWM_IN_PTE5 KINETIS_MUX('E',5,7) /* PTE_5 */
#define PTE6 KINETIS_MUX('E',6,1) /* PTE_6 */
#define LPSPI0_PCS2_PTE6 KINETIS_MUX('E',6,2) /* PTE_6 */
#define LPUART1_RTS_PTE6 KINETIS_MUX('E',6,6) /* PTE_6 */
#define PTE7 KINETIS_MUX('E',7,1) /* PTE_7 */
#define FTM0_CH7_PTE7 KINETIS_MUX('E',7,2) /* PTE_7 */
#define ADC0_SE1_PTE8 KINETIS_MUX('E',8,0) /* PTE_8 */
#define ACMP0_IN3_PTE8 KINETIS_MUX('E',8,0) /* PTE_8 */
#define PTE8 KINETIS_MUX('E',8,1) /* PTE_8 */
#define FTM0_CH6_PTE8 KINETIS_MUX('E',8,2) /* PTE_8 */
#define ADC0_SE0_PTE9 KINETIS_MUX('E',9,0) /* PTE_9 */
#define PTE9 KINETIS_MUX('E',9,1) /* PTE_9 */
#define FTM0_CH7_PTE9 KINETIS_MUX('E',9,2) /* PTE_9 */
#define LPUART2_CTS_PTE9 KINETIS_MUX('E',9,3) /* PTE_9 */
#define PTE10 KINETIS_MUX('E',10,1) /* PTE_10 */
#define CLKOUT_PTE10 KINETIS_MUX('E',10,2) /* PTE_10 */
#define FXIO_D4_PTE10 KINETIS_MUX('E',10,6) /* PTE_10 */
#define TRGMUX_OUT4_PTE10 KINETIS_MUX('E',10,7) /* PTE_10 */
#define TRGMUX_OUT4_PTE10_PTE10_PTE10_PTE10_PTE10_PTE10_PTE10_PTE10 KINETIS_MUX('E',10,7) /* PTE_10 */
#define PTE11 KINETIS_MUX('E',11,1) /* PTE_11 */
#define PWT_IN1_PTE11 KINETIS_MUX('E',11,2) /* PTE_11 */
#define LPTMR0_ALT1_PTE11 KINETIS_MUX('E',11,3) /* PTE_11 */
#define FXIO_D5_PTE11 KINETIS_MUX('E',11,6) /* PTE_11 */
#define TRGMUX_OUT5_PTE11 KINETIS_MUX('E',11,7) /* PTE_11 */
#define TRGMUX_OUT5_PTE11_PTE11_PTE11_PTE11_PTE11_PTE11_PTE11_PTE11 KINETIS_MUX('E',11,7) /* PTE_11 */
#define PTE12 KINETIS_MUX('E',12,1) /* PTE_12 */
#define FTM0_FLT3_PTE12 KINETIS_MUX('E',12,2) /* PTE_12 */
#define LPUART2_TX_PTE12 KINETIS_MUX('E',12,3) /* PTE_12 */
#define TRGMUX_OUT3_PTE12_PTE12_PTE12_PTE12_PTE12_PTE12_PTE12_PTE12 KINETIS_MUX('E',12,7) /* PTE_12 */
#define TRGMUX_OUT3_PTE12 KINETIS_MUX('E',12,7) /* PTE_12 */
#define PTE13 KINETIS_MUX('E',13,1) /* PTE_13 */
#define TRGMUX_OUT5_PTE13 KINETIS_MUX('E',13,7) /* PTE_13 */
#define TRGMUX_OUT5_PTE13_PTE13_PTE13_PTE13_PTE13_PTE13_PTE13_PTE13 KINETIS_MUX('E',13,7) /* PTE_13 */
#define PTE14 KINETIS_MUX('E',14,1) /* PTE_14 */
#define FTM0_FLT1_PTE14 KINETIS_MUX('E',14,2) /* PTE_14 */
#define TRGMUX_OUT4_PTE14 KINETIS_MUX('E',14,7) /* PTE_14 */
#define TRGMUX_OUT4_PTE14_PTE14_PTE14_PTE14_PTE14_PTE14_PTE14_PTE14 KINETIS_MUX('E',14,7) /* PTE_14 */
#define PTE15 KINETIS_MUX('E',15,1) /* PTE_15 */
#define FXIO_D2_PTE15 KINETIS_MUX('E',15,6) /* PTE_15 */
#define TRGMUX_OUT6_PTE15 KINETIS_MUX('E',15,7) /* PTE_15 */
#define TRGMUX_OUT6_PTE15_PTE15_PTE15_PTE15_PTE15_PTE15_PTE15_PTE15 KINETIS_MUX('E',15,7) /* PTE_15 */
#define PTE16 KINETIS_MUX('E',16,1) /* PTE_16 */
#define FXIO_D3_PTE16 KINETIS_MUX('E',16,6) /* PTE_16 */
#define TRGMUX_OUT7_PTE16 KINETIS_MUX('E',16,7) /* PTE_16 */
#define TRGMUX_OUT7_PTE16_PTE16_PTE16_PTE16_PTE16_PTE16_PTE16_PTE16 KINETIS_MUX('E',16,7) /* PTE_16 */
#endif
