#include <avr/io.h>
#include <util/delay.h>
#include "LowLevel/UART.c"
#include "Display/Display_ssd1306.hpp"

int main(void)
{
    //usart_init();
   
    
    Display display;
    uint16_t l = 1024;
    uint8_t pixs[l];
    //usart_transmit('S');
    // for (int i = 0; i < l; i++)
    // {
    //     int d = usart_receive();
    //     pixs[i] = d;
    // }
    
    //usart_transmit('M');
    //display.command(SSD1306_COLUMNADDR, 0, 127);
    //display.command(SSD1306_PAGEADDR, 0, 7);

    display.clear();
    display.fill();
    display.clear();

    //display.write_byte(0x0);
    //display.clear();
    //usart_transmit('E');
    // display.write_bytes((uint8_t *)pixs, l);
    //  display.write_bytes((uint8_t *)pixs, l);
    //  display.write_bytes((uint8_t *)pixs, l);
    //display.write_column(pixs, 60);
    //display.write_bytes(pixs, 2);
    
    return 0;
}
