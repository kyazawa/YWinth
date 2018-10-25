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

/* LCD���������� */
void lcdInit();

/* LCD�R�}���h���M */
void lcdSendCmd(uint8_t cmd);

/* LCD�������M */
void lcdSendData(uint8_t data);

/* LCD�̔C�ӂ̈ʒu�Ɉꕶ���\�� */
void lcdPutc(char ch, uint8_t posx, uint8_t posy);

void lcdPrint();

#endif /* LCD_H_ */