//cat /dev/ttyUSB0
// stty -F /dev/ttyUSB0 9600 raw -echo
// stty -F /dev/ttyUSB0 -hupcl
#ifndef MY_UART
#define MY_UART

#include <stdint.h>
#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)

void uart_init(void (*_byte_recived_callback)(uint8_t));

void uart_receive_blocking(uint8_t *data);
int uart_receive_timeout(uint8_t *out, uint32_t timeout_cycles);
int uart_receive_bytes_blocking(uint8_t *data, uint16_t len);

void uart_transmit(uint8_t data);
int uart_transmit_bytes(uint8_t *data, uint16_t len);



#endif