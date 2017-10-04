#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void createPipe(char* name) {
    /* create a FIFO pipe
    on failure, prints error message and shuts down program with exit code 1 */
    if (mkfifo(name, 0644) == 0) {
        printf("FIFO pipe successfully created.\n");
    } else {
        perror("FIFO pipe create error");
        exit(1);
    }
}

void deletePipe(char* name) {
    /* delete a FIFO pipe
    on failure, prints error message */
    if (unlink(name) == 0) {
        printf("FIFO pipe deleted.\n");
    } else {
        perror("Pipe delete error");
    }
}

int openFile(char* name, int flag) {
    /* open file and return its descriptor
    create the file if cannot be found
    on failure, prints error message and shuts down program with exit code 2 */
    int des = open(name, flag | O_CREAT);
    if (des == - 1) {
        perror("File open error");
        exit(2);
    }
    printf("File %s successfully opened.\n", name);
    return des;
}

int readFile(int from, char* to, int bytes) {
    /* read up to a given number of bytes from file and assign it to a buffer
    on failure, prints error message and shuts down program with exit code 3 */
    int bytesRead = read(from, to, bytes);
    if (bytesRead == -1) {
        perror("File read error");
        exit(3);
    }
    printf ("%d bytes have been read.\n", bytesRead);
    return bytesRead;
}

int writeFile(int to, char* from, int bytes) {
    /* write up to a given number of bytes from buffer to file
    on failure, prints error message and shuts down program with exit code 4 */
    int bytesWritten = write(to, from, bytes);
    if (bytesWritten == -1) {
        perror("File write error");
        exit(4);
    }
    printf ("%d bytes have been written.\n", bytesWritten);
    return bytesWritten;
}

void closeFiles(int* desArray) {
    /* iterate over an array containing descriptors and close each
    on failure, prints error massage with the index of descriptor that could not been closed */
    int size = sizeof(desArray) / sizeof(desArray[0]);
    int i;
    for (i = 0; i < size; i++) {
        if (close(desArray[i]) == -1) {
            printf("On index %d ", i);
            perror("close error");
        }
    }
}
