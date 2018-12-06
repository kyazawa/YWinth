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
	
	/* �e�[�u������g�[���f�[�^�擾 */
	for(i=0; i<35; i++){
		tone_data[i] = pgm_read_word(&TONE_TBL[tone_num][i]);
	}
	
	/* �g�[���f�[�^�������� */
	spiRegWrite( 0x08, 0xF6 );
	_delay_ms(1);
	spiRegWrite( 0x08, 0x00 );
	
	spiRegBarstWrite( 0x07, &tone_data[0], 35 );
}

/* �g�[���f�[�^���W�X�^�ǂݍ��� */
void toneRegRead(uint8_t * tone_data){
	int i;
	for(i=0; i<35; i++){
		tone_data[i] = spiRegRead(0x07+i);
	}
}

/* �g�[���f�[�^���W�X�^�������� */
void toneRegWrite(uint8_t * tone_data){
	/* �g�[���f�[�^�������� */
	spiRegWrite( 0x08, 0xF6 );
	_delay_ms(1);
	spiRegWrite( 0x08, 0x00 );
	
	spiRegBarstWrite( 0x07, &tone_data[0], 35 );
}

void toneWrite(tonedata_t * tone){
	uint8_t tone_data[35];
	toneRegRead(tone_data);
	
	/* �\���̂��烌�W�X�^�ɉ������� */
}

void toneRead(tonedata_t * tone){
	uint8_t tone_data[35];
	
	toneRegRead(tone_data);
	
	/* ���W�X�^�f�[�^����\���̂ɓǂݏo�� */
}