#ifndef HAL_H
#define HAL_H

#include <iostream>

class HAL {

	public:
		int start_HAL();
		int end_HAL();
		
		void write_pwm0(uint8_t val);
	
	private:
		constexpr static int32_t BRIDGE = 0xC0000000;
		constexpr static uint32_t BRIDGE_SPAN = 0xF;
		constexpr static uint32_t PWM0 = 0x0;


		int fd = 0;
		uint8_t *bridge_map = NULL;
};

#endif
