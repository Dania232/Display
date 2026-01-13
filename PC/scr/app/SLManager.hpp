#pragma once
#include "ICanvasImg.hpp"


class SLManager
{

public:
    ICanvasImg *canvas;

    SLManager(ICanvasImg *canvas){
        this->canvas = canvas;
    }

    void Save();
    void Load();
};