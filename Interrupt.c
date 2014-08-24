/*
 * Interrupt.c
 *
 *  Created on: 2014-8-20
 *      Author: HP
 */
#include "Interrupt.h"
#include "Count.h"
#include "Time.h"
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TA0_ISR(void)
{
	_DINT();
	TA0CTL &= ~TAIFG;
	Real_Time();
	P1_IODect();//IOɨ��

	_EINT();
}
void P1_IODect()
{
	static unsigned char P13_Now=0;	//����ֵ������ʱ�豣��

	unsigned char P13_Past=0;

	P13_Past=P13_Now;

	//-----��ѯIO������Ĵ���-----

	if((P1IN&BIT3) == BIT3) 	P13_Now= 1;
		else		P13_Now = 0;
	//-----ǰһ�θߵ�ƽ����һ�ε͵�ƽ��˵����������-----
	if((P1IN&BIT4) == BIT4)
	{
		if((P13_Now==1)&&(P13_Past==0))
#ifndef TEST
			FlagPlus();
#else
			CountDrawLen++;
#endif
		if((P13_Now==0)&&(P13_Past==1))
#ifndef TEST
			FlagSub();
#else
			CountShrinkLen++;
#endif
	}
	else
	{
		if((P13_Now==1)&&(P13_Past==0))
#ifndef TEST
			FlagSub();
#else
			CountShrinkLen++;
#endif
		if((P13_Now==0)&&(P13_Past==1))
#ifndef TEST
			FlagPlus();
#else
			CountDrawLen++;
#endif
	}

}
