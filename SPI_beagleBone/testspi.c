#include "GPIO.h"
#include "nRF24L01.h"
#include "spi.h"
#include <cstdlib>

void setup(void) {
	SPI_init();
}

int main() {
	write_register(STATUS, 1);
	uint8_t a = read_register(STATUS);
	printf("%d", a);
	return 0;
}
