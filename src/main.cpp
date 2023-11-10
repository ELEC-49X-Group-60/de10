#include <HAL.h>

int main() {

	HAL *hal = new HAL();

	hal->start_HAL();
	
	hal->write_pwm0(0);
	hal->write_pwm1(0);
	hal->write_pwm2(0);
	hal->write_pwm3(0);

	hal->end_HAL();

	return 0;
}
