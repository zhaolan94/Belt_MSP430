/*
 * Data.c
 *
 *  Created on: 2014-9-3
 *      Author: HP
 */

#include "Data.h"
unsigned int pageIndex = 0;
unsigned int pageOffsetIndex = OFFSETBASE + 1;
void Push(unsigned int *data)
{
	static unsigned char times = 0;
	write_16(pageIndex,pageOffsetIndex,1,data);
	pageOffsetIndex++;
	if(pageOffsetIndex > 127)
	{
		pageOffsetIndex = 0;
		pageIndex++;
	}
	if(pageIndex>4095)
	{
		pageIndex = 0;
		pageOffsetIndex = OFFSETBASE+1;
	}
	times++;
	if (times == 3)
	{
		SavePointer();
		times = 0;
	}


}
unsigned char Pop(unsigned int *data)
{
	static unsigned char times = 0;
	read_16(pageIndex,pageOffsetIndex,1,data);
	if(pageIndex == 0 && pageOffsetIndex == OFFSETBASE+1)
	{
	//	pageIndex = 4095;
	//	pageOffsetIndex = 127;
		SavePointer();
		return 1;

	}
	if(pageOffsetIndex == 0)
	{
		pageOffsetIndex = 127;

			pageIndex--;
	}

	else
	{
		pageOffsetIndex--;

	}
	times++;
	if (times == 3)
	{
		SavePointer();
		times = 0;
	}
	return 0;
	//SavePointer();


}
void SaveData()
{
	int i;
	for(i = 0;i<ARRAYLEN ;i++)
	{
		Push(&BreathTime[i]);
		Push(&arrayDrawResultLen[i]);
		Push(&arrayShrinkResultLen[i]);
	}
	SavePointer();
}
void FlushFlash()
{
	pageIndex = 0;
	pageOffsetIndex = OFFSETBASE + 1;
	SavePointer();
}
void SavePointer()
{
	write_16(0,0,1,&pageIndex);
	write_16(0,1,1,&pageOffsetIndex);
}
void ReadPointer()
{
	read_16(0,0,1,&pageIndex);
	read_16(0,1,1,&pageOffsetIndex);
}
void SendData()
{
	unsigned char temp,i;
	unsigned int itemp;
/*	if(BState == BTRANSMIT)
	{
		UART_SendString("READY+");
		BState = PRESEND;
		return;
	}*/

	if(BState == BTRANSMIT)
	{
		if(TransmitMode == REALTIME)
		{
			for(i=0;i<ARRAYLEN;i++)
			{

				temp = BreathTime[i] & 0x00ff;
				Tx_FIFO_WriteChar(temp);
				temp = (BreathTime[i]>>8) & 0x00ff;
				Tx_FIFO_WriteChar(temp);
				temp = arrayDrawResultLen[i] & 0x00ff;
				Tx_FIFO_WriteChar(temp);
				temp = (arrayDrawResultLen[i]>>8) & 0x00ff;
				Tx_FIFO_WriteChar(temp);
				temp = arrayShrinkResultLen[i] & 0x00ff;
				Tx_FIFO_WriteChar(temp);
				temp = (arrayShrinkResultLen[i]>>8) & 0x00ff;
				Tx_FIFO_WriteChar(temp);
				/*
				Tx_FIFO_WriteChar(123);
				Tx_FIFO_WriteChar(456);
				Tx_FIFO_WriteChar(123);
				Tx_FIFO_WriteChar(456);
				Tx_FIFO_WriteChar(123);
				Tx_FIFO_WriteChar(456);
		*/
			}
			UART_SendString("READY+");
		}
		else if (TransmitMode == HISTORY)
		{
			i = 0;
			while(!Pop(&itemp))
			{
				temp = itemp & 0x00ff;
				Tx_FIFO_WriteChar(temp);
				temp = (itemp >>8)& 0x00ff;
				Tx_FIFO_WriteChar(temp);
				i++;
				if(i == 15)
				{
					UART_SendString("READY+");
					i = 0;
				}
			}
		}
	//BState = IDLE;
	}


}
