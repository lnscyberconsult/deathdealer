#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int sock, client_socket;
    char buffer[1024];
    char response[20000];

    struct sockadrr_in serv_address, client_address;
    int optval = 1;
    socklen_t client_length;
    sock = socket(AF_INET,SOCK_STREAM,0);
    if(setsockopt(sock,SOL_SOCKET,SOL_REUSEADDR,&optval,sizeof(optval))<0){
        printf("error seting tcp sokcet options #n");
        return 1;
    }
}