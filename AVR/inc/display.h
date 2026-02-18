#ifndef DISPLAY_SSD1306_HPP
#define DISPLAY_SSD1306_HPP

#include <stdint.h>


#define SSD1306_ADDR 0x3C


void disp_init();

void disp_write_byte(uint8_t byte);

void disp_clear();

void disp_fill();

void disp_command(uint8_t c);

void disp_command_op(uint8_t c, uint8_t op);

void disp_command_2op(uint8_t c, uint8_t op1, uint8_t op2);

void disp_set_ptr_atStart();

#endif