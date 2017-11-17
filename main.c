#include <stdio.h>
#include <stdint.h>
#include <wiringPiSPI.h>

#define NCHANS  2

#define CMD_NONE        0x00
#define CMD_MOVE        0x10 // [nsteps:32, bdelay:32, edelay:32]*NCHANS

#define CMD_NONE_SIZE   0
#define CMD_MOVE_SIZE   4


int main(int argc, char *argv[]) {
	int st = 0;
	int fd = wiringPiSPISetup(0, 500000);
	if (fd < 0) {
		perror("cannot init spi");
	}
	uint8_t data[1+CMD_MOVE_SIZE] = {CMD_MOVE,0x55,0x50,0x05,0x55};
	printf("spi tx start\n");
	
	st = wiringPiSPIDataRW(0, data, 1);
	if (st < 0) {
		perror("cannot tx header");
	} else {
		printf("header tx done\n");
	}
	delayMicroseconds(1000);
	
	st = wiringPiSPIDataRW(0, data + 1, CMD_MOVE_SIZE);
	if (st < 0) {
		perror("cannot tx data");
	} else {
		printf("data tx done\n");
	}
	return 0;
}
