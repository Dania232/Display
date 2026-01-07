#include <iostream>
#include <vector>
#include <cstdint>
#include <unistd.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"

int main()
{

    int w, h, channels;
    const int W = 128;
    const int H = 64;

    uint8_t threshold = 20;

    std::vector<uint8_t> resized(W * H);
    std::vector<uint8_t> formated(128 * 8, 0);

    uint8_t *img = stbi_load("image.png", &w, &h, &channels, 1);

    if (!img)
    {
        std::cerr << "image load error\n";
        return 1;
    }

    stbir_resize_uint8_linear(
        img, w, h, 0,
        resized.data(), W, H, 0,
        STBIR_1CHANNEL
    );

    // for (int y = 0; y < H; y++)
    // { // row
    //     for (int x = 0; x < W; x++)
    //     { // column
    //         uint8_t pixel = resized[y * W + x];
    //         if (pixel > threshold)
    //         {
    //             int bit = x % 8;
    //             formated[y * (W / 8) + x / 8] |= (1 << bit);
    //         }
    //     }
    // }

    for (int i = 0; i < formated.size(); i++){
        formated[i] = 0xFF;
        formated[i] = 0x0;
    }

    stbi_image_free(img);
    // std::cout << formated.size() << std::endl;
    write(1, formated.data(), formated.size());
    fflush(stdout);
    return 0;
}
