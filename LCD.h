/*
 * LCD.h
 *
 * Created: 2018/10/25 21:30:35
 *  Author: yazawa
 */ 


#ifndef LCD_H_
#define LCD_H_

#define LCD_ADDR 0x3E
#define LCD_WAIT 30 /* us */
#define LCD_LONG_WAIT 200 /* ms */

#include "YWinthCommon.h"

/* LCD初期化処理 */
void lcdInit();

/* LCDコマンド送信 */
void lcdSendCmd(uint8_t cmd);

/* LCD文字送信 */
void lcdSendData(uint8_t data);

/* LCDの任意の位置に一文字表示 */
void lcdPutc(char ch, uint8_t posx, uint8_t posy);

void lcdPrint();

#endif /* LCD_H_ */