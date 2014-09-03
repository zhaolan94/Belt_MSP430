#include"AT45DB081.h"


unsigned char CMD[5];


//����1д����
void FlashBuffer1ProgNoErase(unsigned int AT450XXPageAddr) //ֱ�ӽ�����1д��Flashһҳ(������)
{


    while(!(GetFlashStatus()&128));
    SPI_CS_Low();


    CMD[0] = (B1_TO_PAGE_WITHOUT_ERASE);
    CMD[1] = ((unsigned char)(AT450XXPageAddr >> 7));
    CMD[2] = ((unsigned char)(AT450XXPageAddr << 1));
    CMD[3] = (0x00);

    SPI_TxFrame(CMD,4);

    SPI_CS_High();
}
void chip_erase()
{
    while(!(GetFlashStatus()&128));
    SPI_CS_Low();


    CMD[0] = (CHIP_ERASE_1);
    CMD[1] = (CHIP_ERASE_2);
    CMD[2] = (CHIP_ERASE_3);
    CMD[3] = (CHIP_ERASE_4);

    SPI_TxFrame(CMD,4);

    SPI_CS_High();
}
//д���棫����������д����
void FlashAutoProgViaBuffer1(unsigned int AT450XXPageAddr,unsigned int start_addr, unsigned int len,unsigned char *buffer)
//��ָ������ͨ������1д��Flashָ��λ��(�Ȳ���)
{

    while(!(GetFlashStatus()&128));
    SPI_CS_Low();


    CMD[0] = (PAGE_PROG_THROUGH_B1);//������1Ϊ82H
    CMD[1] = ((unsigned char)(AT450XXPageAddr >> 7));
    CMD[2] = ((unsigned char)(AT450XXPageAddr << 1 + start_addr>>8));
    CMD[3] = ((unsigned char)start_addr);

    SPI_TxFrame(CMD,4);
    SPI_TxFrame(buffer,len);

    SPI_CS_High();
}

unsigned char GetFlashStatus()
{
    unsigned char staus[1];

    SPI_CS_Low();//оƬѡ��
    CMD[0] = STATUS_REGISTER;
    SPI_TxFrame(CMD,1);


    SPI_RxFrame(staus,1);
    SPI_CS_High();
    return staus[0];

}

//����������1д����
void FlashBuffer1ProgAutoErase(unsigned int AT450XXPageAddr) //ֱ�ӽ�����1д��Flashһҳ(�Ȳ���)
{
    while(!(GetFlashStatus()&128));
    SPI_CS_Low();


    CMD[0] = (B1_TO_PAGE_WITH_ERASE);
    CMD[1] = ((unsigned char)(AT450XXPageAddr >> 7));
    CMD[2] = ((unsigned char)(AT450XXPageAddr << 1));
    CMD[3] = 0;

    SPI_TxFrame(CMD,4);

    SPI_CS_High();
}

void PageToBuffer2(unsigned int AT450XXPageAddr)    //��Flash��һҳ������2
{

    while(!(GetFlashStatus()&128));
    SPI_CS_Low();


    CMD[0] = (PAGE_TO_B2_XFER);

    CMD[1] = ((unsigned char)(AT450XXPageAddr >> 7));
    CMD[2] = ((unsigned char)(AT450XXPageAddr << 1));
    CMD[3] = 0;

    SPI_TxFrame(CMD,4);
    SPI_CS_High();

}

void PageToBuffer1(unsigned int AT450XXPageAddr)    //��Flash��һҳ������2
{

    while(!(GetFlashStatus()&128));
    SPI_CS_Low();


    CMD[0] = (PAGE_TO_B1_XFER);

    CMD[1] = ((unsigned char)(AT450XXPageAddr >> 7));
    CMD[2] = ((unsigned char)(AT450XXPageAddr << 1));
    CMD[3] = 0;

    SPI_TxFrame(CMD,4);
    SPI_CS_High();

}

//���û���2��
void FlashBuffer2Read(unsigned int star_addr,unsigned int len, unsigned char *buffer)
//�ӻ�����2��ָ��λ��(0-255)�ж���ָ���ֽ�
{

    while(!(GetFlashStatus()&128));
    SPI_CS_Low();
    CMD[0] = (BUFFER_2_READ);

    CMD[1] = 0;

    CMD[2] = ((unsigned char)(star_addr>>8));
    CMD[3] = ((unsigned char)(star_addr));

    CMD[4] = 0;

    SPI_TxFrame(CMD,5);

    SPI_RxFrame(buffer,len);



    SPI_CS_High();

}
//���û���1��
void FlashBuffer1Read(unsigned int star_addr,unsigned int len, unsigned char *buffer)
//�ӻ�����1��ָ��λ��(0-255)�ж���ָ���ֽ�
{

    while(!(GetFlashStatus()&128));
    SPI_CS_Low();
    CMD[0] = (BUFFER_1_READ);

    CMD[1] = 0;

    CMD[2] = ((unsigned char)(star_addr>>8));
    CMD[3] = ((unsigned char)(star_addr));

    CMD[4] = 0;

    SPI_TxFrame(CMD,5);

    SPI_RxFrame(buffer,len);



    SPI_CS_High();

}

//���û���1д
void FlashBuffer1Write(unsigned int start_addr, unsigned int len,unsigned char *buffer)
//�򻺳���1��ָ��λ��(0-255)д��ָ���ֽ�
{
    unsigned int i;

    while(!(GetFlashStatus()&128));
    SPI_CS_Low();
    CMD[0] = (BUFFER_1_WRITE);
    CMD[1] = 0;
    CMD[2] = ((unsigned char)(start_addr>>8));
    CMD[3] = ((unsigned char)(start_addr ));


    SPI_TxFrame(CMD,4);


    SPI_TxFrame(buffer,len);

    SPI_CS_High();
}
//���û���2д
void FlashBuffer2Write(unsigned int start_addr, unsigned int len,unsigned char *buffer)
//�򻺳���2��ָ��λ��(0-255)д��ָ���ֽ�
{
    unsigned int i;

    while(!(GetFlashStatus()&128));
    SPI_CS_Low();
    CMD[0] = (BUFFER_2_WRITE);
    CMD[1] = 0;
    CMD[2] = ((unsigned char)(start_addr>>8));
    CMD[3] = ((unsigned char)start_addr);

    SPI_TxFrame(CMD,4);


    SPI_TxFrame(buffer,len);

    SPI_CS_High();
}
