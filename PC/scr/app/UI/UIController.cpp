#include "UIController.hpp"
#include <FL/fl_draw.H>
#include <iostream>
#include <fstream>

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

    //btn_load_ = new Fl_Button(bx, by + 70, 80, 25, "Load");
    //btn_load_->callback(cb_load, this);

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
    UIController *ui = (UIController *)data;

    std::vector<uint8_t> img;
    ui->canvas_.getImg(img); // Получаем данные

    // ПРОВЕРКА ФОРМАТА 128x64
    // 128 * 64 бит = 8192 бит = 1024 байта
    const size_t REQUIRED_SIZE = 1024;

    if (img.size() != REQUIRED_SIZE)
    {
        std::cerr << "Error: Canvas buffer size is " << img.size()
                  << " bytes, but 1024 bytes (128x64) is required." << std::endl;
        // Можно попробовать сделать resize, если это допустимо:
        // img.resize(REQUIRED_SIZE, 0);
        return;
    }

    std::ofstream out("canvas.bin", std::ios::binary);
    if (!out)
    {
        std::cerr << "Failed to open file for saving!" << std::endl;
        return;
    }

    out.write(reinterpret_cast<const char *>(img.data()), img.size());
    out.close();

    std::cout << "Saved 128x64 image (1024 bytes) to canvas.bin" << std::endl;
}

// void UIController::cb_load(Fl_Widget *w, void *data)
// {
//     UIController *ui = (UIController *)data;
//     const size_t REQUIRED_SIZE = 1024; // 128 * 64 / 8

//     std::cout << "[Load] Opening canvas.bin..." << std::endl;

//     // 1. Открываем файл. Важно: ios::ate ставит курсор в конец, чтобы проверить размер
//     std::ifstream in("canvas.bin", std::ios::binary | std::ios::ate);

//     if (!in.is_open())
//     {
//         std::cerr << "[Error] File 'canvas.bin' not found!" << std::endl;
//         return;
//     }

//     // 2. Проверяем размер файла
//     std::streamsize fileSize = in.tellg();
//     if (fileSize != REQUIRED_SIZE)
//     {
//         std::cerr << "[Error] File size mismatch! Got " << fileSize
//                   << " bytes, expected " << REQUIRED_SIZE << " bytes." << std::endl;
//         in.close();
//         return;
//     }

//     // 3. Возвращаемся в начало и читаем
//     in.seekg(0, std::ios::beg);

//     std::vector<uint8_t> img(REQUIRED_SIZE);

//     // Используем read(), а не итераторы, это надежнее для бинарников
//     if (in.read(reinterpret_cast<char *>(img.data()), REQUIRED_SIZE))
//     {
//         // 4. Загружаем в канвас
//         ui->canvas_.setImg(img);

//         // 5. Обновляем UI
//         ui->canvas_view_->redraw();

//         std::cout << "[Load] Success! Loaded " << img.size() << " bytes." << std::endl;
//     }
//     else
//     {
//         std::cerr << "[Error] Failed to read data stream." << std::endl;
//     }
//     in.close();
// }

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
