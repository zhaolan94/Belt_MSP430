/*
 * UART_Global.c
 * ˵����UART��FIFO�⺯��
 *  Created on: 2013-3-18
 *      Author: Administrator
 */
#include "UART_Global.h"

unsigned char Rx_FIFO[RX_FIFO_SIZE]={0};		//UART����FIFO����
unsigned char Rx_FIFO_DataNum=0;					//UART����FIFO�ġ�������ָʾ����
unsigned char Rx_FIFO_IndexR=0;						//UART����FIFO��ģ�⡰��ָ�롱����
unsigned char Rx_FIFO_IndexW=0;						//UART����FIFO��ģ�⡰дָ�롱����

unsigned char Tx_FIFO[TX_FIFO_SIZE]={0};		//UART����FIFO����
unsigned char Tx_FIFO_DataNum=0;					//UART����FIFO�ġ�������ָʾ����
unsigned char Tx_FIFO_IndexR=0;						//UART����FIFO��ģ�⡰��ָ�롱����
unsigned char Tx_FIFO_IndexW=0;						//UART����FIFO��ģ�⡰дָ�롱����
