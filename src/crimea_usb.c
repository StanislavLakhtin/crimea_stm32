//
// Created by Stanislav Lakhtin on 25/06/2017.
//

#include "crimea_usb.h"
#include "audio_descriptors.h"
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/audio.h>

const struct usb_device_descriptor dev = {
    .bLength = USB_DT_DEVICE_SIZE,
    .bDescriptorType = USB_DT_DEVICE,
    .bcdUSB = 0x0110,    // was 0x0110 in Table B-1 example descriptor */
    .bDeviceClass = 0,   // device defined at interface level */
    .bDeviceSubClass = 0,
    .bDeviceProtocol = 0,
    .bMaxPacketSize0 = 64,
    .idVendor = 0x6666,  // Prototype product vendor ID */
    .idProduct = 0x52a3, // dd if=/dev/random bs=2 count=1 | hexdump */
    .bcdDevice = 0x0010, // 0.1
    .iManufacturer = 1,  // index to string desc */
    .iProduct = 2,       // index to string desc */
    .iSerialNumber = 3,  // index to string desc */
    .bNumConfigurations = 1,
};

#define bmaCONTROLS_COUNT 3
#define SUPPORTED_FREQS 3

const static const struct {
  /* structure is */
  struct usb_audio_header_descriptor_head header_head;
  struct usb_audio_header_descriptor_body header_body;

  struct usb_ac_interface_input_descriptor ac_input;
  struct usb_ac_interface_output_descriptor ac_output;

  struct usb_ac_interface_feature_head_descriptor feature_head;
  struct usb_ac_interface_feature_control_body_descriptor feature1;
  struct usb_ac_interface_feature_control_body_descriptor feature2;
  struct usb_ac_interface_feature_control_body_descriptor feature3;
  struct usb_ac_interface_feature_tail_descriptor feature_tail;

  struct usb_interface_descriptor zero_ep;

  struct {
    struct usb_interface_descriptor interface;
    struct usb_audio_streaming_descriptor terminal;
    struct usb_audio_streaming_format_descriptor_head format_head;
    struct usb_audio_streaming_format_descriptor_freq format_freqs[SUPPORTED_FREQS];
    struct usb_standard_ac_interrupt_ep_descriptor ep;
    struct usb_isochronous_audio_data_ep_descriptor audio_data;
  } __attribute__((packed)) stereo_ep;
} __attribute__((packed)) audio_control_functional_descriptors = {
    // HEADER
        .header_head = {
            .bLength = sizeof(struct usb_audio_header_descriptor_head) +
                       1 * sizeof(struct usb_audio_header_descriptor_body) +
                       sizeof (struct usb_ac_interface_input_descriptor) +
                       sizeof (struct usb_ac_interface_output_descriptor) +
                       sizeof (struct usb_ac_interface_feature_head_descriptor) +
                       bmaCONTROLS_COUNT * sizeof (struct usb_ac_interface_feature_control_body_descriptor) +
                       sizeof (struct usb_ac_interface_feature_tail_descriptor),
            .bDescriptorType = USB_AUDIO_DT_CS_INTERFACE,
            .bDescriptorSubtype = USB_AUDIO_TYPE_HEADER,
            .bcdADC = 0x0100,
            .wTotalLength =
            sizeof(struct usb_audio_header_descriptor_head) +
            sizeof(struct usb_audio_header_descriptor_body) +
            sizeof(struct usb_ac_interface_input_descriptor) +
            sizeof(struct usb_ac_interface_output_descriptor) +
            sizeof(struct usb_ac_interface_feature_head_descriptor) +
            3 * sizeof(struct usb_ac_interface_feature_control_body_descriptor) +
            sizeof(struct usb_ac_interface_feature_tail_descriptor) +
            sizeof(struct usb_interface_descriptor) +
            sizeof(struct usb_interface_descriptor) +
            sizeof(struct usb_audio_streaming_descriptor) +
            sizeof(struct usb_audio_streaming_format_descriptor_head) +
            SUPPORTED_FREQS * sizeof(struct usb_audio_streaming_format_descriptor_freq) +
            sizeof(struct usb_standard_ac_interrupt_ep_descriptor) +
            sizeof(struct usb_isochronous_audio_data_ep_descriptor),
            .binCollection = 1,
        },
        .header_body = {
            .baInterfaceNr = 0x01,
        },
    // AudioControl INPUT Interface Descriptor
    .ac_input = {
        .head.bLength = sizeof (struct usb_ac_interface_input_descriptor),
        .head.bDescriptorType = USB_AUDIO_DT_CS_INTERFACE,
        .head.bDescriptorSubtype = USB_AUDIO_TYPE_INPUT_TERMINAL,
        .bTerminalID = 1,
        .wTerminalType = UAC_INPUT_TERMINAL_USB_STREAMING,
        .bAssocTerminal = 0,
        .bNrChannels = 2,
        .wChannelConfig = CHANNEL_CONFIG_LEFT_RIGHT_FRONT,
        .iChannelNames = 0x00, // not used
        .iTerminal = 0x00, // not used
    },
    // AudioControl OUTPUT Interface Descriptor
    .ac_output = {
        .head.bLength = sizeof (struct usb_ac_interface_output_descriptor),
        .head.bDescriptorType = USB_AUDIO_DT_CS_INTERFACE,
        .head.bDescriptorSubtype = USB_AUDIO_TYPE_OUTPUT_TERMINAL,
        .bTerminalID = 2,
        .wTerminalType = UAC_OUTPUT_TERMINAL_SPEAKER,
        .bAssocTerminal = 0,
        .bSourceID = 3,
        .iTerminal = 0,
    },
    // AudioControl FEATURE Interface Descriptor
    .feature_head = {
        .head.bLength = sizeof (struct usb_ac_interface_feature_head_descriptor) +
                        bmaCONTROLS_COUNT * sizeof (struct usb_ac_interface_feature_control_body_descriptor) +
                        sizeof (struct usb_ac_interface_feature_tail_descriptor),
        .head.bDescriptorType = USB_AUDIO_DT_CS_INTERFACE,
        .head.bDescriptorSubtype = USB_AUDIO_TYPE_FEATURE_UNIT,
        .bUnitID = 3,
        .bSourceID = 1,
        .bControlSize = 1,
    },
    .feature1 = {
        .bmaControl = 0x01,
    },
    .feature2 = {
        .bmaControl = 0x02,
    },
    .feature3 = {
        .bmaControl = 0x02,
    },
    .feature_tail = {
        .iFeature = 0,
    },
    .zero_ep = {
        .bLength = sizeof(struct usb_interface_descriptor),
        .bDescriptorType = USB_DT_INTERFACE,
        .bInterfaceNumber = 1,
        .bAlternateSetting = 0,
        .bNumEndpoints = 0,
        .bInterfaceClass = USB_CLASS_AUDIO,
        .bInterfaceSubClass = USB_AUDIO_SUBCLASS_AUDIOSTREAMING,
        .bInterfaceProtocol = 0,
        .iInterface = 0,
    },
    .stereo_ep = {
        .interface = {
            .bLength = sizeof(struct usb_interface_descriptor),
            .bDescriptorType = USB_DT_INTERFACE,
            .bInterfaceNumber = 1,
            .bAlternateSetting = 1,
            .bNumEndpoints = 1,
            .bInterfaceClass = USB_CLASS_AUDIO,
            .bInterfaceSubClass = USB_AUDIO_SUBCLASS_AUDIOSTREAMING,
            .bInterfaceProtocol = 0,
            .iInterface = 0,
        },
        .terminal = {
            .head.bLength = sizeof (struct usb_audio_streaming_descriptor),
            .head.bDescriptorType = USB_AUDIO_DT_CS_INTERFACE,
            .head.bDescriptorSubtype = USB_AUDIO_SUBCLASS_CONTROL,
            .bTerminalLink = 1,
            .bDelay = 0,
            .wFormatTag = STREAMING_PCM_FORMAT
        },
        .format_head = {
            .head.bLength = sizeof(struct usb_audio_streaming_format_descriptor_head) +
                            SUPPORTED_FREQS * sizeof (struct usb_audio_streaming_format_descriptor_freq),
            .head.bDescriptorType = USB_AUDIO_DT_CS_INTERFACE,
            .head.bDescriptorType = AUDIO_FORMAT_SUBTYPE,
            .bFormatType = AUDIO_FORMAT_TYPE_I,
            .bNrChannels = 2,
            .bSubframeSize = 2,
            .bBitResolution = 16,
            .bSamFreqType = 3,
        },
        .format_freqs = {{
             .byte0 = 0x7d,  // 32000 Hz
             .byte1 = 0x00,
             .byte2 = 0x00,},{
             .byte0 = 0xac,  // 44100 Hz
             .byte1 = 0x44,
             .byte2 = 0x00,}, {
             .byte0 = 0xbb,  // 48000 Hz
             .byte1 = 0x80,
             .byte2 = 0x00,},
        },
        .ep = {
            .bLength = sizeof(struct usb_standard_ac_interrupt_ep_descriptor),
            .bDescriptorType = USB_DT_ENDPOINT,
            .bEndpointAddress = 2 | EP_ADDRESS_OUT,
            .bmAttributes = EP_ATTR_SYNC_ADAPTIVE | EP_ATTR_TRANSFER_TYPE_ISOCHRONOUS,
            .wMaxPacketSize = 192,
            .bInterval = 1,
            .bRefresh = 0,
            .bSynchAddress = 0,
        },
        .audio_data = {
            .bLength = sizeof(struct usb_isochronous_audio_data_ep_descriptor),
            .bDescriptorType = USB_AUDIO_DT_CS_ENDPOINT,
            .bDescriptorSubtype = USB_AUDIO_TYPE_HEADER,
            .bmAttributes = EP_ISOCHRONOUS_AUDIO_DATA_NONE_CONTROL,
            .bLockDelayUnits = 2,
            .wLockDelay = 512,
        },
    },
};

const struct usb_interface_descriptor audio_control_iface[] = {{
    .bLength = USB_DT_INTERFACE_SIZE,
    .bDescriptorType = USB_DT_INTERFACE,
    .bInterfaceNumber = 0,
    .bAlternateSetting = 0,
    .bNumEndpoints = 0,
    .bInterfaceClass = USB_CLASS_AUDIO,
    .bInterfaceSubClass = USB_AUDIO_SUBCLASS_CONTROL,
    .bInterfaceProtocol = 0,
    .iInterface = 0,

    .extra = &audio_control_functional_descriptors,
    .extralen = sizeof(audio_control_functional_descriptors)
}};

const struct usb_interface ifaces[] = {
  {
    .num_altsetting = 1,
    .altsetting = audio_control_iface,
  }};

const struct usb_config_descriptor conf = {
    .bLength = USB_DT_CONFIGURATION_SIZE,
    .bDescriptorType = USB_DT_CONFIGURATION,
    .wTotalLength = sizeof(conf), /* can be anything, it is updated automatically
			                               when the usb code prepares the descriptor */
    .bNumInterfaces = 0x03,  // Default, Audio Streaming, HID. Total is 3
    .bConfigurationValue = 0x01,
    .iConfiguration = 0x00,
    .bmAttributes = 0x80, // bus powered
    .bMaxPower = 0x7f, // 250 mA

    .interface = ifaces, // TODO through PCM2707 descriptor
};



const char * usb_strings[] = {
    "EduTerra.PRO",
    "Crimea project",
    "unique"
};

static void ep_callback(usbd_device *usbd_dev, uint8_t ep)
{
  (void)ep;

  char buf[192];
  //int len =
  usbd_ep_read_packet(usbd_dev, 0x01, buf, 192);

  //gpio_toggle(GPIOC, GPIO12);
}

void usb_set_config_handler(usbd_device *usbd_dev, uint16_t wValue)
{
  (void)wValue;

  usbd_ep_setup(usbd_dev, 0x01, EP_ATTR_SYNC_ADAPTIVE | EP_ATTR_TRANSFER_TYPE_ISOCHRONOUS, 192, ep_callback);
}