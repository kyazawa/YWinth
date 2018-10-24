/*
 * Breath.h
 *
 * Created: 2018/10/24 8:51:28
 *  Author: yazawa
 */ 


#ifndef BREATH_H_
#define BREATH_H_

#include "YWinthCommon.h"

/* LPS22HB スレーブアドレス */
#define LPS22_ADDR	0b1011100

/* LPS22HB レジスタアドレス */
#define LPS22_WAMI  0x0F /* LPS22HB 自アドレス返答(Who am I) */
#define LPS22_PLL	0x28 /* LPS22HB 気圧値 0-7 */
#define LPS22_PL	0x29 /* LPS22HB 気圧値 8-15 */
#define LPS22_PH	0x2A /* LPS22HB 気圧値 16-23 */
#define LPS22_CTR1	0x10 /* LPS22HB コントロールレジスタ */

/* グローバル変数 */
extern uint32_t offset; /* 気圧オフセット値 */

/* I2C */
void i2cInit(void);
void i2cStart(void);
void i2cStop(void);
void i2cWrite(int data);
int i2cRead(int i);
int i2cRegRead(uint8_t addr,uint8_t reg);
void i2cRegWrite(uint8_t addr, uint8_t reg, uint8_t data);

void breathInit();
uint32_t breathRead();
void setBreathOffset();
long getBreathOffsetValue();

#endif /* BREATH_H_ */