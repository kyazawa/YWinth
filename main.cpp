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
volatile uint8_t cnt=0;
volatile bool executePermission = ENABLE;


/* �^�C�}�����ݔ���������
   �� 1000Hz T=1mS */
ISR (TIMER0_COMPA_vect){
	/* 120Hz 8mS�Ɉ�x���C���������s */
	if(cnt == 3){
		/* ���C���������s�����s */
		executePermission = ENABLE; /* ���s���̊J���̓��C�������ōs�� */
		cnt = 0;
	}else{
		cnt++;
	}
	/* �`���^�����O�������� 4mS��v�Ń{�^���l�m�� */
	buttonSampling();		/* 1.�T���v�����O */
	buttonAveraging();		/* 2.���ω� */
	buttonPressDetect();	/* 3.�������m */
}

/* ���C������ */
int main(void)
{
	/* ���C�������F���������� */
	char str[100];
	uint32_t data;
	long bdata;
	uint8_t keyval;
	uint16_t noteNum, noteNum_old=0;
	char transpose=12;
	uint8_t vel, vel_old=0;
	
	spiInit();
	spiCtrlCs(DISABLE);
	
	setIOMode();
	buttonInit();
	uartInit();
	
	soundInit();
	setTone();
	setCh();
	
	/* UART�X�^�[�g�A�b�vү���ޑ��M(MIDI�L���̏ꍇ�͑��M���Ȃ�) */
#if (!MIDI_ENABLE)
	sprintf(str, "***      YWinth Serial Console      ***\nFirmware version: %s\n", VERSIONCODE);
	uartPuts(str);
	uartPuts("4 Operator FM Sound Wind Synthesizer.\n");
	uartPuts("Designed by K.Yazawa.\n");
	uartPuts("This is Serial Console.\n");
	uartPuts("Please input command.\n");
#endif

	/* MIDI���������� */
#if MIDI_ENABLE
	//midiInit();
#endif

	/* LCD�\������ LCD�͒x���̂ŋC������ */
	_delay_ms(100);
	lcdInit();
	_delay_ms(100);
	lcdPrint("YWinth");
	_delay_ms(20);
	lcdSetCursor(11,1);
	_delay_ms(20);
	lcdPrint(VERSIONCODE);
	
	initTimer();
	breathInit();
	
	cnt = 0;
	
	_delay_ms(500); /* ������҂� */
	setBreathOffset();
	
	menuInit();
	/* �����������C���荞�ݗL�����I */
	sei();
	
	/* ���C�������F���[�v���� */
	
	while(1){
		
		/* �^�C�}�ɂ�8mS�����Ŏ��s�����s */
		/* ���s���m�F�����s�\�Ȃ���s */
		while(executePermission == DISABLE);
		
		/* ������ ���t���� ������ */
			
		/* �u���X�f�[�^�擾 �� �x���V�e�B���� */
		bdata = getBreathOffsetValue();
		data = breathToVovol(bdata);
		vel = breathToVelocity(bdata);
		
		/* �^�b�`�Z���T�f�[�^�擾 �� �m�[�g�i���o�[���� */
		keyval = touchGet();
		noteNum = fingerToNoteNum(keyval);
			
		/* �m�[�g�i���o�[�{�x���V�e�B �� �L�[�I�� */
		keyOnNoteNoWithVovol(noteNum, data);
		
		/* MIDI���M���� */
#if MIDI_ENABLE
		/* �m�[�g�ω��A��or���i�V �� �O��m�[�g�I�t */
		if( (noteNum!=noteNum_old) || (vel>=4) ){ 
			midiNoteOff(0x01, noteNum);
		}
		
		/* ���A��and�O�񑧃i�V �� �m�[�g�I�� */
		if( (vel_old<4) && (vel>=4) ){
			midiNoteOn(0x01, noteNum, vel);
		}
		else if(vel>=4){
			/* ���p�� �� �A�t�^�[�^�b�` */
			midiAfterTouch(0x01, vel);
		}
		
		
		/* �߂��F�m�[�g�I�����o�̏����͊֐��Ȃǂ����Ă��������܂Ƃ߂���
				�u���X�Ƀq�X�e���V�X������Ƃ悢�C������ */
#endif

		vel_old = vel;
		noteNum_old = noteNum;
		
		/* ���j���[���� */
		menuActivity();
			
		/* ���s����� */
		executePermission = DISABLE;
		
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
	
	OCR0A = 16; /* �R���y�A�Ώ�(255�̏ꍇ �W������Ɠ���) */
	/* ��1mS���� */
	
	TIMSK0 = 0b00000010; /* �^�C�}�����}�X�N���W�X�^ */
	/*               +- OCIE0A ��� ����߯ĺ��߱ϯ�A�����L��
	*/
	
}



