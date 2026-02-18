#include <stdint.h>
#include <avr/io.h>
#include "../inc/display.h"
#include "../inc/i2c.h"
#include "../inc/ssd1306_commands.h"


static uint8_t ctrCommandComing = 0x80;
static uint8_t ctrDataComing = 0xC0;
static uint8_t ctrDataOnlyComing = 0x40;


void disp_init()
{
    i2c_init(100);

    disp_command(SSD1306_DISPLAYOFF);

    // ----- Set display clock divide -----
    disp_command_op(SSD1306_SETDISPLAYCLOCKDIV, 0x80);

    // ----- Set multiplex -----
    disp_command_op(SSD1306_SETMULTIPLEX, 0x3F);

    // ----- Set display offset -----
    disp_command_op(SSD1306_SETDISPLAYOFFSET, 0x00);

    // ----- Set start line -----
    disp_command(SSD1306_SETSTARTLINE | 0x00);

    // ----- Charge pump -----
    disp_command_op(SSD1306_CHARGEPUMP, 0x14);

    // ----- Memory mode -----
    disp_command_op(SSD1306_MEMORYMODE, 0x01);

    // ----- Segment remap -----
    disp_command(SSD1306_SEGREMAP | 0x01);

    // ----- COM scan direction -----
    disp_command(SSD1306_COMSCANDEC);

    // ----- Set COM pins -----
    disp_command_op(SSD1306_SETCOMPINS, 0x12);

    // ----- Set contrast -----
    disp_command_op(SSD1306_SETCONTRAST, 0x7F);

    // ----- Pre-charge period -----
    disp_command_op(SSD1306_SETPRECHARGE, 0xF1);

    // ----- VCOM detect -----
    disp_command_op(SSD1306_SETVCOMDETECT, 0x40);

    // ----- Display resume & normal mode -----
    disp_command(SSD1306_DISPLAYALLON_RESUME);
    disp_command(SSD1306_NORMALDISPLAY);

    // ----- Finally, turn ON display -----
    disp_command(SSD1306_DISPLAYON);

    // ----- Set drawing area (full screen) -----
    disp_command_2op(SSD1306_COLUMNADDR, 0, 127);
    disp_command_2op(SSD1306_PAGEADDR, 0, 7);
}

void disp_write_byte(uint8_t byte)
{
    i2c_begin(SSD1306_ADDR);
    i2c_write(ctrDataComing);
    i2c_write(byte);
    i2c_end();
}

void disp_clear()
{
    i2c_begin(SSD1306_ADDR);
    i2c_write(ctrDataOnlyComing);
    for (uint16_t i = 0; i < 1024; i++)
        i2c_write(0x00);
    i2c_end();
}

void disp_fill()
{
    i2c_begin(SSD1306_ADDR);
    i2c_write(ctrDataOnlyComing);
    for (uint16_t i = 0; i < 1024; i++)
        i2c_write(0xFF);
    i2c_end();
}

void disp_command(uint8_t c)
{
    i2c_begin(SSD1306_ADDR);
    i2c_write(ctrCommandComing);
    i2c_write(c);
    i2c_end();
}

void disp_command_op(uint8_t c, uint8_t op)
{
    i2c_begin(SSD1306_ADDR);
    i2c_write(ctrCommandComing);
    i2c_write(c);
    i2c_write(ctrCommandComing);
    i2c_write(op);
    i2c_end();
}

void disp_command_2op(uint8_t c, uint8_t op1, uint8_t op2)
{
    i2c_begin(SSD1306_ADDR);
    i2c_write(ctrCommandComing);
    i2c_write(c);
    i2c_write(ctrCommandComing);
    i2c_write(op1);
    i2c_write(ctrCommandComing);
    i2c_write(op2);
    i2c_end();
}


void disp_set_ptr_atStart(){
    disp_command_2op(SSD1306_COLUMNADDR, 0, 127);
    disp_command_2op(SSD1306_PAGEADDR, 0, 7);
}