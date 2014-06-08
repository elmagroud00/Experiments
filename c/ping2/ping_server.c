#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define SERV_PORT 8888
#define MSG_LEN   20

void do_something(char* mesg,FILE* fp,int server_sockfd,struct sockaddr* client_addr,socklen_t client_len )
{
	int n;
	time_t day_time;
	struct tm *ltm;
	socklen_t len;
	char buffer[MSG_LEN];
	struct in_addr caddr;
	for(;;)
	{
		len=client_len;
		n=recvfrom(server_sockfd,buffer,MSG_LEN,0,client_addr,&client_len);
		if(n==-1)
		{
			memcpy(buffer,"no data received!",18);
		}
		else
		{
			buffer[n]='\0';
		}
		caddr=((struct sockaddr_in*)client_addr)->sin_addr;
		day_time=time(NULL);
		ltm=localtime(&day_time);
		fprintf(fp,"%d:%d:%d:%d:%d:%d   %s  %s\n",ltm->tm_year+1900,ltm->tm_mon+1,ltm->tm_mday,ltm->tm_hour,ltm->tm_min,ltm->tm_sec,inet_ntoa(caddr),buffer);
		fflush(fp);

		n=sendto(server_sockfd,mesg,MSG_LEN,0,client_addr,len);
	}
}

int main(int argc,char** argv)
{
	int server_sockfd;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	FILE *fp;
	char mesg[MSG_LEN];
	fp=fopen("/var/log/ping_server.log","a+");
	if(argc>1)
	{
		memcpy(mesg,argv[1],MSG_LEN);
		mesg[MSG_LEN]='\0';
	}
	server_sockfd=socket(AF_INET,SOCK_DGRAM,0);

	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=htonl(INADDR_ANY);
	server_address.sin_port=htons(SERV_PORT);

	if(bind(server_sockfd,(struct sockaddr*)&server_address,sizeof(server_address))==-1)
	{
		perror("bind error");
		exit(1);
	}
	
	do_something(mesg,fp,server_sockfd,(struct sockaddr *)&client_address,sizeof(client_address));
	fclose(fp);
	return 0;
}
