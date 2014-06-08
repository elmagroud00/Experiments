#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERV_PORT 8888
#define NUM_THREADS 99999

void *thread_function(void *arg);
int sockfd;
int main(int argc , char** argv)
{
	int res;
	pthread_t a_thread[NUM_THREADS];
	pthread_attr_t tattr;
	size_t size=40906;
	//void *thread_result;
	int lots_of_threads;
	//int sock_fd;
	//char send_content[SEND_LEN];
	struct sockaddr_in server_address;

	pthread_attr_setstacksize(&tattr,size);

	bzero(&server_address,sizeof(server_address));
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(SERV_PORT);
	inet_pton(AF_INET,argv[1],&server_address.sin_addr);
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	connect(sockfd,(struct sockaddr*)&server_address,sizeof(server_address));

	for(lots_of_threads=0;lots_of_threads<NUM_THREADS;lots_of_threads++)
	{
		res=pthread_create(&(a_thread[lots_of_threads]),&tattr,thread_function,(void*)lots_of_threads);
		if(res!=0)
		{
			perror("Thread create error!");
			exit(1);
		}
	//	sleep(1);
	}
       exit(0);
}

void *thread_function(void *arg)
{
	char ch[20];
	sprintf(ch,"%d",(int)arg);
	printf("%d\n",(int)arg);
	write(sockfd,ch,sizeof(ch));
	pthread_exit(NULL);
}















