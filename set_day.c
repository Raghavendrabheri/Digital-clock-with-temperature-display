#include <LPC21xx.h>
#include "delay.h"
#include "kpm.h"
#include "kpm_defines.h"

#include "lcd_defines.h"
#include "lcd.h"

int set_d(int);

void set_day(void)
{
	int day;
	char opt;
	
	day=DOW;
	
	while(1)
	{
		CmdLCD(0x01);
		CmdLCD(0xc0);
//set day		
		day=set_d(day);
		
		opt=KeyScan();
		while(ColScan()==0);
		if(opt=='C')
		{
			CmdLCD(0x01);
			break;
		}
	}
	DOW=day;
}

int set_d(int day)
{
	static int sc;
	char opt;
	
	while(1)
		{
			CmdLCD(0x01);
			StrLCD("SEC   C-Save");
			CmdLCD(0xc0);
			print_day(day);
			
			opt=KeyScan();
			delay_ms(500);
			
			if(opt=='+')
			{
				day++;
				delay_ms(100);
				if(day>6)
					day=0;
			}
			else if(opt=='-')
			{
				day--;
				if(day<0)
					day=6;
			}
			else if (opt=='*')
				break;
			
			else if(opt=='C')
			{
				CmdLCD(0x01);
				StrLCD("C - YES");
				CmdLCD(0xc0);
				StrLCD("* - NO");
				break;
			}
		}
		
		sc=day;
		return sc;
}
