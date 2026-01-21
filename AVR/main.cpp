#include <avr/io.h>
#include <util/delay.h>
#include "LowLevel/UART.h"
#include "Display/Display_ssd1306.hpp"

#include "../Shared/Protocol.hpp"
class TrL : public ITransporLayer
{
public:
    int send_byte(uint8_t byte) override
    {
        uart_transmit(byte);
        return 0;
    }
    int recive_byte(uint8_t &byte) override
    {
        // uart_receive(&byte);
        // return 0;
        return uart_receive_timeout(&byte, 100);
    }
private:
};

class Pr : public Protocol
{
    // int recive_packet(PacketType &packetType, uint8_t *data, uint16_t len) override {
public:
    Pr(ITransporLayer *tl, Display &d) : Protocol(tl), d(d)
    {
        reset();
    }
    // }

    int recive_packet(PacketType &packetType, uint8_t *data, uint16_t len) override
    {
        uint8_t byte;

        while (1)
        {
            if (tl->recive_byte(byte) != 0)
                return eror;

            switch (state)
            {
            case RX_SYNC_1:
                if (byte == 0xAA)
                    state = RX_SYNC_2;
                break;

            case RX_SYNC_2:
                if (byte == 0x55)
                    state = RX_TYPE;
                else
                    reset();
                break;

            case RX_TYPE:
                packetType = (PacketType)byte;
                checksum = byte;
                state = RX_LEN_L;
                break;

            case RX_LEN_L:
                pkt_len = byte;
                checksum ^= byte;
                state = RX_LEN_H;
                break;

            case RX_LEN_H:
                pkt_len |= (uint16_t)byte << 8;
                checksum ^= byte;

                if (pkt_len != len)
                {
                    reset();
                    return eror;
                }

                index = 0;
                state = (pkt_len > 0) ? RX_PAYLOAD : RX_CHECK;
                break;

            case RX_PAYLOAD:
                data[index++] = byte;
                checksum ^= byte;
                d.write_byte(byte);
                if (index >= pkt_len)
                    state = RX_CHECK;
                break;

            case RX_CHECK:
                if (checksum == byte)
                {
                    uint8_t ack = 'c';
                    tl->send_byte(ack); // ACK to PC
                    reset();
                    return 0;
                }
                else
                {
                    reset();
                    return eror;
                }
            }
        }
    }

private:
    enum Eror
    {
        eror = -1
    };

    enum State
    {
        RX_SYNC_1,
        RX_SYNC_2,
        RX_TYPE,
        RX_LEN_L,
        RX_LEN_H,
        RX_PAYLOAD,
        RX_CHECK
    };

    State state;
    uint16_t pkt_len;
    uint16_t index;
    uint8_t checksum;
    Display &d;
    void reset()
    {
        state = RX_SYNC_1;
        pkt_len = 0;
        index = 0;
        checksum = 0;
    }
};
int main(void)
{
    uart_init();

    Display display;
    display.clear();

    uint16_t l = 1024;
    uint8_t data[l];
    uint8_t ctr_byte = 'c';
    TrL transpor_layer;
    Pr protocol(&transpor_layer, display);

    while (1)
    {
        Protocol::PacketType p;
        // recive_packet(p, data, l);
        if (protocol.recive_packet(p, data, l) == 0){ 
            //display.clear();
        }
        //else {display.fill();}
            //display.write_bytes(data, l);
    }

    

    return 0;
}
