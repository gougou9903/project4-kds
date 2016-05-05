#ifndef _NRF24L01_
#define _NRF24L01_

#include "spi.h"
#include "Nordic.h"
#include "GPIO.h"

extern uint8_t csn_pin;
extern uint8_t ce_pin;

void scn(int mode);

#endif
