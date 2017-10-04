#include "lib_shm.h"
#include "lib_sem.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 128
#define SHM_SIZE 256

int main()
{
	int sem = semCreate();
	int shm = shmEnter(SHM_SIZE);
	char* pointer = shmAppend(shm);
	char* pointerCpy = pointer;
	
	FILE* in = fopen("producer.txt", "r");
	FILE* out = fopen("consumer.txt", "w");

	switch(fork()) {
	case -1:
		perror("Fork error");
		exit(1);
	case 0:		/* child - consumer process */
		while (1) {
			semPasseren(sem);
			char buffer[BUF_SIZE];
			strcpy(buffer, pointer);
			fputs(buffer, out);
			semVrijmaken(sem);
		}
		break;
	default:	/* parent - producer process */
		while (1) {
			semPasseren(sem);
			char buffer[BUF_SIZE];
			if (fgets(buffer, BUF_SIZE, in) == NULL) {
				break;
			}
			printf("Material transfered: %s\n", buffer);
			strcpy(pointer, buffer);
			pointer += BUF_SIZE;
			if (pointer >= (char*)SHM_SIZE) {
				pointer = pointerCpy;
			}
			semVrijmaken(sem);
		}
		break;
	}
	fclose(in); fclose(out);
	shmDetach(pointer);
	shmDelete(shm);
	/* that makes the consumer process shut down due to error while trying to access the semaphore */
	semDelete(sem);		
	return 0;
}
