#include <iostream>
#include "Canvas.hpp"
#include "ICanvasImg.hpp"
#include "Flusher.hpp"

#include "../libs/flush.hpp"
#include "../libs/remapimg.hpp"

int main()
{

    Monochrom128x64Canvas canvas;

    Flusher flusher(&canvas, write_to_display, [](std::vector<uint8_t> &vec){remap_display_bits(vec, 64, 128);});

    canvas.clear();

    canvas.setPixel(0, 40, true);
    // canvas.setPixel(1, 1, true);
    // canvas.setPixel(1, 2, true);
    // canvas.setPixel(2, 3, true);
    // canvas.setPixel(2, 4, true);
    // canvas.setPixel(0, 5, true);
    // canvas.setPixel(0, 6, true);
    flusher.flushPicture();

    return 0;
}