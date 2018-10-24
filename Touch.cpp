/*
 * Touch.cpp
 *
 * Created: 2018/10/23 10:20:24
 *  Author: yazawa
 */ 


#include "Touch.h"


using namespace std;
void decodeKey(){
	uint8_t keyval;
	keyval = PINA;
	for(int i=0; i<8; i++){
		if(((keyval>>i)&0x1) == 0){
			switch(i){
				case 4:
				keyOnNoteNo(60);
				break;
				case 5:
				keyOnNoteNo(62);
				break;
				case 6:
				keyOnNoteNo(64);
				break;
				case 7:
				keyOnNoteNo(65);
				break;
				case 0:
				keyOnNoteNo(67);
				break;
				case 1:
				keyOnNoteNo(69);
				break;
				case 2:
				keyOnNoteNo(71);
				break;
				case 3:
				keyOnNoteNo(72);
				break;
				
			}
		}
	}
	
	if(keyval == 0xFF){
		keyOff();
	}
}

uint8_t touchGet(){
	uint8_t FINGER_NNUM_TBL[8] = {
		67, /* G */
		69, /* A */
		71, /* B */
		72, /* C+ */
		60, /* C */
		62, /* D */
		64, /* E */
		65  /* F */
	};
	uint8_t keyval;
	
	/* L�o�́i���d�j */
	PORTA = 0x00;
	DDRA = 0xFF;
	_delay_us(5);
	DDRA = 0x00;
	
	/* �[�d�҂� */
	_delay_us(20);
	
	/* �d�����o */
	keyval = PINA; /* 0:������Ă� 1:������ĂȂ� */
	
	/* ���_���ɕς��ĕԂ� */
	return ~keyval;
	
	#if 0 /* ������ �s�A�m���[�h */
	for(int i=0; i<8; i++){
		if(((keyval>>i)&0x1) == 0){
			keyOnNoteNoWithVovol(FINGER_NNUM_TBL[i],vovol);
		}
	}
	
	if(keyval == 0xFF){
		keyOff();
	}
	#endif
}

