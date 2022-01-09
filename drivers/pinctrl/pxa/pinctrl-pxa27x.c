// SPDX-License-Identifier: GPL-2.0-only
/*
 * Marvell PXA27x family pin control
 *
 * Copyright (C) 2015 Robert Jarzmik
 */
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/pinctrl/pinctrl.h>

#include "pinctrl-pxa2xx.h"

static const struct pxa_desc_pin pxa27x_pins[] = {
	PXA_GPIO_ONLY_PIN(PXA_PINCTRL_PIN(0)),
	PXA_GPIO_ONLY_PIN(PXA_PINCTRL_PIN(1)),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(9),
		     PXA_FUNCTION(0, 3, "FFCTS"),
		     PXA_FUNCTION(1, 1, "HZ_CLK"),
		     PXA_FUNCTION(1, 3, "CHOUT<0>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(10),
		     PXA_FUNCTION(0, 1, "FFDCD"),
		     PXA_FUNCTION(0, 3, "USB_P3_5"),
		     PXA_FUNCTION(1, 1, "HZ_CLK"),
		     PXA_FUNCTION(1, 3, "CHOUT<1>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(11),
		     PXA_FUNCTION(0, 1, "EXT_SYNC<0>"),
		     PXA_FUNCTION(0, 2, "SSPRXD2"),
		     PXA_FUNCTION(0, 3, "USB_P3_1"),
		     PXA_FUNCTION(1, 1, "CHOUT<0>"),
		     PXA_FUNCTION(1, 1, "PWM_OUT<2>"),
		     PXA_FUNCTION(1, 3, "48_MHz")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(12),
		     PXA_FUNCTION(0, 1, "EXT_SYNC<1>"),
		     PXA_FUNCTION(0, 2, "CIF_DD<7>"),
		     PXA_FUNCTION(1, 1, "CHOUT<1>"),
		     PXA_FUNCTION(1, 1, "PWM_OUT<3>"),
		     PXA_FUNCTION(1, 3, "48_MHz")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(13),
		     PXA_FUNCTION(0, 1, "CLK_EXT"),
		     PXA_FUNCTION(0, 2, "KP_DKIN<7>"),
		     PXA_FUNCTION(0, 3, "KP_MKIN<7>"),
		     PXA_FUNCTION(1, 1, "SSPTXD2")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(14),
		     PXA_FUNCTION(0, 1, "L_VSYNC"),
		     PXA_FUNCTION(0, 2, "SSPSFRM2"),
		     PXA_FUNCTION(1, 1, "SSPSFRM2"),
		     PXA_FUNCTION(1, 3, "UCLK")),
	PXA_GPIO_ONLY_PIN(PXA_PINCTRL_PIN(15)),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(16),
		     PXA_FUNCTION(0, 1, "KP_MKIN<5>"),
		     PXA_FUNCTION(1, 2, "PWM_OUT<0>"),
		     PXA_FUNCTION(1, 3, "FFTXD")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(17),
		     PXA_FUNCTION(0, 1, "KP_MKIN<6>"),
		     PXA_FUNCTION(0, 2, "CIF_DD<6>"),
		     PXA_FUNCTION(1, 2, "PWM_OUT<1>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(18),
		     PXA_FUNCTION(0, 1, "RDY")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(19),
		     PXA_FUNCTION(0, 1, "SSPSCLK2"),
		     PXA_FUNCTION(0, 3, "FFRXD"),
		     PXA_FUNCTION(1, 1, "SSPSCLK2"),
		     PXA_FUNCTION(1, 2, "L_CS"),
		     PXA_FUNCTION(1, 3, "nURST")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(20),
		     PXA_FUNCTION(0, 1, "DREQ<0>"),
		     PXA_FUNCTION(0, 2, "MBREQ"),
		     PXA_FUNCTION(1, 1, "nSDCS<2>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(21),
		     PXA_FUNCTION(1, 1, "nSDCS<3>"),
		     PXA_FUNCTION(1, 2, "DVAL<0>"),
		     PXA_FUNCTION(1, 3, "MBGNT")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(22),
		     PXA_FUNCTION(0, 1, "SSPEXTCLK2"),
		     PXA_FUNCTION(0, 2, "SSPSCLKEN2"),
		     PXA_FUNCTION(0, 3, "SSPSCLK2"),
		     PXA_FUNCTION(1, 1, "KP_MKOUT<7>"),
		     PXA_FUNCTION(1, 2, "SSPSYSCLK2"),
		     PXA_FUNCTION(1, 3, "SSPSCLK2")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(23),
		     PXA_FUNCTION(0, 2, "SSPSCLK"),
		     PXA_FUNCTION(1, 1, "CIF_MCLK"),
		     PXA_FUNCTION(1, 1, "SSPSCLK")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(24),
		     PXA_FUNCTION(0, 1, "CIF_FV"),
		     PXA_FUNCTION(0, 2, "SSPSFRM"),
		     PXA_FUNCTION(1, 1, "CIF_FV"),
		     PXA_FUNCTION(1, 2, "SSPSFRM")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(25),
		     PXA_FUNCTION(0, 1, "CIF_LV"),
		     PXA_FUNCTION(1, 1, "CIF_LV"),
		     PXA_FUNCTION(1, 2, "SSPTXD")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(26),
		     PXA_FUNCTION(0, 1, "SSPRXD"),
		     PXA_FUNCTION(0, 2, "CIF_PCLK"),
		     PXA_FUNCTION(0, 3, "FFCTS")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(27),
		     PXA_FUNCTION(0, 1, "SSPEXTCLK"),
		     PXA_FUNCTION(0, 2, "SSPSCLKEN"),
		     PXA_FUNCTION(0, 3, "CIF_DD<0>"),
		     PXA_FUNCTION(1, 1, "SSPSYSCLK"),
		     PXA_FUNCTION(1, 3, "FFRTS")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(28),
		     PXA_FUNCTION(0, 1, "AC97_BITCLK"),
		     PXA_FUNCTION(0, 2, "I2S_BITCLK"),
		     PXA_FUNCTION(0, 3, "SSPSFRM"),
		     PXA_FUNCTION(1, 1, "I2S_BITCLK"),
		     PXA_FUNCTION(1, 3, "SSPSFRM")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(29),
		     PXA_FUNCTION(0, 1, "AC97_SDATA_IN_0"),
		     PXA_FUNCTION(0, 2, "I2S_SDATA_IN"),
		     PXA_FUNCTION(0, 3, "SSPSCLK"),
		     PXA_FUNCTION(1, 1, "SSPRXD2"),
		     PXA_FUNCTION(1, 3, "SSPSCLK")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(30),
		     PXA_FUNCTION(1, 1, "I2S_SDATA_OUT"),
		     PXA_FUNCTION(1, 2, "AC97_SDATA_OUT"),
		     PXA_FUNCTION(1, 3, "USB_P3_2")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(31),
		     PXA_FUNCTION(1, 1, "I2S_SYNC"),
		     PXA_FUNCTION(1, 2, "AC97_SYNC"),
		     PXA_FUNCTION(1, 3, "USB_P3_6")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(32),
		     PXA_FUNCTION(1, 1, "MSSCLK"),
		     PXA_FUNCTION(1, 2, "MMCLK")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(33),
		     PXA_FUNCTION(0, 1, "FFRXD"),
		     PXA_FUNCTION(0, 2, "FFDSR"),
		     PXA_FUNCTION(1, 1, "DVAL<1>"),
		     PXA_FUNCTION(1, 2, "nCS<5>"),
		     PXA_FUNCTION(1, 3, "MBGNT")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(34),
		     PXA_FUNCTION(0, 1, "FFRXD"),
		     PXA_FUNCTION(0, 2, "KP_MKIN<3>"),
		     PXA_FUNCTION(0, 3, "SSPSCLK3"),
		     PXA_FUNCTION(1, 1, "USB_P2_2"),
		     PXA_FUNCTION(1, 3, "SSPSCLK3")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(35),
		     PXA_FUNCTION(0, 1, "FFCTS"),
		     PXA_FUNCTION(0, 2, "USB_P2_1"),
		     PXA_FUNCTION(0, 3, "SSPSFRM3"),
		     PXA_FUNCTION(1, 2, "KP_MKOUT<6>"),
		     PXA_FUNCTION(1, 3, "SSPTXD3")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(36),
		     PXA_FUNCTION(0, 1, "FFDCD"),
		     PXA_FUNCTION(0, 2, "SSPSCLK2"),
		     PXA_FUNCTION(0, 3, "KP_MKIN<7>"),
		     PXA_FUNCTION(1, 1, "USB_P2_4"),
		     PXA_FUNCTION(1, 2, "SSPSCLK2")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(37),
		     PXA_FUNCTION(0, 1, "FFDSR"),
		     PXA_FUNCTION(0, 2, "SSPSFRM2"),
		     PXA_FUNCTION(0, 3, "KP_MKIN<3>"),
		     PXA_FUNCTION(1, 1, "USB_P2_8"),
		     PXA_FUNCTION(1, 2, "SSPSFRM2"),
		     PXA_FUNCTION(1, 3, "FFTXD")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(38),
		     PXA_FUNCTION(0, 1, "FFRI"),
		     PXA_FUNCTION(0, 2, "KP_MKIN<4>"),
		     PXA_FUNCTION(0, 3, "USB_P2_3"),
		     PXA_FUNCTION(1, 1, "SSPTXD3"),
		     PXA_FUNCTION(1, 2, "SSPTXD2"),
		     PXA_FUNCTION(1, 3, "PWM_OUT<0>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(39),
		     PXA_FUNCTION(0, 1, "KP_MKIN<4>"),
		     PXA_FUNCTION(0, 3, "SSPSFRM3"),
		     PXA_FUNCTION(1, 1, "USB_P2_6"),
		     PXA_FUNCTION(1, 2, "FFTXD"),
		     PXA_FUNCTION(1, 3, "SSPSFRM3")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(40),
		     PXA_FUNCTION(0, 1, "SSPRXD2"),
		     PXA_FUNCTION(0, 3, "USB_P2_5"),
		     PXA_FUNCTION(1, 1, "KP_MKOUT<6>"),
		     PXA_FUNCTION(1, 2, "FFDTR"),
		     PXA_FUNCTION(1, 3, "SSPSCLK3")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(41),
		     PXA_FUNCTION(0, 1, "FFRXD"),
		     PXA_FUNCTION(0, 2, "USB_P2_7"),
		     PXA_FUNCTION(0, 3, "SSPRXD3"),
		     PXA_FUNCTION(1, 1, "KP_MKOUT<7>"),
		     PXA_FUNCTION(1, 2, "FFRTS")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(42),
		     PXA_FUNCTION(0, 1, "BTRXD"),
		     PXA_FUNCTION(0, 2, "ICP_RXD"),
		     PXA_FUNCTION(1, 3, "CIF_MCLK")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(43),
		     PXA_FUNCTION(0, 3, "CIF_FV"),
		     PXA_FUNCTION(1, 1, "ICP_TXD"),
		     PXA_FUNCTION(1, 2, "BTTXD"),
		     PXA_FUNCTION(1, 3, "CIF_FV")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(44),
		     PXA_FUNCTION(0, 1, "BTCTS"),
		     PXA_FUNCTION(0, 3, "CIF_LV"),
		     PXA_FUNCTION(1, 3, "CIF_LV")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(45),
		     PXA_FUNCTION(0, 3, "CIF_PCLK"),
		     PXA_FUNCTION(1, 1, "AC97_SYSCLK"),
		     PXA_FUNCTION(1, 2, "BTRTS"),
		     PXA_FUNCTION(1, 3, "SSPSYSCLK3")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(46),
		     PXA_FUNCTION(0, 1, "ICP_RXD"),
		     PXA_FUNCTION(0, 2, "STD_RXD"),
		     PXA_FUNCTION(1, 2, "PWM_OUT<2>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(47),
		     PXA_FUNCTION(0, 1, "CIF_DD<0>"),
		     PXA_FUNCTION(1, 1, "STD_TXD"),
		     PXA_FUNCTION(1, 2, "ICP_TXD"),
		     PXA_FUNCTION(1, 3, "PWM_OUT<3>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(48),
		     PXA_FUNCTION(0, 1, "CIF_DD<5>"),
		     PXA_FUNCTION(1, 1, "BB_OB_DAT<1>"),
		     PXA_FUNCTION(1, 2, "nPOE")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(49),
		     PXA_FUNCTION(1, 2, "nPWE")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(50),
		     PXA_FUNCTION(0, 1, "CIF_DD<3>"),
		     PXA_FUNCTION(0, 3, "SSPSCLK2"),
		     PXA_FUNCTION(1, 1, "BB_OB_DAT<2>"),
		     PXA_FUNCTION(1, 2, "nPIOR"),
		     PXA_FUNCTION(1, 3, "SSPSCLK2")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(51),
		     PXA_FUNCTION(0, 1, "CIF_DD<2>"),
		     PXA_FUNCTION(1, 1, "BB_OB_DAT<3>"),
		     PXA_FUNCTION(1, 2, "nPIOW")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(52),
		     PXA_FUNCTION(0, 1, "CIF_DD<4>"),
		     PXA_FUNCTION(0, 2, "SSPSCLK3"),
		     PXA_FUNCTION(1, 1, "BB_OB_CLK"),
		     PXA_FUNCTION(1, 2, "SSPSCLK3")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(53),
		     PXA_FUNCTION(0, 1, "FFRXD"),
		     PXA_FUNCTION(0, 2, "USB_P2_3"),
		     PXA_FUNCTION(1, 1, "BB_OB_STB"),
		     PXA_FUNCTION(1, 2, "CIF_MCLK"),
		     PXA_FUNCTION(1, 3, "SSPSYSCLK")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(54),
		     PXA_FUNCTION(0, 2, "BB_OB_WAIT"),
		     PXA_FUNCTION(0, 3, "CIF_PCLK"),
		     PXA_FUNCTION(1, 2, "nPCE<2>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(55),
		     PXA_FUNCTION(0, 1, "CIF_DD<1>"),
		     PXA_FUNCTION(0, 2, "BB_IB_DAT<1>"),
		     PXA_FUNCTION(1, 2, "nPREG")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(56),
		     PXA_FUNCTION(0, 1, "nPWAIT"),
		     PXA_FUNCTION(0, 2, "BB_IB_DAT<2>"),
		     PXA_FUNCTION(1, 1, "USB_P3_4")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(57),
		     PXA_FUNCTION(0, 1, "nIOS16"),
		     PXA_FUNCTION(0, 2, "BB_IB_DAT<3>"),
		     PXA_FUNCTION(1, 3, "SSPTXD")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(58),
		     PXA_FUNCTION(0, 2, "LDD<0>"),
		     PXA_FUNCTION(1, 2, "LDD<0>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(59),
		     PXA_FUNCTION(0, 2, "LDD<1>"),
		     PXA_FUNCTION(1, 2, "LDD<1>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(60),
		     PXA_FUNCTION(0, 2, "LDD<2>"),
		     PXA_FUNCTION(1, 2, "LDD<2>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(61),
		     PXA_FUNCTION(0, 2, "LDD<3>"),
		     PXA_FUNCTION(1, 2, "LDD<3>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(62),
		     PXA_FUNCTION(0, 2, "LDD<4>"),
		     PXA_FUNCTION(1, 2, "LDD<4>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(63),
		     PXA_FUNCTION(0, 2, "LDD<5>"),
		     PXA_FUNCTION(1, 2, "LDD<5>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(64),
		     PXA_FUNCTION(0, 2, "LDD<6>"),
		     PXA_FUNCTION(1, 2, "LDD<6>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(65),
		     PXA_FUNCTION(0, 2, "LDD<7>"),
		     PXA_FUNCTION(1, 2, "LDD<7>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(66),
		     PXA_FUNCTION(0, 2, "LDD<8>"),
		     PXA_FUNCTION(1, 2, "LDD<8>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(67),
		     PXA_FUNCTION(0, 2, "LDD<9>"),
		     PXA_FUNCTION(1, 2, "LDD<9>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(68),
		     PXA_FUNCTION(0, 2, "LDD<10>"),
		     PXA_FUNCTION(1, 2, "LDD<10>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(69),
		     PXA_FUNCTION(0, 2, "LDD<11>"),
		     PXA_FUNCTION(1, 2, "LDD<11>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(70),
		     PXA_FUNCTION(0, 2, "LDD<12>"),
		     PXA_FUNCTION(1, 2, "LDD<12>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(71),
		     PXA_FUNCTION(0, 2, "LDD<13>"),
		     PXA_FUNCTION(1, 2, "LDD<13>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(72),
		     PXA_FUNCTION(0, 2, "LDD<14>"),
		     PXA_FUNCTION(1, 2, "LDD<14>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(73),
		     PXA_FUNCTION(0, 2, "LDD<15>"),
		     PXA_FUNCTION(1, 2, "LDD<15>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(74),
		     PXA_FUNCTION(1, 2, "L_FCLK_RD")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(75),
		     PXA_FUNCTION(1, 2, "L_LCLK_A0")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(76),
		     PXA_FUNCTION(1, 2, "L_PCLK_WR")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(77),
		     PXA_FUNCTION(1, 2, "L_BIAS")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(78),
		     PXA_FUNCTION(1, 1, "nPCE<2>"),
		     PXA_FUNCTION(1, 2, "nCS<2>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(79),
		     PXA_FUNCTION(1, 1, "PSKTSEL"),
		     PXA_FUNCTION(1, 2, "nCS<3>"),
		     PXA_FUNCTION(1, 3, "PWM_OUT<2>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(80),
		     PXA_FUNCTION(0, 1, "DREQ<1>"),
		     PXA_FUNCTION(0, 2, "MBREQ"),
		     PXA_FUNCTION(1, 2, "nCS<4>"),
		     PXA_FUNCTION(1, 3, "PWM_OUT<3>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(81),
		     PXA_FUNCTION(0, 2, "CIF_DD<0>"),
		     PXA_FUNCTION(1, 1, "SSPTXD3"),
		     PXA_FUNCTION(1, 2, "BB_OB_DAT<0>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(82),
		     PXA_FUNCTION(0, 1, "SSPRXD3"),
		     PXA_FUNCTION(0, 2, "BB_IB_DAT<0>"),
		     PXA_FUNCTION(0, 3, "CIF_DD<5>"),
		     PXA_FUNCTION(1, 3, "FFDTR")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(83),
		     PXA_FUNCTION(0, 1, "SSPSFRM3"),
		     PXA_FUNCTION(0, 2, "BB_IB_CLK"),
		     PXA_FUNCTION(0, 3, "CIF_DD<5>"),
		     PXA_FUNCTION(1, 1, "SSPSFRM3"),
		     PXA_FUNCTION(1, 2, "FFTXD"),
		     PXA_FUNCTION(1, 3, "FFRTS")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(84),
		     PXA_FUNCTION(0, 1, "SSPCLK3"),
		     PXA_FUNCTION(0, 2, "BB_IB_STB"),
		     PXA_FUNCTION(0, 3, "CIF_FV"),
		     PXA_FUNCTION(1, 1, "SSPCLK3"),
		     PXA_FUNCTION(1, 3, "CIF_FV")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(85),
		     PXA_FUNCTION(0, 1, "FFRXD"),
		     PXA_FUNCTION(0, 2, "DREQ<2>"),
		     PXA_FUNCTION(0, 3, "CIF_LV"),
		     PXA_FUNCTION(1, 1, "nPCE<1>"),
		     PXA_FUNCTION(1, 2, "BB_IB_WAIT"),
		     PXA_FUNCTION(1, 3, "CIF_LV")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(86),
		     PXA_FUNCTION(0, 1, "SSPRXD2"),
		     PXA_FUNCTION(0, 2, "LDD<16>"),
		     PXA_FUNCTION(0, 3, "USB_P3_5"),
		     PXA_FUNCTION(1, 1, "nPCE<1>"),
		     PXA_FUNCTION(1, 2, "LDD<16>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(87),
		     PXA_FUNCTION(0, 1, "nPCE<2>"),
		     PXA_FUNCTION(0, 2, "LDD<17>"),
		     PXA_FUNCTION(0, 3, "USB_P3_1"),
		     PXA_FUNCTION(1, 1, "SSPTXD2"),
		     PXA_FUNCTION(1, 2, "LDD<17>"),
		     PXA_FUNCTION(1, 3, "SSPSFRM2")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(88),
		     PXA_FUNCTION(0, 1, "USBHPWR<1>"),
		     PXA_FUNCTION(0, 2, "SSPRXD2"),
		     PXA_FUNCTION(0, 3, "SSPSFRM2"),
		     PXA_FUNCTION(1, 2, "SSPTXD2"),
		     PXA_FUNCTION(1, 3, "SSPSFRM2")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(89),
		     PXA_FUNCTION(0, 1, "SSPRXD3"),
		     PXA_FUNCTION(0, 3, "FFRI"),
		     PXA_FUNCTION(1, 1, "AC97_SYSCLK"),
		     PXA_FUNCTION(1, 2, "USBHPEN<1>"),
		     PXA_FUNCTION(1, 3, "SSPTXD2")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(90),
		     PXA_FUNCTION(0, 1, "KP_MKIN<5>"),
		     PXA_FUNCTION(0, 3, "USB_P3_5"),
		     PXA_FUNCTION(1, 1, "CIF_DD<4>"),
		     PXA_FUNCTION(1, 2, "nURST")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(91),
		     PXA_FUNCTION(0, 1, "KP_MKIN<6>"),
		     PXA_FUNCTION(0, 3, "USB_P3_1"),
		     PXA_FUNCTION(1, 1, "CIF_DD<5>"),
		     PXA_FUNCTION(1, 2, "UCLK")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(92),
		     PXA_FUNCTION(0, 1, "MMDAT<0>"),
		     PXA_FUNCTION(1, 1, "MMDAT<0>"),
		     PXA_FUNCTION(1, 2, "MSBS")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(93),
		     PXA_FUNCTION(0, 1, "KP_DKIN<0>"),
		     PXA_FUNCTION(0, 2, "CIF_DD<6>"),
		     PXA_FUNCTION(1, 1, "AC97_SDATA_OUT")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(94),
		     PXA_FUNCTION(0, 1, "KP_DKIN<1>"),
		     PXA_FUNCTION(0, 2, "CIF_DD<5>"),
		     PXA_FUNCTION(1, 1, "AC97_SYNC")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(95),
		     PXA_FUNCTION(0, 1, "KP_DKIN<2>"),
		     PXA_FUNCTION(0, 2, "CIF_DD<4>"),
		     PXA_FUNCTION(0, 3, "KP_MKIN<6>"),
		     PXA_FUNCTION(1, 1, "AC97_RESET_n")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(96),
		     PXA_FUNCTION(0, 1, "KP_DKIN<3>"),
		     PXA_FUNCTION(0, 2, "MBREQ"),
		     PXA_FUNCTION(0, 3, "FFRXD"),
		     PXA_FUNCTION(1, 2, "DVAL<1>"),
		     PXA_FUNCTION(1, 3, "KP_MKOUT<6>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(97),
		     PXA_FUNCTION(0, 1, "KP_DKIN<4>"),
		     PXA_FUNCTION(0, 2, "DREQ<1>"),
		     PXA_FUNCTION(0, 3, "KP_MKIN<3>"),
		     PXA_FUNCTION(1, 2, "MBGNT")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(98),
		     PXA_FUNCTION(0, 1, "KP_DKIN<5>"),
		     PXA_FUNCTION(0, 2, "CIF_DD<0>"),
		     PXA_FUNCTION(0, 3, "KP_MKIN<4>"),
		     PXA_FUNCTION(1, 1, "AC97_SYSCLK"),
		     PXA_FUNCTION(1, 3, "FFRTS")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(99),
		     PXA_FUNCTION(0, 1, "KP_DKIN<6>"),
		     PXA_FUNCTION(0, 2, "AC97_SDATA_IN_1"),
		     PXA_FUNCTION(0, 3, "KP_MKIN<5>"),
		     PXA_FUNCTION(1, 3, "FFTXD")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(100),
		     PXA_FUNCTION(0, 1, "KP_MKIN<0>"),
		     PXA_FUNCTION(0, 2, "DREQ<2>"),
		     PXA_FUNCTION(0, 3, "FFCTS")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(101),
		     PXA_FUNCTION(0, 1, "KP_MKIN<1>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(102),
		     PXA_FUNCTION(0, 1, "KP_MKIN<2>"),
		     PXA_FUNCTION(0, 3, "FFRXD"),
		     PXA_FUNCTION(1, 1, "nPCE<1>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(103),
		     PXA_FUNCTION(0, 1, "CIF_DD<3>"),
		     PXA_FUNCTION(1, 2, "KP_MKOUT<0>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(104),
		     PXA_FUNCTION(0, 1, "CIF_DD<2>"),
		     PXA_FUNCTION(1, 1, "PSKTSEL"),
		     PXA_FUNCTION(1, 2, "KP_MKOUT<1>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(105),
		     PXA_FUNCTION(0, 1, "CIF_DD<1>"),
		     PXA_FUNCTION(1, 1, "nPCE<2>"),
		     PXA_FUNCTION(1, 2, "KP_MKOUT<2>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(106),
		     PXA_FUNCTION(0, 1, "CIF_DD<9>"),
		     PXA_FUNCTION(1, 2, "KP_MKOUT<3>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(107),
		     PXA_FUNCTION(0, 1, "CIF_DD<8>"),
		     PXA_FUNCTION(1, 2, "KP_MKOUT<4>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(108),
		     PXA_FUNCTION(0, 1, "CIF_DD<7>"),
		     PXA_FUNCTION(1, 1, "CHOUT<0>"),
		     PXA_FUNCTION(1, 2, "KP_MKOUT<5>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(109),
		     PXA_FUNCTION(0, 1, "MMDAT<1>"),
		     PXA_FUNCTION(0, 2, "MSSDIO"),
		     PXA_FUNCTION(1, 1, "MMDAT<1>"),
		     PXA_FUNCTION(1, 2, "MSSDIO")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(110),
		     PXA_FUNCTION(0, 1, "MMDAT<2>"),
		     PXA_FUNCTION(1, 1, "MMDAT<2>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(111),
		     PXA_FUNCTION(0, 1, "MMDAT<3>"),
		     PXA_FUNCTION(1, 1, "MMDAT<3>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(112),
		     PXA_FUNCTION(0, 1, "MMCMD"),
		     PXA_FUNCTION(0, 2, "nMSINS"),
		     PXA_FUNCTION(1, 1, "MMCMD")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(113),
		     PXA_FUNCTION(0, 3, "USB_P3_3"),
		     PXA_FUNCTION(1, 1, "I2S_SYSCLK"),
		     PXA_FUNCTION(1, 2, "AC97_RESET_n")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(114),
		     PXA_FUNCTION(0, 1, "CIF_DD<1>"),
		     PXA_FUNCTION(1, 1, "UEN"),
		     PXA_FUNCTION(1, 2, "UVS0")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(115),
		     PXA_FUNCTION(0, 1, "DREQ<0>"),
		     PXA_FUNCTION(0, 2, "CIF_DD<3>"),
		     PXA_FUNCTION(0, 3, "MBREQ"),
		     PXA_FUNCTION(1, 1, "UEN"),
		     PXA_FUNCTION(1, 2, "nUVS1"),
		     PXA_FUNCTION(1, 3, "PWM_OUT<1>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(116),
		     PXA_FUNCTION(0, 1, "CIF_DD<2>"),
		     PXA_FUNCTION(0, 2, "AC97_SDATA_IN_0"),
		     PXA_FUNCTION(0, 3, "UDET"),
		     PXA_FUNCTION(1, 1, "DVAL<0>"),
		     PXA_FUNCTION(1, 2, "nUVS2"),
		     PXA_FUNCTION(1, 3, "MBGNT")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(117),
		     PXA_FUNCTION(0, 1, "SCL"),
		     PXA_FUNCTION(1, 1, "SCL")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(118),
		     PXA_FUNCTION(0, 1, "SDA"),
		     PXA_FUNCTION(1, 1, "SDA")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(119),
		     PXA_FUNCTION(0, 1, "USBHPWR<2>")),
	PXA_GPIO_PIN(PXA_PINCTRL_PIN(120),
		     PXA_FUNCTION(1, 2, "USBHPEN<2>")),
};

static int pxa27x_pinctrl_probe(struct platform_device *pdev)
{
	int ret, i;
	void __iomem *base_af[8];
	void __iomem *base_dir[4];
	void __iomem *base_sleep[4];

	base_af[0] = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(base_af[0]))
		return PTR_ERR(base_af[0]);

	base_dir[0] = devm_platform_ioremap_resource(pdev, 1);
	if (IS_ERR(base_dir[0]))
		return PTR_ERR(base_dir[0]);

	base_dir[3] = devm_platform_ioremap_resource(pdev, 2);
	if (IS_ERR(base_dir[3]))
		return PTR_ERR(base_dir[3]);

	base_sleep[0] = devm_platform_ioremap_resource(pdev, 3);
	if (IS_ERR(base_sleep[0]))
		return PTR_ERR(base_sleep[0]);

	for (i = 0; i < ARRAY_SIZE(base_af); i++)
		base_af[i] = base_af[0] + sizeof(base_af[0]) * i;
	for (i = 0; i < 3; i++)
		base_dir[i] = base_dir[0] + sizeof(base_dir[0]) * i;
	for (i = 0; i < ARRAY_SIZE(base_sleep); i++)
		base_sleep[i] = base_sleep[0] + sizeof(base_af[0]) * i;

	ret = pxa2xx_pinctrl_init(pdev, pxa27x_pins, ARRAY_SIZE(pxa27x_pins),
				  base_af, base_dir, base_sleep);
	return ret;
}

static const struct of_device_id pxa27x_pinctrl_match[] = {
	{ .compatible = "marvell,pxa27x-pinctrl", },
	{}
};
MODULE_DEVICE_TABLE(of, pxa27x_pinctrl_match);

static struct platform_driver pxa27x_pinctrl_driver = {
	.probe	= pxa27x_pinctrl_probe,
	.driver	= {
		.name		= "pxa27x-pinctrl",
		.of_match_table	= pxa27x_pinctrl_match,
	},
};
module_platform_driver(pxa27x_pinctrl_driver);

MODULE_AUTHOR("Robert Jarzmik <robert.jarzmik@free.fr>");
MODULE_DESCRIPTION("Marvell PXA27x pinctrl driver");
MODULE_LICENSE("GPL v2");
