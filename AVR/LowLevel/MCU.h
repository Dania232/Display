#ifndef MY_MCU
#define MY_MCU
#define F_CPU 16000000UL
#include <avr/io.h>


void MCU_init(){
    DDRB |= (1 << DDB5);
}

void turn_diod_on(){
    PINB |= (1 << PINB5);
}

void turn_diod_off() {
    PORTB &= ~(1 << PORTB5);
}


#endif