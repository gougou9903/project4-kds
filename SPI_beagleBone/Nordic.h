#pragma once
#define STATUS 0x00
#define CONFIG 0x01
#define TXADDR 0x02
#define RF_SETUP 0x03
#define FIFO_STATUS 0x04
#define NORDIC_POWER_UP (1)
#define NORDIC_POWER_DOWN (0)
#define NORDIC_POWER_UP_MASK (0x02)

/* Instruction Mnemonics */
#define R_REGISTER    0x00
#define W_REGISTER    0x20
#define REGISTER_MASK 0x1F
#define ACTIVATE      0x50
#define R_RX_PL_WID   0x60
#define R_RX_PAYLOAD  0x61
#define W_TX_PAYLOAD  0xA0
#define W_ACK_PAYLOAD 0xA8
#define FLUSH_TX      0xE1
#define FLUSH_RX      0xE2
#define REUSE_TX_PL   0xE3
#define NOP           0xFF