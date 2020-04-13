#include	"KEY.h"
#include "../../head_extern.h"
#include	"../motor/motor.h"
#include	"../comparator/comparator.h"
#include	"../led/led.h"
extern byte motor_state_temp;
extern byte motor_state_temp2;
byte	check_cnt;
dword min130;
void key_init(void)
{
	$ s1 IN,pull;
	$ s2 IN,pull;

	
	$ power_in in,nopull;

}


void check_charging(void)
{
	if(power_in)
	{
		Q4_pin=0;
		f_charging=1;
	}
	else
	{
		if(f_work)	Q4_pin=1;
		else		Q4_pin=0;
	
		f_charging=0;
	}
	
}
void key_scan(void)
{
	if(f_key_scan )
	{
		f_key_scan=0;
		check_charging();

		if(s2==0)
		{
			s1_even();
		}
		else
		{
			f_work=0;
		}
		
		
	}
}

void s1_even(void)
{
	if(s1==0)
	{
		if(S1_count<250)	S1_count++;
		if(S1_count>200&&S1_count<210) //长按
		{
			S1_count=220;
		
		}
	}
	else
	{	
		if(s1_count>2&&s1_count<200)
		{	
			if(f_work)
			{
				f_work=0;
			}
			else
			{
				f_work=1;
			}
			work_time=0;
		}
		S1_count=0;
	}
}
void s2_even(void)
{
	if(s2==0)
	{
		if(S2_count<250)	S2_count++;
		if(S2_count>200&&S2_count<210) //长按
		{
			S2_count=220;
		}
	}
	else
	{	
		if(S2_count>2&&S2_count<200)
		{
			if(f_work)
			{
			
			}
		}
		S2_count=0;
	}
}
