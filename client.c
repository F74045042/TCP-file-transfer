#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]){
	//socket setup
	int sockfd = 0;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd == -1){
		printf("[Client] socket setup Error!\n");
	}

	//socket connection
	struct sockaddr_in info;
	bzero(&info, sizeof(info));
	info.sin_family = AF_INET;

	info.sin_addr.s_addr = inet_addr(argv[3]);
	info.sin_port = htons(argv[4]);
	printf("[Client] IP: %s\n",argv[3]);
	printf("[Client] Port: %s\n",argv[4]);
	
	int err = connect(sockfd, (struct sockaddr *)&info, sizeof(info));
	if(err == -1){
		printf("[Client] Connection error!\n");
	}
	else{
		printf("[Client] Server connected.\n");
		//File transfer
		FILE *fp = fopen(argv[5], "wb");
		char buffer[256] = {};
		int nCount;
		if(!strcmp("recv",argv[2]))
		{
			printf("[Client] Recv Start.\n");
			while((nCount = recv(sockfd, buffer, sizeof(buffer), 0)) > 0){
				fwrite(buffer, sizeof(buffer), nCount, fp);
			}
		}
		fclose(fp);
	}
	close(sockfd);
	return 0;
}
