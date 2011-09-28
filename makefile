all:
	gcc server.c -pthread -o server
	gcc client.c -pthread -o client

