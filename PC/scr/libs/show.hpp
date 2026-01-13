#pragma once
#include <iostream>
#include <vector>
#include <cstdint>




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