#include <avr/io.h>
#include <util/delay.h>
#include "LowLevel/UART.h"
#include "Display/Display_ssd1306.hpp"
#include "LowLevel/MCU.h"

int main(void)
{
    uart_init();
    MCU_init();

    // uart_transmit('S');
    // //Display display;
    // while (1)
    // {
    //     char r = uart_receive();
    //     uart_transmit(r);

    //     turn_diod_on();
    //     _delay_ms(500);
    //     turn_diod_off();
    //     _delay_ms(500);
    //     turn_diod_on();
    //     _delay_ms(500);
    //     turn_diod_off();
    //     _delay_ms(500);
    // }

    Display display;
    uint16_t l = 1024;
    uint8_t pixs[l];
    display.clear();
    while (1)
    {
        for (int i = 0; i < l; i++)
        {
            int d = uart_receive();
            pixs[i] = d;
        }

        display.write_bytes((uint8_t *)pixs, l);

        turn_diod_on();
        _delay_ms(1000);
        turn_diod_off();
    }

    return 0;
}
