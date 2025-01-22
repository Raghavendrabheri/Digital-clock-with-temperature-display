#include <LPC21xx.h>
#include "delay.h"
#include "kpm.h"
#include "kpm_defines.h"

#include "lcd_defines.h"
#include "lcd.h"

void print_date(int,int,int );
int set_dayy(int,int,int);
int set_month(int,int,int);
int set_year(int,int,int);

void set_date(void)
{
	int day,month,year;
	char opt;
	
	day=DOM;
	month=MONTH;
	year=YEAR;
	while(1)
	{
		CmdLCD(0x01);
		CmdLCD(0xc0);
//set hours		
		day=set_dayy(day,month,year);
//set minutes		
		month=set_month(day,month,year);
//set seconds
		year=set_year(day,month,year);
		
		opt=KeyScan();
		while(ColScan()==0);
		if(opt=='C')
		{
			CmdLCD(0x01);
			break;
		}
	}
	
	DOM=day;
	MONTH=month;
	YEAR=year;
}
///////////////////////////////////////////
int set_dayy(int day,int month,int year)
{
	static int dy;
	char opt;
	do
		{
			CmdLCD(0x01);
			StrLCD("DAY");
			CmdLCD(0xc0);
			print_date(day,month,year);
			
			opt=KeyScan();
			delay_ms(500);
			
			if(opt=='+')
			{
				day++;
				if(day>31)
					day=1;
			}
			else if(opt=='-')
			{
				day--;
				if(day<1)
					day=31;
			}
		}
		while(opt!='*');
		dy=day;
		return dy;
}
///////////////////////////////////////////
int set_month(int day,int month,int year)
{
	char opt;
	static int mt;

	do
		{
			CmdLCD(0x01);
			StrLCD("MONTH");
			CmdLCD(0xc0);
			print_date(day,month,year);
			
			opt=KeyScan();
			delay_ms(500);
			
			if(opt=='+')
			{
				month++;
				if(month>11)
					month=0;
			}
			else if(opt=='-')
			{
				month--;
				if(month<0)
					month=11;
			}
		}
		while(opt!='*');
		mt=month;
		return mt;
}
////////////////////////////////////////
int set_year(int day,int month,int year)
{
	char opt;
	static int yr;

	while(1)
		{
			CmdLCD(0x01);
			StrLCD("YEAR   C-Save");
			CmdLCD(0xc0);
			print_date(day,month,year);
			
			opt=KeyScan();
			delay_ms(50);
			
			if(opt=='+')
			{
				year++;
			}
			else if(opt=='-')
			{
				year--;
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
		yr=year;
		return yr;
}

