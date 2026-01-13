#pragma once
#include <vector>
#include <cstdint>


int remap_display_bits(std::vector<uint8_t> &vec, int H, int W)
{
    std::vector<uint8_t> buffer(H * (W / 8));

    for (int col_ind = 0; col_ind < W; col_ind++)
    {
        for (int row_ind = 0; row_ind < H; row_ind++)
        {
            bool val;
            val = vec[col_ind / 8 + row_ind * W / 8] & (1 << (col_ind % 8));
            buffer[row_ind / 8 + col_ind * H / 8] |= (val << (row_ind % 8));
        }
    }
    vec = buffer;
    return 0;
}