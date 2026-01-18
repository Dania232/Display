#include <avr/io.h>
#include <util/delay.h>
#include "LowLevel/UART.h"
#include "Display/Display_ssd1306.hpp"

#include "../Shared/Protocol.hpp"

int main(void)
{
    uart_init();

    Display display;
    display.clear();

    uint16_t l = 1024;
    uint8_t data[l];
    uint8_t ctr_byte = 'c';


    Send_to_line_fn s = uart_transmit_bytes;
    Recive_fr_line_fn r = uart_receive_bytes;

    init_protocol(s, r);

    while (1)
    {
        PacketType p;
        recive_packet(p, data, l);
        display.write_bytes(data, l);
    }

    // while (1)
    // {
    //     for (int i = 0; i < l; i++)
    //     {
    //         display.write_byte(uart_receive());
    //     }
    //     uart_transmit(ctr_byte);
    // }

    return 0;
}
