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
	csn(LOW);
	spi->transfer(reg);
	uint8_t result = SPI_tx_byte(0xff);
	csn(HIGH);
	return result;
}

uint8_t write_register(uint8_t reg, uint8_t value) {
	uint8_t status;
	csn(LOW);
	status = SPI_tx_byte(reg);
	csn(HIGH);

	return status;
}
