/*
 * UART_init.c
 * ���ܣ���ʼ��USCI_A0ģ��ΪUARTģʽ������UARTΪ������9600,8λ����,��У��,1λֹͣλ
 *  Created on: 2013-3-18
 *  Author: Administrator
 */

#include "MSP430G2553.h"
#include "UART_Event.h"
#include "../Global.h"
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
	  P1SEL |= BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
	  P1SEL2 |= BIT1 + BIT2;

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
	//TACCTL0 &= ~CCIE;//Stop Timmer
#ifdef SAVE
	if((IFG2&UCB0TXIFG) == UCB0TXIFG)
	{
	//IFG2 &= ~UCB0TXIFG;
	//	SPI_TxISR_Hook();
	    UCB0RXBUF;                                            				// Tx��Rx�жϱ�־λ������λ���˴���UCA0RXBUF�ղ��������������UCA0RXIFG���жϱ�־λ
		if(SPI_Tx_Size!=0)
		{
			SPI_Tx_Size-- ;														// �����͵����ݼ�1
			SPI_Tx_Buffer++;											// ����ָ������һ�ֽ�ƫ��
			UCB0TXBUF = *SPI_Tx_Buffer;							// ���뷢�ͻ��棬ͬʱ�����������UCA0TXIFG���жϱ�־λ
		}
		else
			IFG2 &= ~UCB0TXIFG;
		if(SPI_Tx_Size==0)
		_bic_SR_register_on_exit(LPM0_bits);
	//IFG2 &= ~UCB0TXIFG;
	}
#endif
	if((IFG2&UCA0TXIFG) == UCA0TXIFG)
	{

	IFG2 &= ~UCA0TXIFG;
	UART_OnTx();					// ����Tx�¼�������
	//IFG2 &= ~UCA0TXIFG;   // �ֶ������־λ

	}


	//TACCTL0 |= CCIE;//Enable Timmer
	//if (isInTimmer == 0) TACCTL0 |= CCIE;
	
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

	TACCTL0 &= ~CCIE;//Stop Timmer
#ifdef SAVE
	if((IFG2&UCB0RXIFG) == UCB0RXIFG)
	{

	//SPI_RxISR_Hook();
		*SPI_Rx_Buffer = UCB0RXBUF;								//  ��ȡ���ջ��棬ͬʱ�����������UCA0RXIFG���жϱ�־λ
		if(SPI_Rx_Size!=0)
		{
			SPI_Rx_Size-- ;														// �����͵����ݼ�1
			SPI_Rx_Buffer++;												// ����ָ������һ�ֽ�ƫ��
			UCB0TXBUF = 0xFF;												// ����Ϊ���ṩCLK��UCA0TXIFG��־λͬʱ�������
		}
	    IFG2 &= ~UCB0TXIFG; //��
	 if(SPI_Rx_Size==0)
	//	 flagRx = 0;
		 _bic_SR_register_on_exit(LPM0_bits);
	}
	#endif
	if((IFG2&UCA0RXIFG) == UCA0RXIFG)
	{
	IFG2 &= ~UCA0RXIFG;     // �ֶ������־λ
	UART_OnRx();					// ����Rx�¼�������

	}

	if (isInTimmer == 0) TACCTL0 |= CCIE;//Enable Timmer

	
}


