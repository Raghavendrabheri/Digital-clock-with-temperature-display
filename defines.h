                   /* defines.h */
									 
#ifndef __DEFINES_H__
#define __DEFINES_H__

#define SETBIT(WORD,BITPOS)            (WORD|=(1<<BITPOS))
#define SSETBIT(WORD,BITPOS)           (WORD=1<<BITPOS)
#define SCLRBIT(WORD,BITPOS)           (WORD=1<<BITPOS)
#define CLRBIT(WORD,BITPOS)            (WORD&=~(1<<BITPOS))
#define CPLBIT(WORD,BITPOS)            (WORD^=(1<<BITPOS))
#define WRITEBIT(WORD,BITPOS,BIT)      (BIT?SETBIT(WORD,BITPOS):CLRBIT(WORD,BITPOS))
#define READBIT(WORD,BITPOS)           ((WORD>>BITPOS)&1)
#define READWRITEBIT(WORD,WBIT,RBIT)   (WORD=((WORD&~(1<<WBIT))|(((WORD>>RBIT)&1)<<WBIT)))
#define WRITEUNIBBLE(WORD,BITPOS,BYTE) (WORD=(WORD&~(0x0000000F<<BITPOS))|((BYTE>>4)<<BITPOS))
#define WRITELNIBBLE(WORD,BITPOS,BYTE) (WORD=(WORD&~(0x0000000F<<BITPOS))|((BYTE&0X0F)<<BITPOS))
#define READNIBBLE(WORD,BITPOS)        ((WORD>>BITPOS)&0x0000000F)
#define WRITEBYTE(WORD,BITPOS,BYTE)    (WORD=(WORD&~(0x000000FF<<BITPOS))|(BYTE<<BITPOS))      
#define READBYTE(WORD,BITPOS)          ((WORD>>BITPOS)&0x000000FF)

#endif










