#include "../Shared/ITransporLayer.hpp"
#include "LowLevel/UART.h"

class TransportLayer : public ITransporLayer
{
public:
    int send_byte(uint8_t byte) override
    {
        uart_transmit(byte);
        return 0;
    }
    int recive_byte(uint8_t &byte) override
    {
        return uart_receive_timeout(&byte, 10000);
    }

private:
};