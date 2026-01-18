#include "../libs/io.hpp"
#include "../libs/flush.hpp"
#include "../../../Shared/Protocol.hpp"

int main()
{

    const int W = 128;
    const int H = 64;
    std::vector<uint8_t> buffer(H * (W / 8));

    if (read_from_app(buffer) != 0)
    {
        std::cerr << "Not enough data!\n";
    }
    Send_to_line_fn s;
    Recive_fr_line_fn r;
    s = [](uint8_t *data, uint16_t len)
    {
        std::vector<uint8_t> vec(data, data + len); // copy exactly len bytes
        write_to_display(vec);
        return 0;
    };

    r = [](uint8_t *data, uint16_t len)
    {
        std::vector<uint8_t> vec(len);
        read_fr_display(vec);                    // fill vector
        std::copy(vec.begin(), vec.end(), data); // copy back to raw pointer
        return 0;
    };

    
    init_protocol(s, r);

    send_packet(PacketType::PKT_IMAGE, buffer.data(), buffer.size());
    // if (write_to_display(buffer) != 0)
    // {
    //     std::cerr << "tty open failed!\n";
    // }

    return 0;
}