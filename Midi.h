/*
 * Midi.h
 *
 * Created: 2018/10/31 23:06:09
 *  Author: yazawa
 */ 


#ifndef MIDI_H_
#define MIDI_H_

#include "YWinthCommon.h"

/* MIDI������ */
void midiInit();

/* MIDI�m�[�g�I�� */
void midiNoteOn(uint8_t ch, uint8_t note, uint8_t vel);

/* MIDI�m�[�g�I�t */
void midiNoteOff(uint8_t ch);

/* MIDI�A�t�^�[�^�b�` */
void midiAfterTouch(uint8_t ch, uint8_t vel);

/* MIDI�R���g���[���`�F���W */
void midiControlChange();

/* MIDI�v���O�����`�F���W */
void midiProgramChange();


#endif /* MIDI_H_ */