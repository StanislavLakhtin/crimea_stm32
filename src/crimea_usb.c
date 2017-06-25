//
// Created by Stanislav Lakhtin on 25/06/2017.
//

#include "crimea_usb.h"
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/audio.h>

static void usb_set_config_handler(usbd_device *usbd_dev, uint16_t wValue)
{
    (void)wValue;

    /*usbd_ep_setup(usbd_dev, 0x01, USB_ENDPOINT_ATTR_ISOCHRONOUS, 64,
                  usbmidi_data_rx_cb);
    usbd_ep_setup(usbd_dev, 0x81, USB_ENDPOINT_ATTR_BULK, 64, NULL);*/
}