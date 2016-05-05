#include "GPIO.h"
#include <stdio.h>
#include "Nordic.h"


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
