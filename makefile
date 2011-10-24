all:
	gcc server.c -pthread -o server
	gcc client.c -pthread -o client
clean:
	rm proxi
	rm browser
	rm client
	rm server
	rm a.out
