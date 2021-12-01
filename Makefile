CFLAGS = -Wall -g

CC = gcc
RM = rm -rf

SERVER_BIN = tcp_server
CLIENT_BIN = tcp_client

SERVER_SRC = server.c
CLIENT_SRC = client.c

SERVER_OBJS = $(SERVER_SRC:.c=.o)
CLIENT_OBJS = $(CLIENT_SRC:.c=.o)

all:
	@$(MAKE) -s build_server;
	@$(MAKE) -s build_client;
	@echo "\033[1;32m" "[COMPILATION DONE]" "\033[m"

build_server: $(SERVER_OBJS)
	@$(CC) $(CFLAGS) -o $(SERVER_BIN) $(SERVER_OBJS)

build_client: $(CLIENT_OBJS)
	@$(CC) $(CFLAGS) -o $(CLIENT_BIN) $(CLIENT_OBJS)

SERVER_OBJS:
	@$(CC) $(CFLAGS) -c $< -o $@

CLIENT_OBJS:
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(SERVER_BIN) $(CLIENT_BIN) *.o
