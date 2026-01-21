#include "../libs/io.hpp"
#include "../libs/flush.hpp"
#include "../libs/DisplayConnection.hpp"
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
    
    DisplayConnection dc;
    Protocol pr(&dc);

    pr.send_packet(Protocol::PacketType::PKT_IMAGE, buffer.data(), buffer.size());
    return 0;
}