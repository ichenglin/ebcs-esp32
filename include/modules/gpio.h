#ifndef GPIO_MODULE_H
#define GPIO_MODULE_H

#include "constants/gpio.h"

typedef void (*gpio_callback_t)(gpio_num_t pin, gpio_level_t level);

void gpio_init    (gpio_num_t      pin);
void gpio_event   (gpio_num_t      pin);
void gpio_listener(gpio_callback_t callback);

#endif // GPIO_MODULE_H
