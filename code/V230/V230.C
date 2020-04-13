#include	"extern.h"
#include	"./user/TIM16/TIM16.h"
#include	"./user/key/key.h"
#include	"./user/led/led.h"
#include	"./user/motor/motor.h"
#include	"./user/STOPSYS/STOPSYS.h"
#include	"./user/comparator/comparator.h"

#include 	"head.h"
//.Writer     Limit   $ + 5
byte count2;
void data_init(void)
{
	f_work=0;
	f_charging=0;	
	f_key_scan=0;
	count2=1;
	count=1;
	S1_count=0;
	sleep_time=0;

}
void	FPPA0 (void)
{

	.ADJUST_IC	SYSCLK=IHRC/8, IHRC=16MHz, VDD=5V;
	.delay 2000*300;
	T16_init();
	key_init();
	motor_init();
	led_init();
	stopsys_init();
	data_init();
	while (1)
	{
		key_scan();
		motor_even();
		led_even();
		stopsys_even();
 	}
}

void	Interrupt (void)
{
	pushaf;

	if (Intrq.T16)
	{	
		Intrq.T16	=	0;
		
		if (--count == 0)					
		{
			count= 39;          // 256 uS * 39 = 9,984 uS ¨P 10 mS
	 		f_key_scan=1;
			if(!f_work && !f_charging )
			{
				sleep_time++;
			}
			else
			{
				sleep_time=0;
			}
			if(--count2==0)
			{
				count2=100;
				if(work_time<50000)work_time++;
			}
		}


	}

	popaf;
}

