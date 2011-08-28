#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_CONN 10
void *function(void *threadid)
{
	long tid;
	tid = (long)threadid;
	printf("thread #%ld!\n", tid);
	pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
	pthread_t threads[MAX_CONN];
	int threadErrorCode;
	long t;
	for(t=0; t<MAX_CONN; t++){
		printf("In main: creating thread %ld\n", t);
		threadErrorCode	=	pthread_create(&threads[t], NULL, function, (void *)t);
		if (threadErrorCode){
			printf("ERROR; return code from pthread_create() is %d\n", threadErrorCode);
			exit(-1);
		}
	}

	/* Last thing that main() should do */
	pthread_exit(NULL);
}

