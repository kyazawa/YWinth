/*
 * Menu.h
 *
 * Created: 2018/10/29 9:12:10
 *  Author: yazawa
 */ 


#ifndef MENU_H_
#define MENU_H_

#include "YWinthCommon.h"

#if 1 /* ������ �쐬���ɂ�... */

/* ���j���[�����` */
#define UP		 1
#define DN		-1
#define NEXT	 1
#define PREV	-1
#define NOCNG	 0

/* ���j���[���ڔԍ��ő�l(���j���[���ڐ�-1) */
#define MENUITEM_MAX_NO 5

/* �� ���j���[���ڃe�[�u�� */
/*								  0123456789ABCDEF */
const char MENUITEM_0[] PROGMEM = "MasterVolume ";
const char MENUITEM_1[] PROGMEM = "PrisetTone   ";
const char MENUITEM_2[] PROGMEM = "Transpose    ";
const char MENUITEM_3[] PROGMEM = "Octave       ";
const char MENUITEM_4[] PROGMEM = "BreathLevel  ";
const char MENUITEM_5[] PROGMEM = "FingerPattern";

/* const�͂Q�񂩂� */
const char* const MENUITEMS_TBL[] PROGMEM = {
	MENUITEM_0,
	MENUITEM_1,
	MENUITEM_2,
	MENUITEM_3,
	MENUITEM_4,
	MENUITEM_5 
};

/* �� ���j���[�ψʃe�[�u�� */
/* �߂��Fchar���������邩�͕s��Ȃ̂ŕ����������Ƃ��́hsigned char�h�Ƃ��邱�ƁI */

/* �ݒ�\�ŏ��l */
const signed char MENUITEM_MIN_TBL[] PROGMEM = {
	0,		/* MasterVolume */
	0,		/* PrisetTone */
	-12,	/* Transpose */
	-4,		/* Octave */
	0,		/* BreathLevel */
	0		/* FingerPattern */
};

/* �ݒ�\�ő�l */
const signed char MENUITEM_MAX_TBL[] PROGMEM = {
	31,		/* MasrerVolume */
	3,		/* PrisetTone */
	12,		/* Transpose */
	4,		/* Octave */
	100,	/* BreathLevel*/
	4		/* FingerPattern */
};

/* �����l�e�[�u�� */
const signed char MENUITEM_DEFAULT_TBL[] PROGMEM = {
	20,		/* MasrerVolume */
	1,		/* PrisetTone */
	0,		/* Transpose */
	0,		/* Octave */
	50,		/* BreathLevel*/
	0		/* FingerPattern */
};

/* �� �ݒ�l�����l:DISABLE �ݒ�l�����O������:ENABLE */
const signed char MENUITEM_HAS_VALUENAME[] PROGMEM = {
	DISABLE,		/* MasrerVolume */
	ENABLE,			/* PrisetTone */
	DISABLE,		/* Transpose */
	DISABLE,		/* Octave */
	DISABLE,		/* BreathLevel*/
	ENABLE			/* FingerPattern */
};

/* ���j���[�C�x���g�e�[�u���F�l�ҏW���̓��� */
#if 0
static (*MENUITEM_EVENT_TBL[])() PROGMEM{
	changeMasterVolume,		/* MasrerVolume */
	setPrisetTone,			/* PrisetTone */
	setTranspose,			/* Transpose */
	setOctave,				/* Octave */
	setBreathLevel,			/* BreathLevel*/
	setFingerPattern		/* FingerPattern */
}
#endif

/* ���j���[�C�x���g�e�[�u���FOK�N���b�N������ */
#if 0
static (*MENUITEM_EVENT_TBL[])() PROGMEM{
	changeMasterVolume,		/* MasrerVolume */
	setPrisetTone,			/* PrisetTone */
	setTranspose,			/* Transpose */
	setOctave,				/* Octave */
	setBreathLevel,			/* BreathLevel*/
	setFingerPattern		/* FingerPattern */
}
#endif

/* ���j���[�C�x���g�e�[�u���F��ݾكN���b�N������ */
#if 0
static (*MENUITEM_EVENT_TBL[])() PROGMEM{
	changeMasterVolume,		/* MasrerVolume */
	setPrisetTone,			/* PrisetTone */
	setTranspose,			/* Transpose */
	setOctave,				/* Octave */
	setBreathLevel,			/* BreathLevel*/
	setFingerPattern		/* FingerPattern */
}
#endif

/* ���ݑI�𒆃��j���[���� */
extern uint8_t menuSelectingItem;

/* ���j���[�ݒ�l */
extern signed char menuItemSetValues[MENUITEM_MAX_NO+1];

/* �I�𒆍��ڂ̐ݒ�l */
extern signed char * menuItemValue;

/* ���j���[�\���X�V */
void menuRefreshDisplay();

/* ���j���[���ڈړ� */
void menuMoveItem(signed char arg);

/* ���j���[�ݒ�l���� */
void menuAdjValue(signed char arg);

/* ���j���[���̃A�N�e�B�r�e�B */
void menuActivity();

/* ���j���[���������� */
void menuInit();

#endif

#endif /* MENU_H_ */