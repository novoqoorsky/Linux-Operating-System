#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

struct sembuf operation = {0, 0, 0};

int semCreate() {
	/* create a semaphore
	on success, return its ID; on failure, shuts down program with exit code 1 */
	int ID = semget(ftok(".", 1), 1, IPC_CREAT|0666);
	if (ID != -1) {
		printf("Semaphore successfully created\n");
		semctl(ID, 0, SETVAL, 1);
		return ID;
	} else {
		perror("Semaphore create error");
		exit(1);
	}
}

void semPasseren(int ID) {
	/* bring semaphore down
	on failure, shuts down program with exit code 2 */
	operation.sem_op = -1;
	if (semop(ID, &operation, 1) == 0) {
		printf("Semaphore is going down\n");
	} else {
		perror("Could not bring semaphore down");
		exit(2);
	}
}

void semVrijmaken(int ID) {
	/* bring semaphore up
	on failure, shuts down program with exit code 3 */
	operation.sem_op = 1;
	if (semop(ID, &operation, 1) == 0) {
		printf("Semaphore is going up\n");
	} else {
		perror("Could not bring semaphore up");
		exit(3);
	}
}

void semStats(int ID) {
	/* check semaphore latest modifier and number of processes waiting for it to bring up */
	printf("PID of the process that performed the last operation on semaphore: %d\n", semctl(ID, 0, GETPID, NULL));
	printf("Processes waiting for semaphore to bring up: %d\n", semctl(ID, 0, GETNCNT, NULL));
}

void semDelete(int ID) {
	/* delete semaphore */
	semctl(ID, 0, IPC_RMID, NULL);
}


