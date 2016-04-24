/*
 * spi.h
 *
 *  Created on: Apr 22, 2016
 *      Author: HaoranFang
 */
#include <MKL25Z4.H>
#include <stdint.h>

#ifndef INCLUDES_SPI_H_
#define INCLUDES_SPI_H_

#define EN_CSN (FPTC->PSOR= 1UL << 9)
#define DS_CSN (FPTC->PCOR= 1UL << 9)

#define EN_CE (FPTC->PSOR= 1UL << 8)
#define DS_CE (FPTC->PCOR= 1UL << 8)

void en_SPI(void);

void spi_init(SPI_MemMapPtr SPI_MemPtr);

uint8_t spi_send(SPI_MemMapPtr SPI_MemPtr,uint8_t data);

#endif /* INCLUDES_SPI_H_ */
