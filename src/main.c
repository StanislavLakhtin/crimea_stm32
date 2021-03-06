//
// Created by sl on 18.02.17.
//

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/usb/audio.h>
#include <libopencm3/usb/usbd.h>

#include <atom.h>

#include <board_setup.h>

#include <ssd1306_i2c.h>
#include <wchar.h>
#include <crimea_usb.h>

uint8_t volumeControl = 5;
static uint8_t usbd_control_buffer[512];
//static char usb_serial_number[25];

#define STACK_SIZE      1024
#define THREAD_PRIO     42

static ATOM_TCB main_tcb;

static uint8_t thread_stacks[2][STACK_SIZE];

static void main_thread_func(uint32_t data);

usbd_device *usbDev;

void usb_wakeup_isr(void) {
  atomIntEnter();
  usbd_poll(usbDev);
  atomIntExit(0);
}

void usb_lp_can_rx0_isr(void) {
  atomIntEnter();
  usbd_poll(usbDev);
  atomIntExit(0);
}

int main(void) {

  int8_t osInitStatus;

  board_setup();
  encoder_setup(&volumeControl);

  /* Print message */
  //ssd1306_drawWCharStr(0, 0, white, wrapDisplay, L"Крым v2.");
  //ssd1306_refresh();
  usbDev = usbd_init(&stm32f107_usb_driver, &dev, &conf, usb_strings, 3, usbd_control_buffer,
                     sizeof(usbd_control_buffer));
  usbd_register_set_config_callback(usbDev, usb_set_config_handler);
  nvic_enable_irq(NVIC_USB_LP_CAN_RX0_IRQ);
  nvic_enable_irq(NVIC_USB_WAKEUP_IRQ);
  /* USB pull up*/
  usb_pullup();
  /**
 * Initialise OS and set up idle thread
 */
  osInitStatus = atomOSInit(&thread_stacks[0][0], STACK_SIZE, FALSE);

  if (osInitStatus == ATOM_OK) {
    /* Set up main thread */
    osInitStatus = atomThreadCreate(&main_tcb, THREAD_PRIO, main_thread_func, 0,
                              &thread_stacks[1][0], STACK_SIZE, TRUE);

    if (osInitStatus == ATOM_OK) {
      atomOSStart();
    }
  }

  while (1);

  /* We will never get here */
  return 0xff;
}

static void main_thread_func(uint32_t data __maybe_unused) {
  uint8_t vC = volumeControl;
  wchar_t buffer[40];

  /* Loop forever and blink the LED */
  while (1) {
    usbd_poll(usbDev);
    if (vC != volumeControl) {
      //ssd1306_clear();
      vC = volumeControl;
      swprintf(buffer, 40, L"%d", vC);
      //ssd1306_drawWCharStr(0, 8, white, nowrap, L"Volume:");
      //ssd1306_drawWCharStr(0, 16, white, nowrap, buffer);
      //ssd1306_refresh();
    }
    atomTimerDelay(SYSTEM_TICKS_PER_SEC);
  }
}