/*
 * Midi.cpp
 *
 * Created: 2018/10/31 23:06:25
 *  Author: yazawa
 */ 

#include "Midi.h"

/* MIDI初期化 */
void midiInit(){
	/* ボーレートを312500BPSに設定 */
	UCSR0B = (1<<TXEN0) | (1<<RXEN0);
	/*
	UBRR0H = (F_CPU/16/MIDIBAUD-1)>>8;
	UBRR0L = (F_CPU/16/MIDIBAUD-1);
	*/
	UBRR0 = 31;
}

/* MIDIノートオン */
void midiNoteOn(uint8_t ch, uint8_t note, uint8_t vel){
	char midimsg[4];
	midimsg[0] = MIDI_NOTEON | ch;
	midimsg[1] = note;
	midimsg[2] = vel;
	midimsg[3] = '\0';
	
	uartPuts(midimsg);
}

/* MIDIノートオフ */
void midiNoteOff(uint8_t ch, uint8_t note){
	char midimsg[4];
	midimsg[0] = MIDI_NOTEON | ch;
	midimsg[1] = note;
	midimsg[2] = 0x00; /* ベロシティ=0 ⇒ noteoff */
	midimsg[3] = '\0';
	
	uartPuts(midimsg);
}

/* MIDIアフタータッチ */
void midiAfterTouch(uint8_t ch, uint8_t vel){
	char midimsg[3];
	
	midimsg[0] = MIDI_CHPRSH | ch;
	midimsg[1] = vel;
	midimsg[2] = '\0';
	
	uartPuts(midimsg);
}

/* MIDIコントロールチェンジ */
void midiControlChange(){
	
}

/* MIDIプログラムチェンジ */
void midiProgramChange(){
	
}