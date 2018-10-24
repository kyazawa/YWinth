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
	uint32_t data;
	long bdata;
	
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
	breathInit();
	sei();
	
	data = i2cRegRead(0b1011100, LPS22_WAMI); //whoami�ǂݍ���
	sprintf(str, "lps22_whoami:%x\n", data);
	uartPuts(str);
	
	_delay_ms(1000);
	setBreathOffset();
	
	while(1){
		
		bdata = getBreathOffsetValue();
		sprintf(str, "lps22:%d", bdata);
		//uartPuts(str);
		data = breathToVovol(bdata);
		sprintf(str, " vovol:%d\n", data);
		//uartPuts(str);
		
		keyOn(0x24,0x17,data);
		//setVovol(data);
		
		//decodeKey();
		//touch.touchGet();
		_delay_ms(1);
		
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

