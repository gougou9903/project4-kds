#ifndef _SPI_BEAGELBONE_
#define _SPI_BEAGELBONE_

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <inttypes.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#define device "/dev/spidev1.0"
int fd = 0;
uint8_t mode;
uint8_t  bits 8
uint8_t  speed 16000000

void SPI_init();

uint8_t SPI_tx_byte(uint8_t tx_);

#endif
