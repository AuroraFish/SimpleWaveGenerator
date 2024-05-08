#include <REGX52.h>
#include "Pwm_Test.h"
#include "SinTable.h"

sbit PWM = P3^0;

unsigned char timeh=0, timel=0;
unsigned char Scale = 50;

/*
  * @brief  计算正弦波定时器重装值
  * @param  none
  * @return none	
  * @note   none
 */
void Data_Handle0(void)
{
    // 1 / freq / 256 * 1000000
    unsigned int temp = 0;
	temp = 62500/(freq*16);  
	timeh =( 65536-temp)/256;
	timel = (65536-temp)%256;
}

/*
  * @brief  计算方波定时器重装值
  * @param  none
  * @return none	
  * @note   none
 */
void Data_Handle1(void)
{
    //1 / freq / 100 * 1000000
    unsigned int temp = 0;
    temp = 10000/freq;
    timeh = (65536-temp)/256;
    timel = (65536-temp)%256;
}

/*
  * @brief  输出正弦波
  * @param  none
  * @return none	
  * @note   none
 */
void Sin_Wave(void)
{
    P2 = sin[sin_count];
    if (sin_count == 256) {
        sin_count = 0;
    }
}

/*
  * @brief  定时器0初始化
  * @param  none
  * @return none	
  * @note   none
 */
void Timer0_Init(void)
{  
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
    TL0 = timel;
    TH0 = timeh;
	TF0 = 0;				//清除TF0标志
	//TR0 = 1;				//定时器0开始计时
    EA = 1;
    ET0 = 1;
}

/*
  * @brief  启动定时器
  * @param  none
  * @return none	
  * @note   none
 */
void Timer0_Start(void)
{
    TL0 = timel;
    TH0 = timeh;
    TR0 = 1;
}

/*
  * @brief  停止定时器
  * @param  none
  * @return none	
  * @note   none
 */
void Timer0_Stop(void)
{
    TR0 = 0;
}

/*
  * @brief  设置占空比
  * @param  x: 占空比
  * @return none	
  * @note   none
 */
void Set_Duty(unsigned char x) 
{
    Scale = x;
}

/*
  * @brief  返回占空比
  * @param  none
  * @return 占空比	
  * @note   none
 */
unsigned char Get_Duty(void)
{
    return Scale;
}

/*
  * @brief  定时器中断
  * @param  none
  * @return none	
  * @note   none
 */
void Timer0_Routine(void) interrupt 1
{  
    switch (Output) {
        //方波
        case REC: {
            TL0 = timel;
            TH0 = timeh;
            rec_count++;
            rec_count %= 100;
            
            if (rec_count < Scale) {
                P2 = 0xFF;
            }
            else {
                P2 = 0x00;
            }
            break;
        }
        //正弦波
        case SIN: {
            TL0 = timel;
            TH0 = timeh;
            sin_count++;
            Sin_Wave();
            break;
        }
    }
}