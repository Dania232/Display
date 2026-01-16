#pragma once
#include <vector>
#include <cstdint>

class ICanvasImg
{

public:
    virtual void setImg(const std::vector<uint8_t> &img){};
    virtual void getImg(std::vector<uint8_t> &img) const{};
};