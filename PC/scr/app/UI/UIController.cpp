#include "UIController.hpp"
#include <FL/fl_draw.H>
#include <iostream>

// --- Виджет для отрисовки канваса ---
class CanvasWidget : public Fl_Widget
{
    IDrawableCanvas &canvas;
    int scale;

public:
    CanvasWidget(int X, int Y, int W, int H, IDrawableCanvas &c, int s = 4)
        : Fl_Widget(X, Y, W, H), canvas(c), scale(s) {}

    void draw() override
    {
        fl_color(FL_BLACK);
        fl_rectf(x(), y(), w(), h());

        fl_color(FL_WHITE);
        fl_rect(x(), y(), w(), h());

        std::vector<uint8_t> img;
        canvas.getImg(img);

        uint16_t width = canvas.getWidth();
        uint16_t height = canvas.getHight();

        if (img.empty())
            return;

        fl_color(FL_WHITE);
        for (int row = 0; row < height; ++row)
        {
            for (int col = 0; col < width; ++col)
            {
                int index = row * (width / 8) + (col / 8);
                if (index >= (int)img.size())
                    continue;

                if ((img[index] >> (col % 8)) & 1)
                {
                    fl_rectf(x() + col * scale, y() + row * scale, scale, scale);
                }
            }
        }
    }

    int handle(int event) override
    {
        if (event == FL_PUSH || event == FL_DRAG)
        {
            int mx = (Fl::event_x() - x()) / scale;
            int my = (Fl::event_y() - y()) / scale;

            if (mx >= 0 && mx < canvas.getWidth() && my >= 0 && my < canvas.getHight())
            {
                bool color = (Fl::event_button() == FL_LEFT_MOUSE);
                canvas.setPixel(mx, my, color);
                redraw();
            }
            return 1;
        }
        return Fl_Widget::handle(event);
    }
};


UIController::UIController(IDrawableCanvas &canvas, ISLManager &sl_manager)
    : Fl_Window(600, 400, "Display Controller"), canvas_(canvas), sl_manager_(sl_manager)
{
    const int SCALE = 4;
    int cw = canvas.getWidth() * SCALE;
    int ch = canvas.getHight() * SCALE;

    canvas_view_ = new CanvasWidget(10, 10, cw, ch, canvas_, SCALE);

    int bx = cw + 20;
    int by = 10;

    btn_clear_ = new Fl_Button(bx, by, 80, 25, "Clear");
    btn_clear_->callback(cb_clear, this);

    btn_save_ = new Fl_Button(bx, by + 35, 80, 25, "Save");
    btn_save_->callback(cb_save, this);

    btn_load_ = new Fl_Button(bx, by + 70, 80, 25, "Load");
    btn_load_->callback(cb_load, this);

    if (w() < bx + 100)
        size(bx + 100, (ch > 150 ? ch + 20 : 150));

    end();
}

UIController::~UIController()
{
}

void UIController::Run()
{
    show();
    Fl::run();
}

void UIController::cb_clear(Fl_Widget *w, void *data)
{
    UIController *ui = (UIController *)data;
    uint16_t W = ui->canvas_.getWidth();
    uint16_t H = ui->canvas_.getHight();

    for (int y = 0; y < H; ++y)
    {
        for (int x = 0; x < W; ++x)
        {
            ui->canvas_.setPixel(x, y, false);
        }
    }
    ui->canvas_view_->redraw();
}

void UIController::cb_save(Fl_Widget *w, void *data)
{
    std::cout << "Save pressed" << std::endl;
}

void UIController::cb_load(Fl_Widget *w, void *data)
{
    UIController *ui = (UIController *)data;
    std::cout << "Load pressed" << std::endl;
    ui->canvas_view_->redraw();
}


int UIController::Update()
{
    return Fl::check();
}

void UIController::RefreshCanvas()
{
    if (canvas_view_)
    {
        canvas_view_->redraw();
    }
}

