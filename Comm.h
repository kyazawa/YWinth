/*
 * Comm.h
 *
 * Created: 2018/12/6 9:22:48
 *  Author: yazawa
 */ 


#ifndef COMM_H_
#define COMM_H_

#include "YWinthCommon.h"

/* �ʐM�֘A */

/* UART�{�[���[�g�F115200bps */
#define BAUD 115200

/* ��M�o�b�t�@ */
extern char RxBuff[256];

/* ��M���荞�݁˂Ƃ肠�����o�b�t�@�ɓ���Ƃ��˃��C�����[�v����o�b�t�@�ɂȂ񂩂���Γǂ� */

void uartInit(void);
void uartPutc(char a);
void uartPuts(char * str);


#endif /* COMM_H_ */