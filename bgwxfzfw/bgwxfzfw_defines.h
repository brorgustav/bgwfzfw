#ifndef BGWXFZFW_DEFINES_H
#define BGWXFZFW_DEFINES_H

#include <furi_hal_gpio.h>

// Toggle this to switch between custom speaker pin (PA6) and default (PB8)
// Comment out to use default speaker pin, uncomment to use custom pin
#define BGWX_CUSTOM_SPEAKER

#define BGW_FURI_HAL_SPEAKER_TIMER      TIM16
#define BGW_FURI_HAL_SPEAKER_CHANNEL    LL_TIM_CHANNEL_CH1
#define BGW_FURI_HAL_SPEAKER_PRESCALER  500
#define BGW_FURI_HAL_SPEAKER_MAX_VOLUME 100

#define BGW_FURI_HAL_SPEAKER_GPIO_Port GPIOA
#define BGW_FURI_HAL_SPEAKER_Pin       LL_GPIO_PIN_6

// Custom speaker pin - defined in furi_hal_resources.c
extern const GpioPin bgw_gpio_speaker;


// #ifdef BGWX_CUSTOM_SPEAKER
// void furi_hal_speaker_release(void);
// #else
// void furi_hal_speaker_release(void);
// #endif  
// bool furi_hal_speaker_is_mine(void);

#endif  // BGWX_DEFINES_H

