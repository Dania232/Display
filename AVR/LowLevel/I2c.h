#ifndef MY_I2c
#define MY_I2c
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void i2c_init(unsigned long frq) // kHz
{
    TWSR0 = 0;
    TWBR0 = ( (F_CPU / (frq * 1000)) - 16 ) / 2; // 72~100kHz  12-400
}

uint8_t i2c_begin(uint8_t addr)
{
    // START
    TWCR0 = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR0 & (1 << TWINT)))
        ;

    // ADDRESS (write)
    TWDR0 = addr << 1;
    TWCR0 = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR0 & (1 << TWINT)))
        ;

    return (TWSR0 & 0xF8);
}

uint8_t i2c_write_byte(uint8_t data)
{
    TWDR0 = data;

    TWCR0 = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR0 & (1 << TWINT)))
        ;

    return (TWSR0 & 0xF8);
}

void i2c_end(void)
{
    TWCR0 = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}





#endif