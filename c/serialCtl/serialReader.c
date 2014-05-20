#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

int speed_attr[] = { B38400, B19200, B115200, B9600, B4800, B1200, B300, 
					 B38400, B19200, B9600, B4800, B1200, B300, };

int name_attr[] = { 38400, 19200, 115200,  9600, 4800, 2400, 1200, 300, 38400,
				    19200, 9600, 4800, 2400, 1200, 300, };

void set_speed(int fd, int speed) {
	int i;
	int status;
	struct termios Opt;

	tcgetattr(fd, &Opt);
	for(i = 0; i < (int)(sizeof(speed_attr) / sizeof(int)); i++) {
		if(speed == name_attr[i]) {
			tcflush(fd, TCIOFLUSH);
			cfsetispeed(&Opt, speed_attr[i]);
			cfsetospeed(&Opt, speed_attr[i]);
			status = tcsetattr(fd, TCSANOW, &Opt);
			if(status != 0) {
				perror("tcsetattr fd 1");
				return;
			}
			tcflush(fd, TCIOFLUSH);
		}
	}
}

int set_Parity(int fd, int databits, int stopbits, int parity) {
	struct termios options;
	
	if(tcgetattr(fd, &options) != 0) {
		perror("setup serial parity 2");
		return false;
	}
	options.c_cflag &= ~CSIZE;
	switch(databits) {
		case 7: options.c_cflag |= CS7;
				break;
		case 8: options.c_cflag |= CS8;
				break;
		default:
				fprintf(stderr, "Unsupported data size\n");
				return false;
	}

	switch(parity) {
		case 'n':
		case 'N': options.c_cflag &= ~PARENB;
				  options.c_iflag &= ~INPCK;
				  break;
		case 'o':
		case 'O': options.c_cflag |= (PARODD | PARENB);
				  options.c_iflag |= INPCK;
				  break;
		case 'e':
		case 'E': options.c_cflag |= PARENB;
				  options.c_cflag &= ~PARODD;
				  options.c_iflag |= INPCK;
				  break;
		case 's':
		case 'S': options.c_cflag &= ~PARENB;
				  options.c_cflag &= ~CSTOPB;
				  break;
		default: fprintf(stderr, "Unsupported parity\n");
				 return false;
	}

	switch(stopbits) {
		case 1: options.c_cflag &= ~CSTOPB;
				break;
		case 2: options.c_cflag |= CSTOPB;
				break;
		default: fprintf(stderr, "Unsupported stop bits\n");
				 return false;
	}

	if(parity != 'n') 
		options.c_iflag |= INPCK;

	tcflush(fd, TCIFLUSH);
	options.c_cc[VTIME] = 150; // time out seconds
	options.c_cc[VMIN] = 0; // Update the options and do it NOW
	if(tcsetattr(fd, TCSANOW, &options) != 0) {
		perror("Setup serials 3");
		return false;
	}

//	options.c_lflag &= ~(ICANON | ECHO | ISIG);
//	options.c_oflag &= ~OPOST;

	return true;
}

int OpenDev(char *Dev) {
	int fd = open(Dev, O_RDWR);

	if(-1 == fd) {
		perror("Cannot Open Serial Port 4");
		return -1;
	} else {
		return fd;
	}
}

int main(int argc, char **argv) {
	int fd;
	int nread;
	char buff[6] = {0};
	char *dev = argv[1];

	fd = OpenDev(dev);
	printf("Port: %s, speed: %d\n", dev, atoi(argv[2]));
	set_speed(fd, atoi(argv[2]));
	if(set_Parity(fd, 8, 1, 'N') == false) {
		printf("Set Parity Error 5\n");
		exit(0);
	}

	while(1) {
		while((nread = read(fd, buff, 5)) > 0) {
			printf("\nLen: %d : ", nread);
			buff[nread + 1] = '\0';
			printf(" Ret: %s\n", buff);
			sleep(1);
		}
	}

	close(fd); // Never here
}
