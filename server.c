#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc , char *argv[])

{
	if(!strcmp(argv[1],"tcp")){
		printf("[Server] tcp\n");
		//socket set up
		char buffer[256] = {};
		int sockfd = 0, forClientSockfd = 0;
		sockfd = socket(AF_INET , SOCK_STREAM , 0);

		if (sockfd == -1){
			printf("ERROR: Fail to create a socket.\n");
		}

		//socket connect
		struct sockaddr_in serverInfo, clientInfo;
		int addrlen = sizeof(clientInfo);
		bzero(&serverInfo,sizeof(serverInfo));

		serverInfo.sin_family = AF_INET;
		serverInfo.sin_addr.s_addr = INADDR_ANY;
		serverInfo.sin_port = htons(argv[4]);
		printf("[Server] IP: %s\n",  argv[3]);
		printf("[Server] Port: %s\n",  argv[4]);
		bind(sockfd,(struct sockaddr *)&serverInfo,sizeof(serverInfo));
		listen(sockfd,5);

		//Accept client
		printf("[Server] Waiting for Connection...\n");
		forClientSockfd = accept(sockfd,(struct sockaddr*) &clientInfo, &addrlen);
		
		printf("[Server] Server connected.\n");
		
		if(forClientSockfd == -1){
			printf("ERROR: Fail to accept a request.\n");
		}
		
		//Sending file
		else{
			//File open
			char *filename = argv[5];
			FILE *fp = fopen(filename, "rb");
			if(fp == NULL){
				printf("ERROR: File opening error.\n");
			}

			//Send process
			//1byte
			int nCount;
			if(!strcmp(argv[2],"send")){
				printf("[Server] Send\n");
				while((nCount = fread(buffer, 1, sizeof(buffer), fp)) > 0){
					send(forClientSockfd, buffer, nCount, 0);
				}
				printf("[Server] Done.\n");
				recv(forClientSockfd, buffer, nCount, 0);

				//closing 
				fclose(fp);
				close(sockfd);
				close(forClientSockfd);
			}
			else if(!strcmp(argv[2],"recv")){
			}
		}
	}
	else if(!strcmp(argv[1],"udp")){
	}
	return 0;
}
