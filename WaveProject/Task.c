#include <REGX52.H>
#include "Pwm_Test.h"
#include "LCD1602.h"	
#include "Delay.h"
#include "Key.h"

//显示状态 默认/方波/正弦
enum WaveState_t{
    DEFAULT_WAVE = 0,
    REC_WAVE,
    SIN_WAVE
};

enum WaveState_t state = DEFAULT_WAVE;
enum KeyState_t button_state;
enum WAVE Output = REC;

unsigned char freq = 1;
unsigned char sin_count = 0;
unsigned char rec_count = 0;
unsigned char temp;

/*
  * @brief  计算重装值
  * @param  cur: REC/SIN
  * @return none	
  * @note   none
 */
void Handle_Freq(enum WAVE cur)
{
    switch (cur) {
        case REC: {
            Data_Handle1();
            break;
        }
        
        case SIN: {
            Data_Handle0(); 
            break;
        }
        default :
            break;
    }
}

/*
  * @brief  获取下一状态
  * @param  cur: DEFAULT_WAVE/REC_WAVE/SIN_WAVE
  * @return none	
  * @note   none
 */
enum WaveState_t Next_WaveState(enum WaveState_t cur)
{
    switch(cur) {
        case DEFAULT_WAVE:
            return REC_WAVE;
        case REC_WAVE:
            return SIN_WAVE;
        case SIN_WAVE:
            return DEFAULT_WAVE;
    }
    
    return DEFAULT_WAVE;
}

/*
  * @brief  显示前初始化
  * @param  cur: 当前状态
  * @return none	
  * @note   none
 */
void Init_Wave_Setting(enum WaveState_t cur)
{
    switch (cur) {
        case DEFAULT_WAVE: {
            Timer0_Stop();
            break;
        }
        case REC_WAVE: {
            freq = 1;
            rec_count = 0;
            Set_Duty(50);
            Data_Handle1();
            Output = REC;
            Timer0_Start();
            break;
        }
        case SIN_WAVE: {
            freq = 1;
            sin_count = 0;
            Data_Handle0(); 
            Output = SIN;
            Timer0_Start();
            break;
        }
    }
}

/*
  * @brief  初始化
  * @param  none
  * @return none	
  * @note   none
 */
void Task_Init(void)
{
    LCD_Init();
    Timer0_Init();
}

/*
  * @brief  LCD显示
  * @param  none
  * @return none	
  * @note   none
 */
void Task_Display(void)
{
    
    switch(state) {
        case DEFAULT_WAVE: {
            //初始界面
            LCD_ShowString(1,1,"hello,world");
            break;
        }
        
        case REC_WAVE: {
            //方波图像
            temp = Get_Duty();
            temp = (temp==100)?99:temp;
            LCD_ShowString(1, 1, "FREQUNCE:");
            LCD_ShowCustomChar(2,2,1);
            LCD_ShowCustomChar(2,3,1);
            LCD_ShowString(2,5,"HZ:");
            LCD_ShowString(2,11,"D:");
            LCD_ShowChar(2,15,'%');
            LCD_ShowNum(2,8,freq,2);
            LCD_ShowNum(2,13,temp,2);
            break;
        }
        
        case SIN_WAVE: {
            //正弦图像
            LCD_ShowString(1, 1, "FREQUNCE:");
            LCD_ShowCustomChar(2,2,2);
            LCD_ShowCustomChar(2,3,3);
            LCD_ShowString(2,5,"HZ:");
            LCD_ShowNum(2,8,freq,2);
            break;
        }
        
        default: 
            break;
    }
}

/*
  * @brief  按键处理
  * @param  none
  * @return none	
  * @note   none
 */
void Task_Key_Handle(void)
{
    button_state = Key();
    switch (button_state) {
        case NO_KEY: {
            break;
        }
        
        case CH_WAVE: {
            state = Next_WaveState(state);
            Init_Wave_Setting(state);
            LCD_CLEAR();
            break;
        }
        
        case ADD_FREQ: {
            freq++;
            if (freq >= 10)
                freq = 10;
            Handle_Freq(Output);
            break;
        }
        
        case SUB_FREQ: {
            freq--;
            if (freq <= 1)
                freq = 1;
            Handle_Freq(Output);
            break;
        }
        
        case ADD_DUTY: {
            if (Output == REC) {
                temp = Get_Duty();
                temp += 10;
                if (temp >= 100) {
                    temp = 100;
                }
                Set_Duty(temp);
            }
            break;
        }
        
        case SUB_DUTY: {
            if (Output == REC) {
                temp = Get_Duty();
                temp -= 10;
                if (temp <= 10) {
                    temp = 10;
                }
                Set_Duty(temp);
            }
            break;
        }
        
        default:
            break;
    }
}