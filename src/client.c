// Client side C/C++ program to demonstrate Socket programming

#include <stdio.h>
#include <sys/socket.h>
#include <poll.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080

int main(int argc, char const *argv[])
{
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char *request = "{ \"request\"=\"foo\" }";
	char buffer[1024] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	printf("Connecting..\n");
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}
	printf("Sending..\n");
	send(sock , request , strlen(request) , 0 );

	struct pollfd fd;
	int ret;
	fd.fd = sock;
	fd.events = POLLIN;

	int patience=10;
	while (patience-->0) {
		ret = poll(&fd,1,2000);
		if (ret<=0) {
			printf("Waiting..\n");
		} else {
			printf("Receiving..\n");
			recv(sock,buffer,sizeof(buffer),0);
			printf("%s\n",buffer );
			break;
		}
	}
	//valread = read( sock , buffer, 1024);
	return 0;
}

