#include "LowLevel/UART.h"
#include "Display/Display_ssd1306.hpp"
#include "../Shared/Protocol.hpp"
#include "TransportLayer.hpp"
#include "ProtocolImpl.hpp"

int main(void)
{
    uart_init();

    Display display;
    display.clear();

    uint16_t l = 1024;
    TransportLayer transpor_layer;
    ProtocolImpl protocol(&transpor_layer, display);

    while (1)
    {
        Protocol::PacketType p;


        /*
            Protocol::recive_packet assumes that the second parameter 
        is an array to which the data will be 
        written (which can then be sent to the 
        display). However, since this CPU has 
        limited memory, and to make rendering 
        smoother, sending to the display occurs 
        within the protocol implementation.
        */
        if (protocol.recive_packet(p, nullptr, l) == 0)
        {
        }
    }

    return 0;
}
