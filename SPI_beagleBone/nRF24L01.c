#include "Nordic.h"
#include "nRF24L01.h"
uint8_t csn_pin =115;
uint8_t ce_pin = 117;
void csn(int mode)
{
	//digitalWrite(csn_pin, mode);
}

void ce(int level) {
	digitalWrite(ce_pin, level);
}
uint8_t read_register(uint8_t reg, uint8_t* buf, uint8_t len)
{
  uint8_t status;

  csn(LOW);
  status = spi->transfer( R_REGISTER | ( REGISTER_MASK & reg ) );
  while ( len-- )
    *buf++ = spi->transfer(0xff);

  csn(HIGH);

  return status;
}
//read data from the register
uint8_t read_register(uint8_t reg) {
	csn(0);
	SPI_tx_byte(reg);
	uint8_t result = SPI_tx_byte(0xff);
	csn(1);
	return result;
}
//write data to the register 
uint8_t write_register(uint8_t reg, uint8_t value) {
	uint8_t status;
	csn(0);
	status = SPI_tx_byte(reg);
	csn(1);

	return status;
}
