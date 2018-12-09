/*
 * Tone.h
 *
 * Created: 2018/12/1 22:15:18
 *  Author: yazawa
 */ 


#ifndef TONE_H_
#define TONE_H_

#include "YWinthCommon.h"



/* �I�y���[�^�f�[�^�ۑ��p�̍\���� */
struct opdata_t {
	uint8_t ar; /* �A�^�b�N���[�g(0-15) */
	uint8_t dr; /* �f�B�P�C���[�g(0-15) */
	uint8_t sr; /* �T�X�e�B�����[�g(0-15) */
	uint8_t sl; /* �T�X�e�B�����x��(0-15) */
	uint8_t rr; /* �����[�X���[�g(0-15) */
	uint8_t mul;/* ���g���{��(0-15) */
	uint8_t det;/* �f�`���[��(0-7) */
	uint8_t tl; /* �g�[�^�����x��(0-63) */
	uint8_t ksl;/* KS�L��(0/1) */
	uint8_t ksr;/* KS�[��(0-3)*/
	uint8_t ws; /* �g�`�I��(0-31) */
	uint8_t dvb;/* �r�u���[�g�[��(0-3) */
	uint8_t evb;/* �r�u���[�g�L��(0/1) */
	uint8_t dam; /* AM�ϒ��[��(0-3)*/
	uint8_t eam; /* AM�ϒ��L��(0/1) */
	uint8_t fb;  /* �t�B�[�h�o�b�N�[��(0-7) */
	uint8_t xof; /* �L�[�I�t����(0/1) */
};

/* �g�[���f�[�^�ۑ��p�̍\���� */
struct tonedata_t {
	/* �S�I�y���[�^���ʃp�����[�^ */
	uint8_t arg; /* �A���S���Y��    (0-7) */
	uint8_t lfo; /* LFO(����g�ϒ�) (0-3) */
	uint8_t bo;  /* �x�[�X�I�N�^�[�u (0-3) */
	
	/* �ʃI�y���[�^�p�����[�^ */
	opdata_t op[4]; /* opertor���Ă��Ԃ�C++�̗\����ŁI */
	
};

const uint8_t TONE_TBL[6][35] PROGMEM = {
	/* default tone(sine wave) */
	{
		0x81,//header
		//T_ADR 0
		0x01,0x85,
		0x00,0x7F,0xF4,0xBB,0x00,0x10,0x40, /* opr1 */
		0x00,0xAF,0xA0,0x0E,0x03,0x10,0x40, /* opr2 */
		0x00,0x2F,0xF3,0x9B,0x00,0x20,0x41, /* opr3 */
		0x00,0xAF,0xA0,0x0E,0x01,0x10,0x40, /* opr4 */
		0x80,0x03,0x81,0x80,
	},
	
	/* Brass1 tone */
	{
		0x81,//header
		//T_ADR 0
		0x01,0x85,
		0x00,0x74,0x7A,0x55,0x00,0x20,0x00,
		0x00,0x8D,0xA0,0x0E,0x03,0x10,0x00,
		0x00,0x74,0x7A,0x42,0x00,0x10,0x00,
		0x00,0x8C,0xA0,0x0E,0x01,0x10,0x10,
		0x80,0x03,0x81,0x80
	},
	/* Brass2 tone */
	{
		0x81,//header
		//T_ADR 0
		0x01,0x85,
		0x00,0x74,0x7B,0x56,0x00,0x10,0x00,
		0x00,0x8D,0xA0,0x02,0x03,0x00,0x08,
		0x00,0x74,0x7B,0x42,0x00,0x10,0x00,
		0x00,0x8C,0xA0,0x02,0x01,0x10,0x08,
		0x80,0x03,0x81,0x80
	},
	
	/* Square Wave */
	{
		0x81,//header
		//T_ADR 0
		0x01,0x85,
		0x00,0x7F,0xF4,0xBB,0x00,0x10,0x30,
		0x00,0xAF,0xA0,0x0E,0x03,0x10,0x30,
		0x00,0x2F,0xF3,0x9B,0x00,0x20,0x31,
		0x00,0xAF,0xA0,0x0E,0x01,0x10,0x30,
		0x80,0x03,0x81,0x80,
	},
	
	/* SawTooth Wave */
	{
		0x81,//header
		//T_ADR 0
		0x01,0x85,
		0x00,0x7F,0xF4,0xBB,0x00,0x10,0xC0,
		0x00,0xAF,0xA0,0x0E,0x03,0x10,0xC0,
		0x00,0x2F,0xF3,0x9B,0x00,0x20,0xC1,
		0x00,0xAF,0xA0,0x0E,0x01,0x10,0xC0,
		0x80,0x03,0x81,0x80,
	},
	
	{
		/* 0 */ 0x81,//headerHeader:1byte(80H+MaximumToneNumber)
		//T_ADR0
		//EntireToneSetting
		/* 1 */ 0x01,//BO(BasicOctave)
		/* 2 */ 0x43,//LFO,ALG
		//Operator1Setting
		/* 3 */ 0x00,//SR,XOF,KSR
		0xE7,//RR,DR
		0xFF,//AR,SL
		0x9D,//TL,KSL
		0x00,//DAM(amplitudemodulationdepth),EAM(enableamplitudemodulation),DVB(vibratodepth),EVB(enablevibrato)
		0x10,//MULTI(magnificationoffrequency),DT(detune)
		0x40,//WS(waveshape),FB(FMfeedbacklevel)
		//Operator2Setting
		0x20,//SR,XOF,KSR
		0x33,//RR,DR
		0xE2,//AR,SL
		0x73,//TL,KSL
		0x00,//DAM(amplitudemodulationdepth),EAM(enableamplitudemodulation),DVB(vibratodepth),EVB(enablevibrato)
		0x50,//MULTI(magnificationoffrequency),DT(detune)
		0x40,//WS(waveshape),FB(FMfeedbacklevel)
		//Operator3Setting
		0x10,//SR,XOF,KSR
		0x41,//RR,DR
		0xD3,//AR,SL
		0x5B,//TL,KSL
		0x00,//DAM(amplitudemodulationdepth),EAM(enableamplitudemodulation),DVB(vibratodepth),EVB(enablevibrato)
		0x10,//MULTI(magnificationoffrequency),DT(detune)
		0x41,//WS(waveshape),FB(FMfeedbacklevel)
		//Operator4Setting
		0x20,//SR,XOF,KSR
		0x63,//RR,DR
		0xD4,//AR,SL
		0x02,//TL,KSL
		0x01,//DAM(amplitudemodulationdepth),EAM(enableamplitudemodulation),DVB(vibratodepth),EVB(enablevibrato)
		0x10,//MULTI(magnificationoffrequency),DT(detune)
		0x40,//WS(waveshape),FB(FMfeedbacklevel)
		0x80,0x03,0x81,0x80,//End(80H,03H,81H,80H)
				
		
	}
};



void setPrisetTone(uint8_t tone_num);

void toneRegRead(uint8_t * tone_data);
void toneRegWrite(uint8_t * tone_data);

void toneWrite(tonedata_t * tone);
void toneRead(tonedata_t * tone);

#endif /* TONE_H_ */