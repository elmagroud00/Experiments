#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define SERV_PORT 8888
#define MSG_LEN  20

int main(int argc ,char **argv)
{
	int sockfd;
	int n;
	FILE* fp;
	char send_content[MSG_LEN];
	char receive_content[MSG_LEN];
	struct sockaddr_in server_address;
	time_t day_time;
	struct tm *ltm;

	if(argc!=3)
	{
		printf("Usage: ping_server (server IP) (MAC address)!\n");
		exit(1);
	}
	fp=fopen("/var/log/ping_client.log","a+");
	if(!fp)
	{	
		printf("/var/log/ folder is not exist!");
		exit (1);
	}
	bzero(&server_address,sizeof(server_address));
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(SERV_PORT);
	if(inet_pton(AF_INET,argv[1],&server_address.sin_addr)<=0)
	{
		printf("[%s] is not a valid IPaddress\n",argv[1]);
		exit(1);
	}
	memcpy(send_content,argv[2],sizeof(send_content));

	sockfd=socket(AF_INET,SOCK_DGRAM,0);

	if(connect(sockfd,(struct sockaddr*)&server_address,sizeof(server_address))==-1)
	{
		perror("connect error!");
		exit(1);
	}

	n=write(sockfd,send_content,sizeof(send_content));
	if(n==-1)
	{
		perror("read error!");
		exit(1);
	}
	n=read(sockfd,receive_content,MSG_LEN);
	receive_content[n]='\0';
	day_time=time(NULL);
	ltm=localtime(&day_time);
	fprintf(fp,"%d:%d:%d:%d:%d:%d   %s  %s\n",ltm->tm_year+1900,ltm->tm_mon+1,ltm->tm_mday,ltm->tm_hour,ltm->tm_min,ltm->tm_sec,argv[1],receive_content);
	fflush(fp);
	fclose(fp);
	return 0;
}
















