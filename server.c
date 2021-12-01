#include <stdio.h>
#include <string.h>		//str functions
#include <unistd.h>		//close
#include <stdlib.h>		//atoi
#include <sys/socket.h>		//socket
#include <sys/types.h>
#include <netinet/in.h>		//sockaddr_in

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage: %s <port-no>\n", argv[0]);
		return -1;
	}

	int server_sockfd = 0, client_sockfd = 0;
	char msg_buff[256] = {'\0'};
	unsigned int msg_len = 0, recv_len = 0, send_len = 0, client_len = 0;
	struct sockaddr_in server_addr, client_addr;

	// Creating a unnamed socket with sock stream type
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_sockfd == -1)
	{
		printf("Failed to create the TCP socket\n");
		return -1;
	}

	//binding the socket on particular port number
	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(atoi(argv[1]));

	if(bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("Unable to bind the socket\n");
		close(server_sockfd);
		return -1;
	}

	//Listen on the socket for client connections upto max 5
	listen(server_sockfd, 5);
	client_len = sizeof(client_addr);
	while(1)
	{
		printf("Waiting for the client connection\n");
		client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &client_len);
		if(client_sockfd > 0)
		{
			memset(msg_buff, '\0', sizeof(msg_buff));
			recv_len = recv(client_sockfd, msg_buff, sizeof(msg_buff), 0);
			if(recv_len > 0)
			{
				printf("Received '%s' message from client\n", msg_buff);
			}
			memset(msg_buff, '\0', sizeof(msg_buff));
			strcpy(msg_buff, "Hello client");
			msg_len = strlen(msg_buff);
			send_len = send(client_sockfd, msg_buff, msg_len, 0);
			if(send_len > 0)
			{
				printf("Sent message successfully to client\n");
			}
			close(client_sockfd);
		}
		else
		{
			printf("Failed to accept the client connection\n");
		}
	}
	close(server_sockfd);
	return 0;
}
