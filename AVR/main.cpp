#include <avr/io.h>
#include <util/delay.h>
#include "LowLevel/UART.h"
#include "Display/Display_ssd1306.hpp"
#include "LowLevel/MCU.h"

int main(void)
{
    uart_init();
    MCU_init();

    Display display;
    uint16_t l = 1024;
    uint8_t ctr_byte = 'c';
    display.clear();

    while (1)
    {
        for (int i = 0; i < l; i++)
        {
            display.write_byte(uart_receive());
        }
        uart_transmit(ctr_byte);
    }

    return 0;
}
