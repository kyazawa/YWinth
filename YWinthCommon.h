/*
 * YWinthCommon.h
 *
 * Created: 2018/10/23 10:23:59
 *  Author: yazawa
 */ 


#ifndef YWINTHCOMMON_H_
#define YWINTHCOMMON_H_


using namespace std;

/* CPUクロック周波数：16MHz */
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

/* UARTボーレート：9600bps */
#define BAUD 9600

#define ENABLE  1 /* 有効 */
#define DISABLE 0 /* 無効 */

#define VERSIONCODE "V0.01"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/twi.h>

#include "SPI.h"
#include "Touch.h"
#include "YMF825.h"
#include "Breath.h"

/* 各種プロトタイプ宣言！（クラスに統合予定！） */

/* AVRペリフェラル関連 */
void setIOMode(void);
void ctrlLed(uint8_t state);
void uartInit(void);
void uartPutc(char a);
void uartPuts(char * str);
void initTimer(void);

/* ノートナンバ⇒FNUM変換関連 */
uint8_t noteNoToScale(uint16_t noteNo);
uint8_t noteNoToBlock(uint16_t noteNo);
uint16_t noteNoToFnum(uint16_t noteNo);
void keyOnNoteNo(uint16_t noteNo);

void decodeKey();
void touchGet();


#endif /* YWINTHCOMMON_H_ */