#include <lpc21xx.h>
#include<stdlib.h>
#include "diceheader.h"
#define sw 14
#define sw2 15
void scroll(void);

/*void scroll()
{
	int i,j;
	for(i=0;msg[i+15]!='\0';i++)
	{
		CMD(0x80);
		for(j=0;j<16;j++)
		{
			DATA(msg[i+j]);
			delay_ms(15);
		}
	}
}
*/
void refresh_display(int p1_score,int p2_score,int duration_ms)
{
	int count =duration_ms/25;
	while(count>0)
	{
		display_plr1(p1_score);
		display_plr2(p2_score);
		count--;
	}
}


int main()
{
	int n=0;
	int player1=0;
 	int player2=0;
 	int num;

 	PINSEL2 &=~(1<<2);
	IODIR1 |= seg_d;
 	IODIR1 |= seg_1|seg_2|seg_3|seg_4;

	T0PR=15000-1;
	T0TCR=0X01;
 	srand(T0TC);

 	INIT();
 	CGRAM_WRITE(48);

 	CMD(0X01);
	CMD(0X80);				   
	STR(" SMART DICE ARENA ");
	delay_ms(1000);

	CMD(0x01);
	CMD(0x80);
 	STR(" two player gameing");
	delay_ms(1000);

 	CMD(0X01);		          
	CMD(0X80);
	STR("GAME START !");
	delay_ms(1000);

 	while(n<5)		   
 	{
  		CMD(0x01);
 		CMD(0X80);
  		STR("ROUND "); //P1
		DATA(n+49);
		STR(" PLAYER 1");
  		while(((IOPIN0>>sw)&1)==1)
		{
			refresh_display(player1,player2,25);
		}	 
		num=(rand()%6)+1;
		CMD(0XC0);
		DATA(num+48);
		player1 +=num;
		refresh_display (player1,player2,1500);

		CMD(0x01); //p2
  		CMD(0X80);
  		STR("ROUND ");
		DATA(n+49);
		STR(" PLAYER 2 ");

		while(((IOPIN0>>sw2)&1)==1)
		{
			refresh_display(player1,player2,25);
		}
		num=(rand()%6)+1;
		CMD(0XC0);
		DATA(num+48);
		player2 +=num;

		refresh_display(player1,player2,1500);
		n++;
	}

	T0TCR=0x00;
	CMD(0x01);
	CMD(0x80);

	if(player1<player2)
		STR("PLAYER 2 WIN");
	else if(player1>player2)
		STR("PLAYER 1 WIN");
	else
		STR("MATCH DRAW");
	while(1)
	{
		display_plr1(player1);	 
		display_plr2(player2);
	}
}




