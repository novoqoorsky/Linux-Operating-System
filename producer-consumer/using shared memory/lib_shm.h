#ifndef LIB_SHM_H
#define LIB_SHM_H

int shmEnter(int);
void shmDelete(int);
char* shmAppend(int);
void shmDetach(char*);

#endif
