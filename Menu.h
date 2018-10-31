/*
 * Menu.h
 *
 * Created: 2018/10/29 9:12:10
 *  Author: yazawa
 */ 


#ifndef MENU_H_
#define MENU_H_

#include "YWinthCommon.h"

#if 1 /* ↓↓↓ 作成中につき... */

/* メニュー動作定義 */
#define UP		 1
#define DN		-1
#define NEXT	 1
#define PREV	-1
#define NOCNG	 0

/* メニュー項目番号最大値(メニュー項目数-1) */
#define MENUITEM_MAX_NO 5

/* ★ メニュー項目テーブル */
/*								  0123456789ABCDEF */
const char MENUITEM_0[] PROGMEM = "MasterVolume ";
const char MENUITEM_1[] PROGMEM = "PrisetTone   ";
const char MENUITEM_2[] PROGMEM = "Transpose    ";
const char MENUITEM_3[] PROGMEM = "Octave       ";
const char MENUITEM_4[] PROGMEM = "BreathLevel  ";
const char MENUITEM_5[] PROGMEM = "FingerPattern";

/* constは２回かく */
const char* const MENUITEMS_TBL[] PROGMEM = {
	MENUITEM_0,
	MENUITEM_1,
	MENUITEM_2,
	MENUITEM_3,
	MENUITEM_4,
	MENUITEM_5 
};

/* ★ メニュー変位テーブル */
/* めも：charが符号あるかは不定なので符号つけたいときは”signed char”とすること！ */

/* 設定可能最小値 */
const signed char MENUITEM_MIN_TBL[] PROGMEM = {
	0,		/* MasterVolume */
	0,		/* PrisetTone */
	-12,	/* Transpose */
	-4,		/* Octave */
	0,		/* BreathLevel */
	0		/* FingerPattern */
};

/* 設定可能最大値 */
const signed char MENUITEM_MAX_TBL[] PROGMEM = {
	31,		/* MasrerVolume */
	3,		/* PrisetTone */
	12,		/* Transpose */
	4,		/* Octave */
	100,	/* BreathLevel*/
	4		/* FingerPattern */
};

/* 初期値テーブル */
const signed char MENUITEM_DEFAULT_TBL[] PROGMEM = {
	20,		/* MasrerVolume */
	1,		/* PrisetTone */
	0,		/* Transpose */
	0,		/* Octave */
	50,		/* BreathLevel*/
	0		/* FingerPattern */
};

/* ★ 設定値が数値:DISABLE 設定値が名前をもつ:ENABLE */
const signed char MENUITEM_HAS_VALUENAME[] PROGMEM = {
	DISABLE,		/* MasrerVolume */
	ENABLE,			/* PrisetTone */
	DISABLE,		/* Transpose */
	DISABLE,		/* Octave */
	DISABLE,		/* BreathLevel*/
	ENABLE			/* FingerPattern */
};

/* メニューイベントテーブル：値編集時の動作 */
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

/* メニューイベントテーブル：OKクリック時動作 */
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

/* メニューイベントテーブル：ｷｬﾝｾﾙクリック時動作 */
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

/* 現在選択中メニュー項目 */
extern uint8_t menuSelectingItem;

/* メニュー設定値 */
extern signed char menuItemSetValues[MENUITEM_MAX_NO+1];

/* 選択中項目の設定値 */
extern signed char * menuItemValue;

/* メニュー表示更新 */
void menuRefreshDisplay();

/* メニュー項目移動 */
void menuMoveItem(signed char arg);

/* メニュー設定値調整 */
void menuAdjValue(signed char arg);

/* メニュー一回のアクティビティ */
void menuActivity();

/* メニュー初期化処理 */
void menuInit();

#endif

#endif /* MENU_H_ */