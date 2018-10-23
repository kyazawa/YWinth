/*
 * �E�B���h�V���Z�T�C�U�[����v���W�F�N�g�wYwinth�x
 * YWinth_MainMPU.cpp
 *
 * Created: 2018/10/02 10:39:11
 * Author : yazawa
 */ 

using namespace std;

/* ���ʃ��C�u���� */
#include "YWinthCommon.h"

/* �O���[�o���ϐ� */
volatile uint8_t ledstate=0;
uint16_t cnt;

/* �N���X�̃I�u�W�F�N�g�̐錾 */
Touch touch;

/* �^�C�}�����ݔ���������
   ��������60Hz�Ōďo */
ISR (TIMER0_COMPA_vect){
	cnt++;
}

int main(void)
{
	char str[100];
	int nno=48; //�m�[�gNo
	
	spiInit();
	spiCtrlCs(DISABLE);
	
	setIOMode();
	uartInit();
	
	_delay_ms(100);
	
	soundInit();
	setTone();
	setCh();
	
	_delay_ms(100);
	sprintf(str, "***      YWinth Serial Console      ***\nFirmware version: %s\n", VERSIONCODE);
	uartPuts(str);
	uartPuts("4 Operator FM Sound Wind Synthesizer.\n");
	uartPuts("Designed by K.Yazawa.\n");
	uartPuts("This is Serial Console.\n");
	uartPuts("Please input command.\n");
	
    /* Replace with your application code */
	//_delay_ms(1000);
	initTimer();
	sei();
	
	while(1){
		
		//decodeKey();
		touch.touchGet();
		_delay_ms(10);
		
	}
}

// PIN13(ARD) = PB5
void setIOMode(void){
	DDRB |= 0b00100000;
}

void ctrlLed(uint8_t state){
	uint8_t reg;
	reg = PORTB;
	reg &= 0b11001111;
	reg |= state << 5;
	PORTB = reg;
}

void uartInit(void){
	UCSR0B = (1<<TXEN0) | (1<<RXEN0);
	UBRR0H = (F_CPU/16/BAUD-1)>>8;
	UBRR0L = (F_CPU/16/BAUD-1);
}

void uartPutc(char a){
	while(!(UCSR0A&0b00100000));
	UDR0 = a;
}

void uartPuts(char * str){
	while(*str != '\0'){
		uartPutc(*str);
		str++;
	}
}

void initTimer(void)
{
	/* Timer0: 8bit�^�C�}�ݒ� */
	TCCR0A = 0b00000010; /* �^�C�}���䃌�W�X�^�` */
	
	/* CTC����I */
	TCCR0B = 0b00000101; /* �^�C�}���䃌�W�X�^�a */
	/*              ||+- CS00 �ۯ�����I��
                    |+-- CS01 101 : 1024���� 
					+--- CS02 16M/1024 = 15.625KHz
					�^�C�}�o�� 61.04Hz T=16.384mS
	*/
	
	OCR0A = 255; /* �R���y�A�Ώ�(255�̏ꍇ �W������Ɠ���) */
	
	TIMSK0 = 0b00000010; /* �^�C�}�����}�X�N���W�X�^ */
	/*               +- OCIE0A ��� ����߯ĺ��߱ϯ�A�����L��
	*/
	
}

#if 1
void spiInit(){
	/* SPI�ݒ� */
	SPCR |= 0b01010001;
	/*	  	  |||||||+- SPR0 SPI�N���b�N�I��
			  ||||||+-- SPR1 
			  |||||+--- CPHA
			  ||||+---- CPOL
			  |||+----- MSTR ��/�����u�ݒ�(MSR=1/SLV=0)
			  ||+------ DORD
			  |+------- SPE  SPI����
			  +-------- SPIE SPI��������
	*/
	
	/* SPI�g�p�|�[�g�ݒ� */
	DDRB  |= 0b10110000; /* �������t����� */
	/*	   	   |||||||+- SCK  SPI�N���b�N  �o�� ���܂���t�I
			   ||||||+-- MISO SPIϽ���     ����
			   |||||+--- MOSI SPIϽ����    �o��
			   ||||+---- SS   SPI�ڰ�޾ڸ� �o��
			   |||+----- BTN4
			   ||+------ BTN3
			   |+------- BTN2
			   +-------- BTN1
	*/
}
void spiSend(uint8_t data){
	SPDR = data; /* SPI�f�[�^���W�X�^�ɏ�������ő��M�J�n */
	while((SPSR & (1<<SPIF)) == 0); /* ���M�����҂� */
}

void spiRead(){
	
}

void spiCtrlCs(uint8_t en){
	
	if(en == DISABLE){
		/* SPI CS=H ������ */
		PORTB|= 0b00010000;
		/*	   	  |||||||+- SCK  SPI�N���b�N  �o��
				  ||||||+-- MISO SPIϽ���     ����
				  |||||+--- MOSI SPIϽ����    �o��
				  ||||+---- SS   SPI�ڰ�޾ڸ� �o��
		*/
	}else{
		/* SPI CS=L �L���� */
		PORTB&= 0b11101111;
		/*	   	  |||||||+- SCK  SPI�N���b�N  �o��
				  ||||||+-- MISO SPIϽ���     ����
				  |||||+--- MOSI SPIϽ����    �o��
				  ||||+---- SS   SPI�ڰ�޾ڸ� �o��
		*/
	}
}

void spiRegWrite(uint8_t addr, uint8_t data){
	spiCtrlCs(ENABLE);
	spiSend(addr);
	spiSend(data);
	spiCtrlCs(DISABLE);
}


void spiRegBarstWrite(uint8_t addr, uint8_t * data, uint8_t dsize){
	spiCtrlCs(ENABLE);
	spiSend(addr);
	for(int i=0; i<dsize; i++){
		spiSend(data[i]);
	}
	spiCtrlCs(DISABLE);
}

void spiRegRead(uint8_t addr){
	spiCtrlCs(ENABLE);
	spiSend( 0b10000000 | addr ); /* RW=1(read) set */
	spiRead();
	spiCtrlCs(DISABLE);
}

void soundInit(){
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

#endif

void setTone(){
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

void keyOn(uint8_t fnumh, uint8_t fnuml, uint8_t vovol){
	vovol *= 4;
	spiRegWrite( 0x0B, 0x00 );//voice num
	spiRegWrite( 0x0C, vovol );//vovol
	spiRegWrite( 0x0D, fnumh );//fnum
	spiRegWrite( 0x0E, fnuml );//fnum
	spiRegWrite( 0x0F, 0x40 );//keyon = 1
}

void keyOff(void){
	spiRegWrite( 0x0F, 0x00 );//keyon = 0
}


void setCh(void){
	spiRegWrite( 0x0F, 0x30 );// keyon = 0
	spiRegWrite( 0x10, 0x71 );// chvol
	spiRegWrite( 0x11, 0x00 );// XVB
	spiRegWrite( 0x12, 0x08 );// FRAC
	spiRegWrite( 0x13, 0x00 );// FRAC
}

uint8_t noteNoToScale(uint16_t noteNo){
	return (noteNo%12);
}

uint8_t noteNoToBlock(uint16_t noteNo){
	return ((noteNo/12)-1);
}

uint16_t noteNoToFnum(uint16_t noteNo){
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

void keyOnNoteNo(uint16_t noteNo){
	uint8_t block, fnuml, fnumh;
	uint16_t fnum;
	fnum = noteNoToFnum(noteNo);
	block = noteNoToBlock(noteNo);
	
	fnuml  = (fnum>>4) & 0b00111000;
	fnumh  =      fnum & 0b01111111;
	fnuml |= block;
	
	keyOn(fnuml, fnumh, 5);
}

void decodeKey(){
	uint8_t keyval;
	keyval = PINA;
	for(int i=0; i<8; i++){
		if(((keyval>>i)&0x1) == 0){
			switch(i){
				case 4:
					keyOnNoteNo(60);
					break;
				case 5:
					keyOnNoteNo(62);
					break;
				case 6:
					keyOnNoteNo(64);
					break;
				case 7:
					keyOnNoteNo(65);
					break;
				case 0:
					keyOnNoteNo(67);
					break;
				case 1:
					keyOnNoteNo(69);
					break;
				case 2:
					keyOnNoteNo(71);
					break;
				case 3:
					keyOnNoteNo(72);
					break;
				
			}
		}
	}
	
	if(keyval == 0xFF){
		keyOff();
	}
}

void touchGet(){
	uint8_t keyval;
	
	/* L�o�́i���d�j */
	PORTA = 0x00;
	DDRA = 0xFF;
	_delay_us(5);
	DDRA = 0x00;
	
	/* �[�d�҂� */
	_delay_us(20);
	
	/* �d�����o */
	keyval = PINA; /* 0:������Ă� 1:������ĂȂ� */
	
	for(int i=0; i<8; i++){
		if(((keyval>>i)&0x1) == 0){
			switch(i){
				case 4:
				keyOnNoteNo(60);
				break;
				case 5:
				keyOnNoteNo(62);
				break;
				case 6:
				keyOnNoteNo(64);
				break;
				case 7:
				keyOnNoteNo(65);
				break;
				case 0:
				keyOnNoteNo(67);
				break;
				case 1:
				keyOnNoteNo(69);
				break;
				case 2:
				keyOnNoteNo(71);
				break;
				case 3:
				keyOnNoteNo(72);
				break;
				
			}
		}
	}
	
	if(keyval == 0xFF){
		keyOff();
	}
	
}