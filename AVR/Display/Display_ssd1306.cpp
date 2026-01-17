#include "Display_ssd1306.hpp"

#include <avr/io.h>
#include <util/delay.h>

#include "../LowLevel/I2c.h"
#include "ssd1306_commands.hpp"

/* ONLY ONE DEFINITION OF THESE */
static uint8_t ctrCommandComing = 0x80;
static uint8_t ctrDataComing = 0xC0;
static uint8_t ctrDataOnlyComing = 0x40;

/* ===== PRIVATE METHODS ===== */

void Display::ssd1306_command(uint8_t command)
{
    i2c_write_byte(ctrCommandComing);
    i2c_write_byte(command);
}

void Display::my_init()
{
    i2c_begin(SSD1306_ADDR);
    ssd1306_command(0xA8);
    ssd1306_command(0x3F);
    ssd1306_command(0xD3);
    ssd1306_command(0x00);
    ssd1306_command(0x40);
    ssd1306_command(0xA1);
    ssd1306_command(0xC8);
    ssd1306_command(0xDA);
    ssd1306_command(0x12);
    ssd1306_command(0x81);
    ssd1306_command(0xFF);
    i2c_end();

    _delay_ms(5);
}

void Display::init()
{
    // ----- Display OFF -----
    command(SSD1306_DISPLAYOFF);

    // ----- Set display clock divide -----
    command(SSD1306_SETDISPLAYCLOCKDIV, 0x80);

    // ----- Set multiplex -----
    command(SSD1306_SETMULTIPLEX, 0x3F);

    // ----- Set display offset -----
    command(SSD1306_SETDISPLAYOFFSET, 0x00);

    // ----- Set start line -----
    command(SSD1306_SETSTARTLINE | 0x00);

    // ----- Charge pump -----
    command(SSD1306_CHARGEPUMP, 0x14);

    // ----- Memory mode -----
    command(SSD1306_MEMORYMODE, 0x01);

    // ----- Segment remap -----
    command(SSD1306_SEGREMAP | 0x01);

    // ----- COM scan direction -----
    command(SSD1306_COMSCANDEC);

    // ----- Set COM pins -----
    command(SSD1306_SETCOMPINS, 0x12);

    // ----- Set contrast -----
    command(SSD1306_SETCONTRAST, 0x7F);

    // ----- Pre-charge period -----
    command(SSD1306_SETPRECHARGE, 0xF1);

    // ----- VCOM detect -----
    command(SSD1306_SETVCOMDETECT, 0x40);

    // ----- Display resume & normal mode -----
    command(SSD1306_DISPLAYALLON_RESUME);
    command(SSD1306_NORMALDISPLAY);

    // ----- Finally, turn ON display -----
    command(SSD1306_DISPLAYON);

    // ----- Set drawing area (full screen) -----
    command(SSD1306_COLUMNADDR, 0, 127);
    command(SSD1306_PAGEADDR, 0, 7);
}
/* ===== CONSTRUCTORS ===== */

Display::Display()
{
    i2c_init(100);
    init();
}

Display::Display(uint8_t *mem)
{
    this->mem = mem;
    i2c_init(100);
    init();
}

/* ===== PUBLIC API ===== */

void Display::write_byte(uint8_t byte)
{
    i2c_begin(SSD1306_ADDR);
    i2c_write_byte(ctrDataComing);
    i2c_write_byte(byte);
    i2c_end();
}

void Display::clear()
{
    i2c_begin(SSD1306_ADDR);
    i2c_write_byte(ctrDataOnlyComing);
    for (uint16_t i = 0; i < 1024; i++)
        i2c_write_byte(0x00);
    i2c_end();
}

void Display::fill()
{
    i2c_begin(SSD1306_ADDR);
    i2c_write_byte(ctrDataOnlyComing);
    for (uint16_t i = 0; i < 1024; i++)
        i2c_write_byte(0xFF);
    i2c_end();
}

void Display::set_ptr_atStart(){
    command(SSD1306_COLUMNADDR, 0, 127);
    command(SSD1306_PAGEADDR, 0, 7);
}
/* command() overloads */
void Display::command(uint8_t c)
{
    i2c_begin(SSD1306_ADDR);
    i2c_write_byte(ctrCommandComing);
    i2c_write_byte(c);
    i2c_end();
}

void Display::command(uint8_t c, uint8_t op)
{
    i2c_begin(SSD1306_ADDR);
    i2c_write_byte(ctrCommandComing);
    i2c_write_byte(c);
    i2c_write_byte(ctrCommandComing);
    i2c_write_byte(op);
    i2c_end();
}

void Display::command(uint8_t c, uint8_t op1, uint8_t op2)
{
    i2c_begin(SSD1306_ADDR);
    i2c_write_byte(ctrCommandComing);
    i2c_write_byte(c);
    i2c_write_byte(ctrCommandComing);
    i2c_write_byte(op1);
    i2c_write_byte(ctrCommandComing);
    i2c_write_byte(op2);
    i2c_end();
}

void Display::write_bytes(uint8_t *bytes, uint16_t len)
{
    command(SSD1306_COLUMNADDR, 0, 127);
    command(SSD1306_PAGEADDR, 0, 7);
    i2c_begin(SSD1306_ADDR);
    i2c_write_byte(ctrDataOnlyComing);
    for (uint16_t i = 0; i < len; i++)
    {
        i2c_write_byte(bytes[i]);
    }
    i2c_end();
}