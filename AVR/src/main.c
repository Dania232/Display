#include <stdint.h>

#include "../inc/display.h"
#include "../inc/fsm.h"
#include "../inc/i2c.h"
#include "../inc/ring_buffer.h"
#include "../inc/uart.h"

FSM *fsm;
Ring_buffer *ring_buffer;

void byte_recived_handler(uint8_t byte){
    fsm_step(fsm, byte);
    if (fsm->state == RX_PAYLOAD){
        rb_push(ring_buffer, byte);
    }
}
int main(){

    FSM t;
    fsm = &t;
    fsm_init(fsm);
    byte_recived_callback = byte_recived_handler;

    uart_init();

    disp_init();

    Ring_buffer r;
    ring_buffer = &r;
    rb_init(ring_buffer);

    

    while (1)
    {
        if (ring_buffer->count > 0){
            uint8_t data;
            rb_pop(ring_buffer, &data);
            disp_write_byte(data);
        }
    }
    

    return 0;
}