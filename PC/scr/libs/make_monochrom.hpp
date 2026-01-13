#pragma once
#include <iostream>
#include <vector>
#include <cstdint>

#define STB_IMAGE_IMPLEMENTATION
#include "../../libs/stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../../libs/stb_image_resize2.h"



int make_monochrom(char *im, std::vector<uint8_t> &formated, int W, int H, int threshold)
{
    std::vector<uint8_t> resized(W * H);
    int w, h, channels;
    uint8_t *img = stbi_load(im, &w, &h, &channels, 1);
    if (!img)
    {
        std::cerr << "image load error\n";
        return 1;
    }

    stbir_resize_uint8_linear(
        img, w, h, 0,
        resized.data(), W, H, 0,
        STBIR_1CHANNEL);

    for (int row_ind = 0; row_ind < H; row_ind++)
    { // row
        for (int col_ind = 0; col_ind < W; col_ind++)
        { // column
            uint8_t pixel = resized[row_ind * W + col_ind];
            if (pixel > threshold)
            {
                int bit = col_ind % 8;
                formated[row_ind * (W / 8) + col_ind / 8] |= (1 << bit);
                // formated[]
            }
        }
    }
    stbi_image_free(img);
    return 0;
}