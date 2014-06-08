/* Auth: sijie.wang@gmail.com */
/* Date: Aug 10, 2013         */
/* Ver: 1.0                   */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <asm-generic/ioctls.h>
#include <errno.h>

#define version "1.0"
#define FALSE -1
#define TRUE 0

int speed_attr[] = { B38400, B19200, B115200, B9600, B4800, B1200, B300, 
					 B38400, B19200, B9600, B4800, B1200, B300, };

int name_attr[] = { 38400, 19200, 115200, 9600, 4800, 2400, 1200, 300, 38400,
				    19200, 9600, 4800, 2400, 1200, 300, };

int set_speed(int fd, int speed) {
	int i;
	int status;
	struct termios Opt;

	tcgetattr(fd, &Opt);
	for(i = 0; i < sizeof(speed_attr) / sizeof(int); i++) {
		if(speed == name_attr[i]) {
			tcflush(fd, TCIOFLUSH);
			cfsetispeed(&Opt, speed_attr[i]);
			cfsetospeed(&Opt, speed_attr[i]);
			status = tcsetattr(fd, TCSANOW, &Opt);
			if(status != 0) {
				perror("tcsetattr fd 1");
				return (FALSE);
			}
			tcflush(fd, TCIOFLUSH);
			return (TRUE);
		}
	}
	
	return (FALSE);
}

int set_Parity(int fd, int databits, int stopbits, int parity) {
	struct termios options;
	
	if(tcgetattr(fd, &options) != 0) {
		perror("setup serial parity 2");
		return (FALSE);
	}
	options.c_cflag &= ~CSIZE;
	switch(databits) {
		case 7: options.c_cflag |= CS7;
			break;
		case 8: options.c_cflag |= CS8;
			break;
		default:
			fprintf(stderr, "Unsupported data size\n");
			return (FALSE);
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
		 return (FALSE);
	}

	switch(stopbits) {
	case 1: options.c_cflag &= ~CSTOPB;
		break;
	case 2: options.c_cflag |= CSTOPB;
		break;
	default: fprintf(stderr, "Unsupported stop bits\n");
		 return (FALSE);
	}

	if(parity != 'n') 
		options.c_iflag |= INPCK;

	tcflush(fd, TCIFLUSH);
	options.c_cc[VTIME] = 50; 
	options.c_cc[VMIN] = 0;   
	if(tcsetattr(fd, TCSANOW, &options) != 0) {
		perror("Setup serials 3");
		return (FALSE);
	}

//	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	options.c_lflag &= ~(ICANON | ECHO | ISIG);
	options.c_oflag &= ~OPOST;
//	options.c_cflag |= (CLOCAL | CREAD);

	return (TRUE);
}

int OpenDev(char *Dev) {
	int fd = open(Dev, O_RDWR | O_NOCTTY);

	if(-1 == fd) {
		perror("Cannot Open Serial Port 4");
		return -1;
	} else {
		fcntl(fd, F_SETFL, 0);
		return fd;
	}
}

int main(int argc, char **argv) {
	int fd;
	int nread;
	int nwrite;
	int status;
	char *dev = argv[1];
	
	fd = OpenDev(dev);

	printf("Ver: %s, Port: %s, speed: %d\n", version,  dev, atoi(argv[2]));

	if(set_speed(fd, atoi(argv[2])) == FALSE) {
		fprintf(stderr, "set_speed error\n");
		close(fd);
		exit(0);
	}

	if(set_Parity(fd, 8, 1, 'N') == FALSE) {
		printf("Set Parity Error 5\n");
		close(fd);
		exit(0);
	}

	ioctl(fd, TIOCMGET, &status); // get hardware status
	printf("status = %d\n", status);

#if 0
	while(1) {
		ioctl(fd, TIOCMGET, &status); // get hardware status
		printf("status = %d\n", status);
		sleep(1);
	}
#endif
#if  0
	char buff[6] = {0};
	while(1) {
		nwrite = write(fd, "hello", 5);
		if(nwrite < 0) {
			fprintf(stderr, "write error\n");
		}

		tcflush(fd, TCIOFLUSH);
		nread = read(fd, buff, 5);
		buff[nread + 1] = '\0';
		printf("\nret: %s\n", buff);
	}
#endif

	close(fd); 
}
