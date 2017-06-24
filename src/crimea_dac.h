//
// Created by sl on 11.06.17.
//

#ifndef CRIMEA_OPENDAC_CRIMEA_DAC_H
#define CRIMEA_OPENDAC_CRIMEA_DAC_H

#include <libopencm3/stm32/gpio.h>

#define USB_PULLUP_PORT GPIOB
#define USB_PULLUP_GPIO  GPIO6

/**
 * External declarations
 */
extern int board_setup(void);
extern void display_WakeUp(void);
extern void encoder_setup(volatile uint8_t *vC);
extern void encoder_handler(void);
extern void exti_setup(void);

// 2 bytes
#define USB_VENDOR_ID 0x08bb
// 2 bytes
#define USB_PRODUCT_ID 2704
// 16 bytes
#define USB_PRODUCT_NAME "Crimea USBDAC v1"
// 32 bytes
#define USB_VENDOR_STRING  "Stanslav Lakhtin DIY project    "
// 1 byte (0x80 -- bus powered)
#define USB_POWER_ATTRIBUTE 0x80
// 1 byte
#define USB_MAX_POWER 0xfa
//3 bytes
#define USB_AUX_HID_DEVICE_ID_1 0x0a
#define USB_AUX_HID_DEVICE_ID_2 0x93
#define USB_AUX_HID_DEVICE_ID_3 0x01

#endif //CRIMEA_OPENDAC_CRIMEA_DAC_H
