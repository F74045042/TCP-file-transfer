#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc , char *argv[])

{
    if(!strcmp(argv[0],"tcp")){
        if(!strcmp(argv[1],"send")){
            //socket set up
            char buffer[256] = {};
            int sockfd = 0,forClientSockfd = 0;
            sockfd = socket(AF_INET , SOCK_STREAM , 0);

            if (sockfd == -1){
                printf("ERROR: Fail to create a socket.\n");
            }

            //socket connect
            struct sockaddr_in serverInfo,clientInfo;
            int addrlen = sizeof(clientInfo);
            bzero(&serverInfo,sizeof(serverInfo));

            serverInfo.sin_family = PF_INET;
            serverInfo.sin_addr.s_addr = inet_addr(argv[2]);
            serverInfo.sin_port = htons(argv[3]);
            bind(sockfd,(struct sockaddr *)&serverInfo,sizeof(serverInfo));
            listen(sockfd,5);

            //Accept client
            forClientSockfd = accept(sockfd,(struct sockaddr*) &clientInfo, &addrlen);
            if(forClientSockfd == -1){
                printf("ERROR: Fail to accept a request.\n");
            }
            //Sending file
            else{
                //File open
                char *filename = argv[4];
                File *fp = fopen(filename, "rb");
                if(fp == NULL){
                    printf("ERROR: File opening error.\n");
                }

                //Send process
                int nCount;
                while((nConut = fread(buffer, 1, sizeof(buffer))) > 0){
                    send(clientInfo, buffer, nCount, 0);
                }
                printf("[Server] Done.\n");
                shutdown(clientInfo, SD_SEND);
                read(clientInfo, buffer, nCount, 0);

                //closing 
                fclose(fp);
                close(serverInfo);
                close(clientInfo);
            }
        }
        else if(!strcmp(argv[1],"recv")){
        }
    }
    else if(!strcmp(argv[0],"udp")){
    }
    return 0;
}
