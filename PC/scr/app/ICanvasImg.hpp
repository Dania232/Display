#pragma once
#include <vector>
#include <cstdint>

class ICanvasImg
{

public:
    virtual void setImg(const std::vector<uint8_t> &img) = 0;
    virtual void getImg(std::vector<uint8_t> &img) const = 0;
};