#ifndef LIB_SEM_H
#define LIB_SEM_H

int semCreate();
void semPasseren(int);
void semVrijmaken(int);
void semStats(int);
void semDelete(int);

#endif
