#include <Regx52.h>
#include "Key.h"
#include "Delay.h"

sbit Change_Wave = P1^0;
sbit Increase_Freq = P1^1;
sbit Decrease_Freq = P1^2;
sbit Increase_Duty = P1^3;
sbit Decrease_Duty = P1^4;

enum KeyState_t key_state;

/*
  * @brief  返回按键状态
  * @param  none
  * @return KeyState_t	
  * @note   none
 */
enum KeyState_t Key()
{
    key_state = NO_KEY;
    if (Change_Wave==0) {Delay(20);while(Change_Wave==0);Delay(20);key_state =CH_WAVE;}
    if (Increase_Freq==0) {Delay(20);while(Increase_Freq==0);Delay(20);key_state =ADD_FREQ;}
    if (Decrease_Freq==0) {Delay(20);while(Decrease_Freq==0);Delay(20);key_state =SUB_FREQ;}
    if (Increase_Duty==0) {Delay(20);while(Increase_Duty==0);Delay(20);key_state =ADD_DUTY;}
    if (Decrease_Duty==0) {Delay(20);while(Decrease_Duty==0);Delay(20);key_state =SUB_DUTY;}
    return key_state;
}