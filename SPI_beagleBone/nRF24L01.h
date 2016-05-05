#ifndef _NRF24L01_
#define _NRF24L01_

#include "spi.h"
#include "Nordic.h"
#include "GPIO.h"

uint8_t csn_pin=115;
uint8_t ce_pin=117;

void scn(int mode);

#endif
