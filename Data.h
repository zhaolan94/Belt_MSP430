/*
 * Data.h
 *
 *  Created on: 2014-9-3
 *      Author: HP
 */

#ifndef DATA_H_
#define DATA_H_
#include "Global.h"
#include "Bluetooth.h"
#include "memorizer.h"
/*
Using Word R/W Mode
��ջʽ����
��һҳǰ��������Ϊ��ǰ����ָ��λ��
*/
#define PAGEBASE 0
#define OFFSETBASE 1
extern unsigned int page;//��ǰҳ����,range [0,4095]
extern unsigned int pageOffset;//ҳ��ƫ��,range [0,127]
void Push(unsigned int *data);
void Pop(unsigned int *data);
void SaveData();//����ARRAYLEN���������
void SendData();
void SavePointer();
void ReadPointer();
#endif /* DATA_H_ */
