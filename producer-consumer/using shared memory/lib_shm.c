#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int shmEnter(int size) {
	/* create a shared memory segment of given size (enter if already created)
	on failure, shuts down program with exit code 1 */
	int ID = shmget(ftok(".", 1), size, IPC_CREAT|0666);
	if (ID != -1) {
		printf("Shared memory successfully entered\n");
		return ID;
	} else {
		perror("Shared memory create error");
		exit(1);
	}
}

void shmDelete(int ID) {
	/* delete segment of shared memory */
	shmctl(ID, IPC_RMID, 0);
}

char* shmAppend(int ID) {
	/* attach segment of shared memory to the address space of the calling process
	on failure, shuts down program with exit code 2 */
	char* p = (char*)shmat(ID, NULL, 0);
	if (p != (char*)-1) {
		printf("Shared memory successfully attached\n");
		return p;
	} else {
		perror("Shared memory append error");
		exit(2);
	}
}

void shmDetach(char* p) {
	/* detach the shared memory segment */
	shmdt(p);
}
