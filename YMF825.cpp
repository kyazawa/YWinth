/*
 * ウィンドシンセサイザー製作プロジェクト『Ywinth』
 * YMF825.cpp
 *
 * Created: 2018/10/02 10:39:11
 * Author : yazawa
 */ 


using namespace std;

#include "YMF825.h"


void YMF825::soundInit(){
	spiRegWrite( 0x1D, 0x00 ); // output power
	spiRegWrite( 0x02, 0x0E );
	_delay_ms(1);
	spiRegWrite( 0x00, 0x01 );//CLKEN
	spiRegWrite( 0x01, 0x00 ); //AKRST
	spiRegWrite( 0x1A, 0xA3 );
	_delay_ms(1);
	spiRegWrite( 0x1A, 0x00 );
	_delay_ms(30);
	spiRegWrite( 0x02, 0x04 );//AP1,AP3
	_delay_ms(1);
	spiRegWrite( 0x02, 0x00 );
	//add
	spiRegWrite( 0x19, 0xF0 );//MASTER VOL
	spiRegWrite( 0x1B, 0x3F );//interpolation
	spiRegWrite( 0x14, 0x00 );//interpolation
	spiRegWrite( 0x03, 0x01 );//Analog Gain
	
	spiRegWrite( 0x08, 0xF6 );
	_delay_ms(21);
	spiRegWrite( 0x08, 0x00 );
	spiRegWrite( 0x09, 0xF8 );
	spiRegWrite( 0x0A, 0x00 );
	
	spiRegWrite( 0x17, 0x40 );//MS_S
	spiRegWrite( 0x18, 0x00 );
}

void YMF825::setTone(){
	uint8_t tone_data[35] ={
		0x81, // header Header: 1byte(80H + Maximum Tone Number)
		// T_ADR 0
		// Entire Tone Setting
		0x01, // BO (Basic Octave)
		0x43, // LFO,ALG
		//Operator1 Setting
		0x00, // SR, XOF, KSR
		0xE7, // RR, DR
		0xFF, // AR, SL
		0x9D, // TL, KSL
		0x00, // DAM(amplitude modulation depth), EAM(enable amplitude modulation), DVB(vibrato depth), EVB(enable vibrato)
		0x10, // MULTI(magnification of frequency), DT(detune)
		0x40, // WS(wave shape), FB(FM feedback level)
		// Operator2 Setting
		0x20, // SR, XOF, KSR
		0x33, // RR, DR
		0xE2, // AR, SL
		0x73, // TL, KSL
		0x00, // DAM(amplitude modulation depth), EAM(enable amplitude modulation), DVB(vibrato depth), EVB(enable vibrato)
		0x50, // MULTI(magnification of frequency), DT(detune)
		0x40, // WS(wave shape), FB(FM feedback level)
		// Operator3 Setting
		0x10, // SR, XOF, KSR
		0x41, // RR, DR
		0xD3, // AR, SL
		0x5B, // TL, KSL
		0x00, // DAM(amplitude modulation depth), EAM(enable amplitude modulation), DVB(vibrato depth), EVB(enable vibrato)
		0x10, // MULTI(magnification of frequency), DT(detune)
		0x41, // WS(wave shape), FB(FM feedback level)
		// Operator4 Setting
		0x20, // SR, XOF, KSR
		0x63, // RR, DR
		0xD4, // AR, SL
		0x02, // TL, KSL
		0x01, // DAM(amplitude modulation depth), EAM(enable amplitude modulation), DVB(vibrato depth), EVB(enable vibrato)
		0x10, // MULTI(magnification of frequency), DT(detune)
		0x40, // WS(wave shape), FB(FM feedback level)
		0x80,0x03,0x81,0x80, // End(80H,03H,81H,80H)
	};
	
	spiRegWrite( 0x08, 0xF6 );
	_delay_ms(1);
	spiRegWrite( 0x08, 0x00 );
	
	spiRegBarstWrite( 0x07, &tone_data[0], 35 );
}

void YMF825::keyOn(uint8_t fnumh, uint8_t fnuml, uint8_t vovol){
	vovol *= 4;
	spiRegWrite( 0x0B, 0x00 );//voice num
	spiRegWrite( 0x0C, vovol );//vovol
	spiRegWrite( 0x0D, fnumh );//fnum
	spiRegWrite( 0x0E, fnuml );//fnum
	spiRegWrite( 0x0F, 0x40 );//keyon = 1
}

void YMF825::keyOff(void){
	spiRegWrite( 0x0F, 0x00 );//keyon = 0
}


void YMF825::setCh(void){
	spiRegWrite( 0x0F, 0x30 );// keyon = 0
	spiRegWrite( 0x10, 0x71 );// chvol
	spiRegWrite( 0x11, 0x00 );// XVB
	spiRegWrite( 0x12, 0x08 );// FRAC
	spiRegWrite( 0x13, 0x00 );// FRAC
}

uint8_t YMF825::noteNoToScale(uint16_t noteNo){
	return (noteNo%12);
}

uint8_t YMF825::noteNoToBlock(uint16_t noteNo){
	return ((noteNo/12)-1);
}

uint16_t YMF825::noteNoToFnum(uint16_t noteNo){
	uint8_t scale;
	uint16_t FNUM_TABLE[12] = {
		/*  0:C  */ 357,
		/*  1:C# */ 378,
		/*  2:D  */ 401,
		/*  3:D# */ 425,
		/*  4:E  */ 450,
		/*  5:F  */ 477,
		/*  6:F# */ 505,
		/*  7:G  */ 535,
		/*  8:G# */ 567,
		/*  9:A  */ 601,
		/* 11:A# */ 637,
		/* 12:B  */ 674
	};
	
	scale  = noteNoToScale(noteNo);
	return FNUM_TABLE[scale];
}

void YMF825::keyOnNoteNo(uint16_t noteNo){
	uint8_t block, fnuml, fnumh;
	uint16_t fnum;
	fnum = noteNoToFnum(noteNo);
	block = noteNoToBlock(noteNo);
	
	fnuml  = (fnum>>4) & 0b00111000;
	fnumh  =      fnum & 0b01111111;
	fnuml |= block;
	
	keyOn(fnuml, fnumh, 5);
}


