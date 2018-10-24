/*
 * Finger.cpp
 *
 * Created: 2018/10/24 23:16:00
 *  Author: yazawa
 */ 

#include "Finger.h"

uint16_t fingerToNoteNum(uint8_t finger){
	uint16_t noteNum;
	noteNum = FINGER_TBL[(int)finger];
	return noteNum;
}
