#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>

#define SIZE_BUFFER 2048
#define MAX_SIZE 2048

int port;
char host[MAX_SIZE], identifier[MAX_SIZE];

void printUrl() {
	printf("\nHost : %s",host);
	printf("\nPort : %d",port);
	printf("\nIdentifier : %s",identifier);
}


int main() {
	int sockfd,nsd,i,rsd,rc,bi, errorCode;
	char content[SIZE_BUFFER]="\0", buf[SIZE_BUFFER],x[SIZE_BUFFER];
	char BUFFER[SIZE_BUFFER];
	char request[MAX_SIZE]="\0";

	struct sockaddr_in serv_addr, cl_addr, rserv_addr;

	sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	if(sockfd < 0) {
		perror("socket");
		exit(1);
	}

	struct hostent *h;
	bzero((char*)&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(port);
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);

	bi=bind(sockfd,((struct sockaddr *)&serv_addr),sizeof(serv_addr));
	if(bi==-1){
		perror("bind");
		exit(1);
	}
	i=sizeof(cl_addr);
	socklen_t t;
	t=sizeof(struct sockaddr_in);

	// gets(content);
	//strcpy(content,"http://athena.nitc.ac.in:80/~b090421cs/con.php");

	strcpy(content,"http://localhost:80/hello.html");
	//parseUrl(content);
	strcpy(host,"localhost");
	port = 80;
	strcpy(identifier,"/hello.html");
	printUrl();
	h=gethostbyname(host);
	if(h==NULL) {
		printf("Unknown host :%s",host);
		goto exit;
	}

	rserv_addr.sin_family=h->h_addrtype;
	memcpy((char *) &rserv_addr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
	rserv_addr.sin_port=htons(port);
	rsd = socket(AF_INET, SOCK_STREAM, 0);

	if(rsd<0) {
		perror("cannot open socket ");
		goto exit;
	}

	printf("Binding port number...  \n");
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(0);

	rc = bind(rsd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	if(rc<0) {
		printf(" cannot bind port TCP %u\n",port);//(LOCAL_SERVER_PORT);
		perror("error ");
		exit(1);
	}

	printf("Connect to server...\n");
	rc = connect(rsd, (struct sockaddr *) &rserv_addr, sizeof(rserv_addr));
	if(rc<0) {
		perror("cannot connect ");
		goto exit;
	}

	strcpy(request,"GET ");
	strcat(request,identifier);
	strcat(request," HTTP/1.1\r\nHost: ");
	strcat(request,host);
	strcat(request,"\r\nUser-Agent: Mozilla/5.0 (X11; Linux i686; rv:6.0) Gecko/20100101 Firefox/6.0\r\nAccept: text/plain\r\nAccept-Language: en-us,en;q=0.5\r\nAccept-Encoding: none\r\nAccept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\r\nConnection: keep-alive\r\nCache-Control: no-cache\r\n\r\n");

	printf("Sending the request to the remote server :\n %s",request);
	if(write(rsd,request,strlen(request))==-1) {
	perror("can't send the request");
	}
	bzero(BUFFER,SIZE_BUFFER);
	printf("\n\nSending the desired response.....\n\n");

	do {
		bzero(BUFFER,SIZE_BUFFER);	//  init line 
		rc = read(rsd, BUFFER, SIZE_BUFFER);
		if( rc > 0) { 
			printf("%s",BUFFER);
		}
	} while(rc>0);

	printf("\nResponse is sent");

	exit: close(rsd);

	bzero(content,sizeof content);
	bzero(BUFFER,SIZE_BUFFER); 
	close(nsd);

	return(0);
}
