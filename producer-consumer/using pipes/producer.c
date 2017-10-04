#include "lib_pipe.h"
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    createPipe("pipe.fifo");
    int* descriptors = (int*)malloc(2 * sizeof(int));
    descriptors[0] = openFile("pipe.fifo", O_WRONLY);
    descriptors[1] = openFile("producer.txt", O_RDONLY);
    char* buffer = (char*)malloc(128 * sizeof(char));
    int n;

    while (n = readFile(descriptors[1], buffer, 128)) {
        writeFile(descriptors[0], buffer, n);
    }

    closeFiles(descriptors);
    deletePipe("pipe.fifo");
    free(descriptors); free(buffer);
    return 0;
}

