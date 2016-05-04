/*
 * nRF24L01.h
 *
 *  Created on: Apr 22, 2016
 *      Author: HaoranFang
 */

#ifndef INCLUDES_NRF24L01_H_
#define INCLUDES_NRF24L01_H_

#include <stdint.h>

#define RX_PLOAD_WIDTH	32
#define TX_PLOAD_WIDTH	32
#define TX_ADR_WIDTH	5
#define RX_ADR_WIDTH	5

//**********************************************************
#define NRF_READ_REG	0x00
#define NRF_WRITE_REG	0x20
#define R_RX_PL_WID		0x60
#define RD_RX_PLOAD		0x61
#define WR_TX_PLOAD		0xA0
#define FLUSH_TX		0xE1
#define FLUSH_RX		0xE2
#define REUSE_TX_PL		0xE3
#define NOP				0xFF
//*****************************************************************************************
#define CONFIG			0x00
#define EN_AA			0x01
#define EN_RXADDR		0x02
#define SETUP_AW		0x03
#define SETUP_RETR		0x04
#define RF_CH			0x05
#define RF_SETUP		0x06
#define NRFRegSTATUS	0x07
#define OBSERVE_TX		0x08
#define CD				0x09
#define RX_ADDR_P0		0x0A
#define RX_ADDR_P1		0x0B
#define RX_ADDR_P2		0x0C
#define RX_ADDR_P3		0x0D
#define RX_ADDR_P4		0x0E
#define RX_ADDR_P5		0x0F
#define TX_ADDR			0x10
#define RX_PW_P0		0x11
#define RX_PW_P1		0x12
#define RX_PW_P2		0x13
#define RX_PW_P3		0x14
#define RX_PW_P4		0x15
#define RX_PW_P5		0x16
#define FIFO_STATUS		0x17
//*************************************************************************************
//*********************************************NRF24L01*************************************
#define RX_DR6
#define TX_DS5
#define MAX_RT4

#define MODEL_RX1
#define MODEL_TX2
#define MODEL_RX23
#define MODEL_TX24

extern uint8_t NRF24L01_RXDATA[RX_PLOAD_WIDTH];
extern uint8_t NRF24L01_TXDATA[RX_PLOAD_WIDTH];
extern uint8_t NRF24L01_TXDATA_RC[RX_PLOAD_WIDTH];

//void Nrf24l01_Init(uint8_t model, uint8_t ch);
//void NRF_TxPacket(uint8_t * tx_buf, uint8_t len);
//void NRF_TxPacket_AP(uint8_t * tx_buf, uint8_t len);
uint8_t NRF_Read_Reg(uint8_t reg);
uint8_t NRF_Write_Reg(uint8_t reg, uint8_t value);
uint8_t NRF_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t uchars);
uint8_t NRF_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t len);
uint8_t Nrf24l01_Check(void);
void TX_Mode(uint8_t * BUF);
void RX_Mode(uint8_t * BUF);
void delay_ms(uint8_t x);
uint8_t NRF24l01_Check(void);
void Nrf24l01_Init(uint8_t model);
#endif /* INCLUDES_NRF24L01_H_ */
