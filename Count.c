/*
 * Count.c
 *
 *  Created on: 2014-8-21
 *      Author: HP
 */
#include "Count.h"

void FlagPlus()
{
	if (Flag >= FLAGMAX)
	{
		Flag = FLAGMAX;
		ResultCalc();
	}
	else
	{
		Flag++;
		Temp++;
	}
}
void FlagSub()
{
	if (Flag <=FLAGMIN)
	{
		Flag =FLAGMIN;
		ResultCalc();
	}
	else
	{
		Flag--;
		Temp++;
	}
}
void ResultCalc()
{
	static unsigned char Flag_Past=(FLAGMAX-FLAGMIN)/2;	//����ֵ������ʱ�豣��
	unsigned int ShrinkResultLen = 0;
	unsigned int DrawResultLen = 0;
	if (Flag == FLAGMAX && Flag_Past == FLAGMIN)//Shrink Over
	{
		CalcBreathTime();
		ShrinkResultLen = CountShrinkLen + Temp - (FLAGMAX - FLAGMIN - 1);
		SaveShrinkToArray(ShrinkResultLen);
		CountShrinkLen = 0;
		CountDrawLen = CountDrawLen + (FLAGMAX - FLAGMIN - 1);
		Temp = 0;
		CountShrink++;

	}
	if (Flag == FLAGMIN && Flag_Past == FLAGMAX)//Draw Over
	{
		CalcBreathTime();
		DrawResultLen = CountDrawLen + Temp- (FLAGMAX - FLAGMIN - 1);
		SaveDrawToArray(DrawResultLen);
		CountDrawLen = 0;
		CountShrinkLen = CountShrinkLen + (FLAGMAX - FLAGMIN - 1);
		Temp = 0;
		CountDraw++;

	}
	if (Flag == FLAGMIN && Flag_Past == FLAGMIN)//Shrinking
	{
		CountShrinkLen++;

	}
	if (Flag == FLAGMAX && Flag_Past == FLAGMAX)//Shrinking
	{
		CountDrawLen++;

	}
	Flag_Past = Flag;

}
void SaveDrawToArray(const unsigned int _DrawResultLen)
{
	static unsigned char indexDrawResultLen = 0;
	if (indexDrawResultLen >30) indexDrawResultLen = 0;
	arrayDrawResultLen[indexDrawResultLen] = _DrawResultLen;
	indexDrawResultLen++;

}
void SaveShrinkToArray(const unsigned int _ShrinkResultLen)
{
	static unsigned char indexShrinkResultLen = 0;
	if (indexShrinkResultLen >30) indexShrinkResultLen = 0;
	arrayShrinkResultLen[indexShrinkResultLen] = _ShrinkResultLen;
	indexShrinkResultLen++;

}
