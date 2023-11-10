#ifndef HAL_H
#define HAL_H

#include <iostream>

class HAL {

	public:
		int start_HAL();
		int end_HAL();
		
		void write_pwm0(uint8_t val);
		void write_pwm1(uint8_t val);
		void write_pwm2(uint8_t val);
		void write_pwm3(uint8_t val);
	
	private:
		constexpr static int32_t BRIDGE = 0xC0000000;
		constexpr static uint32_t BRIDGE_SPAN = 0x3F;
		constexpr static uint32_t PWM0 = 0x00;
		constexpr static uint32_t PWM1 = 0x10;
		constexpr static uint32_t PWM2 = 0x20;
		constexpr static uint32_t PWM3 = 0x30;


		int fd = 0;
		uint8_t *bridge_map = NULL;
};

#endif
