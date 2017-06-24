//
// Created by Stanislav Lakhtin on 11.06.17.
//

#include <crimea_dac.h>

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/exti.h>

void exti_setup(void) {
  nvic_enable_irq(NVIC_EXTI3_IRQ);
  exti_enable_request(EXTI3);
  exti_set_trigger(EXTI3, EXTI_TRIGGER_FALLING);
  exti_select_source(EXTI3, GPIOA);

  nvic_enable_irq(NVIC_EXTI2_IRQ);
  exti_enable_request(EXTI2);
  exti_set_trigger(EXTI2, EXTI_TRIGGER_FALLING);
  exti_select_source(EXTI2, GPIOA);
}

uint8_t reverse(uint8_t b) {
  b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
  b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
  b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
  return b;
}