
#include <iostream>
#include <vector>
#include <cstdint>
#include <unistd.h>

#include "../libs/make_monochrom.hpp"
#include "../libs/io.hpp"



int main(int argc, char *argv[])
{

    const int W = 128;
    const int H = 64;
    uint8_t threshold = 100;

    std::vector<uint8_t> resized(W * H);
    std::vector<uint8_t> formated(128 * 8, 0);
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << "image.png\n";
    }

    // flag check
    for (int i = 1; i < argc; i++)
    {
        if (std::string(argv[i]) == "-th" && i + 1 < argc)
        {
            threshold = std::stoi(argv[i + 1]);
            i++;
        }
    }

    if (threshold == 0)
    {
        threshold = 90;
    }
    //////

    char *scr_img = argv[1];
    reform(scr_img, formated, W, H, threshold);
    write_stdin(formated);
    return 0;
}