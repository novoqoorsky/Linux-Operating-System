#ifndef LIB_PIPE_H
#define LIB_PIPE_H

void createPipe(char*);
void deletePipe(char*);
int openFile(char*, int);
int readFile(int, char*, int);
int writeFile(int, char*, int);
void closeFiles(int*);

#endif // LIB_PIPE_H
