/*
 * main.c
 *
 *  Created on: Mar 26, 2021
 *      Author: manht
 */
#include <avr/io.h>
#include <util/delay.h>
int main()
{
	DDRC = (1<<PC0);
	PORTC = (1<<PC0);
	while (1)
	{
		PORTC ^=(1<<PC0);
		_delay_ms(1000);
	}
}
