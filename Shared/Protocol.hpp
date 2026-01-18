
/*
+--------+------+-------+---------+---------+
| SYNC   | TYPE | LEN   | PAYLOAD | CHECK   |
+--------+------+-------+---------+---------+
| 0xAA55 | 1 B  | 2 B   | N bytes | 1 B     |
*/

#ifdef __AVR__
#include <avr/io.h>
#include <util/delay.h>

#else
#include <cstdint>
#endif

typedef int (*Send_to_line_fn)(uint8_t *data, uint16_t len);
typedef int (*Recive_fr_line_fn)(uint8_t *data, uint16_t len);

Send_to_line_fn send_to_line;
Recive_fr_line_fn recive_fr_line;

enum PacketType : uint8_t
{
    PKT_IMAGE = 0x01,
    PKT_CLEAR = 0x02,
    PKT_PING = 0x03
};

uint8_t checksum(const uint8_t *data, uint16_t len);

void init_protocol(Send_to_line_fn _send_to_line, Recive_fr_line_fn _recive_fr_line)
{
    send_to_line = _send_to_line;
    recive_fr_line = _recive_fr_line;
}

int send_packet(PacketType packetType, uint8_t *data, uint16_t len)
{
    uint8_t header[5];
    header[0] = 0xAA;
    header[1] = 0x55;
    header[2] = packetType;
    header[3] = len & 0xFF;
    header[4] = (len >> 8) & 0xFF;

    send_to_line(header, 5);
    send_to_line(data, len);

    uint8_t chk = checksum(&header[2], 3);
    chk ^= checksum(data, len);

    send_to_line(&chk, 1);

    uint8_t ack = 0;
    recive_fr_line(&ack, 1);
    if (ack == 'c')
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int recive_packet(PacketType &packetType, uint8_t *data, uint16_t len)
{
    uint8_t header[5];
    //uint8_t pack_data[len];
    uint8_t pack_chk;
    recive_fr_line(header, 5);
    if (header[0] != 0xAA || header[1] != 0x55){
        return -3;
    }
    uint16_t data_len = header[3] | (header[4] << 8);
    if (data_len != len){
        return -1;
    }
    recive_fr_line(data, len);
    recive_fr_line(&pack_chk, 1);

    uint8_t chk = checksum(&header[2], 3);
    chk ^= checksum(data, data_len);

    if(chk != pack_chk){
        return -2;
    }
    packetType = (PacketType)header[2];

    uint8_t ack = 'c';
    send_to_line(&ack, 1);

    return 0;
}

uint8_t checksum(const uint8_t *data, uint16_t len)
{
    uint8_t c = 0;
    for (uint16_t i = 0; i < len; ++i)
        c ^= data[i];
    return c;
}