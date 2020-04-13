#include	"led.h"
#include "../../head_extern.h"
#include	"../key/key.h"
#include	"../motor/motor.h"
#define led_on	1
#define led_off 0    
void led_init(void)
{ 
	$ led_blue out,low;
	led_blue=led_off;

	 
	$ led_red out,low;
	led_red=led_off;
}
void led_even(void)
{
	blue_even();
}

void blue_even(void)
{

	if(f_work)
	{
		if(work_time<20*60)
		{
			led_blue=led_on;
			led_red=led_off;
		}
		else if(work_time<30*60)
		{
			led_blue=led_off;
			led_red=led_on;
		}
		else
		{
			led_blue=led_off;
			led_red=led_off;
			f_work=0;
		}
	}
	else
	{
		led_blue=led_off;
		led_red=led_off;	
	}

}



/********************/