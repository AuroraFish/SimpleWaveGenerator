#ifndef __PWM_TEST_H__
#define __PWM_TEST_H__

//正弦/方波
enum WAVE {
    REC = 0,
    SIN
};

extern unsigned char freq;
extern unsigned char sin_count;
extern unsigned char rec_count;
extern enum WAVE Output;
//定时器
void Timer0_Init(void);
void Timer0_Start(void);
void Timer0_Stop(void);
//频率
void Data_Handle0(void);
void Data_Handle1(void);
//占空比
void Set_Duty(unsigned char x);
unsigned char Get_Duty(void);

#endif
