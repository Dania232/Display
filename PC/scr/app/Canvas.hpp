#pragma once
#include "ICanvasUpdateGetter.hpp"
#include "ICanvasImg.hpp"
#include "UI/IDrawableCanvas.hpp"
#include <vector>
#include <cstdint>


class Monochrom128x64Canvas : public ICanvasImg, public ICanvasUpdateGetter, public IDrawableCanvas
{
public:
    static constexpr uint16_t WIDTH  = 128;
    static constexpr uint16_t HEIGHT = 64;
    static constexpr uint16_t PAGES = HEIGHT / 8; 
    static constexpr uint16_t BUFFER_SIZE = (WIDTH * HEIGHT) / 8;

    Monochrom128x64Canvas();

    uint16_t getWidth() override;
    uint16_t getHight() override;

    // ICanvasImg interface
    void setImg(const std::vector<uint8_t>& img) override;
    void getImg(std::vector<uint8_t>& img) const override;

    // Drawing helpers
    void clear();
    void fill();
    void setPixel(uint16_t x, uint16_t y, bool color = true);

private:
    std::vector<uint8_t> buffer;
};
