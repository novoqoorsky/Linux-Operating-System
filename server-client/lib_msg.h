#ifndef LIB_MSG_H
#define LIB_MSG_H

typedef struct msgbuf {
	long mtype;
	char mtext[20];
} msgbuf;

int msgEnter();
void msgSend(int, msgbuf*);
void msgReceive(int, msgbuf*, long);
void msgDelete(int);

#endif
