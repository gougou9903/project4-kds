#include "GPIO.h"
#include <stdio.h>
#include "Nordic.h"
#include <stdint.h>

void setup(void) {
	SPI_init();
}

int main() {
	void setup(void);
	write_register(CONFIG, 1);
	uint8_t a = read_register(CONFIG);
	printf("%d", a);
	return 0;
}
