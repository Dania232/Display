#ifndef RING_BUFFER_H
#define RING_BUFFER_H

// must be a power-of-two multiple
#define BUF_SIZE 256




typedef struct
{
    uint8_t buffer[BUF_SIZE];
    volatile uint8_t tail;
    volatile uint8_t head;
} Ring_buffer;

void rb_init(Ring_buffer *rb);
int rb_push(Ring_buffer *rb, uint8_t val);
int rb_pop(Ring_buffer *rb, uint8_t *val);
int rb_is_empty(Ring_buffer *rb);
int rb_is_full(Ring_buffer *rb);

#endif