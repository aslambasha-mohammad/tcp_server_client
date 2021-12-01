#include <stdio.h>
#include <string.h>		//strcpy, strlen
#include <unistd.h>		//close
#include <stdlib.h>		//atoi
#include <sys/socket.h>		//socket
#include <sys/types.h>
#include <netinet/in.h>		//sockaddr_in

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Usage: %s <port-no>\n", argv[0]);
		return -1;
	}

	int client_sockfd = 0;
	char msg_buff[256] = {'\0'};
	unsigned int msg_len = 0, recv_len = 0, send_len = 0;
	struct sockaddr_in server_addr;

	client_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(client_sockfd == -1)
	{
		printf("Failed to create client tcp socket\n");
		return -1;
	}

	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(atoi(argv[1]));

	if(connect(client_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("Failed to connect to the server\n");
		close(client_sockfd);
		return -1;
	}

	strcpy(msg_buff, "Hello server");
	msg_len = strlen(msg_buff);
	send_len = send(client_sockfd, msg_buff, msg_len, 0);
	if(send_len > 0)
		printf("Sent message successfully to server\n");

	memset(msg_buff, '\0', sizeof(msg_buff));
	recv_len = recv(client_sockfd, msg_buff, sizeof(msg_buff), 0);
	if(recv_len > 0)
		printf("Received '%s' message from server\n", msg_buff);
	else
		printf("Failed to receive the message from server\n");

	close(client_sockfd);
	return 0;
}
