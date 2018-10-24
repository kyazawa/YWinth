/*
 * ウィンドシンセサイザー製作プロジェクト『Ywinth』
 * YMF825.h
 *
 * Created: 2018/10/02 10:39:11
 * Author : yazawa
 */ 

#ifndef _YMF825_H_
#define _YMF825_H_

using namespace std;

#include "YWinthCommon.h"

/* YMF825制御関連 */
void soundInit();
void setTone();
void keyOn(uint8_t fnumh, uint8_t fnuml, uint8_t vovol);
void keyOff(void);
void setCh(void);

#endif