/*
 * Tone.cpp
 *
 * Created: 2018/12/1 22:15:35
 *  Author: yazawa
 */ 

#include "Tone.h"

void setPrisetTone(uint8_t tone_num){
	uint8_t tone_data[35];
	int i;
	
	/* テーブルからトーンデータ取得 */
	for(i=0; i<35; i++){
		tone_data[i] = pgm_read_word(&TONE_TBL[tone_num][i]);
	}
	
	/* トーンデータ書き込み */
	spiRegWrite( 0x08, 0xF6 );
	_delay_ms(1);
	spiRegWrite( 0x08, 0x00 );
	
	spiRegBarstWrite( 0x07, &tone_data[0], 35 );
}