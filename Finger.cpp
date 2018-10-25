/*
 * Finger.cpp
 *
 * Created: 2018/10/24 23:16:00
 *  Author: yazawa
 */ 

#include "Finger.h"

uint16_t fingerToNoteNum(uint8_t finger){
	uint16_t noteNum;
	//noteNum = FINGER_TBL[fingerI];
	noteNum = pgm_read_word(&FINGER_TBL[finger]);
	/* PROGMEMﾃｰﾌﾞﾙ参照時は，?の関数を読んで読み出す！！
	   配列として読むと変な値が出るので注意する！ */
	return noteNum;
}
