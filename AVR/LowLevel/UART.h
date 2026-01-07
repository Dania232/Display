//cat /dev/ttyUSB0
// stty -F /dev/ttyUSB0 9600 raw -echo

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

char uart_receive(void)
{
    // Wait for data to be in the receive buffer (RXC0 flag is set)
    while (!(UCSR0A & (1 << RXC0)))
        ;

    // Return the data from the UDR0 buffer
    return UDR0;
}

void uart_transmit(uint8_t data)
{
    // Wait for the transmit buffer to be empty (UDRE0 flag is set)
    while (!(UCSR0A & (1 << UDRE0)))
        ;

    // Put the data into the UDR0 buffer, which sends it
    UDR0 = data; //(*(volatile uint8_t *)(0xC6))
}

#endif