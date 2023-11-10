#include <HAL.h>

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int main() {

	/*HAL *hal = new HAL();

	hal->start_HAL();
	
	hal->write_pwm0(150);
	hal->write_pwm1(128);
	hal->write_pwm2(128);
	hal->write_pwm3(128);

	hal->end_HAL();*/

	int server_fd, new_socket;
	ssize_t valread;
	struct sockaddr_in address;
	int opt = 1;
	socklen_t addrlen = sizeof(address);
	
	
	HAL *hal = new HAL();
	hal->start_HAL();

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		return -1;
	}

	if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEADDR, &opt, sizeof(opt))) {
		perror("setsockopt");
		return -1;
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("bind failed");
		return -1;
	}

	if(listen(server_fd, 3) < 0) {
		perror("listen");
		return -1;
	}

	if((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0) {
		perror("accept");
		return -1;
	}

	uint8_t buff[8] = { 0 } ;
	bool ignore_packet = false;

	for(;;) {

		for(int i = 0; i < 8; i++) {
			buff[i] = 0;
		}

		read(new_socket, buff, sizeof(buff));

		if(ignore_packet) {
			ignore_packet = false;
			continue;
		}
		
		uint8_t pwm0_speed = buff[0];
		uint8_t pwm1_speed = buff[1];
		uint8_t pwm2_speed = buff[2];
		uint8_t pwm3_speed = buff[3];

		printf("---------\n");
		printf("PWM0 : %d\n", pwm0_speed);
		printf("PWM1 : %d\n", pwm1_speed);
		printf("PWM2 : %d\n", pwm2_speed);
		printf("PWM3 : %d\n", pwm3_speed);

		ignore_packet = true;
		
		hal->write_pwm0(pwm0_speed);
		hal->write_pwm1(pwm1_speed);
		hal->write_pwm2(pwm2_speed);
		hal->write_pwm3(pwm3_speed);

		//if(exit) {
		//	break;
		//}
	}	

	close(server_fd);
	hal->end_HAL();

	return 0;
}
