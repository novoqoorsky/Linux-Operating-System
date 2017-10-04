#include "lib_msg.h"
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>

int main()
{
	int msgQueue = msgEnter();	/* server process creates a queue */
	while (1) {
		msgbuf server;
		msgReceive(msgQueue, &server, 0);
		printf("Received message: %s\n", server.mtext);
		int i = 0;
		while (server.mtext[i] != '\0') {	/* server's job is to transform the message into uppercase */
			server.mtext[i] = toupper(server.mtext[i]);
			i++;
		}
		msgSend(msgQueue, &server);
	}
	return 0;
}
