/*
 * client.c
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
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

	/* global declarations */

	int sockfd, portno, n, threadRead, threadWrite;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	pthread_t threads[2];

void error(const char *msg)
{
	perror(msg);
	exit(0);
}

void *chatRead(void) {
	int errorCode;
	char buffer[256];
	while(1)
	{
		bzero(buffer,255);
		errorCode = read(sockfd,buffer,255);
		if( errorCode >= 0)
		printf("%s\n",buffer);
	}
	pthread_exit(NULL);
}

void *chatWrite(void) {
	int errorCode;
	char buffer[256];
	while(1) {
		bzero(buffer,255);
		fgets(buffer,255,stdin);
		n = write(sockfd,buffer,strlen(buffer));
		if (n < 0)
			 error("ERROR writing to socket");
	}
}

int main(int argc, char *argv[])
{

	char buffer[256];
	if (argc < 3) {
		fprintf(stderr,"usage %s hostname port\n", argv[0]);
		exit(0);
	}
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	server = gethostbyname(argv[1]);
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
		error("ERROR connecting");
	threadWrite = pthread_create(&threads[1], NULL,chatWrite ,(void *)sockfd);
	chatRead();

	if( threadRead)
		error("ERROR on threading");

	close(sockfd);
	fprintf(stdout,"Client exiting");
	return 0;
}

