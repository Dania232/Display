#include "../libs/remapimg.hpp"
#include "../libs/io.hpp"




int main(){

    const int W = 128;
    const int H = 64;
    std::vector<uint8_t> buffer(H * (W / 8));

    if (read_stdin(buffer) != 0)
    {
        std::cerr << "Not enough data!\n";
    }

    remap_display_bits(buffer, H, W);

    write_stdin(buffer);

    return 0;
}