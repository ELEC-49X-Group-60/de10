#include "HAL.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int HAL::start_HAL() {
	fd = open("/dev/mem", O_RDWR | O_SYNC);

	if(fd < 0) {
		std:: cerr << "Couldn't open /dev/mem\n";
		return -1;
	}

	bridge_map = static_cast<uint8_t *>(
				mmap(NULL, BRIDGE_SPAN, PROT_READ | PROT_WRITE, MAP_SHARED, fd, BRIDGE)
			);

	if (bridge_map == MAP_FAILED) {
		std::cerr << "mmap failed\n";
		close(fd);
		return -2;
	}

	return 0;
}

int HAL::end_HAL() {
	int result = munmap(bridge_map, BRIDGE_SPAN);

	if (result < 0) {
		std::cerr << "Couldn't unmap bridge\n";
		close(fd);
		return -3;
	}

	close(fd);
	return 0;
}

void HAL::write_pwm0(uint8_t val) {
	uint8_t *addr = bridge_map + PWM0;

	*(reinterpret_cast<uint8_t *>(addr)) = val;
}
