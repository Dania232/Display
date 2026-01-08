#include <iostream>
#include <vector>
#include <cstdint>
#include <unistd.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"

int main(int argc, char *argv[])
{

    int w, h, channels;
    const int W = 128;
    const int H = 64;

    uint8_t threshold = 100;

    std::vector<uint8_t> resized(W * H);
    std::vector<uint8_t> formated(128 * 8, 0);
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << "image.png\n";
    }
    uint8_t *img = stbi_load(argv[1], &w, &h, &channels, 1);

    if (!img)
    {
        std::cerr << "image load error\n";
        return 1;
    }


    // flag check 


    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-th" && i + 1 < argc) {
            threshold = std::stoi(argv[i + 1]);
            i++;
        }
    }

    if (threshold == 0){
        threshold = 90;
    }

    //////


    stbir_resize_uint8_linear(
        img, w, h, 0,
        resized.data(), W, H, 0,
        STBIR_1CHANNEL
    );

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

    // for (int i = 0; i < formated.size(); i++){
    //     formated[i] = 0xFF;
    //     //formated[i] = 0x0;
    // }

    stbi_image_free(img);
    // std::cout << formated.size() << std::endl;
    write(1, formated.data(), formated.size());
    fflush(stdout);
    return 0;
}
