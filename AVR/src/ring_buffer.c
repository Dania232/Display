#include <stdint.h>
#include "../inc/ring_buffer.h"

void rb_init(Ring_buffer *rb)
{
    for (int i = 0; i < BUF_SIZE; i++)
        rb->buffer[i] = 0;
    rb->head = 0;
    rb->tail = 0;
}

int rb_push(Ring_buffer *rb, uint8_t val) {
    if (rb_is_full(rb)) return -1;
    rb->buffer[rb->head++] = val;
    return 0;
}

int rb_pop(Ring_buffer *rb, uint8_t *val) {
    if (rb_is_empty(rb)) return -1;
    *val = rb->buffer[rb->tail]; 
    rb->tail++;
    return 0;
}

int rb_is_full(Ring_buffer *rb) {
    return (uint8_t)(rb->head + 1) == rb->tail;
}

int rb_is_empty(Ring_buffer *rb)
{
    return rb->head == rb->tail;
}