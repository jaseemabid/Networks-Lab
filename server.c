/*
 * server.c
 * This file is part of unix server - client chat system
 *
 * Copyright (C) 2011 - Jaseem Abid <jaseemabid@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>


#define MAX_CONN 10

	/* Declarations */

struct connection {
	int sock;
	int index;
};

int sockfd, newsockfd, portno, errorCode, loopIndex = 0;
socklen_t clilen;
struct sockaddr_in serv_addr, cli_addr;
struct connection user[MAX_CONN];

	/* The thread part of it !*/

pthread_t threads[MAX_CONN];
int threadErrorCode;
long t;

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

void *newClient(void *aUser ) {

	struct connection *temp;
	temp = (struct connection *)aUser;
	int sockfd, self, peer, flag = 1;
	char buffer[256], msg[256];
	sockfd = temp->sock ;
	self = temp->index;

	while(1) {
		bzero(buffer,256);
		bzero(msg,256);
		if (flag) {
			strcpy(msg, "Welcome to chat server\nChat format : @{uid} Message. @* Group message ");
			flag =0;
		}
		/* Accept new message */
		errorCode = write(user[self].sock,msg,strlen(msg));
		errorCode = read(user[self].sock, buffer, 256);
		char *ch = &buffer[1]; // @<uid>
		if( *ch == '*') {
			// Code to send a group message
			int n = 0;
			printf("\nloopIndex : %d\n",loopIndex);
			for ( n = 0; n < loopIndex; n++) {
				if (n != self ) {
					errorCode = write(user[n].sock,buffer,strlen(buffer));
				}
				if (errorCode < 0) error("ERROR writing to socket");
			}
		}
		else { // Normal peer to peer chat
			peer = atoi(ch); // Cant convert int to string. So not printing peer id to client.
			errorCode = write(user[peer].sock,buffer,strlen(buffer));
			if (errorCode < 0) error("ERROR writing to socket");
		}
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
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0)
			error("ERROR on accept");
		
		user[loopIndex].sock = newsockfd;
		user[loopIndex].index = loopIndex;
		fprintf(stdout,"\n%d Added\n", loopIndex);
		threadErrorCode	= pthread_create(&threads[t], NULL, newClient , (void *) &user[loopIndex] );
		if (threadErrorCode)
			printf("ERROR; return code from pthread_create() is %d\n", threadErrorCode);
	loopIndex = loopIndex+1;
	}

	/* Dead code ! will never work */
	close(newsockfd); /* Should be closing all connections if closing */
	close(sockfd);
	return 0;
}

/* End of main */
