/*
  * Copyright © 2017 Owasys.
  *
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation; either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  */
  
 #ifndef __OWA4X_GPIO_H__
 #define __OWA4X_GPIO_H__
  
 #include <linux/types.h>
  
 #define GPIO_TO_PIN(bank, gpio)     (32 * (bank) + (gpio))
 #define GPIO_LED_SW0  GPIO_TO_PIN(1, 15)  /* gpmc_ad15 */
 #define GPIO_LED_SW1  GPIO_TO_PIN(3, 7)  /* emu0 */
 #define GPIO_LED_SW2  GPIO_TO_PIN(2, 20) /* mii1_rxd1 */
 #define GPIO_LIN_K_EN GPIO_TO_PIN(1, 12)  /* gpmc_ad12 */
 #define GPIO_PPS_GPS  GPIO_TO_PIN(1, 13)  /* gpmc_ad13 */
 #define GPIO_BOOT_UC  GPIO_TO_PIN(1, 23) /* gpmc_a7 */
 #define GPIO_RESET_UC GPIO_TO_PIN(2, 9) /* lcd_data3 */
 #define GPIO_GPS_ON    GPIO_TO_PIN(2, 13) /* lcd_data7 */
 #define GPIO_ANT_OPEN  GPIO_TO_PIN(2, 21) /* mii1_rxd0  */
 #define GPIO_ANT_SHORT GPIO_TO_PIN(3, 8)  /* emu1 */
 #define GPIO_CAN_NRESET GPIO_TO_PIN(2, 22)  /* lcd_vsync */
 #define GPIO_CAN2_SLOPE  GPIO_TO_PIN(1, 18) /* gpmc_a2 */
 #define GPIO_CAN3_SLOPE  GPIO_TO_PIN(1, 19) /* gpmc_a3 */
 #define GPIO_CAN4_SLOPE  GPIO_TO_PIN(1, 22) /* gpmc_a6 */
 #define GPIO_CAN_EN      GPIO_TO_PIN(2, 12) /* lcd_data6 */
 #define GPIO_ETH_ON      GPIO_TO_PIN(2, 11) /* lcd_data5 */
 #define GPIO_nDAI_ENABLE GPIO_TO_PIN(2, 24) /* lcd_pclk */
 #define GPIO_SPI0_MOSI   GPIO_TO_PIN(0, 3) /* spi0_d0 */
 #define GPIO_CODEC_NRST  GPIO_TO_PIN(2, 23) /* lcd_hsync */
 #define GPIO_USB0_DRVVBUS  GPIO_TO_PIN(0, 18) /* USB0_DRVVBUS */
 #define GPIO_GPMC_A8  GPIO_TO_PIN(1, 24) /* gpmc_a8 */
 #define GPIO_KLINE1_LOWTH  GPIO_TO_PIN(1, 25) /* gpmc_a9 */
 #define GPIO_KLINE2_LOWTH  GPIO_TO_PIN(1, 17) /* gpmc_a1 */
 #define GPIO_UART2_TXD GPIO_TO_PIN(3, 10) /* gmii1_rxclk */
 #define GPIO_UART2_RXD GPIO_TO_PIN(3, 9) /* gmii1_txclk */
 #define GPIO_UART2_RTS GPIO_TO_PIN(3, 6) /* I2C0_SCL */
 #define GPIO_UART1_RXD GPIO_TO_PIN(0, 14) /* uart1_rxd */
 #define GPIO_UART4_CTS GPIO_TO_PIN(0, 8) /* lcd_data12 */
 #define GPIO_UART4_RTS GPIO_TO_PIN(0, 9) /* lcd_data13 */
 #define GPIO_EXTSIM_SEL GPIO_TO_PIN(2, 10) /* lcd_data4 */
 #define GPIO_SPI0_CS1 GPIO_TO_PIN(0, 6) /* spi0_cs1 */
 #define GPIO_I2C0_SDA GPIO_TO_PIN(3, 5) /* i2c0_sda */
 #define GPIO_HUB_RST GPIO_TO_PIN(2, 25) /* lcd_ac_bias_en */
 #define GPIO_TPM_INT GPIO_TO_PIN(0, 20) /* xdma_event_intr1 */
 #define GPIO_GPMC_BEn1 GPIO_TO_PIN(1, 28) /* gpmc_ben1 */
  
 #define FIRST_GPIO   GPIO_TO_PIN(0, 0)
 #define LAST_GPIO    GPIO_TO_PIN(3, 21)
  
 #define AM3352_SCM_BASE          0x44E10000
 #define AM3352_GPIO_CONF_OFFSET  0x0800
 #define AM3352_GPIO_CONF_END     0x0A34
 #define AM3352_SCM_GPIO_BASE     (AM3352_SCM_BASE + AM3352_GPIO_CONF_OFFSET)
 #define AM3352_GPIO_CONF_SIZE    (AM3352_GPIO_CONF_END - AM3352_GPIO_CONF_OFFSET + 4)
  
  
 #define CONF_MCASP0_ACLKR        0x01A0
 #define CONF_MCASP0_FSR          0x01A4
 #define CONF_MCASP0_AKR1         0x01A8
 #define CONF_MCASP0_AHCLKX       0x01AC
 #define CONF_SPI0_D0             0x0154
 #define CONF_LCD_DATA12          0x00d0
 #define CONF_LCD_DATA13          0x00d4
 #define CONF_USB0_DRVVBUS        0x021c
 #define CONF_SPI0_CS1            0x0160
 #define CONF_CAN2_SLOPE          0x0048
 #define CONF_CAN3_SLOPE          0x004c
 #define CONF_CAN4_SLOPE          0x0058
 #define CONF_KLINE1_LOWTH        0x0064
 #define CONF_KLINE2_LOWTH        0x0044
 #define CONF_UART2_TXD           0x0130
 #define CONF_UART2_RXD           0x012c
 #define CONF_UART2_RTS           0x018c
 #define CONF_UART1_RXD           0x0180
 #define CONF_UART4_CTS           CONF_LCD_DATA12
 #define CONF_UART4_RTS           CONF_LCD_DATA13
 //#define CONF_GMPC_AD15           0x003C
  
 #define AM3352_GPIO_CONF_MASK    0x0000007F
  
 #define INVALID_VALUE(VALUE) ( (VALUE < 0) || (VALUE > 1) )
 #define INVALID_PIN(PIN) ( (PIN < FIRST_GPIO) || (PIN > LAST_GPIO) )
 #define INVALID_OFFSET(offset) ( (offset < 0) || (offset > (AM3352_GPIO_CONF_END - AM3352_GPIO_CONF_OFFSET)))
 #define INVALID_CAN_TX_MODE(VALUE) ( (VALUE < 0) || (VALUE > 2) )
 #define INVALID_KLINE_THERSHOLD(VALUE) ( (VALUE < 0) || (VALUE > 1) )
  
 typedef struct _t_owa4x_gpio
 {
    int pin;
    int value;
 } t_owa4x_gpio;
  
 /* Get basic GPIO characteristics info */
 #define SET_OUTPUT_VALUE   _IOW ('Y', 1, struct _t_owa4x_gpio)
 #define GET_INPUT_VALUE    _IOW ('Y', 2, struct _t_owa4x_gpio)
 #define SET_GPIO_MODE      _IOW ('Y', 3, struct _t_owa4x_gpio)
 #define SET_GPIO_INPUT     _IOW ('Y', 4, struct _t_owa4x_gpio)
 #define SET_GPIO_OUTPUT    _IOW ('Y', 5, struct _t_owa4x_gpio)
  
 #endif /* __OWA4X_GPIO_H__ */