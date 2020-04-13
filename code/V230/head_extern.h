#ifndef __head_extern_H
#define __head_extern_H	

//*************************************************//
//变量的定义，修改变量必须同步修改head_extern.h
//***********************************************//

extern  BYTE	Sys_Flag;
BIT		f_work		:	Sys_Flag.0;		//开关机
BIT		f_charging	:	Sys_Flag.1;		//充电
bit     f_key_scan	:	Sys_Flag.2;		//按键扫描
bit     f_charging_full:Sys_Flag.3;		//充满
bit     f_heating   :   sys_flag.4;
extern  BYTE motor_state,motor_state2;		//马达工作模式0~7
extern  BYTE count;//T16计数
extern  byte S1_count,s2_count,s3_count,s4_count,s5_count;
extern word motor_time,motor_time2;
extern byte pwm_num;
extern word pwm_num2;
extern WORD sleep_time;
extern bit pwm_bit;
extern  BYTE rate;
extern  BYTE pwm_duty,pwm_cnt; 
extern  word  led_time; 
extern byte  led_cnt,led_time2;
extern bit f_low;
extern byte  low_cnt,low_time;
extern dword min30;
extern word led_mode;
extern byte led_time2;
extern byte power_mode;
extern word motor_pwmtime;
extern word work_time;
#endif