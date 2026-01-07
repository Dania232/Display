#include <avr/io.h>
#include <util/delay.h>
#include "LowLevel/UART.h"
#include "Display/Display_ssd1306.hpp"

int main(void)
{
    uart_init();

    Display display;
    uint16_t l = 1024;
    uint8_t pixs[l];
    uart_transmit('S');
    for (int i = 0; i < l; i++)
    {
        int d = uart_receive();
        pixs[i] = d;
    }

    display.write_bytes((uint8_t *)pixs, l);

    return 0;
}
