#include <iostream>
#include <thread>
#include <chrono>
#include "Canvas.hpp"
#include "ICanvasImg.hpp"
#include "Flusher.hpp"
#include "SLManager.hpp"
#include "UI/UIController.hpp"

#include "../../../Shared/Protocol.hpp"
#include "../libs/flush.hpp"
#include "../libs/DisplayConnection.hpp"
#include "../libs/remapimg.hpp"

int main()
{
    Monochrom128x64Canvas canvas;
    SLManager sl_manager(&canvas);
    UIController ui(canvas, sl_manager);

    
    /*
        DisplayConnection is created in every call.
    In the future, it would be better to refactor
    the Flusher class so that it accepts objects 
    rather than function references. This would 
    avoid creating DisplayConnection and Protocol
    objects for every call.
    */
    auto flush_fun = [](std::vector<uint8_t> &buf){
        DisplayConnection dc;
        Protocol pr(&dc);
        pr.send_packet(Protocol::PKT_IMAGE, buf.data(), buf.size());
        return 0;
    };


    auto remap_fun = [](std::vector<uint8_t> &vec)
    { remap_display_bits(vec, 64, 128); };
    Flusher flusher(&canvas, flush_fun, remap_fun);
    

    std::thread thread_for_fl(&Flusher::run, &flusher);
    ui.Run();

    flusher.stop();

    thread_for_fl.join();

    return 0;
}