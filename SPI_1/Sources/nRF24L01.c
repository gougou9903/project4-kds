/*
 * nRF24L01.c
 *
 *  Created on: Apr 21, 2016
 *      Author: HaoranFang
 */
#include "nRF24L01.h"
#include "MKL25Z4.h"
#include "spi.h"

uint8_t NRF24L01_RXDATA[RX_PLOAD_WIDTH];//nrf24l01 received data
uint8_t NRF24L01_TXDATA[RX_PLOAD_WIDTH];//nrf24l01 transmitting data

uint8_t TX_ADDRESS[TX_ADR_WIDTH] = {
		0xE1, 0xE2, 0xE3, 0xE4, 0xE5
};//transmitting address

uint8_t RX_ADDRESS[RX_ADR_WIDTH] = {
0xE1,0xE2,0xE3,0xE4,0xE5
};//receiving address

uint8_t NRF_Write_Reg(uint8_t reg, uint8_t value){
	uint8_t status;
	EN_CSN;
	status = spi_send(SPI0_BASE_PTR,reg);//write address first
	spi_send(SPI0_BASE_PTR, value);//write data
	DS_CSN;

	return status;
}

uint8_t NRF_Read_Reg(uint8_t reg){
	uint8_t read_val;
	EN_CSN;
	spi_send(SPI0_BASE_PTR, reg);//write address first
	read_val = spi_send(SPI0_BASE_PTR, 0);//write data
	DS_CSN;
	return read_val;
}

uint8_t NRF_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t len){

	uint8_t i;
	uint8_t status = 1;
	EN_CSN;
	status = spi_send(SPI0_BASE_PTR, reg); //transmit register address first
	for(i = 0; i < len; i++){
		spi_send(SPI0_BASE_PTR, pBuf[i]);  //transmit TX_ADDR
	}
	DS_CSN;
	return status;
}

uint8_t NRF_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t len){

	uint8_t i;
	uint8_t status;
	EN_CSN;
	status = spi_send(SPI0_BASE_PTR, reg); //transmit register address first
	for(i = 0; i < len; i++){
		pBuf[i] = spi_send(SPI0_BASE_PTR, 0);// read data
	}
	DS_CSN;
	return status;
}

void TX_Mode(uint8_t * BUF){// BUF points to the data
	EN_CE;
	NRF_Write_Buf(NRF_WRITE_REG + TX_ADDR,TX_ADDRESS, TX_ADR_WIDTH);//writing transmitting address
	NRF_Write_Buf(NRF_WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);//receiving channel 0 must be the same as transmitting address
	NRF_Write_Buf(WR_TX_PLOAD, BUF, TX_PLOAD_WIDTH);//write data to TX FIFO
	NRF_Write_Reg(NRF_WRITE_REG + EN_AA, 0x01);//Enable auto acknowledgement data pipe 0
	NRF_Write_Reg(NRF_WRITE_REG + EN_RXADDR, 0x01);//Enable data pipe 0
	NRF_Write_Reg(NRF_WRITE_REG + SETUP_RETR, 0x0A);//Auto Retransmit Delay 250us and Auto Retransmit Count 10
	NRF_Write_Reg(NRF_WRITE_REG + RF_CH, 0x40);//Select RF channel 0x40
	NRF_Write_Reg(NRF_WRITE_REG + RF_SETUP, 0x07);//Air Data Rate 1Mbps, RF output power 0dBm, Setup LNA gain
	NRF_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0E);//TX Mode
	DS_CE;
}

void RX_Mode(uint8_t * BUF){
	EN_CE;
	NRF_Write_Buf(NRF_WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);
	NRF_Write_Reg(NRF_WRITE_REG + EN_AA, 0x01);
	NRF_Write_Reg(NRF_WRITE_REG + EN_RXADDR, 0x01);
	NRF_Write_Reg(NRF_WRITE_REG + RF_CH, 0x40);
	NRF_Write_Reg(RX_PW_P0, 0x40);
	NRF_Write_Reg(NRF_WRITE_REG + RF_SETUP, 0x07);
	NRF_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0F);
	DS_CE;
}
//we can use TX_Mode or RX_Mode instead
void Nrf24l01_Init(uint8_t model){
	EN_CE;
	NRF_Write_Buf(NRF_WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH);
	NRF_Write_Buf(NRF_WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);
	NRF_Write_Reg(NRF_WRITE_REG + EN_AA, 0x01);
	NRF_Write_Reg(NRF_WRITE_REG + EN_RXADDR, 0x01);
	NRF_Write_Reg(NRF_WRITE_REG + SETUP_RETR, 0x1a);
	NRF_Write_Reg(NRF_WRITE_REG + RF_CH, 40);
	NRF_Write_Reg(NRF_WRITE_REG + RF_SETUP, 0X0f);

	if(model == 1){
		NRF_Write_Reg(NRF_WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH);
		NRF_Write_Reg(NRF_WRITE_REG + CONFIG, 0X0f);
	}else if(model == 2){
		NRF_Write_Reg(NRF_WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH);
		NRF_Write_Reg(NRF_WRITE_REG + CONFIG, 0X0e);
	}
	DS_CE;
}

void delay_ms(uint8_t x){
	uint8_t i, j;

	for( i = 0; i < x; i++){
		j = 500;
		while(--j);

	}
}

uint8_t NRF24l01_Check(void){//check if the data can be written into NRF
	uint8_t buf1[5];
	uint8_t i;
	NRF_Write_Buf(NRF_WRITE_REG + TX_ADDR, TX_ADDRESS, 5);
	NRF_Read_Buf(TX_ADDR, buf1, 5);

	for(i = 0; i < 5; i++){
		if(buf1[i] != TX_ADDRESS[i])
			break;
	}

	if(i == 5)
		return 1; // success
	else
		return 2; // fail
}

