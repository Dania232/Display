#pragma once
#include <cstdint>
#include <vector>

class IDrawableCanvas
{

public:
    virtual uint16_t getWidth() { return 0; }

    virtual uint16_t getHight() { return 0; }

    virtual void getImg(std::vector<uint8_t> &img) const {}

    virtual void setPixel(uint16_t x, uint16_t y, bool color = true) {}
};