/*
 * UART_init.c
 * ���ܣ���ʼ��USCI_A0ģ��ΪUARTģʽ������UARTΪ������9600,8λ����,��У��,1λֹͣλ
 *  Created on: 2013-3-18
 *  Author: Administrator
 */

#include "MSP430G2553.h"
#include "UART_Event.h"
#include "../SPI.h"
/******************************************************************************************************
 * ��       �ƣ�USCI_A0_init()
 * ��       �ܣ���ʼ��USCI_A0ģ��ΪUARTģʽ
 * ��ڲ�������
 * ���ڲ�������
 * ˵       ����UART��Ϊ������9600,8λ����,��У��,1λֹͣλ
 * 					UART��ʼ�����ýϸ��ӣ�����ʹ��Grace���ú�����ֲ����ķ���
 * ��       ������
 ******************************************************************************************************/
void USCI_A0_init(void)
{
	//-----����IO�ڵ�TXD��RXD����-----
	  P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
	  P1SEL2 = BIT1 + BIT2;
	  P1DIR |= BIT6;
	  UCA0CTL1 |= UCSWRST;

	  //-----����UARTʱ��ԴΪACLK-----
	  UCA0CTL1 |= UCSSEL_2;                // CLK = smCLK
	  //-----��ֲGrace���õĲ����ʲ���-----
	  UCA0BR0 =8;                           // Boud = 115200
	  UCA0BR1 = 0;
	  UCA0MCTL = UCBRS_6;     // Modulation UCBRSx = 6
	  UCA0CTL1 &= ~UCSWRST;               // **Initialize USCI state machine**
      IE2 |= UCA0RXIE + UCA0TXIE;           // Enable USCI_A0 TX/RX interrupt
      _enable_interrupts();                 		  // �����ж�
}
/******************************************************************************************************
 * ��       �ƣ�USCI0TX_ISR()
 * ��       �ܣ���ӦTx�жϷ���
 * ��ڲ�������
 * ���ڲ�������
 * ˵       ���������жϱ�־λ�п��ܲ����Զ�����ģ����ֶ����һ�Σ��Է���һ
 * ��       ������
 ******************************************************************************************************/
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
{
	_DINT();
	if((IFG2&UCA0TXIFG) == UCA0TXIFG)
	{

	IFG2&=~UCA0TXIFG;
	UART_OnTx();					// ����Tx�¼�������
       // �ֶ������־λ

	}
	#ifdef SAVE
	if((IFG2&UCB0TXIFG) == UCB0TXIFG)
	{
		SPI_TxISR_Hook();
	}
	#endif
	_EINT();
}
/******************************************************************************************************
 * ��       �ƣ�USCI0RX_ISR()
 * ��       �ܣ���ӦRx�жϷ���
 * ��ڲ�������
 * ���ڲ�������
 * ˵       ���������жϱ�־λ�п��ܲ����Զ�����ģ����ֶ����һ�Σ��Է���һ
 * ��       ������
 ******************************************************************************************************/
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	_DINT();
	if((IFG2&UCA0RXIFG) == UCA0RXIFG)
	{
	IFG2&=~UCA0RXIFG;     // �ֶ������־λ
	UART_OnRx();					// ����Rx�¼�������
	//P1OUT ^= BIT6;
	}
	#ifdef SAVE
	if((IFG2&UCB0RXIFG) == UCB0RXIFG)
	{
	SPI_RxISR_Hook();
	}
	#endif
	_EINT();
}


