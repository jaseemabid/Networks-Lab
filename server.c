#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define MAX_CONN 10

/*

		In order to be notified of incoming connections on a  socket,  you  can
		use  select(2)  or  poll(2).  A readable event will be delivered when a
		new connection is attempted and you may then call  accept()  to  get  a
		socket  for  that connection.  Alternatively, you can set the socket to
		deliver SIGIO when activity occurs  on  a  socket;  see  socket(7)  for
		details.


*/

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{

	/* Declarations */

	int sockfd[MAX_CONN], newsockfd[MAX_CONN], portno, n, connId = 0;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;

	if (argc < 2) {
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}

	/* Have to do this per client */
	void newConn( aConnId ) {
		sockfd[connId] = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd[connId] < 0)
			error("ERROR opening socket");
		bzero((char *) &serv_addr, sizeof(serv_addr));
		portno = atoi(argv[1]);
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(portno);
		if (bind(sockfd[connId], (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
			error("ERROR on binding");
		listen(sockfd[connId],5);
		clilen = sizeof(cli_addr);
		newsockfd[connId] = accept(sockfd[connId], (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd[connId] < 0)
			error("ERROR on accept");
		/* Accepts multiple messages from 1 socket */
		while(1) {
			bzero(buffer,256);
			n = read(newsockfd[connId],buffer,255);
			if (n < 0) error("ERROR reading from socket");
			printf("Here is the message: %s\n",buffer);
			n = write(newsockfd[connId],"I got your message",18);
			if (n < 0) error("ERROR writing to socket");
		}
	}
	
	newConn(0);
	
	/* Dead code ! will never work */
	close(newsockfd[0]); /* Should be closing all connections */
	close(sockfd[0]);
	return 0;
}

