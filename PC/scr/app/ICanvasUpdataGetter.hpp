
/*
    unused for now
*/
#pragma once
#include <vector>
#include <cstdint>

class ICanvasUpdataGetter
{
public:
    struct updatedPixelInf
    {
        uint8_t x;
        uint8_t y;
        bool val;
    };

    updatedPixelInf getUpdatedPixs();
};