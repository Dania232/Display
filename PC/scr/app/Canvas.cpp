#include "Canvas.hpp"
#include <algorithm>

Monochrom128x64Canvas::Monochrom128x64Canvas()
    : buffer(BUFFER_SIZE, 0)
{
}

void Monochrom128x64Canvas::setImg(const std::vector<uint8_t>& img)
{
    if (img.size() == BUFFER_SIZE)
    {
        buffer = img;
    }
}

void Monochrom128x64Canvas::getImg(std::vector<uint8_t>& img) const
{
    img = buffer;
}

void Monochrom128x64Canvas::clear()
{
    std::fill(buffer.begin(), buffer.end(), 0x00);
}

void Monochrom128x64Canvas::fill()
{
    std::fill(buffer.begin(), buffer.end(), 0xFF);
}

void Monochrom128x64Canvas::setPixel(uint16_t x, uint16_t y, bool color)
{
    if (x >= WIDTH || y >= HEIGHT)
        return;

    //uint16_t index = ;
    //uint8_t bit = 1 << (y % 8);

    if (color){
        //buffer[index] |= bit;
        int bit = x % 8;
        buffer[y * (128 / 8) + x / 8] |= (1 << bit);
    }
    else{
        int bit = x % 8;
        buffer[y * (128 / 8) + x / 8] &= ~(1 << bit);
    }
        //buffer[index] &= ~bit;
}

void Monochrom128x64Canvas::invertPixel(uint16_t x, uint16_t y)
{
    if (x >= WIDTH || y >= HEIGHT)
        return;

    uint16_t index = indexForPixel(x, y);
    buffer[index] ^= (1 << (y % 8));
}

uint16_t Monochrom128x64Canvas::indexForPixel(uint16_t x, uint16_t y) const
{
    // Column-major layout:
    // Each column has 8 pages (64/8)
    return y / 8 + x;
}
