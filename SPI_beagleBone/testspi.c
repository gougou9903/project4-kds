#include "GPIO.h"
#include "nRF24L01.h"
#include <stdio.h>



void setup(void) {
	SPI_init();
}

int main() {
	void setup(void);
	write_register(STATUS, 1);
	uint8_t a = read_register(STATUS);
	printf("%d", a);
	return 0;
}
