#pragma once
#include "ICanvasImg.hpp"
#include "UI/ISLManager.hpp"

class SLManager : public ISLManager
{

public:
    ICanvasImg *canvas;

    SLManager(ICanvasImg *canvas)
    {
        this->canvas = canvas;
    }

    void Save() override {};
    void Load() override {};
};