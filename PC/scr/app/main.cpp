#include <iostream>
#include "Canvas.hpp"
#include "ICanvasImg.hpp"
#include "Flusher.hpp"


#include "../libs/flush.hpp"
#include "../libs/remapimg.hpp"

int main()
{

    Monochrom128x64Canvas canvas;

    
    auto remap_fun = [](std::vector<uint8_t> &vec){remap_display_bits(vec, 64, 128);};
    Flusher flusher(&canvas, write_to_display, remap_fun);
    //SLManager sl_manager(&canvas);
    //UIController c(canvas, sl_manager);



    canvas.clear();

    canvas.setPixel(127, 10, true);
    flusher.flushPicture();

    return 0;
}