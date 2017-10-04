#include "lib_msg.h"
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <string.h>

int main()
{
	int msgQueue = msgEnter();	/* client process enters the queue */
	msgbuf client;
	strcpy(client.mtext, "server-client");
	msgSend(msgQueue, &client);
	msgReceive(msgQueue, &client, 1);	
	printf("Received message: %s\n", client.mtext);
	return 0;
}
