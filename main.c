#include <stdio.h>
#include <stdint.h>
#include <wiringPiSPI.h>

#define BATCH_SIZE 16

#define NCHANS  2

#define CMD_NONE        0x00
#define CMD_MOVE        0x10 // [nsteps:32, bdelay:32, edelay:32]*NCHANS

#define CMD_NONE_SIZE   0
#define CMD_MOVE_SIZE   ((4+4+4)*NCHANS)

int main(int argc, char *argv[]) {
	int st = 0;
	int fd = wiringPiSPISetup(0, 500000);
	if (fd < 0) {
		perror("cannot init spi");
	}
	uint8_t data[BATCH_SIZE];
	
	printf("spi txrx start\n");
	int i;
	int k = 0;
	for (;;) {
		int j;
		data[0] = CMD_MOVE;
		for (j = 0; j < BATCH_SIZE - 1; ++j) {
			data[1 + j] = 0x00;
		}

		st = wiringPiSPIDataRW(0, data, BATCH_SIZE);
		if (st < 0) {
			perror("txrx error");
			break;
		}

		/*
		if (data[1] == 0xFF) {
			k += 1;
		} else {
			printf("error %02X\n", data[0]);
		}
		printf("sent: %d,\n received: %d\n", k, *((uint32_t*)(data + 4)));
		*/

		for (j = 0; j < 8; ++j) {
			printf("%02X", data[j]);
		}
		printf("\n");

		delayMicroseconds(250000);
	}

	return 0;
}
