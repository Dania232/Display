#include "../inc/fsm.h"

void fsm_init(FSM *fsm){
    reset(fsm);
}

static void reset(FSM *fsm){
    fsm->checksum = 0;
    fsm->data_index = 0;
    fsm->data_len = 0;
    fsm->pack_type = 0;
    fsm->state = RX_SYNC_1;
}
uint8_t fsm_step(FSM *fsm, uint8_t byte){
    switch (fsm->state)
    {
    case RX_SYNC_1:
        
        if (byte == 0xAA)
            fsm->state = RX_SYNC_2;
        else
            reset(fsm);
            return SIGN_ER;
        break;

    case RX_SYNC_2:
        if (byte == 0x55){
            fsm->state = RX_TYPE;
            return SIGN_OK;
        }
        else{
            reset(fsm);
            return SIGN_ER;
        }
        break;

    case RX_TYPE:
        fsm->checksum = byte;
        fsm->state = RX_LEN_L;
        fsm->pack_type = byte;
        break;

    case RX_LEN_L:
        fsm->data_len = byte;
        fsm->checksum ^= byte;
        fsm->state = RX_LEN_H;
        break;

    case RX_LEN_H:
        fsm->data_len |= (uint16_t)byte << 8;
        fsm->checksum ^= byte;
        fsm->data_index = 0;
        fsm->state = (fsm->data_len > 0) ? RX_PAYLOAD : RX_CHECK;
        return GOT_LEN;

    case RX_PAYLOAD:
        fsm->data_index++;
        fsm->checksum ^= byte;
        if (fsm->data_index >= fsm->data_len)
            fsm->state = RX_CHECK;
        break;

    case RX_CHECK:
        if (fsm->checksum == byte)
        {
            return CHECKSUM_OK;
        }
        else
        {
            reset(fsm);
            return CHECKSUM_ER;
        }
    }
    return NONE;
}