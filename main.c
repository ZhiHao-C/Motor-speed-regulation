#include <REGX52.H>
#include "delay.h"
#include "shumaguan.h"
#include "keycode.h"
unsigned char keynum;
unsigned char c,compare;
void timing_1init()             //用定时器1初始化
{
	TMOD=0X10;
	TF1=0;
	EA=ET1=1;
	TL1 = 0xB4;		//设置定时初值
	TH1 = 0xFE;		//设置定时初值
	TR1 =1;
}


void main()
{
	
	compare=100;            //初始先在第一个数码管显示0并调节占空比为0
	display(1,0);
	timing_init();
	while(1)
	{
		keynum=key();
		if(keynum)
		{
			if(keynum==1)//按键1按下占空比为1/4
			{
				compare=75;
				display(1,keynum);
			}
			else if(keynum==2)
			{
				compare=50;
				display(1,keynum);
			}
			else if(keynum==3)
			{
				compare=20;
				display(1,keynum);
			}
			else if(keynum==4)
			{
				compare=0;
				display(1,keynum);
			}
		}
		
	}
}




void timing()interrupt 3
{
	TL1 = 0xB4;		//设置定时初值
	TH1 = 0xFE;		//设置定时初值
	c++;                    //每次中断加1
	c=c%100;                //c为100清零
	if(c<compare)           //调节占空比
	{
		P1_0=0;
	}
	else if(c>=compare)
	{
		P1_0=1;
	}
}
