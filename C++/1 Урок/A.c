#include <lzma.h>
#include <stdio.h>
#include <malloc.h>

#define BUFFERSIZE 64

void parseAllString(char **strs) {
    char *oneLine = NULL;
    while (feof(stdin)) {
        oneLine = malloc(sizeof(char) * BUFFERSIZE);
    }
};

