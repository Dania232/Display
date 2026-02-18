#include "../inc/timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static volatile timer_callback_t current_handler = 0;
static volatile uint16_t target_count = 50;
static volatile uint16_t internal_ms_counter = 0;
static volatile uint8_t is_active = 0; 

void timer_init(void) {
    TCCR0A = (1 << WGM01); 
    TCCR0B = (1 << CS02) | (1 << CS00); 
    OCR0A = 156; 
    TIMSK0 |= (1 << OCIE0A);
}

void timer_set_handler(timer_callback_t callback) {
    current_handler = callback;
}

void timer_set_period(uint16_t ms) {
    uint8_t sreg = SREG;
    cli();
    target_count = (ms < 10) ? 1 : (ms / 10);
    internal_ms_counter = 0;
    SREG = sreg;
}

void timer_start(void) {
    is_active = 1;
}

void timer_stop(void) {
    is_active = 0;
    internal_ms_counter = 0;
}

ISR(TIMER0_COMPA_vect) {
    if (!is_active) return; 

    internal_ms_counter++;
    if (internal_ms_counter >= target_count) {
        internal_ms_counter = 0;
        if (current_handler) {
            current_handler();
        }
    }
}