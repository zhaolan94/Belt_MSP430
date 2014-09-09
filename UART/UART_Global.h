/*
 * UART_Global.h
 * ˵����UART��FIFO�⺯��ͷ�ļ�
 *  Created on: 2013-3-18
 *      Author: Administrator
 */

#ifndef UART_GLOBAL_H_
#define UART_GLOBAL_H_
#include "../Bluetooth.h"
#include "../Global.h"
#define RX_FIFO_SIZE 16		//���ջ�������С�궨��
#define TX_FIFO_SIZE 64		//���ͻ�������С�궨��

extern  unsigned char Rx_FIFO[RX_FIFO_SIZE];
extern  unsigned char Rx_FIFO_DataNum;
extern  unsigned char Rx_FIFO_IndexR;
extern  unsigned char Rx_FIFO_IndexW;

extern  unsigned char Tx_FIFO[TX_FIFO_SIZE];
extern  unsigned char Tx_FIFO_DataNum;
extern  unsigned char Tx_FIFO_IndexR;
extern  unsigned char Tx_FIFO_IndexW;

#endif /* UART_GLOBAL_H_ */
