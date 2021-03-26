/*
 * main.c
 *
 *  Created on: Oct 12, 2019
 *      Author: kylin
 */

#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include "IE74595.h"
#include <avr/interrupt.h>
#define BTN PB3
volatile unsigned char j,i,val,b;
void effect1()
{
	for(i=0;i<4;i++)
	{
		//Sang tu led 1->8
		for(j=0;j<8;j++)
		{
			IE74595_Out_Byte(1<<j);
			_delay_ms(15);
		}
		//Sang tu led 8->1
		for(j=0;j<8;j++)
		{
			IE74595_Out_Byte(0x80>>j);
			_delay_ms(15);
		}
	}
	IE74595_Out_Byte(0xFF);
	_delay_ms(30);
	IE74595_Out_Byte(0);
}
void effect2()
{
//Sang led chan, le
	for(j=0;j<10;j++)
	{
		IE74595_Out_Byte(0xAA);
		_delay_ms(20);
		IE74595_Out_Byte(0x55);
		_delay_ms(20);
	}
	IE74595_Out_Byte(0);
}
void effect3()
{
	b=0;
	//Sang dan cac led tu 1-8
	for (i=0;i<4;i++)
	{
	for(j=0;j<8;j++)
	{
		b|=(1<<j);
		IE74595_Out_Byte(b);
		_delay_ms(15);
	}
	//Tat dan cac led tu 8-1
	for(j=0;j<8;j++)
	{
		b&=~(0x80>>j);
		IE74595_Out_Byte(b);
		_delay_ms(15);
	}
	}
}
void effect4()
{
	unsigned char a,k=0;
	b=0;
	for(j=8;j>0;j--)
	{
		for (a=0;a<j;a++)
		{
			b=(0x80>>a)|k;
			IE74595_Out_Byte(b);
			_delay_ms(15);
		}
		k=b;
	}
	k=0;
	b=0;
	IE74595_Out_Byte(b);
	for(j=8;j>0;j--)
		{
			for (a=0;a<j;a++)
			{
				b=(1<<a)|k;
				IE74595_Out_Byte(b);
				_delay_ms(15);
			}
			k=b;
		}
	for(j=0;j<5;j++)
	{
		IE74595_Out_Byte(0xff);
		_delay_ms(15);
		IE74595_Out_Byte(0x00);
		_delay_ms(15);
	}
}
int main()
{

	DDRB |=(1<<DS)|(1<<SH_CP)|(1<<ST_CP);
	PORTB |= (1<<DS)|(1<<SH_CP)|(1<<ST_CP);
	DDRB &=~(1<<BTN);
	PORTB |=(1<<BTN);
	//Tat ngoai vi khong can thiet
	ACSR = (1<<ACD);
	//Thiet lap ngat pin change
	GIMSK=(1<<PCIE);
	PCMSK = (1<<PCINT3);
	sei();
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	while (1)
	{
		sleep_mode();
	}
}
ISR(PCINT0_vect)
{
	if(val == 0) effect1();
	else if (val == 2) effect2();
	else if (val == 4) effect3();
	else if (val == 6) effect4();
	val++;
	if (val >8) val =0;
}
