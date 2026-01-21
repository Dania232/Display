#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <vector>
#include "IDrawableCanvas.hpp"
#include "ISLManager.hpp"

class CanvasWidget;

class UIController : public Fl_Window
{
public:
    UIController(IDrawableCanvas &canvas, ISLManager &sl_manager);
    virtual ~UIController();

    int Update();
    void RefreshCanvas();
    void Run();

private:
    IDrawableCanvas &canvas_;
    ISLManager &sl_manager_;

    CanvasWidget *canvas_view_;
    Fl_Button *btn_clear_;
    Fl_Button *btn_save_;
    //Fl_Button *btn_load_;

    static void cb_clear(Fl_Widget *, void *);
    static void cb_save(Fl_Widget *, void *);
    static void cb_load(Fl_Widget *, void *);
};