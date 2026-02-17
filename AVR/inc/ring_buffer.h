#define BUF_SIZE 100
#include <avr/io.h>




typedef struct
{
    uint8_t buffer[BUF_SIZE];
    uint8_t tail;
    uint8_t head;
    uint8_t count;
} Ring_buffer;

void rb_init(Ring_buffer *rb);
int rb_push(Ring_buffer *rb, uint8_t val);
int rb_pop(Ring_buffer *rb, uint8_t *val);