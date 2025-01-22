//adc_defines.h
#define FOSC 12000000  //Hz 
#define CCLK (FOSC*5)  //Hz
#define PCLK (CCLK/4)  //Hz 
#define ADCCLK 3000000 //Hz
#define CLKDIV ((PCLK/ADCCLK)-1)

//defines for ADCR sfr
#define CLKDIV_START_BIT 8 //bit 8 to 15
#define PDN_BIT          21
#define ADC_START_BIT    24

//define for ADDR sfr
#define RESULT_START_BIT 6 //bit 6 to 15
#define DONE_BIT         31 
