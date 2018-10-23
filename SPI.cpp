/*
 * SPI.cpp
 *
 * Created: 2018/10/23 13:16:12
 *  Author: yazawa
 */ 

#include "SPI.h"

void SPI::spiInit(){
	/* SPI�ݒ� */
	SPCR |= 0b01010001;
	/*	  	  |||||||+- SPR0 SPI�N���b�N�I��
			  ||||||+-- SPR1 
			  |||||+--- CPHA
			  ||||+---- CPOL
			  |||+----- MSTR ��/�����u�ݒ�(MSR=1/SLV=0)
			  ||+------ DORD
			  |+------- SPE  SPI����
			  +-------- SPIE SPI��������
	*/
	
	/* SPI�g�p�|�[�g�ݒ� */
	DDRB  |= 0b10110000; /* �������t����� */
	/*	   	   |||||||+- SCK  SPI�N���b�N  �o�� ���܂���t�I
			   ||||||+-- MISO SPIϽ���     ����
			   |||||+--- MOSI SPIϽ����    �o��
			   ||||+---- SS   SPI�ڰ�޾ڸ� �o��
			   |||+----- BTN4
			   ||+------ BTN3
			   |+------- BTN2
			   +-------- BTN1
	*/
}
void SPI::spiSend(uint8_t data){
	SPDR = data; /* SPI�f�[�^���W�X�^�ɏ�������ő��M�J�n */
	while((SPSR & (1<<SPIF)) == 0); /* ���M�����҂� */
}

void SPI::spiRead(){
	
}

void SPI::spiCtrlCs(uint8_t en){
	
	if(en == DISABLE){
		/* SPI CS=H ������ */
		PORTB|= 0b00010000;
		/*	   	  |||||||+- SCK  SPI�N���b�N  �o��
				  ||||||+-- MISO SPIϽ���     ����
				  |||||+--- MOSI SPIϽ����    �o��
				  ||||+---- SS   SPI�ڰ�޾ڸ� �o��
		*/
	}else{
		/* SPI CS=L �L���� */
		PORTB&= 0b11101111;
		/*	   	  |||||||+- SCK  SPI�N���b�N  �o��
				  ||||||+-- MISO SPIϽ���     ����
				  |||||+--- MOSI SPIϽ����    �o��
				  ||||+---- SS   SPI�ڰ�޾ڸ� �o��
		*/
	}
}

void SPI::spiRegWrite(uint8_t addr, uint8_t data){
	spiCtrlCs(ENABLE);
	spiSend(addr);
	spiSend(data);
	spiCtrlCs(DISABLE);
}


void SPI::spiRegBarstWrite(uint8_t addr, uint8_t * data, uint8_t dsize){
	spiCtrlCs(ENABLE);
	spiSend(addr);
	for(int i=0; i<dsize; i++){
		spiSend(data[i]);
	}
	spiCtrlCs(DISABLE);
}

void SPI::spiRegRead(uint8_t addr){
	spiCtrlCs(ENABLE);
	spiSend( 0b10000000 | addr ); /* RW=1(read) set */
	spiRead();
	spiCtrlCs(DISABLE);
}