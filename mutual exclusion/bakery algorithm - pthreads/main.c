#define _REENTRANT

#define NUM_THREADS 4
#define NUM_CRIT_ENTRIES 3

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* data shared by threads, initialized with 0s, couse global */
int entering[NUM_THREADS];
int number[NUM_THREADS];
int globalCount;

void* threadFunction(void*);
void lock(int);
void unlock(int);
int findMax();
int checkPriority(int, int);
void criticalSection(int);

/* MAIN */

int main()
{
    system("clear");
    pthread_t threads[NUM_THREADS];
    int i;
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, threadFunction, (void*)(intptr_t)i);
    }
    for (i = 0; i < NUM_THREADS; i++) {     /* attach to the main thread so that it waits for each created thread to finish */
        pthread_join(threads[i], NULL);
    }
    system("clear");
    printf("Global count value after finishing threads: %d\n", globalCount);     /* should be NUM_THREADS * NUM_CRIT_ENTRIES */
    return 0;
}

/* END OF MAIN */

void* threadFunction(void* i) {
    /* modify the shared data NUM_CRIT_ENTRIES times */
    int id = (intptr_t)i, j;
    for (j = 0; j < NUM_CRIT_ENTRIES; j++) {
        printf("\033[%d;1HThread no. %d waiting for entrance\n", id + 3, id);
        lock(id);
        criticalSection(id);
        unlock(id);
    }
}

void lock(int i) {
    /* breaking the loops means the thread is allowed to enter critical section */
    entering[i] = 1;
    number[i] = 1 + findMax();
    entering[i] = 0;
    int j;
    for (j = 0; j < NUM_THREADS; j++) {
        while(entering[j]) {}
        while(checkPriority(j, i)) {}
    }
}

void unlock(int i) {
    /* set the thread priority to lowest */
    number[i] = 0;
}

int findMax() {
    /* iterate over the global array and find its max value */
    int result = number[0];
    int i;
    for (i = 1; i < NUM_THREADS; i++) {
        if (number[i] > result) {
            result = number[i];
        }
    }
    return result;
}

int checkPriority(int a, int b) {
    /* return true if threadA's number differs from 0 and it is less than threadB's number
    if the numbers are equal, the ID decides */
    return ( number[a] &&  ( (number[a] < number[b]) || ( (number[a] == number[b]) && (a < b) ) ));
}

void criticalSection(int id) {
    printf("\033[%d;1H                                  \n", id + 3);     /* just some clean up */
    printf("\033[%d;50HThread no. %d critical section\n", id + 3, id);
    globalCount++;
    sleep(rand() % 4);      /* the random sleep simulates work-time on shared data */
    printf("\033[%d;50H                              \n", id + 3);   /* another clean up */
}
