#ifndef __KEY_H__
#define __KEY_H__

enum KeyState_t{
    NO_KEY = 0,
    CH_WAVE,
    ADD_FREQ,
    SUB_FREQ,
    ADD_DUTY,
    SUB_DUTY
};

enum KeyState_t Key();

#endif