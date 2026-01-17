#include <iostream>
#include <thread>
#include <chrono>
#include "Canvas.hpp"
#include "ICanvasImg.hpp"
#include "Flusher.hpp"
#include "SLManager.hpp"
#include "UI/UIController.hpp"

#include "../libs/flush.hpp"
#include "../libs/remapimg.hpp"

int main()
{

    Monochrom128x64Canvas canvas;

    SLManager sl_manager(&canvas);
    auto remap_fun = [](std::vector<uint8_t> &vec)
    { remap_display_bits(vec, 64, 128); };
    Flusher flusher(&canvas, write_to_display, remap_fun);
    UIController ui(canvas, sl_manager);

    std::thread thread_for_fl(&Flusher::run, &flusher);
    ui.Run();

    flusher.stop();

    thread_for_fl.join();

    // canvas.setPixel(127, 63, true);

    return 0;
}