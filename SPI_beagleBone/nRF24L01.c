#include "Nordic.h"
#include "nRF24L01.h"
#include "spi.h"

void csn(int mode)
{
	digitalWrite(csn_pin, mode);
}

void ce(int level) {
	digitalWrite(ce_pin, level);
}

uint8_t read_register(uint8_t reg) {
	csn(0);
	transfer(reg);
	uint8_t result = SPI_tx_byte(0xff);
	csn(1);
	return result;
}

uint8_t write_register(uint8_t reg, uint8_t value) {
	uint8_t status;
	csn(0);
	status = SPI_tx_byte(reg);
	csn(1);

	return status;
}
