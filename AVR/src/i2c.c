#include "../inc/i2c.h"
#include <avr/io.h>

#define F_CPU 16000000UL
#define I2C_TIMEOUT_COUNT 10000 // Busy-wait threshold

/**
 * @brief Waits for the TWI interrupt flag to be set with a timeout.
 * @return I2C_OK on success, I2C_TIMEOUT on failure.
 */
static i2c_status_t i2c_wait(void)
{
    volatile uint16_t timer = I2C_TIMEOUT_COUNT;
    while (!(TWCR0 & (1 << TWINT)))
    {
        if (--timer == 0)
            return I2C_TIMEOUT;
    }
    return I2C_OK;
}

/**
 * @brief Initializes the I2C peripheral.
 * @param freq_khz SCL clock frequency in kHz (e.g., 100 or 400).
 */
void i2c_init(uint16_t freq_khz)
{
    TWSR0 = 0; // Prescaler = 1
    // Bit rate formula from datasheet
    TWBR0 = (uint8_t)(((F_CPU / (freq_khz * 1000L)) - 16) / 2);
}

/**
 * @brief Sends I2C START condition and device address.
 * @param addr 7-bit device address.
 * @return I2C_OK, I2C_TIMEOUT, I2C_NACK, or I2C_BUS_ERROR.
 */
i2c_status_t i2c_begin(uint8_t addr)
{
    // 1. Send START condition
    TWCR0 = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    if (i2c_wait() != I2C_OK)
        return I2C_TIMEOUT;

    // Check status: 0x08 (Start) or 0x10 (Repeated Start)
    uint8_t status = TWSR0 & 0xF8;
    if (status != 0x08 && status != 0x10)
        return I2C_BUS_ERROR;

    // 2. Send device address + Write bit (0)
    TWDR0 = (addr << 1);
    TWCR0 = (1 << TWINT) | (1 << TWEN);
    if (i2c_wait() != I2C_OK)
        return I2C_TIMEOUT;

    // Check if device acknowledged (0x18 - ADDR_ACK)
    if ((TWSR0 & 0xF8) != 0x18)
        return I2C_NACK;

    return I2C_OK;
}

/**
 * @brief Transmits one byte of data over I2C.
 * @param data Byte to be sent.
 * @return I2C_OK, I2C_TIMEOUT, or I2C_NACK.
 */
i2c_status_t i2c_write(uint8_t data)
{
    TWDR0 = data;
    TWCR0 = (1 << TWINT) | (1 << TWEN);
    if (i2c_wait() != I2C_OK)
        return I2C_TIMEOUT;

    // Check if data was acknowledged (0x28 - DATA_ACK)
    if ((TWSR0 & 0xF8) != 0x28)
        return I2C_NACK;

    return I2C_OK;
}

/**
 * @brief Sends I2C STOP condition.
 */
void i2c_end(void)
{
    TWCR0 = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    // Wait for the STOP condition to be executed on the bus
    volatile uint16_t timer = I2C_TIMEOUT_COUNT;
    while (TWCR0 & (1 << TWSTO))
    {
        if (--timer == 0)
            break;
    }
}