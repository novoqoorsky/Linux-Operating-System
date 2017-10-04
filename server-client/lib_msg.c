#include "lib_msg.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>

int msgEnter() {
	/* enter a message queue (create if not found)
	on success, returns queue ID; on failure, shuts down program with exit code 1 */
	int ID = msgget(ftok(".", 1), IPC_CREAT|0666);
	if (ID != -1) {
		printf("Message queue successfully entered\n");
		return ID;
	} else {
		perror("Message queue create error");
		exit(1);
	}
}

void msgSend(int ID, msgbuf* msg) {
	/* send a message to queue
	on failure, shuts down program with exit code 2 */
	if (msgsnd(ID, msg, sizeof(msgbuf), 0) == 0) {
		printf("Message successfully sent\n");
	} else {
		perror("Could not send message");
		exit(2);
	}
}

void msgReceive(int ID, msgbuf* msg, long type) {
	/* receive a message from queue
	on failure, shuts down program with exit code 3 */
	if (msgrcv(ID, msg, sizeof(msgbuf), type, 0) != -1) {
		printf("Message successfully received\n");
	} else {
		perror("Could not receive message");
		exit(3);
	}
}

void msgDelete(int ID) {
	/* delete a message queue 
	on failure, shuts down program with exit code 4 */
	if (msgctl(ID, IPC_RMID, 0) == 0) {
		printf("Message queue deleted\n");
	} else {
		perror("Could not delete message queue");
		exit(4);
	}
}
