#pragma once
#include <vector>
#include <cstdint>

#include "IFlushFn.hpp"
#include "IRemapFn.hpp"
#include "ICanvasImg.hpp"

class Flusher
{

public:
    ICanvasImg *canvas;

    Flush_fn flush_fn;
    Remap_fn remap_fn;

    Flusher(ICanvasImg *canvas, Flush_fn flush_fn, Remap_fn remap_fn)
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