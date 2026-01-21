#ifndef ITRANSPORT_LAYER
#define ITRANSPORT_LAYER
#ifdef __AVR__
#include <avr/io.h>
#include <util/delay.h>

#else
#include <cstdint>
#endif




class ITransporLayer
{
public:
    virtual int send_byte(uint8_t byte) = 0;
    virtual int recive_byte(uint8_t &byte) = 0;
};

#endif