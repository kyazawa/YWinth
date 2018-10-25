/*
 * LCD.cpp
 *
 * Created: 2018/10/25 21:30:50
 *  Author: yazawa
 */ 

#include "LCD.h"

/* LCDコマンド送信 */
void lcdSendCmd(uint8_t cmd){
	i2cRegWrite(LCD_ADDR, 0x00, cmd);
}

/* LCD文字送信 */
void lcdSendData(uint8_t data){
	i2cRegWrite(LCD_ADDR, 0x40, data);
}

/* LCD初期化
 * 参考：http://akizukidenshi.com/download/ds/xiamen/AQM1602_rev2.pdf
 */
void lcdInit(){
	/* Function Set 1 */
	lcdSendCmd(0x38);
	_delay_us(LCD_WAIT);
	
	/* Function Set 2 */
	lcdSendCmd(0x39);
	_delay_us(LCD_WAIT);
	
	/* Internal OSC Freqency */
	lcdSendCmd(0x14);
	_delay_us(LCD_WAIT);
	
	/* Contrast Set */
	lcdSendCmd(0x73);
	_delay_us(LCD_WAIT);
	
	/* POWER/ICON/Contrast Control */
	lcdSendCmd(0x56);
	_delay_us(LCD_WAIT);
	
	/* Follower Control */
	lcdSendCmd(0x6C);
	
	_delay_ms(LCD_LONG_WAIT);
	
	/* Function Set */
	lcdSendCmd(0x38);
	_delay_us(LCD_WAIT);
	
	/* Clear Display */
	lcdSendCmd(0x01);
	_delay_us(LCD_WAIT);
	
	/* Display ON/OFF Control */
	lcdSendCmd(0x0C);
	_delay_us(LCD_WAIT);
	
	/*  Initialization end! */
}

void lcdPutc(char ch, uint8_t posx, uint8_t posy){
	
}

void lcdPrint(){
	char str[]="YWinth V0.1";
	int i;
	for(i=0; str[i]!='\0'; i++){
		lcdSendData(str[i]);
	}
}