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

struct usb_ac_interface_descriptor_header {
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint8_t bDescriptorSubtype;
} __attribute__((packed));

struct usb_ac_interface_input_descriptor {
  struct usb_ac_interface_descriptor_header head;
  uint8_t bTerminalID;
  uint16_t wTerminalType;
  uint8_t bAssocTerminal;
  uint8_t bNrChannels;
  uint16_t wChannelConfig;
  uint8_t iChannelNames;    // unused
  uint8_t iTerminal;        // unused
} __attribute__((packed));

struct usb_ac_interface_output_descriptor {
  struct usb_ac_interface_descriptor_header head;
  uint8_t bTerminalID;
  uint16_t wTerminalType;
  uint8_t bAssocTerminal;
  uint8_t bSourceID;
  uint8_t iTerminal;
} __attribute__((packed));

// BEGIN FEATURE DESCRIPTOR

struct usb_ac_interface_feature_head_descriptor {
  struct usb_ac_interface_descriptor_header head;
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

#endif //CRIMEA_STM32_AUDIO_DESCRIPTORS_H
