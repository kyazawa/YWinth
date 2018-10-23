/*
 * SPI.h
 *
 * Created: 2018/10/23 13:16:00
 *  Author: yazawa
 */ 


#ifndef SPI_H_
#define SPI_H_

using namespace std;
#include "YWinthCommon.h"

class SPI {
	public:
	/* SPI�ʐM�֘A */
	void spiInit();
	void spiSend(uint8_t data);
	void spiRead();
	void spiCtrlCs(uint8_t en);
	void spiRegWrite(uint8_t addr, uint8_t data);
	void spiRegRead(uint8_t addr);
	void spiRegBarstWrite(uint8_t addr, uint8_t * data, uint8_t dsize);
};



#endif /* SPI_H_ */