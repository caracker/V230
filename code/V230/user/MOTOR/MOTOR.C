
#include	"motor.h"
#include "../../head_extern.h"
#include	"../key/key.h"
/*	输出频率 = Y ÷ [256 × S1 × (S2+1) ]
*	输出空占比 = ( K＋1 ) ÷ 256×100%
*	Y = tm2c[7:4] : Timer2 所选择的时钟源频率
*	K = tm2b[7:0] : 上限寄存器设定的值(十进制)
*	S1 = tm2s[6:5] : 预分频器设定值 (1, 4, 16, 64)
*	S2 = tm2s[4:0] : 分频器值 (十进制，1 ~ 31)
*/
/*void motor_init2(void)
{
	//2000000/32/631=99hz
	pwmg1c=0B_0_0_0_0_000_0;	//控制寄存器	pa4
	pwmgclk=0B_1_101_000_0;		//系统时钟，pwmg启用，32分频
	//CB=631
	pwmgcubl=(631&0x6)<<6;	//计数上限低位寄存器
	pwmgcubh=(631>>2);			//计数上限高位寄存器 
	//DB=1023   占空比50%
	pwmg1dtl=(126&0x6)<<6;	
	pwmg1dth=(126>>2);
	motor2_off;

}


void motor_init(void)
{ 
	tm2ct=0;
	tm2b = 255;			 //上限寄存器    k=127
	tm2c = 0b_0001_00_1_0;	 // 系统时钟, 输出 = PA3, PWM 模式
	tm2s = 0b_0011_0011;	 // 8位pwm:256, 预分频 = 1, 分频 = 2   S1=1  S2=1
	motor_off;
}
*/
void motor_pwm(void);
void motor_mode1(void);
void motor_mode2(void);
void motor_mode3(void);
void motor_mode4(void);
void motor_mode5(void);
void motor_mode6(void);
void motor_mode7(void);
void motor_mode8(void);
byte pwmnum;
void motor_init(void)
{ 

	$ q4_pin out,low;
	$ q6_pin out,low;

}

//byte pwmnum;
word motor_step;
void motor_pwm(void)
{
	if(pwmnum<40)
	{
		if(motor_pwmtime<pwmnum)
		{	
			motor_pin=1;
			motor2_pin=1;
		}
		elseif(motor_pwmtime<40)
		{
			motor_pin=0;
			motor2_pin=0;
		}
		else
		{
			motor_step++;
			motor_pwmtime=0;	
		}
	}
	else
	{
		if(motor_pwmtime<40)
		{
			motor_pin=1;
			motor2_pin=1;
		}
		else
		{
			motor_step++;
			motor_pwmtime=0;	
		}
	}
}
byte motor_state_temp;
void motor_mode1(void)
{
	if(motor_state != motor_state_temp)
	{
		motor_state_temp=motor_state;	
		motor_time=0;
		motor_pwmtime=0;
		motor_step=0;
	}
	motor_pwm();
}
//模式二：1(173.5ms) -0(213.9ms)
void motor_mode2(void)
{
	if(motor_state != motor_state_temp)
	{
		motor_state_temp=motor_state;	
		motor_time=0;
		motor_pwmtime=0;
		motor_step=0;
	}
	if(motor_step<17)
	{
		motor_pwm();
		motor_time=0;
	}
	else
	{
		if(motor_time<833)
		{
			motor_pin=0;
			motor2_pin=0;
		}
		else
		{
			motor_time=0;
			motor_pwmtime=0;
			motor_step=0;
		}
	}
}
//模式三：1(81.68ms) -0(99.32ms)
void motor_mode3(void)
{
	if(motor_state != motor_state_temp)
	{
		motor_state_temp=motor_state;	
		motor_time=0;
		motor_pwmtime=0;
		motor_step=0;
	}
	if(motor_step<8)
	{
		motor_pwm();
		motor_time=0;
	}
	else
	{
		if(motor_time<387)
		{
			motor_pin=0;
			motor2_pin=0;
		}
		else
		{
			motor_time=0;
			motor_pwmtime=0;
			motor_step=0;
		}
	}
}
//模式四：[1（71.55ms）-0(99.49)]9次-1(889.3ms)-0(99.49ms)
byte  motor_step2;
void motor_mode4(void)
{
	if(motor_state != motor_state_temp)
	{
		motor_state_temp=motor_state;	
		motor_time=0;
		motor_pwmtime=0;
		motor_step=0;
	}
	if(motor_step2<9)
	{
		if(motor_step<7)
		{
			motor_pwm();
			motor_time=0;
		}
		else
		{
			if(motor_time<387)
			{
				motor_pin=0;
				motor2_pin=0;
			}
			else
			{
				motor_time=0;
				motor_pwmtime=0;
				motor_step=0;
				motor_step2++;
			}
		}
	}
	else
	{
		if(motor_step<87)
		{
			motor_pwm();
			motor_time=0;
		}
		else
		{
			if(motor_time<387)
			{
				motor_pin=0;
				motor2_pin=0;
			}
			else
			{
				motor_time=0;
				motor_pwmtime=0;
				motor_step=0;
				motor_step2=0;
			}
		}
	}
}
//模式五：1(51.03ms)-0(45.82ms)
void motor_mode5(void)
{
	if(motor_state != motor_state_temp)
	{
		motor_state_temp=motor_state;	
		motor_time=0;
		motor_pwmtime=0;
		motor_step=0;
	}
	if(motor_step<5)
	{
		motor_pwm();
		motor_time=0;
	}
	else
	{
		if(motor_time<178)
		{
			motor_pin=0;
			motor2_pin=0;
		}
		else
		{
			motor_time=0;
			motor_pwmtime=0;
			motor_step=0;
		}
	}
}
//模式六：[1(40.82ms)-0(305.6ms)]6次-[1(256.3ms)-0(366.8ms)]7次-1(2.082s)-0(305.6ms)
void motor_mode6(void)
{
	if(motor_state != motor_state_temp)
	{
		motor_state_temp=motor_state;	
		motor_time=0;
		motor_pwmtime=0;
		motor_step=0;
	}
	if(motor_step2<6)
	{
		if(motor_step<4)
		{
			motor_pwm();
			motor_time=0;
		}
		else
		{
			if(motor_time<1193)
			{
				motor_pin=0;
				motor2_pin=0;
			}
			else
			{
				motor_time=0;
				motor_pwmtime=0;
				motor_step=0;
				motor_step2++;
			}
		}
	}
	else if(motor_step2<13)
	{
		if(motor_step<25)
		{
			motor_pwm();
			motor_time=0;
		}
		else
		{
			if(motor_time<1432)
			{
				motor_pin=0;
				motor2_pin=0;
			}
			else
			{
				motor_time=0;
				motor_pwmtime=0;
				motor_step=0;
				motor_step2++;
			}
		}
	}
	else
	{
		if(motor_step<206)
		{
			motor_pwm();
			motor_time=0;
		}
		else
		{
			if(motor_time<1193)
			{
				motor_pin=0;
				motor2_pin=0;
			}
			else
			{
				motor_time=0;
				motor_pwmtime=0;
				motor_step=0;
				motor_step2=0;
			}
		}
	}
}
//模式七：1(40.83ms)-0(122.3ms)-[1(51.03ms)-0(122.3ms)]7次-1(1.837s)-0(123.7ms)
void motor_mode7(void)
{
	if(motor_state != motor_state_temp)
	{
		motor_state_temp=motor_state;	
		motor_time=0;
		motor_pwmtime=0;
		motor_step=0;
	}
	if(motor_step2<1)
	{
		if(motor_step<4)
		{
			motor_pwm();
			motor_time=0;
		}
		else
		{
			if(motor_time<477)
			{
				motor_pin=0;
				motor2_pin=0;
			}
			else
			{
				motor_time=0;
				motor_pwmtime=0;
				motor_step=0;
				motor_step2++;
			}
		}
	}
	else if(motor_step2<8)
	{
		if(motor_step<5)
		{
			motor_pwm();
			motor_time=0;
		}
		else
		{
			if(motor_time<477)
			{
				motor_pin=0;
				motor2_pin=0;
			}
			else
			{
				motor_time=0;
				motor_pwmtime=0;
				motor_step=0;
				motor_step2++;
			}
		}
	}
	else
	{
		if(motor_step<183)
		{
			motor_pwm();
			motor_time=0;
		}
		else
		{
			if(motor_time<483)
			{
				motor_pin=0;
				motor2_pin=0;
			}
			else
			{
				motor_time=0;
				motor_pwmtime=0;
				motor_step=0;
				motor_step2=0;
			}
		}
	}
}
//模式八：1(265.4ms)-0(366.7ms)
void motor_mode8(void)
{
	if(motor_state != motor_state_temp)
	{
		motor_state_temp=motor_state;	
		motor_time=0;
		motor_pwmtime=0;
		motor_step=0;
	}
	if(motor_step<26)
	{
		motor_pwm();
		motor_time=0;
	}
	else
	{
		if(motor_time<1431)
		{
			motor_pin=0;
			motor2_pin=0;
		}
		else
		{
			motor_time=0;
			motor_pwmtime=0;
			motor_step=0;
		}
	}
}

void motor_mode9(void)
{
	if(motor_state != motor_state_temp)
	{
		motor_state_temp=motor_state;
		motor_on;
		motor_time=0;
	}
	if(motor_time<3906)
	{
		tm2b = 41;
		motor_on;
	}
	else if(motor_time<3906*2)
	{
		tm2b = 148;
		motor_on;
	}
	else
	{
		motor_time=0;	
	}
}
void motor_mode10(void)
{
	if(motor_state != motor_state_temp)
	{
		motor_state_temp=motor_state;
		motor_on;
		motor_time=0;
	}
	if(motor_time<781)
	{
		tm2b = 41;
		motor_on;
	}
	else if(motor_time<781*2)
	{
		tm2b = 148;
		motor_on;
	}
	else
	{
		motor_time=0;	
	}
}
void motor_even(void)
{
	if(f_work)
	{
		if(work_time<20*60)
		{
			q6_pin=1;
		}
		else
		{
			q6_pin=0;
		}
	
	}
	else
	{
		q6_pin=0;
	}
}