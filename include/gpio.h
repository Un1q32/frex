#ifndef _FREX_GPIO_H_
#define _FREX_GPIO_H_

#include <peripherals/gpio.h>

typedef enum _GpioFunc {
  GFInput = 0,
  GFOutput = 1,
  GFAlt0 = 4,
  GFAlt1 = 5,
  GFAlt2 = 6,
  GFAlt3 = 7,
  GFAlt4 = 3,
  GFAlt5 = 2
} GpioFunc;

extern void gpio_pin_set_func(uint8_t, GpioFunc);
extern void gpio_pin_enable(uint8_t);

#endif
