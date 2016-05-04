/*
 * spi.c
 *
 *  Created on: Apr 22, 2016
 *      Author: HaoranFang
 */
#include "spi.h"

void spi_init(SPI_MemMapPtr SPI_MemPtr){
	en_SPI();
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	PORTC_PCR8 = PORT_PCR_MUX(1); /* (First  ALT) Pin PTC8  is GPIO (CE) */
	PORTC_PCR9 = PORT_PCR_MUX(1); //(First  ALT) Pin PTC9  is GPIO (CSN)
	PORTC_PCR5 = PORT_PCR_MUX(2); //(Second ALT) Pin PTC5  is SPI0_SCK
	PORTC_PCR6 = PORT_PCR_MUX(2); //(Second ALT) Pin PTC6  is SPI0_MOSI
	PORTC_PCR7 = PORT_PCR_MUX(2); //(Second ALT) Pin PTC7  is SPI0_MISO
	FPTC->PDOR = (1 << 8)|(1 << 9); // switch blue led off
	FPTC->PDDR = (1UL << 8)|(1UL << 9);
	EN_CSN;
	EN_CE;
	SPI_MemPtr->C1 |= ((1<<SPI_C1_SPE_SHIFT)|(1<<SPI_C1_MSTR_SHIFT)|(1<<SPI_C1_CPHA_SHIFT));// Master mode is selected, SPI is Enabled, CPHA=1
	SPI_MemPtr->C2 |= (1<<SPI_C2_SPISWAI_SHIFT);
	SPI_MemPtr->BR = 0x00; // SPPR=1, SPR=2
}

//enable the SPI0 module by enabling the SPI Clock Gating
void en_SPI(void){
		SIM->SCGC4 |= SIM_SCGC4_SPI0_MASK;
}

uint8_t spi_send(SPI_MemMapPtr Ptr,uint8_t data){
	//uint8_t TranData = data;
	uint8_t RecData= 0;
	//uint8_t spi_test = 0;
	while (((Ptr->S)&SPI_S_SPTEF_MASK)!= 0x20){ // transmit buffer not empty
	}

	Ptr->D=data;
	//spi_test = Ptr->S;
	while (((Ptr->S)&SPI_S_SPRF_MASK)!= 0x80){ // receiving buffer empty
	}

	RecData=Ptr->D;
	//spi_test = Ptr->S;

	return RecData;
}
