#pragma once
#include <cstdint>
#include <vector>




class IDrawableCanvas{

public:
    //virtual uint16_t getWidth();
    //virtual uint16_t getHight();
    virtual ~IDrawableCanvas() = default;
    virtual void getImg(std::vector<uint8_t>& img);

    virtual void setPixel(uint16_t x, uint16_t y, bool color = true);
};