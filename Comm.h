/*
 * Comm.h
 *
 * Created: 2018/12/6 9:22:48
 *  Author: yazawa
 */ 


#ifndef COMM_H_
#define COMM_H_

#include "YWinthCommon.h"

/* 通信関連 */

/* UARTボーレート：115200bps */
#define BAUD 115200

/* 受信バッファ */
extern char RxBuff[256];

/* 受信割り込み⇒とりあえずバッファに入れとく⇒メインループからバッファになんかあれば読む */

void uartInit(void);
void uartPutc(char a);
void uartPuts(char * str);


#endif /* COMM_H_ */