#include	"comparator.h"
#include "../../head_extern.h"
#include	"../key/key.h"
#include	"../led/led.h"
void comparator_test(void);
extern byte motor_state_temp,motor_state_temp2;
void comparator_init(void)
{
//	(gpcs.5=0 & gpcs.4=0)		V internal R = (9+n)/32*VDD, n = gpcs[3:0] in decimal
//	(gpcs.5=1 & gpcs.4=1)		V internal R = (n+1)/32*VDD, n = gpcs[3:0] in decimal					
//	(gpcs.5=0 & gpcs.4=1)		V internal R = (n+1)/24* VDD, n = gpcs[3:0] in decimal
//	(gpcs.5=1 & gpcs.4=0)		V internal R = (9+n)/40*VDD, n = gpcs[3:0] in decimal

// gpcs = 0x20 | 8;					// choose case 3 and R=8 => 2.8V
//	gpcc = 0b1_0_00_010_0;			 // 启用比较器, 负输入=band-gap, 正输入=Vinternal R
//	$ gpcs = 0b1_0_10_1000;
		/*	At bit 5 ~ 0, you can use the follow items
				VDD*(9~24)/32
				VDD*(1~16)/24
				VDD*(9~24)/40
				VDD*(1~16)/32

                        Ex :    $ GPCS  Output, VDD*15/32
                                $ GPCS  Output, VDD/2
		*/
	$ gpcs   VDD*13/32;;    	//2.90v
//	$ gpcs  VDD*7/24;    		//3.96v
//	$ gpcs  VDD*8/24;    		//3.51v
//	$ gpcs   VDD*12/40;;    	//3.96v								
//	$ gpcs   VDD*9/32;;    		//4.13v
//	$ gpcs   VDD*11/40;;    	//4.22v

//	$ gpcs   VDD*12/40;;    	//3.96v	
//		$ gpcs   VDD*13/32;;    	//2.86v	
	$ gpcc  Enable, BANDGAP,P_R;  // 启用比较器, 负输入=band-gap, 正输入=Vinternal R
		
//	while(1)
	{
//		comparator_test();
	}
	
}

void comparator_test(void)
{

	if(gpcc.6 )  //VDD大于3.3v
	{
		nop;
	}
	else	//VDD小于3.3v
	{
		nop;
	}
}
 
void check_low(void)
{
	if(f_work)
	{
		if(gpcc.6 )  //VDD大2.9
		{
			nop;
			low_cnt=0;
		}
		else	//VDD小于2.9v
		{
			low_cnt++;
			if(low_cnt>100)
			{
				f_work=0;
				motor_state=0;   
				motor_state_temp=100;
				low_cnt=0;
			}
		}
	}
	else
	{
		low_cnt=0;
	}
	
}