
#include	"motor.h"
#include "../../head_extern.h"
#include	"../key/key.h"
/*	���Ƶ�� = Y �� [256 �� S1 �� (S2+1) ]
*	�����ռ�� = ( K��1 ) �� 256��100%
*	Y = tm2c[7:4] : Timer2 ��ѡ���ʱ��ԴƵ��
*	K = tm2b[7:0] : ���޼Ĵ����趨��ֵ(ʮ����)
*	S1 = tm2s[6:5] : Ԥ��Ƶ���趨ֵ (1, 4, 16, 64)
*	S2 = tm2s[4:0] : ��Ƶ��ֵ (ʮ���ƣ�1 ~ 31)
*/
/*void motor_init2(void)
{
	//2000000/32/631=99hz
	pwmg1c=0B_0_0_0_0_000_0;	//���ƼĴ���	pa4
	pwmgclk=0B_1_101_000_0;		//ϵͳʱ�ӣ�pwmg���ã�32��Ƶ
	//CB=631
	pwmgcubl=(631&0x6)<<6;	//�������޵�λ�Ĵ���
	pwmgcubh=(631>>2);			//�������޸�λ�Ĵ��� 
	//DB=1023   ռ�ձ�50%
	pwmg1dtl=(126&0x6)<<6;	
	pwmg1dth=(126>>2);
	motor2_off;

}


void motor_init(void)
{ 
	tm2ct=0;
	tm2b = 255;			 //���޼Ĵ���    k=127
	tm2c = 0b_0001_00_1_0;	 // ϵͳʱ��, ��� = PA3, PWM ģʽ
	tm2s = 0b_0011_0011;	 // 8λpwm:256, Ԥ��Ƶ = 1, ��Ƶ = 2   S1=1  S2=1
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
//ģʽ����1(173.5ms) -0(213.9ms)
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
//ģʽ����1(81.68ms) -0(99.32ms)
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
//ģʽ�ģ�[1��71.55ms��-0(99.49)]9��-1(889.3ms)-0(99.49ms)
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
//ģʽ�壺1(51.03ms)-0(45.82ms)
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
//ģʽ����[1(40.82ms)-0(305.6ms)]6��-[1(256.3ms)-0(366.8ms)]7��-1(2.082s)-0(305.6ms)
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
//ģʽ�ߣ�1(40.83ms)-0(122.3ms)-[1(51.03ms)-0(122.3ms)]7��-1(1.837s)-0(123.7ms)
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
//ģʽ�ˣ�1(265.4ms)-0(366.7ms)
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