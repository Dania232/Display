#ifndef DISPLAY_SSD1306_HPP
#define DISPLAY_SSD1306_HPP

#include <stdint.h>

#define SSD1306_ADDR 0x3C

class Display
{
private:
    uint8_t *mem;

    void ssd1306_command(uint8_t command);
    void my_init();
    void init();

public:
    Display();
    Display(uint8_t *mem);

    void set_ptr_atStart();

    void put_pix(uint16_t col, uint8_t row);

    void write_byte(uint8_t byte);
    void write_bytes(uint8_t *bytes, uint16_t len);
    void write_column(uint8_t *column, uint8_t ind);

    void clear();
    void fill();

    void command(uint8_t command);
    void command(uint8_t command, uint8_t op);
    void command(uint8_t command, uint8_t op1, uint8_t op2);
};

#endif
