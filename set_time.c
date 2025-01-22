#include <LPC21xx.h>
#include "delay.h"
#include "kpm.h"
#include "kpm_defines.h"

#include "lcd_defines.h"
#include "lcd.h"

void print_time(int,int,int );
int set_hour(int,int,int);
int set_min(int,int,int);
int set_sec(int,int,int);

void set_time(void)
{
	int hour,min,sec;
	char opt;
	
	hour=HOUR;
	min=MIN;
	sec=SEC;
	
//	CmdLCD(0x01);
//	StrLCD("HH:MM:SS");
//	CmdLCD(0xc0);
//	print_time(hour,min,sec);
		
	while(1)
	{
		CmdLCD(0x01);
		CmdLCD(0xc0);
//set hours		
		hour=set_hour(hour,min,sec);
//set minutes		
		min=set_min(hour,min,sec);
//set seconds
		sec=set_sec(hour,min,sec);
		
		opt=KeyScan();
		while(ColScan()==0);
		if(opt=='C')
		{
			CmdLCD(0x01);
			break;
		}
	}
	
	HOUR=hour;
	MIN=min;
	SEC=sec;

}
///////////////////////////////////////////
int set_hour(int hour,int min,int sec)
{
	static int hr;
	char opt;
	do
		{
			CmdLCD(0x01);
			StrLCD("HOUR");
			CmdLCD(0xc0);
			print_time(hour,min,sec);
			
			opt=KeyScan();
			delay_ms(500);
			
			if(opt=='+')
			{
				hour++;
				if(hour>23)
					hour=0;
			}
			else if(opt=='-')
			{
				hour--;
				if(hour<0)
					hour=23;
			}
		}while(opt!='*');
		hr=hour;
	
		return hr;
}
//////////////////////////////////////
int set_min(int hour,int min,int sec)
{
	static int mn;
	char opt;
	
	do
		{
			CmdLCD(0x01);
			StrLCD("MIN");
			CmdLCD(0xc0);
			print_time(hour,min,sec);
			
			opt=KeyScan();
			delay_ms(500);
			
			if(opt=='+')
			{
				min++;
				if(min>60)
					min=0;
			}
			else if(opt=='-')
			{
				min--;
				if(min<0)
					min=60;
			}
		}
		while(opt!='*');
		mn=min;

		return mn;
}
////////////////////////////////////////
int set_sec(int hour,int min,int sec)
{
	static int sc;
	char opt;
	
	while(1)
		{
			CmdLCD(0x01);
			StrLCD("SEC   C-Save");
			CmdLCD(0xc0);
			print_time(hour,min,sec);
			
			opt=KeyScan();
			delay_ms(500);
			
			if(opt=='+')
			{
				sec++;
				delay_ms(10);
				if(sec>60)
					sec=0;
			}
			else if(opt=='-')
			{
				sec--;
				if(sec<0)
					sec=60;
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
		
		sc=sec;
		return sc;
}
