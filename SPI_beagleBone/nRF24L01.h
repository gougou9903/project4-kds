#ifndef _NRF24L01_
#define _NRF24L01_

#include "spi.h"
#include "Nordic.h"
#include "GPIO.h"

extern uint8_t csn_pin;
extern uint8_t ce_pin;

void scn(int mode);
uint8_t read_register(uint8_t reg);
uint8_t read_register(uint8_t reg, uint8_t* buf, uint8_t len);
uint8_t write_register(uint8_t reg, uint8_t value);

#endif
