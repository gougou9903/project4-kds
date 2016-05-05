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

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

#define device "/dev/spidev1.0"
extern int fd ;
extern uint8_t mode;
extern uint8_t  bits;
extern uint32_t  speed;
void SPI_init();

uint8_t SPI_tx_byte(uint8_t tx_);

#endif
