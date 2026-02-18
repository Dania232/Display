#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

typedef void (*timer_callback_t)(void);

void timer_init(void);
void timer_set_handler(timer_callback_t callback);
void timer_set_period(uint16_t ms);

void timer_start(void);
void timer_stop(void);  

#endif