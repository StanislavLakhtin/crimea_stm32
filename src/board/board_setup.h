//
// Created by sl on 28.06.17.
//

#ifndef CRIMEA_STM32_BOARD_SETUP_H
#define CRIMEA_STM32_BOARD_SETUP_H

#include <libopencm3/stm32/gpio.h>

#define USB_PULLUP_PORT GPIOE
#define USB_PULLUP_GPIO GPIO2

void clock_setup(void);
void spi1_setup(void);
void systick_setup(void);
void gpio_setup(void);
void i2c_setup(void);
void display_WakeUp(void);
void usb_pullup(void);
int board_setup(void);

void encoder_handler(void);
void encoder_setup(uint8_t *volumeControl);

#endif //CRIMEA_STM32_BOARD_SETUP_H
