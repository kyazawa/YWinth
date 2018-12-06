/*
 * Comm.cpp
 *
 * Created: 2018/12/6 9:22:35
 *  Author: yazawa
 */ 

#include "Comm.h"

/* 受信バッファ */
char RxBuff[256];

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