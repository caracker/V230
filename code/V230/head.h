#ifndef __HEAD_H
#define __HEAD_H	

//*************************************************//
//变量的定义，修改变量必须同步修改head_extern.h
//***********************************************//

BYTE	Sys_Flag;
BIT		f_work		:	Sys_Flag.0;		//开关机
BIT		f_charging	:	Sys_Flag.1;		//充电
bit     f_key_scan	:	Sys_Flag.2;		//按键扫描
bit     f_charging_full:Sys_Flag.3;		//充满
bit     f_heating   :   sys_flag.4;
byte motor_state;		//马达工作模式0~7
byte count;//T16计数
byte S1_count,s2_count,s3_count,s4_count,s5_count;//按键计数
word motor_time;
byte pwm_num;
WORD sleep_time;
word  led_time; 
byte  led_cnt,led_time2;
bit   f_low;
byte  low_cnt,low_time;
dword min30;
byte led_mode;
byte power_mode;
word motor_pwmtime;

word work_time;
#endif