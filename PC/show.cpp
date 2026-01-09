#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstdint>

int read_stdin(std::vector<uint8_t> &buf);
void print_bitmap(std::vector<uint8_t> &buffer, int W, int H);

int main()
{
    const int W = 128;
    const int H = 64;
    std::vector<uint8_t> buffer(H * (W / 8));

    read_stdin(buffer);

    print_bitmap(buffer, W, H);

    return 0;
}

int read_stdin(std::vector<uint8_t> &buf)
{
    size_t total_read = 0;
    while (total_read < buf.size())
    {
        ssize_t n = read(0, buf.data() + total_read, buf.size() - total_read);
        if (n <= 0)
            break; // EOF or error
        total_read += n;
    }

    if (total_read != buf.size())
    {
        // std::cerr << "Not enough data!\n";
        return 1;
    }

    return 0;
}

void print_bitmap(std::vector<uint8_t> &buffer, int W, int H)
{
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
}