
/*
+--------+------+-------+---------+---------+
| SYNC   | TYPE | LEN   | PAYLOAD | CHECK   |
+--------+------+-------+---------+---------+
| 0xAA55 | 1 B  | 2 B   | N bytes | 1 B     |
*/
#include "ITransporLayer.hpp"

#ifdef __AVR__
#include <avr/io.h>
#include <util/delay.h>

#else
#include <cstdint>
#endif

class Protocol
{
public:
    enum PacketType : uint8_t
    {
        PKT_IMAGE = 0x01,
        PKT_CLEAR = 0x02,
        PKT_PING = 0x03
    };
    Protocol() {}
    Protocol(ITransporLayer *tl) : tl(tl) {}

    virtual int send_packet(PacketType packetType, uint8_t *data, uint16_t len)
    {
        uint8_t header[5];
        header[0] = 0xAA;
        header[1] = 0x55;
        header[2] = packetType;
        header[3] = len & 0xFF;
        header[4] = (len >> 8) & 0xFF;

        for (int i = 0; i < 5; ++i)
            tl->send_byte(header[i]);

        for (int i = 0; i < len; ++i)
            tl->send_byte(data[i]);

        uint8_t chk = checksum(&header[2], 3);
        chk ^= checksum(data, len);

        tl->send_byte(chk);

        uint8_t ack = 0;
        tl->recive_byte(ack);
        if (ack == 'c')
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }

    virtual int recive_packet(PacketType &packetType, uint8_t *data, uint16_t len)
    {
        uint8_t header[5];
        // uint8_t pack_data[len];
        uint8_t pack_chk;
        // recive_fr_line(header, 5);
        for (int i = 0; i < 5; i++)
        {
            tl->recive_byte(header[i]);
        }
        if (header[0] != 0xAA || header[1] != 0x55)
        {
            return -3;
        }
        uint16_t data_len = header[3] | (header[4] << 8);
        if (data_len != len)
        {
            return -1;
        }
        for (int i = 0; i < len; i++)
        {
            tl->recive_byte(data[i]);
        }
        tl->recive_byte(pack_chk);

        uint8_t chk = checksum(&header[2], 3);
        chk ^= checksum(data, data_len);

        if (chk != pack_chk)
        {
            return -2;
        }
        packetType = (PacketType)header[2];

        uint8_t ack = 'c';
        // send_to_line(&ack, 1);
        tl->send_byte(ack);
        return 0;
    }
    uint8_t checksum(const uint8_t *data, uint16_t len)
    {
        uint8_t c = 0;
        for (uint16_t i = 0; i < len; ++i)
            c ^= data[i];
        return c;
    }

protected:
    ITransporLayer *tl;
};

