#include "../libs/show.hpp"
#include "../libs/io.hpp"





int main()
{
    const int W = 128;
    const int H = 64;
    std::vector<uint8_t> buffer(H * (W / 8));

    read_from_app(buffer);

    print_bitmap(buffer, W, H);

    return 0;
}