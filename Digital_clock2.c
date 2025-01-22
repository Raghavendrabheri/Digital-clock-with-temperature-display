#include <LPC21xx.h>

#include "delay.h"
#include "defines.h"

#include "kpm.h"
#include "kpm_defines.h"

#include "lcd_defines.h"
#include "lcd.h"

#define EINT_CHNO 15
 u8 flag = 0;
void menu_isr(void)__irq;

void RTC_Init(void);
void set_time(void);
void set_date(void);
void set_day(void);

void print_day(int d)
{
	char day[7][5]={{"SUN"},{"MON"},{"TUE"},{"WED"},{"THU"},{"FRI"},{"SAT"}};
	StrLCD(day[d]);
}

void print_time(int hour,int min,int sec)
{
		CharLCD((hour/10)+48);
		CharLCD((hour%10)+48);
		CharLCD(':');
		CharLCD((min/10)+48);
		CharLCD((min%10)+48);
		CharLCD(':');
		CharLCD((sec/10)+48);
		CharLCD((sec%10)+48);
}

void print_date(int day,int mon,int year)
{
	char month[12][5]={{"JAN"},{"FEB"},{"MAR"},{"APR"},{"MAY"},{"JUN"},{"JUL"},{"AUG"},{"SEP"},{"OCT"},{"NOV"},{"DEC"}};
		
		CharLCD((day/10)+48);
		CharLCD((day%10)+48);
		CharLCD(' ');
		StrLCD(month[mon]);
		CharLCD(' ');
		S32LCD(year);
}
void Init_ADC(void);
f32 Read_ADC(u32);

int main()
{
	float temp;
	PINSEL0|=0x000000CC;

	VICIntEnable=1<<EINT_CHNO;
	VICVectCntl0=1<<5|EINT_CHNO;
	VICVectAddr0=(unsigned int)menu_isr;

	EXTMODE=1<<1;
	
	RTC_Init();
	InitLCD();
	Init_KPM();
	Init_ADC();

	while (1) 
		{
				CmdLCD(0x80);
				print_time(HOUR,MIN,SEC);
				CmdLCD(0xC0);
				print_date(DOM,MONTH,YEAR);
				CmdLCD(0x89);
				print_day(DOW);
				temp=Read_ADC(1);
				CmdLCD(0xCD);
				U32LCD(temp*100);
				CmdLCD(0xCF);
				CharLCD('C');
				if(flag == 1)
				{
				char str[3][10]={{"1.TIME"},{"2.DATE"},{"3.DAY"}};
					int i=0;
					u8 opt;
					
					while(1)
					{
						CmdLCD(0x01);
						StrLCD(str[i]);
						CmdLCD(0xc0);
						StrLCD(str[i+1]);
						opt=KeyScan();
						while(ColScan()==0);
					
						switch(opt)
						{
							case '-': {
							  			if(i<2)
											i++;
										};break;
							case '+':  {
										if(i>0)
											i--;
										};break;
				
							case '1': set_time();break;
							case '2': set_date();break;
							case '3': set_day();break;
							case 'C': flag = 0 ;
									   break;
						}
   						if(flag == 0)
						break;
					}	
				}
    	}		
}

void menu_isr(void)__irq
{
	flag=1;
	EXTINT=1<<1;
	VICVectAddr=0;
}
