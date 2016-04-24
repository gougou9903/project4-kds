/*
 * spi.c
 *
 *  Created on: Apr 22, 2016
 *      Author: HaoranFang
 */
#include "spi.h"

void spi_init(SPI_MemMapPtr SPI_MemPtr){
	en_SPI();
	PORTC_PCR8 = PORT_PCR_MUX(1);
	PORTC_PCR9 = PORT_PCR_MUX(1);
	PORTC_PCR5 = PORT_PCR_MUX(2);
	PORTC_PCR6 = PORT_PCR_MUX(2);
	PORTC_PCR7 = PORT_PCR_MUX(2);
	FPTC->PDOR = (1 << 8)|(1 << 9); // switch blue led off
	FPTC->PDDR = (1UL << 8)|(1UL << 9);
	EN_CSN;
	SPI_MemPtr->C1 |= ((1<<SPI_C1_SPE_SHIFT)|(1<<SPI_C1_MSTR_SHIFT)|(1<<SPI_C1_CPHA_SHIFT));// Master mode is selected, SPI is Enabled, CPHA=1
	SPI_MemPtr->C2 |= (1<<SPI_C2_SPISWAI_SHIFT);
	SPI_MemPtr->BR = 0x00; // SPPR=1, SPR=2
}


void en_SPI(void){
		SIM->SCGC4 = (1<<SIM_SCGC4_SPI0_SHIFT) | (SIM->SCGC4);
}

uint8_t spi_send(SPI_MemMapPtr SPI_MemPtr,uint8_t data){
	uint8_t RecData=0;
	while (((SPI_MemPtr->S)&SPI_S_SPTEF_MASK)!= 0x20){
	}

	SPI_MemPtr->D=data;

	while (((SPI_MemPtr->S)&SPI_S_SPRF_MASK)!= 0x80){
	}

	RecData=SPI_MemPtr->D;

	return RecData;
}
