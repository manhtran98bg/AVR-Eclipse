/*
 * IE74595.c
 *
 *  Created on: Oct 12, 2019
 *      Author: kylin
 */
#include <avr/io.h>
#include "IE74595.h"
#include "util.h"
void IE74595_Out_Byte(unsigned char chr)
{
	unsigned char i;
	for (i=0;i<8;i++)
	{
		if(chr&(0x80>>i)) sbi(PORTB,DS); else cbi(PORTB,DS);
		cbi(PORTB,SH_CP);
		sbi(PORTB,SH_CP);
	}
	cbi(PORTB,ST_CP);
	sbi(PORTB,ST_CP);
}

