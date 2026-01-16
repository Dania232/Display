
/*
    unused for now
*/
#pragma once
#include <vector>
#include <cstdint>

class ICanvasUpdateGetter
{
public:
    virtual void setImg(const std::vector<uint8_t> &img);
    virtual void getImg(std::vector<uint8_t> &img) const;
};