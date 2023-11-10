#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
	
	constexpr uint32_t BRIDGE = 0xC0000000;
	constexpr uint32_t BRIDGE_SPAN = 0xF;
	constexpr uint32_t PWM0 = 0x0;

	uint8_t pwm0_val = 0;  // 0 to 255

	uint8_t *pwm0_map = NULL;

	uint8_t *bridge_map = NULL;

	int fd = 0;
	int result = 0;
	
	fd = open("/dev/mem", O_RDWR | O_SYNC);

	if (fd < 0) {
		std::cerr << "Couldn't open /dev/mem\n";
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

	pwm0_map = bridge_map + PWM0;

	std::cout << "bridge_map = " << bridge_map << "\n";

	*(reinterpret_cast<uint8_t *>(pwm0_map)) = pwm0_val;

	result = munmap(bridge_map, BRIDGE_SPAN);

	if (result < 0) {
		std::cerr << "Couldn't unmap bridge\n";
		close(fd);
		return -3;
	}

	close(fd);
	return 0;
}
