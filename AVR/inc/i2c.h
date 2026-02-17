#ifndef I2C_H
#define I2C_H

#include <stdint.h>

typedef enum {
    I2C_OK = 0,
    I2C_TIMEOUT,
    I2C_NACK,
    I2C_BUS_ERROR
} i2c_status_t;

void i2c_init(uint16_t freq_khz);
i2c_status_t i2c_start(uint8_t addr);
i2c_status_t i2c_write(uint8_t data);
void i2c_stop(void);

#endif