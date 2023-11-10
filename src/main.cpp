#include <HAL.h>

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <strings.h>

#define PORT 8080

int main() {

	/*HAL *hal = new HAL();

	hal->start_HAL();
	
	hal->write_pwm0(0);
	hal->write_pwm1(0);
	hal->write_pwm2(0);
	hal->write_pwm3(0);

	hal->end_HAL();*/

	int status, valread, client_fd;
	struct sockaddr_in serv_addr;

	if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Socket creation error \n");
		return -1;
	}

	bzero(&serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("192.168.1.102");
	serv_addr.sin_port = htons(PORT);

	if(connect(client_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != 0) {
		printf("Connection with the server failed");
		return -1;
	}

	char buff[80];
	for(;;) {
		bzero(buff, sizeof(buff));
		read(client_fd, buff, sizeof(buff));

		printf("From Server : %s", buff);

		if(strncmp("exit", buff, 4) == 0) {
			break;
		}
	}	

	close(client_fd);

	return 0;
}
