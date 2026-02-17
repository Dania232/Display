#include "LowLevel/UART.h"
#include "Display/Display_ssd1306.hpp"

enum State
{
    RX_SYNC_1,
    RX_SYNC_2,
    RX_TYPE,
    RX_LEN_L,
    RX_LEN_H,
    RX_PAYLOAD,
    RX_CHECK
} state;
uint16_t pkt_len;
uint16_t index;
uint8_t checksum;
uint8_t packetType;

Display display;
enum Eror
{
    eror = -1
};
int next_step(uint16_t len, Display &d, uint8_t byte);
void reset();
void byte_recive_handler(uint8_t byte){
    next_step(1024, display, byte);
}
int main(void)
{
    uart_init();

    
    display.clear();
    reset();
    byte_transmited_handler = byte_recive_handler;
    while (1)
    {
        //next_step(1024, display);
    }

    return 0;
}


void reset()
{
    state = RX_SYNC_1;
    pkt_len = 0;
    index = 0;
    checksum = 0;
}


int next_step(uint16_t len, Display &d, uint8_t byte)
{
    //uint8_t byte;

    // if (uart_receive_timeout(&byte, 10000) != 0){
    //     char *message = "timeout\n";
    //     uart_transmit_bytes((uint8_t *)message, 8);
    //     return eror;
    // }
    //uart_receive(&byte);
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
        packetType = byte;
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
        index++;
        checksum ^= byte;
        d.write_byte(byte);
        if (index >= pkt_len)
            state = RX_CHECK;
        break;

    case RX_CHECK:
        if (checksum == byte)
        {
            uint8_t ack = 'c';
            uart_transmit(ack); // ACK to PC
            reset();
            return 0;
        }
        else
        {
            reset();
            return eror;
        }
    }

    return 0;
}