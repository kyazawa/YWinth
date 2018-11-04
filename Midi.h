/*
 * Midi.h
 *
 * Created: 2018/10/31 23:06:09
 *  Author: yazawa
 */ 


#ifndef MIDI_H_
#define MIDI_H_

#include "YWinthCommon.h"

#define MIDI_ENABLE 1

/* MIDI�{�[���[�g�F31250bps */
#define MIDIBAUD 31250

#define MIDI_NOTEON 0x90 /* �m�[�g�I�� */
#define MIDI_NOTEOF 0x80 /* �m�[�g�I�t */
#define MIDI_CHPRSH 0xD0 /* �`�����l���v���b�V���[ */


/* MIDI������ */
void midiInit();

/* MIDI�m�[�g�I�� */
void midiNoteOn(uint8_t ch, uint8_t note, uint8_t vel);

/* MIDI�m�[�g�I�t */
void midiNoteOff(uint8_t ch, uint8_t note);

/* MIDI�I�[���m�[�g�I�t */
void midiAllNoteOff(uint8_t ch);

/* MIDI�A�t�^�[�^�b�` */
void midiAfterTouch(uint8_t ch, uint8_t vel);

/* MIDI�R���g���[���`�F���W */
void midiControlChange();

/* MIDI�v���O�����`�F���W */
void midiProgramChange();


#endif /* MIDI_H_ */