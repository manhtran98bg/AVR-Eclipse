/*
 * macro.h
 *
 *  Created on: Oct 5, 2019
 *      Author: kylin
 */

#ifndef MACRO_H_
#define MACRO_H_


#define sbi(sfr,bit)	(sfr|=(1<<bit))	//Set bit cho thanh ghi
#define cbi(sfr,bit)	(sfr&=~(1<<bit))	//clear bit cho thanh ghi
#define tbi(sfr,bit)	(sfr^=(1<<bit)) //dao trang thai bit cua thanh ghi


#endif /* MACRO_H_ */
