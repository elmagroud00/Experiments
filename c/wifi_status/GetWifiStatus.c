#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <errno.h>
#include <net/if.h>

struct ethtool_value
{
	__uint32_t cmd;
	__uint32_t data;
};

int main(int argc, char **argv)
{
	struct ethtool_value edata;
	int fd = -1, err = 0;
	struct ifreq ifr;

	memset(&ifr, 0, sizeof(ifr));
	strcpy(ifr.ifr_name, "eth1");
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd < 0)
	{
		perror("Cannot get control socket");
		return 1;
	}
	edata.cmd = 0x0000000a; //command is get link status
	ifr.ifr_data = (caddr_t)&edata;
	err = ioctl(fd, 0x8946, &ifr);
	if(err == 0)
	{
		if(edata.data)
		{
			fprintf(stdout,"Link detected yes");
			return 0;
		}
		else
		{
			fprintf(stdout, "Link detected no");
			return 2;
		}
	}
	else if(errno != EOPNOTSUPP)		
	{
		perror("Cannot get link status");	
		return 1;
	}
	else
	{
		perror("Unknow status");
		return 3;
	}
}

