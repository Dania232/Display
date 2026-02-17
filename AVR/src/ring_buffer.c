
#include "../inc/ring_buffer.h"

void rb_init(Ring_buffer *rb)
{
    for (int i = 0; i < BUF_SIZE; i++)
        rb->buffer[i] = 0;
    rb->count = 0;
    rb->head = 0;
    rb->tail = 0;
}

int rb_push(Ring_buffer *rb, uint8_t val)
{
    if (rb->count >= BUF_SIZE)
        return -1;

    rb->buffer[rb->head] = val;
    rb->head = (rb->head + 1) % BUF_SIZE;
    rb->count++;
    return 0;
}
int rb_pop(Ring_buffer *rb, uint8_t *val){
    if (rb->count == 0)
        return -1;
    
    *val = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % BUF_SIZE;
    rb->count--;
    return 0;
}