#include <stdint.h>
#include <avr/delay.h>

#include "../inc/display.h"
#include "../inc/fsm.h"
#include "../inc/i2c.h"
#include "../inc/ring_buffer.h"
#include "../inc/uart.h"
#include "../inc/gpio.h"
#include "../inc/timer.h"

FSM fsm;
Ring_buffer ring_buffer;
int is_error_diod_on = 0;

void error();

void uart_byte_recived_handler(uint8_t byte)
{
    rb_push(&ring_buffer, byte);
}
void timer_int_handler(){
    is_error_diod_on ^= 1;
}
int main()
{

    fsm_init(&fsm);

    disp_init();
    disp_clear();
    rb_init(&ring_buffer);

    led_init();

    timer_init();
    timer_set_handler(timer_int_handler);
    uart_init(uart_byte_recived_handler);

    while (1)
    {
        if (!rb_is_empty(&ring_buffer))
        {
            uint8_t data;

            rb_pop(&ring_buffer, &data);
            if (fsm.state == RX_PAYLOAD)
            {
                disp_write_byte(data);
            }

            FsmStatus s = fsm_step(&fsm, data);
            if (s == GOT_LEN)
            {
                if (fsm.data_len != 1024)
                {
                    error(100);
                }
                else
                {
                    disp_set_ptr_atStart();
                }
            }

            if (s == CHECKSUM_OK)
            {
                uart_transmit('c');
            }
            else if (s == CHECKSUM_ER)
            {
                uart_transmit('n');
            }
        }
        
        if (is_error_diod_on){
            led_on();
        }
        else{
            led_off();
        }
        
    }

    return 0;
}

void error(uint16_t fr_ms)
{
    timer_start();
    timer_set_period(fr_ms);
}
