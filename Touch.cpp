/*
 * Touch.cpp
 *
 * Created: 2018/10/23 10:20:24
 *  Author: yazawa
 */ 


#include "Touch.h"


using namespace std;

Touch::Touch(){
	/* コンストラクタ */
}

Touch::~Touch(){
	/* デストラクタ */
}

void Touch::decodeKey(){
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

void Touch::touchGet(){
	uint8_t keyval;
	
	/* L出力（放電） */
	PORTA = 0x00;
	DDRA = 0xFF;
	_delay_us(5);
	DDRA = 0x00;
	
	/* 充電待ち */
	_delay_us(20);
	
	/* 電圧検出 */
	keyval = PINA; /* 0:押されてる 1:押されてない */
	
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