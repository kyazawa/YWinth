/*
 * Touch.h
 *
 * Created: 2018/10/23 10:20:41
 *  Author: yazawa
 */ 


#ifndef TOUCH_H_
#define TOUCH_H_


using namespace std;
#include "YWinthCommon.h"

class Touch {
	public:
	void decodeKey();
	void touchGet();
	
	/* �R���X�g���N�^ */
	Touch();
	/* �f�X�g���N�^ */
	~Touch();
};

#endif /* TOUCH_H_ */