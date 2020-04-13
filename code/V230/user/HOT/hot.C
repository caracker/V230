#include	"hot.h"
#include "../../head_extern.h"

void hot_init(void)
{
//32000000/(16*1*2048)=976hz
	pwmg0c=0B_0_0_0_0_011_1;	//控制寄存器	pa0
	pwmgclk=0B_0_10_00000;		//分频寄存器

	//CB=2047
	pwmgcubl=(2047&0x7)<<5;	//计数上限低位寄存器
	pwmgcubh=(2047>>3);			//计数上限高位寄存器 
	//DB=1023   占空比50%
	pwmg0dtl=(1000&0x7)<<5;	
	pwmg0dth=(1000>>3);
}

void hot_40pwm(void)
{
	pwmgclk=0B_0_10_00000;		//分频寄存器
	pwmg0c=0B_0_0_0_0_011_1;
	pwmg0dtl=(1433&0x7)<<5;	
	pwmg0dth=(1433>>3);
	pwmg0c=0B_1_0_0_0_011_1;
	pwmgclk=0B_1_10_00000;		//分频寄存器
}
void hot_50pwm(void)
{
	pwmgclk=0B_0_10_00000;		//分频寄存器
	pwmg0c=0B_0_0_0_0_011_1;
	pwmg0dtl=(1638&0x7)<<5;	
	pwmg0dth=(1638>>3);
	pwmg0c=0B_1_0_0_0_011_1;
	pwmgclk=0B_1_10_00000;		//分频寄存器
}
byte hot_mode_temp;
void hot_even(void)
{
	if(f_heating && !f_charging)
	{
		if(hot_mode != hot_mode_temp)
		{
			hot_mode_temp=hot_mode;
			switch(hot_mode_temp)
			{
				case 0:
					pwmgclk=0B_0_10_00000;		//分频寄存器
					pwmg0c=0B_0_0_0_0_011_1;
					break;
				case 1:
					hot_40pwm();
					break;
				case 2:
					hot_50pwm();
					break;
				default:
					hot_mode_temp=0;
					break;
			}
		}
	}
	else
	{
		hot_mode=0;
		hot_mode_temp=100;
		pwmg0c=0B_0_0_0_0_011_1;
		pwmgclk=0B_0_10_00000;		//分频寄存器
	}

}