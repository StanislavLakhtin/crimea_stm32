//
// Created by sl on 26.06.17.
//

#ifndef CRIMEA_STM32_AUDIO_DESCRIPTORS_H
#define CRIMEA_STM32_AUDIO_DESCRIPTORS_H

#include <stdint.h>

/* Terminals - 2.2 Input Terminal Types */
#define UAC_INPUT_TERMINAL_USB_STREAMING  0x0101

#define UAC_INPUT_TERMINAL_UNDEFINED			0x200
#define UAC_INPUT_TERMINAL_MICROPHONE			0x201
#define UAC_INPUT_TERMINAL_DESKTOP_MICROPHONE		  0x202
#define UAC_INPUT_TERMINAL_PERSONAL_MICROPHONE		0x203
#define UAC_INPUT_TERMINAL_OMNI_DIR_MICROPHONE		0x204
#define UAC_INPUT_TERMINAL_MICROPHONE_ARRAY		    0x205
#define UAC_INPUT_TERMINAL_PROC_MICROPHONE_ARRAY	0x206

/* Terminals - 2.3 Output Terminal Types */
#define UAC_OUTPUT_TERMINAL_UNDEFINED			0x300
#define UAC_OUTPUT_TERMINAL_SPEAKER			  0x301
#define UAC_OUTPUT_TERMINAL_HEADPHONES		0x302
#define UAC_OUTPUT_TERMINAL_HEAD_MOUNTED_DISPLAY_AUDIO	0x303
#define UAC_OUTPUT_TERMINAL_DESKTOP_SPEAKER		0x304
#define UAC_OUTPUT_TERMINAL_ROOM_SPEAKER		  0x305
#define UAC_OUTPUT_TERMINAL_COMMUNICATION_SPEAKER	    0x306
#define UAC_OUTPUT_TERMINAL_LOW_FREQ_EFFECTS_SPEAKER	0x307

/* from PCM2707 descriptor */
#define CHANNEL_CONFIG_LEFT_RIGHT_FRONT 0x03

struct usb_interface_descriptor_header {
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint8_t bDescriptorSubtype;
} __attribute__((packed));

struct usb_ac_interface_input_descriptor {
  struct usb_interface_descriptor_header head;
  uint8_t bTerminalID;
  uint16_t wTerminalType;
  uint8_t bAssocTerminal;
  uint8_t bNrChannels;
  uint16_t wChannelConfig;
  uint8_t iChannelNames;    // unused
  uint8_t iTerminal;        // unused
} __attribute__((packed));

struct usb_ac_interface_output_descriptor {
  struct usb_interface_descriptor_header head;
  uint8_t bTerminalID;
  uint16_t wTerminalType;
  uint8_t bAssocTerminal;
  uint8_t bSourceID;
  uint8_t iTerminal;
} __attribute__((packed));

// ------------------- BEGIN FEATURE DESCRIPTOR ----------------------------

struct usb_ac_interface_feature_head_descriptor {
  struct usb_interface_descriptor_header head;
  uint8_t bUnitID;
  uint8_t bSourceID;
  uint8_t bControlSize;
} __attribute__((packed));

struct usb_ac_interface_feature_control_body_descriptor  {
  uint8_t bmaControl;
} __attribute__((packed));

struct usb_ac_interface_feature_tail_descriptor {
  uint8_t iFeature;
} __attribute__((packed));

// END FEATURE DESCRIPTOR

#define STREAMING_PCM_FORMAT 1

#define AUDIO_FORMAT_SUBTYPE 2
#define AUDIO_FORMAT_TYPE_I 1
// -------------------------- BEGIN AudioStreaming Interface Descriptor -----------------

/*
 *      AudioStreaming Interface Descriptor:
        bLength                 7
        bDescriptorType        36
        bDescriptorSubtype      1 (AS_GENERAL)
        bTerminalLink           1
        bDelay                  0 frames
        wFormatTag              1 PCM
 * */

struct usb_audio_streaming_descriptor {
  struct usb_interface_descriptor_header head;
  uint8_t bTerminalLink;
  uint8_t bDelay;
  uint8_t wFormatTag;
} __attribute__((packed));

/*      AudioStreaming Interface Descriptor:
        bLength                17
        bDescriptorType        36
        bDescriptorSubtype      2 (FORMAT_TYPE)
        bFormatType             1 (FORMAT_TYPE_I)
        bNrChannels             2
        bSubframeSize           2
        bBitResolution         16
        bSamFreqType            3 Discrete
        tSamFreq[ 0]        32000
        tSamFreq[ 1]        44100
        tSamFreq[ 2]        48000 */

struct usb_audio_streaming_format_descriptor_head {
  struct usb_interface_descriptor_header head;
  uint8_t bFormatType;
  uint8_t bNrChannels;
  uint8_t bSubframeSize;
  uint8_t bBitResolution;
  uint8_t bSamFreqType;
} __attribute__((packed));

struct usb_audio_streaming_format_descriptor_freq {
  uint8_t byte0;
  uint8_t byte1;
  uint8_t byte2;
} __attribute__((packed));

// END AudioStreaming Interface Descriptor

// -------------------- Table 4-17: Standard AC Interrupt Endpoint Descriptor

/*
Offset |  Field           | Size  | Value     | Description
0         bLength           1       Number      Size of this descriptor, in bytes: 9
1         bDescriptorType   1       Constant    ENDPOINT descriptor type
2         bEndpointAddress  1       Endpoint    The address of the endpoint on the USB
                                                device described by this descriptor. The
                                                address is encoded as follows:
                                                  D7:    Direction. 1 = IN endpoint
                                                  D6..4: Reserved, reset to zero
                                                  D3..0: The endpoint number, determined by the designer.
3         bmAttributes      1       Bit Map       D3..2: Synchronization type
                                                    00 = None
                                                  D1..0: Transfer type
                                                    11 = Interrupt
                                                  All other bits are reserved.
4         wMaxPacketSize    2       Number        Maximum packet size this endpoint is
                                                  capable of sending or receiving when this
                                                  configuration is selected. Used here to
                                                  pass 2-byte status information.
                                                  Set to 2 if not shared, set to the
                                                  appropriate value if shared.
6         bInterval         1       Number        Left to the designer’s discretion. A value
                                                  of 10 ms or more seems sufficient.
7         bRefresh          1       Number        Reset to 0.
8         bSynchAddress     1       Endpoint      Reset to 0.
*/

#define EP_ADDRESS_IN   0b10000000
#define EP_ADDRESS_OUT  0b00000000

#define EP_ATTR_SYNC_NONE        0b00000000
#define EP_ATTR_SYNC_ASYNC       0b00000100
#define EP_ATTR_SYNC_ADAPTIVE    0b00001000
#define EP_ATTR_SYNC_SYNC        0b00001100

#define EP_ATTR_TRANSFER_TYPE_CONTROL     0b00000000
#define EP_ATTR_TRANSFER_TYPE_ISOCHRONOUS 0b00000001
#define EP_ATTR_TRANSFER_TYPE_BULK        0b00000010
#define EP_ATTR_TRANSFER_TYPE_INTERRUPT   0b00000011


struct usb_standard_ac_interrupt_ep_descriptor {
  uint8_t   bLength;
  uint8_t   bDescriptorType;
  uint8_t   bEndpointAddress;
  uint8_t   bmAttributes;
  uint16_t  wMaxPacketSize;
  uint8_t   bInterval;
  uint8_t   bRefresh;
  uint8_t   bSynchAddress;
} __attribute__((packed));

/*
 * Table 4-21: Class-Specific AS Isochronous Audio Data Endpoint Descriptor
    Offset      | Field             | Size      | Value     | Description
    0             bLength             1           Number      Size of this descriptor, in bytes: 7
    1             bDescriptorType     1           Constant    CS_ENDPOINT descriptor type.
    2             bDescriptorSubtype  1           Constant    EP_GENERAL descriptor subtype.
    3             bmAttributes        1           Bit Map     A bit in the range D6..0 set to 1 indicates
                                                              that the mentioned Control is supported
                                                              by this endpoint.
                                                                D0:     Sampling Frequency
                                                                D1:     Pitch
                                                                D6..2:  Reserved
                                                              Bit D7 indicates a requirement for
                                                              wMaxPacketSize packets.
                                                                D7:     MaxPacketsOnly
    4             bLockDelayUnits     1           Number      Indicates the units used for the
                                                              wLockDelay field:
                                                                0:      Undefined
                                                                1:      Milliseconds
                                                                2:      Decoded PCM samples
                                                                3..255: Reserved
    5             wLockDelay         2            Number     Indicates the time it takes this endpoint
                                                             to reliably lock its internal clock recovery
                                                             circuitry. Units used depend on the value
                                                             of the bLockDelayUnits field.
 *
 * */

#define EP_ISOCHRONOUS_AUDIO_DATA_NONE_CONTROL        0b00000000
#define EP_ISOCHRONOUS_AUDIO_DATA_SAMPLING_FREQUENCY  0b00000001
#define EP_ISOCHRONOUS_AUDIO_DATA_PITCH               0b00000010
#define EP_ISOCHRONOUS_AUDIO_DATA_MAXPACKETSIZEONLY   0b10000000

#define EP_ISOCHRONOUS_AUDIO_DATA_LOCKDELAY_UNDEFINED 0x00
#define EP_ISOCHRONOUS_AUDIO_DATA_LOCKDELAY_MILLISECONDS 0x01
#define EP_ISOCHRONOUS_AUDIO_DATA_LOCKDELAY_DECODED_PCM_SAMPLES 0x02

struct usb_isochronous_audio_data_ep_descriptor {
  uint8_t   bLength;
  uint8_t   bDescriptorType;
  uint8_t   bDescriptorSubtype;
  uint8_t   bmAttributes;
  uint8_t   bLockDelayUnits;
  uint16_t  wLockDelay;
} __attribute__((packed));

#endif //CRIMEA_STM32_AUDIO_DESCRIPTORS_H
