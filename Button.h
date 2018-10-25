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

/* �{�^���T���v�����O�l�i6�{�^�� �~ 8��j */
extern uint8_t buttonSampleValue[6];

/* �{�^������m��l */
extern uint8_t buttonDefValue;

/* �{�^���O��m��l */
extern uint8_t buttonDefPrevValue;

/* �{�^���������o(�O�񖢉����ˍ��񉟉�) */
extern uint8_t buttonPressed;


/* ����{�^���|�[�g������ */
void buttonInit();

/* �{�^�����̒l�擾 */
uint8_t buttonGet();

/* �{�^���l�T���v�����O */
void buttonSampling();

/* �{�^���l���T���v�����O�l���畽�ω�(��v���o) */
void buttonAveraging();

/* �{�^���������o �V���ɉ����ꂽ�{�^���̃r�b�g�𗧂Ă� */
void buttonPressDetect();

#endif /* BUTTON_H_ */