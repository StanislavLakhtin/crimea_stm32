//
// Created by Stanislav Lakhtin on 25/06/2017.
//

#ifndef CRIMEA_STM32_USB_H
#define CRIMEA_STM32_USB_H
#include <libopencm3/usb/usbd.h>


extern const struct usb_device_descriptor dev;
extern const struct usb_config_descriptor conf;
extern const char * usb_strings[];

void usb_set_config_handler(usbd_device *usbd_dev, uint16_t wValue);

#endif //CRIMEA_STM32_USB_H
