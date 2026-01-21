//cat /dev/ttyUSB0
// stty -F /dev/ttyUSB0 9600 raw -echo
// stty -F /dev/ttyUSB0 -hupcl

#ifndef MY_UART
#define MY_UART

#include <avr/io.h>
#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)

void uart_init(void)
{
    // 1. Set the Baud Rate
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8); // Set high byte
    UBRR0L = (uint8_t)(UBRR_VALUE);      // Set low byte

    // 2. Set Frame Format (8N1)
    // UCSR0C is 8-bit data (UCSZ01, UCSZ00) by default,
    // 1 stop bit (USBS0) by default,
    // and no parity (UPM01, UPM00) by default.
    // We can explicitly set 8-bit mode:
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

    // 3. Enable Transmitter and Receiver
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
}

void uart_receive(uint8_t *data)
{
    // Wait for data to be in the receive buffer (RXC0 flag is set)
    while (!(UCSR0A & (1 << RXC0)))
        ;

    // Return the data from the UDR0 buffer
    *data = UDR0;
}

void uart_transmit(uint8_t data)
{
    // Wait for the transmit buffer to be empty (UDRE0 flag is set)
    while (!(UCSR0A & (1 << UDRE0)))
        ;

    // Put the data into the UDR0 buffer, which sends it
    UDR0 = data; //(*(volatile uint8_t *)(0xC6))
}

int uart_transmit_bytes(uint8_t *data, uint16_t len){
    uint8_t *cur_ptr = data;
    while (cur_ptr != (data + len))
    {
        uart_transmit(*cur_ptr);
        cur_ptr++;
    }
    return 0;
}

int uart_receive_bytes(uint8_t *data, uint16_t len){
    uint8_t *cur_ptr = data;
    while (cur_ptr != (data + len))
    {
        uart_receive(cur_ptr);
        cur_ptr++;
    }
    return 0;
}

int uart_receive_timeout(uint8_t *out, uint32_t timeout_cycles)
{
    while (timeout_cycles--) {
        if (UCSR0A & (1 << RXC0)) {
            *out = UDR0;
            return 0; // OK
        }
    }
    return -1; // TIMEOUT
}



#endif