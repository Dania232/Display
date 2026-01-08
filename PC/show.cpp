#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstdint>

int main()
{
    const int W = 128;
    const int H = 64;
    std::vector<uint8_t> buffer(H * (W / 8));

    // read all bytes from stdin
    size_t total_read = 0;
    while (total_read < buffer.size())
    {
        ssize_t n = read(0, buffer.data() + total_read, buffer.size() - total_read);
        if (n <= 0)
            break; // EOF or error
        total_read += n;
    }

    if (total_read != buffer.size())
    {
        std::cerr << "Not enough data!\n";
        return 1;
    }

    // print bitmap to terminal
    for (int y = 0; y < H; y++)
    {
        for (int x_byte = 0; x_byte < W / 8; x_byte++)
        {
            uint8_t b = buffer[y * (W / 8) + x_byte];
            for (int bit = 0; bit < 8; bit++)
            {
                bool pixel = (b >> bit) & 1;
                std::cout << (pixel ? "#" : " "); // "#" = on, " " = off
            }
        }
        std::cout << "\n";
    }

    return 0;
}
