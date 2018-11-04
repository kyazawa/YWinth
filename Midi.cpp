/*
 * Midi.cpp
 *
 * Created: 2018/10/31 23:06:25
 *  Author: yazawa
 */ 

#include "Midi.h"

/* MIDI������ */
void midiInit(){
	/* �{�[���[�g��312500BPS�ɐݒ� */
	UCSR0B = (1<<TXEN0) | (1<<RXEN0);
	/*
	UBRR0H = (F_CPU/16/MIDIBAUD-1)>>8;
	UBRR0L = (F_CPU/16/MIDIBAUD-1);
	*/
	UBRR0 = 31;
}

/* MIDI�m�[�g�I�� */
void midiNoteOn(uint8_t ch, uint8_t note, uint8_t vel){
	char midimsg[4];
	midimsg[0] = MIDI_NOTEON | ch;
	midimsg[1] = note;
	midimsg[2] = vel;
	midimsg[3] = '\0';
	
	uartPuts(midimsg);
}

/* MIDI�m�[�g�I�t */
void midiNoteOff(uint8_t ch, uint8_t note){
	char midimsg[4];
	midimsg[0] = MIDI_NOTEOF | ch;
	midimsg[1] = note;
	midimsg[2] = 0x00; /* �x���V�e�B=0 �� noteoff */
	midimsg[3] = '\0';
	
	uartPuts(midimsg);
}

/* MIDI�I�[���m�[�g�I�t */
void midiAllNoteOff(uint8_t ch){
	char midimsg[4];
	midimsg[0] = 0xB0 | ch;
	midimsg[1] = 0x7B;
	midimsg[2] = 0x00;
	midimsg[3] = '\0';
	
	uartPuts(midimsg);
}

/* MIDI�A�t�^�[�^�b�` */
void midiAfterTouch(uint8_t ch, uint8_t vel){
	char midimsg[3];
	
	midimsg[0] = MIDI_CHPRSH | ch;
	midimsg[1] = vel;
	midimsg[2] = '\0';
	
	uartPuts(midimsg);
}

/* MIDI�R���g���[���`�F���W */
void midiControlChange(){
	
}

/* MIDI�v���O�����`�F���W */
void midiProgramChange(){
	
}