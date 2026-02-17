#include <stdint.h>



typedef enum 
{
    RX_SYNC_1,
    RX_SYNC_2,
    RX_TYPE,
    RX_LEN_L,
    RX_LEN_H,
    RX_PAYLOAD,
    RX_CHECK
} FsmState;
typedef enum {
    NONE,
    SIGN_OK,
    SIGN_ER,
    CHECKSUM_OK,
    CHECKSUM_ER,
    GOT_LEN
} FsmStatus;

typedef struct
{
    FsmState state;
    uint8_t checksum;
    uint8_t pack_type;
    uint16_t data_len;
    uint8_t data_index;
} FSM;


void fsm_init();
void fsm_step(FSM *fsm, uint8_t byte);
