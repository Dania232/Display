#include "../libs/io.hpp"


int main()
{

    const int W = 128;
    const int H = 64;
    std::vector<uint8_t> buffer(H * (W / 8));

    if (read_from_app(buffer) != 0)
    {
        std::cerr << "Not enough data!\n";
    }

    if (write_serial(buffer) != 0)
    {
        std::cerr << "tty open failed!\n";
    }

    return 0;
}