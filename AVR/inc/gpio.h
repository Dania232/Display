#ifndef LED_H
#define LED_H

#include <avr/io.h>

// Макросы для удобной смены пина в будущем
#define LED_PORT PORTB
#define LED_DDR  DDRB
#define LED_PIN  PB5 // Встроенный светодиод на платах Arduino

// Прототипы функций
void led_init(void);
void led_on(void);
void led_off(void);
void led_toggle(void); // Переключить состояние (мигнуть)

#endif