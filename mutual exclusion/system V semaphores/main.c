#include "lib_sem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void criticalSection() {
	printf("Critical section\n");
}

int main()
{
	int sem = semCreate();
	int shared = 0;
	int i;
	switch(fork()) {
	case -1:
		perror("Fork error");
		exit(1);
	case 0:		/* child process */
		printf("--- Child process staring ---\n");	
		semPasseren(sem);
		semStats(sem);
		criticalSection();
		semVrijmaken(sem);
		printf("--- Child process ending ---\n");
		break;
	default:	/* parent process */
		printf("--- Parent process staring ---\n");	
		semPasseren(sem);
		sleep(1);
		semStats(sem);
		criticalSection();
		semVrijmaken(sem);
		printf("--- Parent process ending ---\n");
		break;
	}
	wait();		/* wait for child's process to finish */
	semDelete(sem);
	return 0;
}
