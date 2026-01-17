#include "Canvas.hpp"
#include <algorithm>

Monochrom128x64Canvas::Monochrom128x64Canvas()
    : buffer(BUFFER_SIZE, 0)
{
}

void Monochrom128x64Canvas::setImg(const std::vector<uint8_t> &img)
{
    if (img.size() == BUFFER_SIZE)
    {
        buffer = img;
    }
}

void Monochrom128x64Canvas::getImg(std::vector<uint8_t> &img) const
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

    uint16_t index = y * (WIDTH / 8) + (x / 8);
    uint8_t bit = 1 << (x % 8); // LSB-first: leftmost pixel is rightmost in byte

    if (color)
        buffer[index] |= bit;
    else
        buffer[index] &= ~bit;
}


uint16_t Monochrom128x64Canvas::getWidth()
{
    return 128;
}
uint16_t Monochrom128x64Canvas::getHight()
{
    return 64;
}