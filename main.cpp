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
	
	
	/* �`���^�����O��������
	   4mS��v�Ń{�^���l�m�� */
	
	#if 1
	buttonSampling();		/* 1.�T���v�����O */
	buttonAveraging();		/* 2.���ω� */
	buttonPressDetect();	/* 3.�������m */
	#endif
	
	/* �{�^�������l�ւ̃A�N�Z�X�͒ʏ폈�����ōs�� */
}

/* ���C������ */
int main(void)
{
	/* ���C�������F���������� */
	char str[100];
	int nno=48; //�m�[�gNo
	uint32_t data;
	long bdata;
	uint8_t keyval;
	uint16_t noteNum;
	char transpose=12;
	uint8_t btn, btncmd;
	
	spiInit();
	spiCtrlCs(DISABLE);
	
	setIOMode();
	buttonInit();
	uartInit();
	
	soundInit();
	setTone();
	setCh();
	
	/* UART�X�^�[�g�A�b�vү���ޑ��M */
	sprintf(str, "***      YWinth Serial Console      ***\nFirmware version: %s\n", VERSIONCODE);
	uartPuts(str);
	uartPuts("4 Operator FM Sound Wind Synthesizer.\n");
	uartPuts("Designed by K.Yazawa.\n");
	uartPuts("This is Serial Console.\n");
	uartPuts("Please input command.\n");
	
	/* LCD�\������ LCD�͒x���̂ŋC������ */
	_delay_ms(100);
	lcdInit();
	_delay_ms(100);
	lcdPrint("YWinth");
	_delay_ms(20);
	lcdSetCursor(0,1);
	_delay_ms(20);
	lcdPrint("Initializing.");
	
	initTimer();
	menuInit();
	breathInit();
	
	cnt = 0;
	
	
	data = i2cRegRead(0b1011100, LPS22_WAMI); //whoami�ǂݍ���
	sprintf(str, "lps22_whoami:%x\n", data);
	uartPuts(str);
	
	_delay_ms(200); /* ������҂� */
	setBreathOffset();
	
	/* �����������C���荞�ݗL�����I */
	sei();
	
	/* ���C�������F���[�v���� */
	
	while(1){
		
		/* �^�C�}�ɂ�8mS�����Ŏ��s�����s */
		/* ���s���m�F�����s�\�Ȃ���s */
		while(executePermission == DISABLE);
		
			/* ���t���� */
			bdata = getBreathOffsetValue();
			sprintf(str, "lps22:%d", bdata);
			//uartPuts(str);
			data = breathToVovol(bdata);
			sprintf(str, " vovol:%d\n", data);
			//uartPuts(str);
		
			keyval = touchGet();
			noteNum = fingerToNoteNum(keyval) + transpose;
			keyOnNoteNoWithVovol(noteNum, data);
		
			btn = buttonGet();
		
			sprintf(str,"%d %d", btn, btncmd);		
		
			//sprintf(str, "Nn:%02d Ve:%02d", noteNum, data);
			//uartPuts(str);
			
			//lcdSetCursor(0,1);
			//lcdPrint(str);
			
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



