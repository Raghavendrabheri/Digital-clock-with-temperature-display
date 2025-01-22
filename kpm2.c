//kpm2.c
#include <LPC21xx.h>
#include "types.h"
#include "defines.h"
#include "kpm_defines.h"
/*
u8 kpmLUT[4][4]=
{
	{1,2,3,4},
	{5,6,7,8},
	{9,10,11,12},
	{13,14,15,16}
};
*/
u8 kpmLUT[4][4]=
{
	{'7','8','9','/'},
	{'4','5','6','x'},
	{'1','2','3','-'},
	{'C','0','*','+'}
};

u32 ColScan(void)
{
	u32 t0,t1,t2,t3;
	t0=READBIT(IOPIN1,COL0);
	t1=READBIT(IOPIN1,COL1);
	t2=READBIT(IOPIN1,COL2);
	t3=READBIT(IOPIN1,COL3);
	return (t0&t1&t2&t3);	
}

u32 RowCheck(void)
{
	u32 rNo;
	//ground 0th row ,with others high
	SCLRBIT(IOCLR1,ROW0);
	SSETBIT(IOSET1,ROW1);
	SSETBIT(IOSET1,ROW2);
	SSETBIT(IOSET1,ROW3);
	if(ColScan()==0)	{	rNo=0; goto exitRowCheck;	}
	//ground 1st row ,with others high
	SCLRBIT(IOCLR1,ROW1);
	SSETBIT(IOSET1,ROW0);
	SSETBIT(IOSET1,ROW2);
	SSETBIT(IOSET1,ROW3);
	if(ColScan()==0)	{	rNo=1; goto exitRowCheck;	}	
	//ground 2nd row ,with others high
	SCLRBIT(IOCLR1,ROW2);
	SSETBIT(IOSET1,ROW0);
	SSETBIT(IOSET1,ROW1);
	SSETBIT(IOSET1,ROW3);
	if(ColScan()==0)	{	rNo=2; goto exitRowCheck;	}	
	//ground 3rd row ,with others high
	SCLRBIT(IOCLR1,ROW3);
	SSETBIT(IOSET1,ROW0);
	SSETBIT(IOSET1,ROW1);
	SSETBIT(IOSET1,ROW2);
	if(ColScan()==0)	{	rNo=3;	                	}	
	
	exitRowCheck:
	//re-initialize all rows
	SCLRBIT(IOCLR1,ROW0);
	SCLRBIT(IOCLR1,ROW1);
	SCLRBIT(IOCLR1,ROW2);
	SCLRBIT(IOCLR1,ROW3);

	return rNo;
}

u32 ColCheck(void)
{
	u32 cNo;
	if(READBIT(IOPIN1,COL0)==0)       		cNo=0;
	else if(READBIT(IOPIN1,COL1)==0)  		cNo=1;
	else if(READBIT(IOPIN1,COL2)==0)  		cNo=2;
	else if(READBIT(IOPIN1,COL3)==0)  		cNo=3;
	return cNo;
}	

u8 KeyScan(void)
{
	u32 rNo,cNo,keyV;
	//wait to detect any key press
	while(ColScan());
	//identify row in which key was pressed
	rNo=RowCheck();
	//identify col in which key was pressed
	cNo=ColCheck();
	//extract/map key value for key pressed
	keyV=kpmLUT[rNo][cNo];
	return keyV;
}

void Init_KPM(void)
{
	//cfg row lines as gpio output
	SETBIT(IODIR1,ROW0);
	SETBIT(IODIR1,ROW1);
	SETBIT(IODIR1,ROW2);
	SETBIT(IODIR1,ROW3);
	//hence all rows are grounded
	//default all col lines are gpio input
}

u32 ReadNum(void)
{
	u8 keyC;
	u32 num=0;
	while(1)
	{
		keyC=KeyScan();
		if(keyC>='0' && keyC<='9')
		{
			num=(num*10)+(keyC-48);
			while(ColScan()==0);
		}
		else
		{
			break;
		}	
	}
	return num;
}
