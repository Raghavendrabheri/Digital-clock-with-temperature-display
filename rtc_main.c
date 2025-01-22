#include <lpc21xx.h>

//include LCD header files
#include "lcd_defines.h"
#include "lcd.h"

// System clock and peripheral clock Macros
#define FOSC 12000000
#define CCLK (FOSC*5)    
#define PCLK (CCLK/4)

// RTC Macros
#define PREINT_VAL  ((PCLK / 32768) - 1)
#define PREFRAC_VAL (PCLK-((PREINT + 1) * 32768))
#define RTC_ENABLE  (1<<0)
#define RTC_RESET   (1<<1)
#define RTC_EXT_CLOCK (1<<4)




void RTC_SetTimeInfo(unsigned int hour, unsigned int min, unsigned int sec);
void RTC_SetDateInfo(unsigned int date, unsigned int month, unsigned int year);
void RTC_SetHour(unsigned int);
void RTC_SetMin(unsigned int);
void RTC_SetSec(unsigned int);
void RTC_SetDate(unsigned int);
void RTC_SetMonth(unsigned int);
void RTC_SetYear(unsigned int);
void RTC_SetDay(unsigned int);

unsigned int RTC_GetHour(void);
unsigned int RTC_GetMin(void);
unsigned int RTC_GetSec(void);
unsigned int RTC_GetDate(void);
unsigned int RTC_GetMonth(void);
unsigned int RTC_GetYear(void);
unsigned int RTC_GetDay(void);




// RTC Initialization: Configures and enables the RTC
void RTC_Init(void) 
{
    // Reset the RTC
		//CCR = RTC_RESET;
	
    // Set prescaler integer part
		PREINT = PREINT_VAL;
	
    // Set prescaler fractional part
		PREFRAC = PREFRAC_VAL;
    // Enable the RTC
		CCR = RTC_ENABLE|RTC_EXT_CLOCK;
	
}
// RTC_SetTime: Sets the time and date on the RTC
void RTC_SetTimeInfo(unsigned int hour, unsigned int min, unsigned int sec) 
{

    // Set hours
		HOUR = hour;	  
    // Set minutes
		MIN = min;
	  // Set seconds
		SEC = sec;

}





