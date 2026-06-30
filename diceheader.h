#ifndef DICEHEADER_H
#define DICEHEADER_H

#include <lpc21xx.h>
#define DATA_PIN 0xff
#define RS    1<<8
#define E     1<<9
#define seg_d 0xff<<23
#define seg_1 1<<16 //27//pinsel1
#define seg_2 1<<17
#define seg_3 1<<18
#define seg_4 1<<19
void DATA(unsigned char d);
void CMD(unsigned char cd);
void delay_ms(int ms);
void STR(unsigned char *s);
void display_plr1(int n);
void display_plr2(int n);
void INIT(void);
void CGRAM_WRITE(unsigned char nbytes);

unsigned char seg_lut[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90};
unsigned char cg_lut[]={0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00, //1
	 					0x00,0x00,0x00,0x08,0x00,0x02,0x00,0x00, //2
 						0x00,0x00,0x00,0x08,0x40,0x02,0x00,0x00, //3
 						0x00,0x00,0x00,0x0a,0x00,0xa0,0x00,0x00, //4
 						0x00,0x00,0x00,0x0a,0x04,0x0a,0x00,0x00, //5
 						0x00,0x00,0x00,0x0a,0x0a,0x0a,0x00,0x00}; //6

void delay_ms(int ms)
{
	T1PR=15000-1;
	T1TCR=0X01;
	while(T1TC<ms);
	T1TCR=0X03;
	T1TCR=0x00;

}

void STR(unsigned char *s)
{
	while(*s)
	DATA(*s++);
}

void display_plr1(int n)
{
	if(n<=9)
	{
		IOCLR1=seg_d;
		IOSET1=(seg_lut[0])<<23;
		IOCLR1=seg_1;
		delay_ms(5);
		IOSET1=seg_1;
		//delay_ms(20);

		IOCLR1=seg_d;
		IOSET1=(seg_lut[n])<<23;
		IOCLR1=seg_2;
		delay_ms(5);
		IOSET1=seg_2;
	}
	else
	{	
		IOCLR1=seg_d;
		IOSET1=(seg_lut[n/10])<<23;
		IOCLR1=seg_1;
		delay_ms(5);
		IOSET1=seg_1;

//		delay_ms(20);
		IOCLR1=seg_d;
		IOSET1=(seg_lut[n%10])<<23;
		IOCLR1=seg_2;
		delay_ms(5);
		IOSET1=seg_2;
//		delay_ms(20);
	}
}

void display_plr2(int n)
{
	if(n<=9)
	{
		IOCLR1=seg_d;
		IOSET1=(seg_lut[0])<<23;
		IOCLR1=seg_3;
		delay_ms(5);
		IOSET1=seg_3;
//		delay_ms(20);

		IOCLR1=seg_d;
		IOSET1=(seg_lut[n])<<23;
		IOCLR1=seg_4;
		delay_ms(5);
		IOSET1=seg_4;
	}
	else
	{
		IOCLR1=seg_d;
		IOSET1=(seg_lut[n/10])<<23;
		IOCLR1=seg_3;
		delay_ms(5);
		IOSET1=seg_3;
		//delay_ms(20);

		IOCLR1=seg_d;
		IOSET1=(seg_lut[n%10])<<23;
		IOCLR1=seg_4;
		delay_ms(5);
		IOSET1=seg_4;
		//delay_ms(20);
	}
}

void INIT(void)
{
 	IODIR0 |=DATA_PIN|RS|E;
 	CMD(0X01);
 	CMD(0X02);
 	CMD(0X0C);
 	CMD(0X38);
}

void CGRAM_WRITE(unsigned char nbytes)
{
	unsigned char i;
	CMD(0X40);
	for(i=0;i<nbytes;i++)
	DATA(cg_lut[i]);
}

void CMD(unsigned char cd)
{
	IOCLR0=DATA_PIN;
	IOSET0=cd;
	IOCLR0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
}

void DATA(unsigned char d) 
{
	IOCLR0=DATA_PIN;
	IOSET0=d;
	IOSET0=RS;	
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
}

#endif
