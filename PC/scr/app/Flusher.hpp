#pragma once
#include <vector>
#include <cstdint>

#include "IFlushFn.hpp"
#include "IRemapFn.hpp"
#include "ICanvasUpdateGetter.hpp"

class Flusher
{

public:
    ICanvasUpdateGetter *canvas;

    Flush_fn flush_fn;
    Remap_fn remap_fn;

    Flusher(ICanvasUpdateGetter *canvas, Flush_fn flush_fn, Remap_fn remap_fn)
        : canvas(canvas), flush_fn(flush_fn), remap_fn(remap_fn)
    {
    }

    void flushPicture()
    {
        std::vector<uint8_t> img;
        this->canvas->getImg(img);
        remap_fn(img);
        flush_fn(img);
    }
};