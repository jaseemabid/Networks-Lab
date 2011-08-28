#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define MAX_CONN 10

	/* Declarations */

struct connection
{
	int sockfd;
	int index;
}

int sockfd, newsockfd, portno, errorCode, connId = 0, loopIndex = 0;
socklen_t clilen;
struct sockaddr_in serv_addr, cli_addr;
struct connection conn[MAX_CONN];

	/* The thread part of it !*/

pthread_t threads[MAX_CONN];
int threadErrorCode;
long t;

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

void *newClient(void *aSocket) {

	int sockfd;
	char buffer[256];
	sockfd =(int)aSocket;

	while(1) {
		bzero(buffer,256);
		errorCode = read(sockfd,buffer,255);
		if (errorCode < 0) error("ERROR reading from socket");
			printf("Here is the message: %s\n",buffer);
		errorCode = write(sockfd,"I got your message",18);
		if (errorCode < 0) error("ERROR writing to socket");
	}
}

int main(int argc, char *argv[])
{

	if (argc < 2) {
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}

	/* Server configuration */

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
		error("ERROR on binding");
	listen(sockfd,5);

	/* Have to do this per client */

	while (loopIndex < MAX_CONN) {
		clilen = sizeof(cli_addr);
		printf("\nthread loop : %d\n ", loopIndex);
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0)
			error("ERROR on accept");
		threadErrorCode	= pthread_create(&threads[t], NULL, newClient , (void *)newsockfd );
		if (threadErrorCode){
			printf("ERROR; return code from pthread_create() is %d\n", threadErrorCode);
			exit(-1);
		}
	loopIndex = loopIndex+1;
	}

	/* Dead code ! will never work */
	close(newsockfd); /* Should be closing all connections if closing */
	close(sockfd);
	return 0;
}

/* End of main */
