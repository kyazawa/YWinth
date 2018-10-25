/*
 * Button.h
 *
 * Created: 2018/10/25 22:37:02
 *  Author: yazawa
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "YWinthCommon.h"

/* BTN1~4 : PORTB */
#define BTN1 PB0
#define BTN2 PB1
#define BTN3 PB2
#define BTN4 PB3

/* BTN5~6: PORTC */
#define BTN5 PC6
#define BTN6 PC7

/* ボタンサンプリング値（6ボタン × 8回） */
extern uint8_t buttonSampleValue[6];

/* ボタン今回確定値 */
extern uint8_t buttonDefValue;

/* ボタン前回確定値 */
extern uint8_t buttonDefPrevValue;

/* ボタン押下検出(前回未押下⇒今回押下) */
extern uint8_t buttonPressed;


/* 操作ボタンポート初期化 */
void buttonInit();

/* ボタン生の値取得 */
uint8_t buttonGet();

/* ボタン値サンプリング */
void buttonSampling();

/* ボタン値をサンプリング値から平均化(一致検出) */
void buttonAveraging();

/* ボタン押下検出 新たに押されたボタンのビットを立てる */
void buttonPressDetect();

#endif /* BUTTON_H_ */