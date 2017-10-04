#include "lib_pipe.h"
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    int* descriptors = (int*)malloc(2 * sizeof(int));
    descriptors[0] = openFile("pipe.fifo", O_RDONLY);
    descriptors[1] = openFile("consumer.txt", O_WRONLY);
    char* buffer = (char*)malloc(128 * sizeof(char));
    int n;

    while (n = readFile(descriptors[0], buffer, 128)) {
        writeFile(descriptors[1], buffer, n);
    }

    closeFiles(descriptors);
    free(descriptors); free(buffer);
    return 0;
}
