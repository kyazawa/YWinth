/*
 * Midi.h
 *
 * Created: 2018/10/31 23:06:09
 *  Author: yazawa
 */ 


#ifndef MIDI_H_
#define MIDI_H_

#include "YWinthCommon.h"

/* MIDI初期化 */
void midiInit();

/* MIDIノートオン */
void midiNoteOn(uint8_t ch, uint8_t note, uint8_t vel);

/* MIDIノートオフ */
void midiNoteOff(uint8_t ch);

/* MIDIアフタータッチ */
void midiAfterTouch(uint8_t ch, uint8_t vel);

/* MIDIコントロールチェンジ */
void midiControlChange();

/* MIDIプログラムチェンジ */
void midiProgramChange();


#endif /* MIDI_H_ */