#include "spi.h"

uint8_t mode = 0 ;

uint8_t bits = 8 ;

uint32_t speed = 16000000;
int fd = 0;

void SPI_init() {
	int ret = 0;
	fd = open(device, O_RDWR);
	if (fd < 0) {
		abort();
	}
	//spi mode
	ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
	if (ret == -1)
	{
		abort();
	}

	ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
	if (ret == -1)
	{
		abort();
	}

	/*
	* bits per word
	*/
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == -1)
	{
		abort();
	}

	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
	if (ret == -1)
	{
		abort();
	}
	/*
	* max speed hz
	*/
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1)
	{
		abort();
	}

	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
	if (ret == -1)
	{
		abort();
	}
}

uint8_t SPI_tx_byte(uint8_t tx_) {
	int ret;
	uint8_t tx[] = { 0 };
	tx[0] = tx_;

	uint8_t rx[] = { 0 };
	struct spi_ioc_transfer tr;
	tr.tx_buf = (unsigned long)tx;
	tr.rx_buf = (unsigned long)rx;
	tr.len = 1;
	tr.delay_usecs = 0;
	tr.cs_change = 1;
	tr.speed_hz = speed;
	tr.bits_per_word = bits;

	ret=ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1) {
		abort();
	}
	
	return rx[0];
}
