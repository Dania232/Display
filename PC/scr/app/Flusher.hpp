#pragma once
#include <vector>
#include <cstdint>
#include <atomic>
#include "IFlushFn.hpp"
#include "IRemapFn.hpp"
#include "ICanvasUpdateGetter.hpp"

class Flusher
{
private:
    std::atomic<bool> is_running{true};

public:
    ICanvasUpdateGetter *canvas;

    Flush_fn flush_fn;
    Remap_fn remap_fn;

    Flusher(ICanvasUpdateGetter *canvas, Flush_fn flush_fn, Remap_fn remap_fn)
        : canvas(canvas), flush_fn(flush_fn), remap_fn(remap_fn)
    {
    }

    void stop()
    {
        is_running = false;
    }

    void run()
    {
        while (is_running)
        {
            this->flushPicture();
        }

    }

    void flushPicture()
    {
        std::vector<uint8_t> img;
        this->canvas->getImg(img);
        remap_fn(img);
        flush_fn(img);
    }
};