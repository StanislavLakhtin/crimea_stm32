//
// Created by Stanislav Lakhtin on 25/06/2017.
//

#ifndef CRIMEA_STM32_USB_H
#define CRIMEA_STM32_USB_H

static const struct usb_device_descriptor dev = {
    .bLength = USB_DT_DEVICE_SIZE,
    .bDescriptorType = USB_DT_DEVICE,
    .bcdUSB = 0x0200,    // was 0x0110 in Table B-1 example descriptor */
    .bDeviceClass = 0,   // device defined at interface level */
    .bDeviceSubClass = 0,
    .bDeviceProtocol = 0,
    .bMaxPacketSize0 = 64,
    .idVendor = 0x4444,  // Prototype product vendor ID */
    .idProduct = 0x52a3, // dd if=/dev/random bs=2 count=1 | hexdump */
    .bcdDevice = 0x0010, // 0.1
    .iManufacturer = 1,  // index to string desc */
    .iProduct = 2,       // index to string desc */
    .iSerialNumber = 3,  // index to string desc */
    .bNumConfigurations = 1,
};

static const struct usb_config_descriptor conf = {
    .bLength = USB_DT_CONFIGURATION_SIZE,
    .bDescriptorType = USB_DT_CONFIGURATION,
    .wTotalLength = sizeof(conf),
    .bNumInterfaces = 0x03,  // Default, Audio Streaming, HID. Total is 3
    .bConfigurationValue = 0x01,
    .iConfiguration = 0x01,
    .bmAttributes = 0x00,
    .bMaxPower = 0x7f,
};

static const char * usb_strings[] = {
    "libopencm3.org",
    "MIDI demo",
    "usb_serial_number"
};

uint8_t usbd_control_buffer[256];

void usb_set_config_handler(usbd_device *usbd_dev, uint16_t wValue);

#endif //CRIMEA_STM32_USB_H
