#include <REGX52.H>
#include "delay.h"
#include "shumaguan.h"
#include "keycode.h"
#include "IR.h"
//sbit led=P2^0;
unsigned char keynum;
unsigned char num;
unsigned char c,compare;
unsigned char address;
unsigned char command;
unsigned char dataflag;
void timing_1init()
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
	
	compare=100;
	display(1,0);
	timing_init();
	while(1)
	{
		keynum=key();
		if(keynum)
		{
			if(keynum==1)
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



//void main()
//{
//	
//	timing_1init();
//	timing_0init();
//	outinterrupt_init();
//	compare=100;
//	display(1,0);
//	while(1)
//	{
//		if(IR_getdataflag())
//		{
//			address=getaddress();
//			command=getcommand();
//			if(command==0x0c)
//			{
//				compare=75;
//				display(1,1);
//			}
//			else if(command==0x18)
//			{
//				compare=50;
//				display(1,2);
//			}
//			else if(command==0x5e)
//			{
//				compare=20;
//				display(1,3);
//			}
//			else if(command==0x08)
//			{
//				compare=0;
//				display(1,4);
//			}
//		}
//	}
//	
//	
//	
//}









void timing()interrupt 3
{
	TL1 = 0xB4;		//设置定时初值
	TH1 = 0xFE;		//设置定时初值
	c++;
	c=c%100;
	if(c<compare)
	{
		P1_0=0;
		led=0;
	}
	else if(c>=compare)
	{
		P1_0=1;
		led=1;
	}
}
